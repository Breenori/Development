#ifndef test_arithmetic_parser_h
#define test_arithmetic_parser_h

#include "arithmetic_parser.h"
#include <iostream>

std::map<std::string, double> variables{ {"a", 5}, {"ab2c", 10.2}, {"7c", 4.7}, {"k8", 18.8} };

void test_single_char_identifier() {

	std::cout << "Single Char Identifier a: ";
	ArithmeticParser p;

	double value = p.parse("single_char_identifier.txt", variables);

	std::cout << value << "\n";
}

void test_complex_identifier() {

	std::cout << "Complex Identifier ab2c: ";
	ArithmeticParser p;

	double value = p.parse("complex_identifier.txt", variables);

	std::cout << value << "\n";
}

void test_invalid_identifier() {

	std::cout << "Invalid Identifier starting with number 7c: ";
	ArithmeticParser p;

	try {
		double value = p.parse("invalid_identifier.txt", variables);
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_unknown_identifier() {
	std::cout << "Unknown identifier asdf: ";

	ArithmeticParser p;
	try {
		double value = p.parse("unknown_identifier.txt",variables);
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_identifiers() {
	std::cout << "Identifiers in use: a*7+ab2c: ";

	ArithmeticParser p;
	try {
		double value = p.parse("identifiers.txt", variables);
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}


#endif // !test_arithmetic_parser_h
