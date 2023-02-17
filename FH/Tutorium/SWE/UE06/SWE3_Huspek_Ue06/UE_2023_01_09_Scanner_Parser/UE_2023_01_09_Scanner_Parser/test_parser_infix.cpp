#include "test_parser_infix.h"
#include "arithmetic_parser.h"
#include <fstream>

void test_parse_file(std::string filename) {
	std::cout << "Test case test_parser_from_file:\n";
	ArithmeticParser p;
	std::cout << "\tParse from " << filename << "\n";
	try {
		std::ifstream in{ filename };
		double result = p.parse(in);
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
		double result = p.parse(str);
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
	test_parse_file("test_invalid1.txt");
	test_parse_file("test_invalid2.txt");
	test_parse_file("test_invalid3.txt");
	test_parse_file("test_invalid4.txt");
}

void test_parse_from_string() {
	test_parse_string("5.5 * 8");
	test_parse_string("");
	test_parse_string("( 13 + ( 4 * 5.5) - 10) / (6 - 6)");
	test_parse_string("8*16+(4.8-3)-23");
	test_parse_string("10 - 3 + (12.5 - 4 + (3 * -5)) / -7 * -3");
	test_parse_string("(8 + 4 ( -3 * 2)");
	test_parse_string("5 * (6 % 3)");
	test_parse_string(" / 8 + 3 4");
	test_parse_string("12.4 - 8.2 + (8");
}