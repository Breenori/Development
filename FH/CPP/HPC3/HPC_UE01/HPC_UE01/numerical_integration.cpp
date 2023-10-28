#include<mpi.h>
#include<cassert>
#include<iostream>
#include<format>
#include<exception>
#include<vector>
#include<tuple>
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
				sum += (i%2 == 0) ? 2 * f(a + i * h) : 4 * f(a + i * h);
			}

			return (h / 3) * sum;
		}			
	};
	std::vector<integratee_t> integratees = {
		[](double x) { return x * x; },
		[](double x) { return std::sin(x); },
		[](double x) { return cos(x); }
	};

	


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

	void mpi_recv_wrapper(int* const message, const int argc = 1) {
		MPI_Status status{};

		check(MPI_Recv(message, argc, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status));

		std::cout << std::format("{}/{} received {}", get_host(), get_rank(), *message) << std::endl;
	}
	void mpi_send_wrapper(const int dest, int* const message, const int argc = 1) {
		check(MPI_Send(message, argc, MPI_INT, dest, 0, MPI_COMM_WORLD));

		std::cout << std::format("{}/{} sent {}", get_host(), get_rank(), *message) << std::endl;
	}
	void mpi_recv_wrapper(double* const message, const int argc = 1) {
		MPI_Status status{};

		check(MPI_Recv(message, argc, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status));
		std::cout << std::format("{}/{} received {}", get_host(), get_rank(), *message) << std::endl;
	}
	void mpi_send_wrapper(const int dest, double* const message, const int argc = 1) {
		check(MPI_Send(message, argc, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD));
		std::cout << std::format("{}/{} sent {}", get_host(), get_rank(), *message) << std::endl;
	}


	double integrate_parallel(double a, double b, int n, int integrator_id, int integratee_id) {
		if (get_rank() == 0) {
			for (int rank{ 1 }; rank < get_size(); rank++) {
				// Send Integrator, Integratee, Stepsize and Interval a + b
				mpi_send_wrapper(rank, &a, 1);
				mpi_send_wrapper(rank, &b, 1);
				mpi_send_wrapper(rank, &n, 1);
				mpi_send_wrapper(rank, &integrator_id, 1);
				mpi_send_wrapper(rank, &integratee_id, 1);
			}
		} else {
			mpi_recv_wrapper(&a, 1);
			mpi_recv_wrapper(&b, 1);
			mpi_recv_wrapper(&n, 1);
			mpi_recv_wrapper(&integrator_id, 1);
			mpi_recv_wrapper(&integratee_id, 1);
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

		double interval{ (b - a)/ (get_size() * 1.0)};
		b = a + (get_rank() + 1) * interval ;
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

		std::cout << std::format("{} {} {} {} {}", a, b, n, integrator_id, integratee_id) << std::endl;

		MPI_Finalize();
	}
	catch (std::exception const& error) {
		std::cerr << error.what() << std::endl;
	}

	return 0;
}