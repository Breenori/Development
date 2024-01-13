#include "arithmetic_parser_test.h"

double test_arith(std::istream& in)
{
	ArithmeticParser ap;
	return ap.parse(in);
}



void run_test(std::istream& in, std::string const& description, double expected_result)
{
	std::cout << description << std::endl;

	double res = test_arith(in);

	std::cout << "Expected Result : " << expected_result << std::endl;
	std::cout << "Actual Result : " << res << std::endl;

	expected_result == res ? std::cout << "Test successfull" : std::cout << "Test failed";
	std::cout << std::endl << std::endl;

}

void run_test_sstream(std::string in, std::string const& description, double expected_result)
{
	std::cout << description << std::endl;
	std::cout << "Expression: " << in << std::endl;

	std::stringstream ss(in);

	double res = test_arith(ss);

	std::cout << "Expected Result : " << expected_result << std::endl;
	std::cout << "Actual Result : " << res << std::endl;

	expected_result == res ? std::cout << "Test successfull" : std::cout << "Test failed";
	std::cout << std::endl << std::endl;
}

void run_neg_test(std::string in, std::string const& description)
{
	std::cout << description << std::endl;
	std::cout << "Expression: " << in << std::endl;

	std::stringstream ss(in);

	try
	{
		double res = test_arith(ss);
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
		std::cout << e.what() << std::endl<< std::endl;
	}
	ifs.close();
}

void test_working_file()
{
	std::ifstream ifs("example.txt");
	run_test(ifs, "Testing existing file",-24);
	ifs.close();
}

void test_simple_expr()
{
	run_test_sstream("1+2*3", "Testing a simple expression", 7);
}

void test_neg_nrs()
{
	run_test_sstream("-2-3", "Testing negative numbers", -5);
}

void test_p_expr()
{
	run_test_sstream("(1+2)*3", "Testing an expression with parentheses", 9);
}

void test_mult_div()
{
	run_test_sstream("1*3/2", "Testing an multiplication and division", 1.5);
}

void test_add_sub()
{
	run_test_sstream("1+2-3", "Testing additon and subtraction", 0);
}

void neg_test_simple_expr()
{
	run_neg_test("invalid+3", "Testing a invalid Expression");
}

void neg_test_term()
{
	run_neg_test("3+invalid", "Testing a invalid Term");
}


void neg_test_mult_div()
{
	run_neg_test("3*(-invalid)", "Testing a invalid Factor");
}


void neg_test_div_by_zero() {
	run_neg_test("1/0", "Testing division by zero");
}
