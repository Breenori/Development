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
		if (normalized_rank >= power_2(step) && normalized_rank < power_2(step + 1) && normalized_rank - power_2(step) >= 0) {
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
	auto read_matrices(std::istream&& in) {
		std::tuple<int, std::vector<int>, std::vector<int>> data{};
		auto& [n, A, B] {data};
		in >> n;

		A.resize(n * n);
		for (auto& el : A)
			in >> el;

		B.resize(n * n);
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

	// Helper function to read CLI params
	std::string_view get_option(
		const std::vector<std::string_view>& args,
		const std::string_view& option_name) {
		for (auto it = args.begin(), end = args.end(); it != end; ++it) {
			if (*it == option_name)
				if (it + 1 != end)
					return *(it + 1);
		}

		return "";
	}

	void convert_tile_format(std::vector<int>& matrix) {
		std::vector<int> temp(matrix);
		int n{ (int)sqrt(matrix.size()) };
		int tiledim{ (int)sqrt(matrix.size() / hpc::mpi::get_size()) };

		for (int i{ 0 }; i < temp.size(); i++) {
			int tileX{ (i % n) / tiledim };
			int tileXoff{ (i % n) % tiledim };
			int tileY{ (i / n) / tiledim };
			int tileYoff{ (i / n) % tiledim };
			matrix[(tileY * n * tiledim) + (tileYoff * tiledim) + (tileX * tiledim * tiledim) + tileXoff] = temp[i];
		}
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

		int p_1dim{ (int)sqrt(hpc::mpi::get_size()) };

		int n { 0 };
		std::vector<int> A, B;

		if (get_rank() == mpi_root) {
			std::tie(n, A, B) = read_matrices(std::ifstream{ "data/fox.txt" });
			convert_tile_format(A);
			convert_tile_format(B);
		}

		// Broadcast all dimensions
		broadcast(mpi_root, n);

		// Exception/Input handling
		if (p_1dim != sqrt(hpc::mpi::get_size()) || n % p_1dim != 0) {
			throw new std::exception("Invalid process number given. Terminating.");
		}
		else {
			MPI_Comm grid_comm{};
			MPI_Cart_create(MPI_COMM_WORLD, 2, new int[] {p_1dim, p_1dim}, new int[] {true, true}, true, &grid_comm);

			MPI_Comm row_comm{};
			MPI_Cart_sub(grid_comm, new int[] {false, true}, &row_comm);

			MPI_Comm col_comm{};
			MPI_Cart_sub(grid_comm, new int[] {true, false}, &col_comm);

			int elements = (n * n) / hpc::mpi::get_size();

			std::vector<int> A_local;
			std::vector<int> B_local;

			// Initialize the local matrices with the right size and fill by scatter
			A_local.resize(elements);
			B_local.resize(elements);
			hpc::mpi::check(MPI_Scatter(A.data(), elements, MPI_INT, A_local.data(), elements, MPI_INT, mpi::mpi_root, MPI_COMM_WORLD));
			hpc::mpi::check(MPI_Scatter(B.data(), elements, MPI_INT, B_local.data(), elements, MPI_INT, mpi::mpi_root, MPI_COMM_WORLD));

			// Clear initial matrices
			A.clear();
			B.clear();

			int rowRank, colRank { -1 };
			MPI_Comm_rank(row_comm, &rowRank);
			MPI_Comm_rank(col_comm, &colRank);

			std::vector<int> C_local(elements);
			// Swap B with every node
			for (int i{ 0 }; i < p_1dim; i++) {
				// Multiply A_local and B_local


				// Send B_local to the next node (rank += 1, til it has cycled)
				MPI_Sendrecv_replace(B_local.data(),
					B_local.size(),
					MPI_INT,
					(rowRank + i) % p_1dim,
					0,
					hpc::mpi::get_rank() == 0 ? hpc::mpi::get_size() - 1 : hpc::mpi::get_rank() - 1,
					0,
					MPI_COMM_WORLD,
					MPI_STATUS_IGNORE
				);
			}


			// Initialize vector of necessary dimensions and get final result by combining subresults with gather
			std::vector<int> C(elements * hpc::mpi::get_size());
			MPI_Gather(C_local.data(), C_local.size(), MPI_INTEGER, C.data(), C_local.size(), MPI_INTEGER, mpi::mpi_root, MPI_COMM_WORLD);
			convert_tile_format(C);

			// Only the root reports the result
			if (get_rank() == mpi_root) {
				std::cout << std::format("{} has the result C:\n{}\n\n", hpc::mpi::get_rank(), vecToStr(C, n));
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