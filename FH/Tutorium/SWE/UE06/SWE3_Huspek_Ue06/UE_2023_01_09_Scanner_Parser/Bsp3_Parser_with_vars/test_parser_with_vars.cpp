#include "test_parser_with_vars.h"
#include "arithmetic_parser.h"
#include <fstream>

void test_parse_file(std::string filename) {
	std::cout << "Test case test_parser_from_file:\n";
	ArithmeticParser p;
	std::cout << "\tParse from " << filename << "\n";
	try {
		std::ifstream in{ filename };
		std::map<std::string, double> vars = {	{"x", 4}, 
												{"test", -8.9}, 
												{"i", 22.9}, 
												{"var", 18.4} };
		double result = p.parse(in, vars);
		std::cout << "\tThe result is: " << result << "\n";
	}
	catch (ParserException ex) {
		std::cout << "\t" << ex.what() << "\n";
	}
	catch (DivideByZeroException ex) {
		std::cout << "\t" << ex.what() << "\n";
	}
	catch (pfc::scn::exception& ex) {
		std::cout << "\t" << ex.what() << "\n";
	}
	std::cout << "\n";
}

void test_parse_string(std::string str) {
	std::cout << "Test case test_parser_from_string:\n";
	ArithmeticParser p;
	std::cout << "Parse string: " << str << "\n";
	try {
		std::map<std::string, double> vars = { {"x", 4}, {"test", -8.9}, {"i", 22.9}, {"var", 18.4} };
		double result = p.parse(str, vars);
		std::cout << "\tThe result is: " << result << "\n";
	}
	catch (ParserException ex) {
		std::cout << "\t" << ex.what() << "\n";
	}
	catch (DivideByZeroException ex) {
		std::cout << "\t" << ex.what() << "\n";
	}
	catch (pfc::scn::exception& ex) {
		std::cout << "\t" << ex.what() << "\n";
	}
	std::cout << "\n";
}

void test_parse_from_file() {
	test_parse_file("test_empty.txt");
	test_parse_file("test_file1.txt");
	test_parse_file("test_file2.txt");
	test_parse_file("test_file3.txt");
	test_parse_file("test_div_by_zero.txt");
	test_parse_file("test_invalid2.txt");
	test_parse_file("test_invalid3.txt");
}

void test_parse_from_string() {
	test_parse_string("5.5 * x");
	test_parse_string("");
	test_parse_string("( 13 + ( 4 * var) - 10) / (6 - 6)");
	test_parse_string("8*x+(4.8-3)-i");
	test_parse_string("10 - 3 + (12.5 - test + (3 * -5)) / -7 * -3");
	test_parse_string("(8 + ( -3 * z))");
	test_parse_string("x");
	test_parse_string("6 + i * y");
}