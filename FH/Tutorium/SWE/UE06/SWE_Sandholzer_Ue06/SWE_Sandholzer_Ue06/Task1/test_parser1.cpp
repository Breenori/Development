#include "arithmetic_parser_infix.h"
#include "test_parser1.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::string;
using std::vector;
using std::stringstream;

void test1()
{
	cout << "start test 1\n\n";

	vector<string> files{ 
		"../../test_infix/ok.txt",
		"i do not exist.txt",
		"../../test_infix/invalid.txt"};

	for (auto iter(files.begin()); iter < files.end(); ++iter)
	{
		try
		{
			cout << "Expression (" << *iter << "): ";
			arithmetic_parser_base::print_file_content(*iter);

			arithmetic_parser_infix parser;
			cout << "\nResult = " << parser.parse(*iter) << "\n\n";
		}
		catch (const std::exception& ex)
		{
			cout << "Parse Error: " << ex.what() << "\n\n";
		}
	}

	cout << "end test 1\n\n";
}

void test2()
{
	cout << "start test 2\n\n";

	vector<string> expr{ "+33", "-69", "3+3", "100-50+200", "4--3", "6*-5", "-(32/3)", "-32/3", "+32/3"};
	arithmetic_parser_infix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult = " << parser.parse(sst) << "\n\n";
		}
		catch (const std::exception& ex)
		{
			cout << "Parse Error: " << ex.what() << "\n\n";
		}
	}

	cout << "end test 2\n\n";
}

void test3()
{
	cout << "start test 3\n\n";

	vector<string> expr{ "5+4*3", "(5+4)*3", "5+(4*3)", "(5+4*3)", "(1-3/5)/8/10", "(1-3)/5/8/10", "1-3/5/8/10"};
	arithmetic_parser_infix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult = " << parser.parse(sst) << "\n\n";
		}
		catch (const std::exception& ex)
		{
			cout << "Parse Error: " << ex.what() << "\n\n";
		}
	}

	cout << "end test 3\n\n";
}

void test4()
{
	cout << "start test 4\n\n";

	vector<string> expr{ "1/0", "6+300000/(500*0)", "8/-0", "-0/8", "0/69*-1", "0/69*-1*-1", "0*0*0/(6*4-24)", "-0+3", "0+3"};
	arithmetic_parser_infix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult = " << parser.parse(sst) << "\n\n";
		}
		catch (const std::exception& ex)
		{
			cout << "Parse Error: " << ex.what() << "\n\n";
		}
	}

	cout << "end test 4\n\n";
}

void test5()
{
	cout << "start test 5\n\n";

	vector<string> expr{ "4,1 + 99", "5 6", "4(4+2)", "5 * ", "(5*7", "+", "0-", "78/3 3", "1+1x"};
	arithmetic_parser_infix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult = " << parser.parse(sst) << "\n\n";
		}
		catch (const std::exception& ex)
		{
			cout << "Parse Error: " << ex.what() << "\n\n";
		}
	}

	cout << "end test 5\n\n";
}

void test6()
{
	cout << "start test 6\n\n";

	vector<string> expr{ "", "5-2)", "7.1 - 3", "80/0.000001", "4*x", "+33", "++33", "3++3", "3+++3"};
	arithmetic_parser_infix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult = " << parser.parse(sst) << "\n\n";
		}
		catch (const std::exception& ex)
		{
			cout << "Parse Error: " << ex.what() << "\n\n";
		}
	}

	cout << "end test 6\n\n";
}
