#include<mpi.h>
#include<cassert>
#include<iostream>
#include<format>
#include<exception>

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
	int resultlen {-1};
	check(MPI_Get_processor_name(buffer, &resultlen));
	return buffer;
}

void queen() {
	// in final homework version: make dedicated versions, that replace MPI_INT etc. directly with the necessary constant
	// --> overloading
	// or --> templates
	int			message{ -1 };
	MPI_Status	status{};

	for (int i{ 1 }; i < get_size(); i++) {
		check(MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status));

		std::cout << std::format("Received message '{}' from swarm node #{}", message, status.MPI_SOURCE) << std::endl;

		// TODO: Throw exception
	}
}

void hive() {
	int message{ get_rank() * 10 };
	std::cout << std::format("{}/{} sent '{}' to queen node.", get_host(), get_rank(), message) << std::endl;
	check(MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD));
}

int main(int argc, char * argv []) {
	try {
		check(MPI_Init(&argc, &argv));

		std::cout << std::format("[{}] Rank {} of {}", get_host(), get_rank(), get_size()) << std::endl;

		if (get_rank() == 0) {
			queen();
		}
		else {
			hive();
		}

		MPI_Finalize();
	}
	catch (std::exception const& error) {
		std::cerr << error.what() << std::endl;
	}
}