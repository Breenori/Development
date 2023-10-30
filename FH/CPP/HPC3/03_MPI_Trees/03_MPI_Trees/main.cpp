#include<mpi.h>
#include<cassert>
#include<iostream>
#include<format>
#include<exception>
#include<vector>
#include<functional>
#include<string>

namespace hpc::mpi {
	using integratee_t = std::function<double(double)>;
	using integrator_t = std::function<double(double, double, int, integratee_t)>;

	double integrate_serial(double a, double b, int n, integrator_t integrator, integratee_t integratee);

	std::vector<integrator_t> integrators = {
		[](double a, double b, int n, integratee_t f) { // Trapezoidal rule
			double h{(b - a) / n};
			double sum{ 0.5 * (f(a) + f(b)) };
			for (int i{ 1 }; i < n; i++) {
				sum += f(a + i * h);
			}

			return h * sum;
		},
		[](double a, double b, int n, integratee_t f) { // Simpsons Rule
			double h{(b - a) / n};
			double sum{f(a) + f(b) };

			for (int i{ 1 }; i < n; i++) {
				sum += (i % 2 == 0) ? 2 * f(a + i * h) : 4 * f(a + i * h);
			}

			return (h / 3) * sum;
		}
	};
	std::vector<integratee_t> integratees = {
		[](double x) { return x * x; },
		[](double x) { return std::sin(x); },
		[](double x) { return cos(x); }
	};
	int const mpi_root = 0;



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

	int must_send(int step, int rank, int dest, int size) {

		int normalized_rank = rank - dest < 0 ? size + (rank - dest) : rank - dest;

		if (normalized_rank < std::pow(2, step) && normalized_rank + (int)std::pow(2, step) < size)
			return (normalized_rank + dest + (int)std::pow(2, step)) % size;
		else
			return -1;
	}
	int must_receive(int step, int rank, int dest, int size) {

		int normalized_rank = rank - dest < 0 ? size + (rank - dest) : rank - dest;
		//std::cout << std::format("Rank {} normalized: {}", rank, normalized_rank) << std::endl;

		if (step == 3 && rank == 12) {
			int i = 1;
		}

		if (normalized_rank >= std::pow(2, step) && normalized_rank < std::pow(2, step + 1) && normalized_rank - (int)std::pow(2, step) >= 0) {
			int target = (normalized_rank + dest - (int)std::pow(2, step));
			//std::cout << std::format("Target formula for {}: {} + {} - {} = {}", rank, normalized_rank, dest, (int)std::pow(2, step), target) << std::endl;
			return target >= 0 ? target % size : target + size;
		}
		else {
			return -1;
		}
	}

	int ceil_log2(int dec) {
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


	double integrate_parallel(double a, double b, int n, int integrator_id, int integratee_id) {
		for (int step{ 0 }; step < ceil_log2(get_size()); step++) {
			int buddy{ -1 };
			if ((buddy = must_send(step, get_rank(), mpi_root, get_size())) > -1) {
				std::cout << std::format("Step {}: {} --> {}!", step, get_rank(), buddy) << std::endl;
				mpi_send_wrapper(buddy, &a);
				mpi_send_wrapper(buddy, &b);
				mpi_send_wrapper(buddy, &n);
				mpi_send_wrapper(buddy, &integrator_id);
				mpi_send_wrapper(buddy, &integratee_id);
			}
			else if ((buddy = must_receive(step, get_rank(), mpi_root, get_size())) > -1) {
				std::cout << std::format("Step {}: {} <-- {}!", step, get_rank(), buddy) << std::endl;
				mpi_recv_wrapper(&a);
				mpi_recv_wrapper(&b);
				mpi_recv_wrapper(&n);
				mpi_recv_wrapper(&integrator_id);
				mpi_recv_wrapper(&integratee_id);
			}
		}

		double sum = integrate_serial(a, b, n, integrators[integrator_id], integratees[integratee_id]);

		if (get_rank() == 0) {
			double remote_res{ -1 };
			for (int i{ 1 }; i < get_size(); i++) {
				mpi_recv_wrapper(&remote_res, 1);
				sum += remote_res;
			}
		}
		else {
			mpi_send_wrapper(0, &sum, 1);
		}

		return sum;
	}

	double integrate_serial(double a, double b, int n, integrator_t integrator, integratee_t integratee) {
		// If number of hosts > number of splines, return 0 as neutral element
		if (n <= (get_rank())) {
			return 0;
		}

		double interval{ (b - a) / (get_size() * 1.0) };
		b = a + (get_rank() + 1) * interval;
		a = a + get_rank() * interval;

		// Remainder is always less than cluster-size --> if id is less than remainder, add 1.
		n = n / get_size() + ((n % get_size()) > get_rank() ? 1 : 0);

		// Debugging:
		std::cout << std::format("Node {} has:\t[{}, {}] with {} splines", get_rank(), a, b, n) << std::endl;

		double sum = integrator(a, b, n, integratee);

		return sum;
	}
}

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

int main(int argc, char* argv[]) {
	try {
		hpc::mpi::check(MPI_Init(&argc, &argv));

		std::cout << std::format("[{}] Rank {} of {}", hpc::mpi::get_host(), hpc::mpi::get_rank(), hpc::mpi::get_size()) << std::endl;

		/*
		if (hpc::mpi::get_rank() == 0) {
			int size = 200;
			for (int step{ 0 }; step < hpc::mpi::ceil_log2(size); step++) {
				std::cout << std::format("Step {}", step) << std::endl;
				for (int rank{ 0 }; rank < size; rank++) {
					int buddy = -1;
					if ((buddy = hpc::mpi::must_receive(step, rank, hpc::mpi::mpi_root, size)) > -1) {
						std::cout << std::format("{} <-- {}", rank, buddy) << std::endl;
					}
					else if ((buddy = hpc::mpi::must_send(step, rank, hpc::mpi::mpi_root, size)) > -1) {
						std::cout << std::format("{} --> {}", rank, buddy) << std::endl;
					}
				}
				std::cout << std::endl;
			}
		}*/
		
		// Read from commandline
		const std::vector<std::string_view> args(argv + 1, argv + argc);
		double a = get_option(args, "--left").data() != "" ? std::stod(get_option(args, "--left").data()) : 0;
		double b = get_option(args, "--right").data() != "" ? std::stod(get_option(args, "--right").data()) : 1;
		int n = get_option(args, "--splines").data() != "" ? std::stoi(get_option(args, "--splines").data()) : 100;
		int integrator_id = get_option(args, "--integrator").data() != "" ? std::stoi(get_option(args, "--integrator").data()) : 0;
		int integratee_id = get_option(args, "--integratee").data() != "" ? std::stoi(get_option(args, "--integratee").data()) : 0;

		double result = hpc::mpi::integrate_parallel(a, b, n, integrator_id, integratee_id);

		if (hpc::mpi::get_rank() == 0) {
			std::cout << std::format("The result is: {}", result) << std::endl;
		}

		//std::cout << std::format("{} {} {} {} {}", a, b, n, integrator_id, integratee_id) << std::endl;

		MPI_Finalize();
	}
	catch (std::exception const& error) {
		std::cerr << error.what() << std::endl;
	}

	return 0;
}