#include "arithmetic_variable_parser_test.h"



void test_with_var()
{
	ArithmeticVariableParser avp;
	avp.createVarible("pi", 3.14);
	std::stringstream ss("pi*10");
	double result = avp.parse(ss);

	std::cout << "Testing existing variable\n";
	std::cout << "Expression: pi*10\n";
	std::cout << "Expected Result : " << 31.4 << std::endl;
	std::cout << "Actual Result : " << result << std::endl;

	result == result ? std::cout << "Test successfull" : std::cout << "Test failed";
	std::cout << std::endl << std::endl;
}

void test_var_non_existant()
{
	ArithmeticVariableParser avp;
	std::stringstream ss("pi*10");

	std::cout << "Testing non-existant variable\n";

	try
	{
		double result = avp.parse(ss);

	}
	catch (ParserException e)
	{
		std::cout << "Error\n" << e.what() << std::endl << std::endl;
	}
}

void test_updated_var()
{
	ArithmeticVariableParser avp;
	avp.createVarible("pi", 3.14);
	std::stringstream ss("pi*10");
	double result = avp.parse(ss);
	std::cout << "Testing variable update\n";
	std::cout << "Expression: pi*10\n";
	std::cout << "Before variable update(pi = 3.14):\n";
	std::cout << "Result: " << result << std::endl;
	std::cout << "After variable update(pi = 3):\n";
	avp.updateVarible("pi", 3);
	ss = std::stringstream("pi*10");
	result = avp.parse(ss);
	std::cout << "Result: " << result << std::endl << std::endl;

}

void test_delete_var()
{
	ArithmeticVariableParser avp;
	avp.createVarible("pi", 3.14);
	std::stringstream ss("pi*10");
	double result = avp.parse(ss);
	std::cout << "Testing variable update\n";
	std::cout << "Expression: pi*10\n";
	std::cout << "Before variable update(pi = 3.14):\n";
	std::cout << "Result: " << result << std::endl;
	std::cout << "After variable update(pi is no longer defined):\n";
	avp.deleteVarible("pi");
	try
	{
		ss = std::stringstream("pi*10");
		result = avp.parse(ss);

	}
	catch (ParserException e)
	{
		std::cout << "Error\n" << e.what() << std::endl << std::endl;
	}

}

