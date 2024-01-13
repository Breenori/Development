#include<mpi.h>
#include<cassert>
#include<iostream>
#include<format>
#include<exception>
#include<vector>
#include<concepts>
#include<functional>
#include<string>

namespace hpc::mpi {
	int mpi_root{ 1 };

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

	using integratee_t = std::function<double(double)>;
	using integrator_t = std::function<double(double, double, int, integratee_t)>;

	// List of integrators and integratees to choose from
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
		[](double x) { return sin(x); },
		[](double x) { return cos(x); }
	};

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
	template <typename T> void broadcast(int const root, T& value) {
		for (int step{ 0 }; step < ceil_log_2(get_size()); step++) {
			int buddy{ -1 };
			if ((buddy = must_send(step, root)) > -1) {
				mpi_send_wrapper(buddy, &value);
				std::cout << std::format("Broadcast - Step {}: #{} sent value \"{}\" to #{}!", step, get_rank(), value, buddy) << std::endl;
			}
			else if ((buddy = must_receive(step, root)) > -1) {
				mpi_recv_wrapper(&value);
				std::cout << std::format("Broadcast - Step {}: #{} received value \"{}\" from #{}!", step, get_rank(), value, buddy) << std::endl;
			}
		}
	}

	// make the function in reduce freely pickable (e.g. subtract instead of addition -> 2 parameters, 1 return
	template <std::floating_point T> using binary_function_t = std::function <T(T, T)>;
	template <typename T> T reduce(int const root, T value, binary_function_t<T> const op) {
		// Reverse the loop and conditions (broadcast in reverse order)
		for (int step{ ceil_log_2(get_size()) - 1 }; step >= 0 ; step--) {
			int buddy{ -1 };
			if ((buddy = must_receive(step, root)) > -1) {
				mpi_send_wrapper(buddy, &value);
				std::cout << std::format("Reduce - Step {}: #{} sent value \"{}\" to #{}!", step, get_rank(), value, buddy) << std::endl;
			}
			else if ((buddy = must_send(step, root)) > -1) {
				double add{ value };
				mpi_recv_wrapper(&add);
				std::cout << std::format("Reduce - Step {}: #{} received value \"{}\" from #{}!", step, get_rank(), value, buddy) << std::endl;
				value = op(value, add);
			}
		}

		return value;
	}

	// Reduce functions
	template <typename T>
	T add(T op1, T op2) {
		return op1 + op2;
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

		// Debugging: let each node print their contribution
		std::cout << std::format("Node {} has:\t[{}, {}] with {} splines", get_rank(), a, b, n) << std::endl;

		double sum = integrator(a, b, n, integratee);

		return sum;
	}

	double integrate_parallel(int argc, char* argv[]) {


		// Quick output when node starts the task
		std::cout << std::format("[{}] Rank {} of {}", hpc::mpi::get_host(), hpc::mpi::get_rank(), hpc::mpi::get_size()) << std::endl;

		double a, b{ -1 };
		int n, integrator_id, integratee_id{ -1 };

		// Read input from argc and argv
		if (get_rank() == mpi_root) {
			const std::vector<std::string_view> args(argv + 1, argv + argc);
			a = !get_option(args, "--left").empty() ? std::stod(get_option(args, "--left").data()) : 0;
			b = !get_option(args, "--right").empty() ? std::stod(get_option(args, "--right").data()) : 1;

			if (b < a) {
				std::swap(a, b);
			}

			n = !get_option(args, "--subs").empty() ? std::stoi(get_option(args, "--subs").data()) : 100;
			integrator_id = !get_option(args, "--integrator").empty() ? std::stoi(get_option(args, "--integrator").data()) : 0;
			integratee_id = !get_option(args, "--integratee").empty() ? std::stoi(get_option(args, "--integratee").data()) : 0;
		}

		// Broadcast all values
		broadcast(mpi_root, a);
		broadcast(mpi_root, b);
		broadcast(mpi_root, n);
		broadcast(mpi_root, integrator_id);
		broadcast(mpi_root, integratee_id);

		// Calculate integral for own interval
		double sum = integrate_serial(a, b, n, integrators[integrator_id], integratees[integratee_id]);

		// Define reduce function and reduce the input
		binary_function_t<double> reduce_function = add<double>;
		sum = reduce(mpi_root, sum, reduce_function);

		if (get_rank() == mpi_root) {
			std::cout << std::format("The result is: {}", sum) << std::endl;
		}

		return sum;
	}
}

int main(int argc, char* argv[]) {
	try {
		hpc::mpi::check(MPI_Init(&argc, &argv));

		double result = hpc::mpi::integrate_parallel(argc, argv);

		MPI_Finalize();
	}
	catch (std::exception const& error) {
		std::cerr << error.what() << std::endl;
	}

	return 0;
}