#ifndef test_arithmetic_parser_h
#define test_arithmetic_parser_h

#include "arithmetic_parser.h"
#include <iostream>

void test_single_value() {

	std::cout << "Single negative Value -22: ";
	ArithmeticParser p;

	double value=p.parse("single_value.txt");

	std::cout << value << "\n";
}

void test_single_PExpression() {
	std::cout << "Single PExpression (8.5*4): ";
	ArithmeticParser p;

	double value = p.parse("single_PExpression.txt");

	std::cout << value << "\n";
}

void test_invalid_start() {
	std::cout << "Invalid Start *4+7: ";

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
	std::cout << "Invalid Middle 9*a+(6/2): ";

	ArithmeticParser p;
	try {
		double value = p.parse("invalid_middle.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_multiple_closing() {
	std::cout << "Too many closing parenthesis: 8*(7+0.2)): ";

	ArithmeticParser p;

	double value = p.parse("multiple_closing.txt");

	std::cout << value << "\n";
}

void test_multiple_ops_invalid() {
	std::cout << "Multiple Operators invalid: +*4/-7: ";

	ArithmeticParser p;
	try {
		double value = p.parse("multiple_ops_invalid.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_multiple_ops_valid() {
	std::cout << "Multiple Operators valid: 4*-3: ";

	ArithmeticParser p;

	double value = p.parse("multiple_ops_valid.txt");

	std::cout << value << "\n";
}

void test_multiple_PExpressions() {
	std::cout << "Multiple PExpressions: (7+(21-10))/(5-(2*4)): ";

	ArithmeticParser p;

	double value = p.parse("multiple_PExpressions.txt");

	std::cout << value << "\n";
}

void test_klapustri() {
	std::cout << "Klammer vor Punkt vor Strich: 10+2*(5-2): ";

	ArithmeticParser p;

	double value = p.parse("klapustri.txt");

	std::cout << value << "\n";
}

void test_division_by_zero() {
	std::cout << "Division by Zero: 8/(-5.7+5.7): ";

	ArithmeticParser p;
	try {
		double value = p.parse("division_by_zero.txt");
		std::cout << value << "\n";
	}
	catch (ParserException e) {
		std::cout << e.what() << "\n";
	}
}

void test_several_expressions() {
	std::cout << "More than one Expression: 5*7 8+2*5 7: ";

	ArithmeticParser p;
	try {
		double value = p.parse("several_expressions.txt");
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
