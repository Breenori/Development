#include "arithmetic_parser_advanced.h"
#include "test_parser3.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::string;
using std::vector;
using std::stringstream;
using var_t = std::map<string, int>;

void print_variables(var_t const& variables)
{
	cout << "variabes {\n";
	for (auto iter(variables.begin()); iter != variables.end(); ++iter)
	{
		cout << "   " << iter->first << " => " << iter->second << std::endl;
	}

	cout << "}\n\n";
}

void test1()
{
	cout << "start test 1\n\n";

	arithmetic_parser_advanced parser;

	vector<string> files{
		"../../test_infix/ok.txt",
		"i do not exist.txt",
		"../../test_infix/invalid.txt",
		"../../test_infix/with_variables.txt"};

	var_t variables;
	variables["x"] = 5;
	variables["holadrio"] = -4;
	variables["viel"] = 400;
	print_variables(variables);
	parser.set_variables(variables);

	for (auto iter(files.begin()); iter < files.end(); ++iter)
	{
		try
		{
			cout << "Expression (" << *iter << "): ";
			arithmetic_parser_base::print_file_content(*iter);

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

	vector<string> expr{ 
		"+33", "-69", "3+3", "100-50+200", "4--3", "6*-5", "-(32/3)", "-32/3", "+32/3",
		"5+4*3", "(5+4)*3", "5+(4*3)", "(5+4*3)", "(1-3/5)/8/10", "(1-3)/5/8/10", "1-3/5/8/10" };
	
	arithmetic_parser_advanced parser;

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

	vector<string> expr { "4*a", "b+b", "b*b", "0*c", "a+b*c", "90-(a+b)*a", "a--b", "a-b", "(8-+c)", "(8-c)"};
	arithmetic_parser_advanced parser;

	var_t variables;
	variables["a"] = 5;
	variables["b"] = -4;
	variables["c"] = 40;
	print_variables(variables);
	parser.set_variables(variables);

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

	vector<string> expr{ "(a+b)*(a+c)", "(a+b)*(a-b)", "100/a/c", "100/a/c*c*c", "(a+c)*((a-c)/(1-b))", "(((a+b)))"};
	arithmetic_parser_advanced parser;

	var_t variables;
	variables["a"] = 10;
	variables["b"] = -20;
	variables["c"] = 3;
	print_variables(variables);
	parser.set_variables(variables);

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

	vector<string> expr{ "3/0", "5/(a-10)", "7-0/0", "b", "-b", "7/b", "a*b+a/b", "a*(b+a)/b"};
	arithmetic_parser_advanced parser;

	var_t variables;
	variables["a"] = 10;
	variables["b"] = 0;
	print_variables(variables);
	parser.set_variables(variables);

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

	vector<string> expr{ "5 6", "term(5+factor)", "5 * ", "1+1x", "term+4)", "1++factor", "1+++factor", "factor*" };

	arithmetic_parser_advanced parser;

	var_t variables;
	variables["term"] = 10;
	variables["factor"] = 0;
	print_variables(variables);
	parser.set_variables(variables);

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

void test7()
{
	cout << "start test 7\n\n";

	vector<string> expr{ "3*x", "(5*10)x", "var", "07*2+(5+8)*2", "a*x*a*x", "", "0", "7**4+value"};

	arithmetic_parser_advanced parser;

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

	cout << "end test 7\n\n";
}
