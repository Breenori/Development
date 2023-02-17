#pragma once
#include "arithmetic_parser.h"

bool test_variables() {
	std::cout << "\n-------------------------------------------\n";
	std::cout << __func__ << "\n";
	std::cout << "\nTEST00:\n";
	try
	{
		arithmetic_parser p0;
		std::string var0{ "x" };
		std::istringstream input0{ var0 };
		std::cout << "Input: " << var0 << " = 3\n";
		std::cout << "Expected output: 3\n";
		p0.assign_Variable(var0, 3);
		std::cout <<"Actual output: "<< p0.parse(input0) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what()<<"\n";
	}
	std::cout << "\n-------------------------------------------\n";
	std::cout << "\nTEST01:\n";
	try
	{
		arithmetic_parser p1;
		std::string var1{ "y" };
		std::istringstream input1{ var1 };
		std::cout << "Input: " << var1 << " = 0\n";
		std::cout << "Expected output: 0\n";
		p1.assign_Variable(var1, 0);
		std::cout << "Actual output: " << p1.parse(input1) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";
	std::cout << "\nTEST02:\n";
	try
	{
		arithmetic_parser p2;
		std::string var2{ "x" };
		std::istringstream input2{ var2 };
		std::cout << "Input: " << var2 << " = 5\n";
		std::cout << "Expected output: 5\n";
		p2.assign_Variable(var2, 5);
		std::cout << "Actual output: " << p2.parse(input2) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";

	std::cout << "\nTEST03:\n";
	try
	{
		arithmetic_parser p3;
		std::string var3{ "z" };
		std::string var31{ "i" };
		std::istringstream input3{ var3+ var31};
		std::cout << "Input: " << var3 << " = 5\n";
		std::cout << "Expected output: Not found.\n";
		p3.assign_Variable(var3, 3);
		std::cout << "Actual output: " << p3.parse(input3) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";

	std::cout << "\nTEST04:\n";
	try
	{
		arithmetic_parser p4;
		std::string var4{ "x+5" };
		std::istringstream input4{ var4 };
		std::cout << "Input: " << var4 << " = x+5\n";
		std::cout << "Expected output: 8\n";
		p4.assign_Variable("x", 3);
		std::cout << "Actual output: " << p4.parse(input4) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";

	std::cout << "\nTEST05:\n";
	try
	{
		arithmetic_parser p4;
		std::string var4{ "x-5" };
		std::istringstream input4{ var4 };
		std::cout << "Input: " << var4 << " = x-5\n";
		std::cout << "Expected output: -3\n";
		p4.assign_Variable("x", 2);
		std::cout << "Actual output: " << p4.parse(input4) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";

	std::cout << "\nTEST06:\n";
	try
	{
		arithmetic_parser p4;
		std::string var4{ "x-l" };
		std::istringstream input4{ var4 };
		std::cout << "Input: " << var4 << " = x-l\n";
		std::cout << "Expected output: 5\n";
		p4.assign_Variable("x", 2);
		p4.assign_Variable("l", -3);
		std::cout << "Actual output: " << p4.parse(input4) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";

	std::cout << "\nTEST07:\n";
	try
	{
		arithmetic_parser p4;
		std::string var4{ "x*3" };
		std::istringstream input4{ var4 };
		std::cout << "Input: " << var4 << " = x*3\n";
		std::cout << "Expected output: 6\n";
		p4.assign_Variable("x", 2);
		std::cout << "Actual output: " << p4.parse(input4) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";
	std::cout << "\nTEST08:\n";
	try
	{
		arithmetic_parser p4;
		std::string var4{ "x/2" };
		std::istringstream input4{ var4 };
		std::cout << "Input: " << var4 << " = x/2\n";
		std::cout << "Expected output: 3\n";
		p4.assign_Variable("x", 6);
		std::cout << "Actual output: " << p4.parse(input4) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";
	std::cout << "\nTEST09:\n";
	try
	{
		arithmetic_parser p4;
		std::string var4{ "x/0" };
		std::istringstream input4{ var4 };
		std::cout << "Input: " << var4 << " = x/0\n";
		std::cout << "Expected output: Error.\n";
		p4.assign_Variable("x", 6);
		std::cout << "Actual output: " << p4.parse(input4) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";
	std::cout << "\nTEST10:\n";
	try
	{
		arithmetic_parser p4;
		std::string var4{ "10/x" };
		std::istringstream input4{ var4 };
		std::cout << "Input: " << var4 << " = 10/x\n";
		std::cout << "Expected output: 2\n";
		p4.assign_Variable("x", 5);
		std::cout << "Actual output: " << p4.parse(input4) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";
	std::cout << "\nTEST11:\n";
	try
	{
		arithmetic_parser p4;
		std::string var4{ "10/x" };
		std::istringstream input4{ var4 };
		std::cout << "Input: " << var4 << " = 10/x\n";
		std::cout << "Expected output: Error.\n";
		p4.assign_Variable("x", 0);
		std::cout << "Actual output: " << p4.parse(input4) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	std::cout << "\n-------------------------------------------\n";

	return EXIT_SUCCESS;
}
