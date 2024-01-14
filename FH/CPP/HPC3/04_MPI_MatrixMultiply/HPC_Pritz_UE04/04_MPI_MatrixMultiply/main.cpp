#include<mpi.h>
#include<cassert>
#include<iostream>
#include<format>
#include<exception>
#include<vector>
#include<concepts>
#include<functional>
#include<string>
#include<fstream>

namespace hpc::mpi {
	int mpi_root{ 0 };

	// Own implementation of log2 = bitshift right until number is zero
	int ceil_log_2(int dec) {
		if (dec < 0)
			dec *= -1;

		dec -= 1;

		int exponent = 0;
		while (dec) {
			dec = (dec >> 1);
			exponent++;
		}

		return exponent;
	}
	// Own implementation of power 2 = bitshift 1 by exponent
	int power_2(int exponent) {
		return 1 << exponent;
	}

	// MPI exception resolution
	struct mpi_exception : std::runtime_error {
		mpi_exception(std::string const& error) : std::runtime_error{ error } {

		}
	};
	void check(int const error) {
		if (error != MPI_SUCCESS) {
			char buffer[MPI_MAX_ERROR_STRING];
			int length{ -1 };

			MPI_Error_string(error, buffer, &length);

			throw mpi_exception(buffer);
		}
	}

	// MPI helper functions
	int get_rank() {
		int rank{ -1 };
		check(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
		return rank;
	}
	int get_size() {
		int size{ -1 };
		check(MPI_Comm_size(MPI_COMM_WORLD, &size));
		return size;
	}
	std::string get_host() {
		char buffer[MPI_MAX_PROCESSOR_NAME]{};
		int resultlen{ -1 };
		check(MPI_Get_processor_name(buffer, &resultlen));
		return buffer;
	}

	// For broadcast and reduce: check if node has to send or receive in a given step
	int must_send(int step, int dest) {
		// "normalize" rank, by working as if the root was still 0
		int normalized_rank = get_rank() - dest < 0 ? get_size() + (get_rank() - dest) : get_rank() - dest;

		if (normalized_rank < power_2(step) && normalized_rank + power_2(step) < get_size())
			return (normalized_rank + dest + power_2(step)) % get_size();
		else
			return -1;
	}
	int must_receive(int step, int dest) {

		int normalized_rank = get_rank() - dest < 0 ? get_size() + (get_rank() - dest) : get_rank() - dest;
		if (normalized_rank >= power_2(step) && normalized_rank < power_2(step+1) && normalized_rank - power_2(step) >= 0) {
			int target = (normalized_rank + dest - power_2(step));
			return target >= 0 ? target % get_size() : target + get_size();
		}
		else {
			return -1;
		}
	}

	// Wrappers using overload to handle different datatypes
	void mpi_recv_wrapper(int* const message, const int argc = 1) {
		MPI_Status status{};

		check(MPI_Recv(message, argc, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status));

		//std::cout << std::format("{}/{} received {}", get_host(), get_rank(), *message) << std::endl;
	}
	void mpi_send_wrapper(const int dest, int* const message, const int argc = 1) {
		check(MPI_Send(message, argc, MPI_INT, dest, 0, MPI_COMM_WORLD));

		//std::cout << std::format("{}/{} sent {} to {}", get_host(), get_rank(), *message, dest) << std::endl;
	}
	void mpi_recv_wrapper(double* const message, const int argc = 1) {
		MPI_Status status{};

		check(MPI_Recv(message, argc, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status));
		//std::cout << std::format("{}/{} received {}", get_host(), get_rank(), *message) << std::endl;
	}
	void mpi_send_wrapper(const int dest, double* const message, const int argc = 1) {
		check(MPI_Send(message, argc, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD));
		//std::cout << std::format("{}/{} sent {} to {}", get_host(), get_rank(), *message, dest) << std::endl;
	}

	// value by reference to serve as input for boss, and output for minions
	template <typename T> void broadcast(int const root, T& value, int const argc = 1) {
		for (int step{ 0 }; step < ceil_log_2(get_size()); step++) {
			int buddy{ -1 };
			if ((buddy = must_send(step, root)) > -1) {
				mpi_send_wrapper(buddy, &value);
				//std::cout << std::format("Broadcast - Step {}: #{} sent value \"{}\" to #{}!", step, get_rank(), value, buddy) << std::endl;
			}
			else if ((buddy = must_receive(step, root)) > -1) {
				mpi_recv_wrapper(&value);
				//std::cout << std::format("Broadcast - Step {}: #{} received value \"{}\" from #{}!", step, get_rank(), value, buddy) << std::endl;
			}
		}
	}

	// double ampersand: temporary references (e.g., putting the ifstream constructor right inside the method call)
	auto read_matrices(std::istream && in) {
		std::tuple<int, int, int, std::vector<int>, std::vector<int>> data{};
		auto& [m, n, o, A, B] {data};
		in >> m >> n >> o;


		A.resize(m * n);
		for (auto & el : A) 
			in >> el;
		

		B.resize(n * o);
		for (auto& el : B)
			in >> el;

		return data;
	}

	std::string vecToStr(std::vector<int>& vec, int rowLength) {
		std::string tmp = "";

		int i = 0;
		while (i < vec.size()) {
			if (i > 0 && i % rowLength == 0)
				tmp += "\n";
			tmp += std::to_string(vec[i]) + "\t";
			i++;
		}

		return tmp;
	}

	double multiply_serial() {
		// Debugging: let each node print their contribution
		//std::cout << std::format("Node {} has:\t[{}, {}] with {} splines", get_rank(), a, b, n) << std::endl;

		double sum = 0;//integrator(a, b, n, integratee);

		return sum;
	}

	void multiply_parallel(int argc, char* argv[]) {
		// Quick output when node starts the task
		std::cout << std::format("[{}] Rank {} of {}", hpc::mpi::get_host(), hpc::mpi::get_rank(), hpc::mpi::get_size()) << std::endl;

		int m, n, o{ 0 };
		std::vector<int> A, B;

		if (get_rank() == mpi_root) {
			std::tie(m, n, o, A, B) = read_matrices(std::ifstream{ "C:/Data/git/Development/FH/CPP/HPC3/04_MPI_MatrixMultiply/04_MPI_MatrixMultiply/data/input.txt" });
		}

		std::vector<int> A_local;
		std::vector<int> B_local;

		// Broadcast all dimensions
		broadcast(mpi_root, m);
		broadcast(mpi_root, n);
		broadcast(mpi_root, o);

		int elementsA = (m * n) / hpc::mpi::get_size();
		int elementsB = (n * o) / hpc::mpi::get_size();

		// Initialize the local matrices with the right size and fill by scatter
		A_local.resize(elementsA);
		B_local.resize(elementsB);
		hpc::mpi::check(MPI_Scatter(A.data(), elementsA, MPI_INT, A_local.data(), elementsA, MPI_INT, mpi::mpi_root, MPI_COMM_WORLD));
		hpc::mpi::check(MPI_Scatter(B.data(), elementsB, MPI_INT, B_local.data(), elementsB, MPI_INT, mpi::mpi_root, MPI_COMM_WORLD));

		// Exception/Input handling
		if (m % hpc::mpi::get_size() != 0 || n % hpc::mpi::get_size() != 0) {
			if (get_rank() == mpi_root)
				std::cout << "Either m or n is not dividable by the node count without remainder. Terminating." << std::endl;
		} else {
			// Clear initial matrices
			A.clear();
			B.clear();

			std::vector<int> C_local(m / hpc::mpi::get_size() * o);
			int values_per_step = (n / hpc::mpi::get_size());
			// Swap B with every node
			for (int currStep{ 0 }; currStep < hpc::mpi::get_size(); currStep++) {
				// For every Row in Matrix A_local
				for (int row_A{ 0 }; row_A < m / hpc::mpi::get_size(); row_A++) {
					// For every column in Matrix B_local
					for (int col_B{ 0 }; col_B < o; col_B++) {
						// Both columns share the dimension n --> shared index
						for (int rel_el_idx{ 0 }; rel_el_idx < values_per_step; rel_el_idx++) {
							// Calculate the indices using the rank, and the current step (= how often local_B has been swapped)
							int abs_offset = (hpc::mpi::get_rank() - currStep);
							abs_offset = abs_offset < 0 ? hpc::mpi::get_size() + abs_offset : abs_offset;

							// Compound operator+ operation on C
							C_local[row_A * o + col_B] += A_local[row_A * n + (rel_el_idx + values_per_step * abs_offset) ] * B_local[o * rel_el_idx + col_B];
						}
					}
				}

				// Send B_local to the next node (rank += 1, til it has cycled)
				MPI_Sendrecv_replace(B_local.data(),
					B_local.size(),
					MPI_INT,
					(hpc::mpi::get_rank() + 1) % hpc::mpi::get_size(),
					0,
					hpc::mpi::get_rank() == 0 ? hpc::mpi::get_size() - 1 : hpc::mpi::get_rank() - 1,
					0,
					MPI_COMM_WORLD,
					MPI_STATUS_IGNORE
				);
			}


			// Initialize vector of necessary dimensions and get final result by combining subresults with gather
			std::vector<int> C(m * o);
			MPI_Gather(C_local.data(), C_local.size(), MPI_INTEGER, C.data(), C_local.size(), MPI_INTEGER, mpi::mpi_root, MPI_COMM_WORLD);

			// Only the root reports the result
			if (get_rank() == mpi_root) {
				std::cout << std::format("{} has the result C:\n{}\n\n", hpc::mpi::get_rank(), vecToStr(C, o));
			}
		}
	}
}

int main(int argc, char* argv[]) {
	try {
		hpc::mpi::check(MPI_Init(&argc, &argv));

		hpc::mpi::multiply_parallel(argc, argv);

		MPI_Finalize();
	}
	catch (std::exception const& error) {
		std::cerr << error.what() << std::endl;
	}

	return 0;
}