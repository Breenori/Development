#include "prefix_parser_test.h"

double test_prefix(std::istream& in) {
	PrefixParser pp;
	return pp.parse(in);

}

void run_test(std::istream& in, std::string const& description, double expected_result) {
	std::cout << description << std::endl;

	double res = test_prefix(in);

	std::cout << "Expected Result : " << expected_result << std::endl;
	std::cout << "Actual Result : " << res << std::endl;

	expected_result == res ? std::cout << "Test successfull" : std::cout << "Test failed";
	std::cout << std::endl << std::endl;
}

void run_test_sstream(std::string in, std::string const& description, double expected_result) {
	std::cout << description << std::endl;
	std::cout << "Expression: " << in << std::endl;

	std::stringstream ss(in);

	double res = test_prefix(ss);

	std::cout << "Expected Result : " << expected_result << std::endl;
	std::cout << "Actual Result : " << res << std::endl;

	expected_result == res ? std::cout << "Test successfull" : std::cout << "Test failed";
	std::cout << std::endl << std::endl;
}

void run_neg_test(std::string in, std::string const& description) {
	std::cout << description << std::endl;
	std::cout << "Expression: " << in << std::endl;

	std::stringstream ss(in);

	try
	{
		double res = test_prefix(ss);
	}
	catch (ParserException e)
	{
		std::cout << "Error:\n";
		std::cout << e.what() << std::endl;
	}



	std::cout << std::endl << std::endl;
}

void test_inv_file()
{
	std::ifstream ifs("thisFileDoesNotExist.txt");
	try
	{
		run_test(ifs, "Testing non existent file", 0);
	}
	catch (ParserException e)
	{
		std::cout << "Error:\n";
		std::cout << e.what() << std::endl << std::endl;
	}
	ifs.close();
}

void test_working_file()
{
	std::ifstream ifs("example.txt");
	run_test(ifs, "Testing existing file", 14);
	ifs.close();
}

void test_simple_expr() {
	run_test_sstream("+ 1 * 4 5","Testing simple expression",21);
}
void test_neg_nrs() {
	run_test_sstream("- 0 1", "Testing negative number", -1);

}
void test_mult_div() {
	run_test_sstream("/ 1 * 2 2", "Testing muliplication and division ", 0.25);
}
void test_add_sub() {
	run_test_sstream("+ 1 - 3 4", "Testing addition and subtraction", 0);
}

void neg_test_simple_expr() {
	run_neg_test("+ invalid 3", "Testing invalid expression");
}
void neg_test_mult_div() {
	run_neg_test("invalid 3 ", "Testing invalid expression");
}

void neg_test_div_by_zero() {
	run_neg_test("/ 1 0", "Testing division by zero exception");
}