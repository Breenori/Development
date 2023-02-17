#ifndef test_arithmetic_parser_h
#define test_arithmetic_parser_h

#include "arithmetic_parser.h"
#include <iostream>

void test_negative_value_invalid() {

	std::cout << "negative value invalid -22: ";
	ArithmeticParser p;

	try {
		double value = p.parse("negative_value_invalid.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_negative_value_valid() {

	std::cout << "negative value valid -0 22.2: ";
	ArithmeticParser p;

	double value = p.parse("negative_value_valid.txt");

	std::cout << value << "\n";
}


void test_invalid_start() {
	std::cout << "Invalid Start a*4 5: ";

	ArithmeticParser p;
	try {
		double value = p.parse("invalid_start.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_invalid_middle() {
	std::cout << "Invalid Middle *9a: ";

	ArithmeticParser p;
	try {
		double value = p.parse("invalid_middle.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}


void test_too_many_ops() {
	std::cout << "Too many operators: +*4 -7: ";

	ArithmeticParser p;
	try {
		double value = p.parse("too_many_operators.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_several_expressions() {
	std::cout << "more than one expressions: /-4 6.2 7 +2 8: ";

	ArithmeticParser p;

	try {
		double value = p.parse("several_expressions.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}


void complex_expression() {
	std::cout << "Complex Expression: + 5 * 3 / 5 10: ";

	ArithmeticParser p;

	double value = p.parse("complex_expression.txt");

	std::cout << value << "\n";
}

void complex_expression_2() {
	std::cout << "All operators at the beginning / + * + 2 3 5 1 2: ";

	ArithmeticParser p;

	double value = p.parse("complex_expression_2.txt");

	std::cout << value << "\n";
}

void test_division_by_zero() {
	std::cout << "Division by Zero: / 5 + 4 -0 4: ";

	ArithmeticParser p;
	try {
		double value = p.parse("division_by_zero.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_empty_file() {
	std::cout << "Leeres File: ";

	ArithmeticParser p;
	try {
		double value = p.parse("empty.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

#endif // !test_arithmetic_parser_h
