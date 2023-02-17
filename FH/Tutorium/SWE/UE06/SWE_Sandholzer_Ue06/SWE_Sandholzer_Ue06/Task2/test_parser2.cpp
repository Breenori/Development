#include "arithmetic_parser_prefix.h"
#include "test_parser2.h"
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

		"../../test_prefix/ok.txt",
		"i do not exist.txt",
		"../../test_prefix/invalid.txt"
	};

	for (auto iter(files.begin()); iter < files.end(); ++iter)
	{
		try
		{
			cout << "Expression (" << *iter << "): ";
			arithmetic_parser_base::print_file_content(*iter);

			arithmetic_parser_prefix parser;
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

	vector<string> expr{ "33", "-0 69", "+3 3", "+-100 50 200", "-4-0 3", "*6 -0 5", "-0/32 3", "/32 3"};
	arithmetic_parser_prefix parser;

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

	//vector<string> expr{ "5+4*3", "(5+4)*3", "5+(4*3)", "(5+4*3)", "(1-3/5)/8/10", "(1-3)/5/8/10", "1-3/5/8/10" };
	vector<string> expr{ "+5 *4 3", "*+5 4 3", "*3+4 5", "/ /- 1 /3 5 8 10", "/ / / - 1 3 5 8 10", "- 1/ / / 3 5 8 10"};
	arithmetic_parser_prefix parser;

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

	vector<string> expr{ "++4 4 4", "--5 5 5", "**3 3 3", "//8 4 2" , "/ /8 4 2", "/*/10 2 10 25",
		"/ */10 2 10 25", "/ //64 2 2 2", "/ / /64 2 2 2", "-+*/70 10 5 13 10"};
	arithmetic_parser_prefix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult: " << parser.parse(sst) << "\n\n";
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

	vector<string> expr{ "/3 0", "-6/8 0", "/0 0 0 0 0", "/ a 0", "/ 0 0001"};
	arithmetic_parser_prefix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult: " << parser.parse(sst) << "\n\n";
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

	vector<string> expr{ "1000", "0", "-33", "+34", "+4 4", "++2 2 2", "++2 2 2 2", "+++2 2 2"};
	arithmetic_parser_prefix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult: " << parser.parse(sst) << "\n\n";
		}
		catch (const std::exception& ex)
		{
			cout << "Parse Error: " << ex.what() << "\n\n";
		}
	}

	cout << "end test 6\n\n";
}

void test7()
{
	cout << "start test 7\n\n";

	vector<string> expr{ "(+1 1)", "* 3 x", "*", "", "hi", "+5,5", "+5.34 10", "+-0 00 000", "+3 3 nope"};
	arithmetic_parser_prefix parser;

	for (auto iter(expr.begin()); iter != expr.end(); iter++)
	{
		try
		{
			stringstream sst(*iter);
			cout << "Expression: " << *iter;
			cout << "\nResult: " << parser.parse(sst) << "\n\n";
		}
		catch (const std::exception& ex)
		{
			cout << "Parse Error: " << ex.what() << "\n\n";
		}
	}

	cout << "end test 7\n\n";
}
