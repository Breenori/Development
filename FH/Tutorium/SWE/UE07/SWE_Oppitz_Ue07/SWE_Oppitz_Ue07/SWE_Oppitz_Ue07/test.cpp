#include "test.h"


void print_result(std::string test_name, double value, double expected_result = 0) {
	std::cout << "Testing: " << "\"" << test_name << "\"" << "\n";
	std::cout << "result: " << value << '\n';
	std::cout << "Expected result: " << expected_result << "\n";
	if (expected_result == value) {
		std::cout << "SUCCESSFUL" << "\n";
	}
	else {
		std::cout << "FAILED" << "\n";
	}
	std::cout << "-----------------------------------------------------\n";
}

void print_exception(std::string const& test_name, std::exception const& x, bool expect_exception, std::string const& expected_result = "") {
	std::cout << "Testing: " << "\"" << test_name << "\"" << "\n";
	std::cerr << "Error: " << x.what();
	if (expect_exception) {
		std::cout << "Expected result: " << expected_result << '\n';;
		std::cout << "SUCCESSFUL" << "\n";
	}
	else {
		std::cout << "Expected result: " << "No exception" << '\n';;
		std::cout << "FAILED" << "\n";
	}
	std::cout << "-----------------------------------------------------\n";
}

void basic_function_test() {
	std::cout << "----------------------------------\n";

	try {
		xpr::ParseSyntaxTree().parse("print(2 + 3);");
	}
	catch (std::exception const& x) {
		std::cerr << x.what() << "\n";
	}

	std::cout << "----------------------------------\n";
}