#include "test_prefix_parser.h"
#include "prefix_parser.h"

void test_parse_file(std::string filename) {
	std::cout << "Test case test_parser_from_file:\n";
	Prefix_Parser p;
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
	Prefix_Parser p;
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
	catch (pfc::scn::exception ex) {
		std::cout << "\t" << ex.what() << "\n";
	}
	std::cout << "\n";
}

void test_parse_from_file() {
	test_parse_file("test_empty.txt");
	test_parse_file("test_file1.txt");
	test_parse_file("test_file2.txt");
	test_parse_file("test_file3.txt");
	test_parse_file("test_file4.txt");
	test_parse_file("test_file5.txt");
	test_parse_file("test_file6.txt");
	test_parse_file("test_div_by_zero.txt");
	test_parse_file("test_invalid1.txt");
	test_parse_file("test_invalid2.txt");
	test_parse_file("test_invalid3.txt");
	test_parse_file("test_invalid4.txt");
}

void test_parse_from_string() {
	test_parse_string("+ 4 23");
	test_parse_string("");
	test_parse_string("* - 5 6 3");
	test_parse_string("/ - 9 2 * 4 5");
	test_parse_string("- 7 * 5 6 8");
	test_parse_string("* 3 4 - 5 6");
	test_parse_string("*-456");
	test_parse_string("+ ( 8 9 - 16 4");
	test_parse_string("3 4 +");
	test_parse_string("/ * 3 6 - 5 5");
	test_parse_string("/11+*17.3 22 3");
	test_parse_string("++1 2.7 * 3 - 5 4");
}