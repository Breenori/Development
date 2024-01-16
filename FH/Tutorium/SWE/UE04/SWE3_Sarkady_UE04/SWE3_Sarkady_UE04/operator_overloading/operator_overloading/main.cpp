#include "rational.h"
#include "div_by_zero.h"
#include "number.h"
 
// tests with
// **** Rational<Number<int>> *****************************************
void test_comparison() {
	std::cout << "test equal to\n";
	Rational<Number<int>> r1(8, 4);
	Rational<Number<int>> r2(4, 2);
	std::cout << r1 << r2;
	bool res = r1 == r2;
	std::cout << std::boolalpha << res;
	// !=
	std::cout << "\n\ntest unequal\n";
	std::cout << r1 << r2;
	res = r1 != r2;
	std::cout << std::boolalpha << res;
	// <
	std::cout << "\n\ntest smaller than\n";
	std::cout << r1 << r2;
	res = r1 < r2;
	std::cout << std::boolalpha << res;
	// <=
	std::cout << "\n\ntest smaller than or equal to\n";
	std::cout << r1 << r2;
	res = r1 <= r2;
	std::cout << std::boolalpha << res;
	// >
	std::cout << "\n\ntest greater than\n";
	std::cout << r1 << r2;
	res = r1 > r2;
	// >=
	std::cout << std::boolalpha << res;
	std::cout << "\n\ntest greater than or equal to\n";
	std::cout << r1 << r2;
	res = r1 >= r2;
	std::cout << std::boolalpha << res;
}
void test_comparison_unequal() {
	// ==
	std::cout << "\n\ntest equal to\n";
	Rational<Number<int>> r1(8, 5);
	Rational<Number<int>> r2(4, 2);
	std::cout << r1 << r2;
	bool res = r1 == r2;
	std::cout << std::boolalpha << res;
	// !=
	std::cout << "\n\ntest unequal\n";
	std::cout << r1 << r2;
	res = r1 != r2;
	std::cout << std::boolalpha << res;
	// <
	std::cout << "\n\ntest smaller than\n";
	std::cout << r1 << r2;
	res = r1 < r2;
	std::cout << std::boolalpha << res;
	// <=
	std::cout << "\n\ntest smaller than or equal to\n";
	std::cout << r1 << r2;
	res = r1 <= r2;
	std::cout << std::boolalpha << res;
	// >
	std::cout << "\n\ntest greater than\n";
	std::cout << r1 << r2;
	res = r1 > r2;
	// >=
	std::cout << std::boolalpha << res;
	std::cout << "\n\ntest greater than or equal to\n";
	std::cout << r1 << r2;
	res = r1 >= r2;
	std::cout << std::boolalpha << res << "\n";
}
// Arithmetic Operators
void test_addition() {
	std::cout << "\n\nTest addition\n";
	Rational<Number<int>> a(4, 2);
	Rational<Number<int>> b(5, 2);
	std::cout << a << b << "result: " << a + b;
}
void test_substraction() {
	std::cout << "\nTest substraction\n";
	Rational<Number<int>> a(4, 2);
	Rational<Number<int>> b(5, 2);
	std::cout << a << b << "result: " << a - b;
}
void test_multiplication() {
	std::cout << "\nTest multiplication\n";
	Rational<Number<int>> a(4, 2);
	Rational<Number<int>> b(5, 2);
	std::cout << a << b << "result: " << a * b;
}
void test_division() {
	std::cout << "\nTest division\n";
	Rational<Number<int>> a(4, 2);
	Rational<Number<int>> b(5, 2);
	std::cout << a << b << "result: " << a / b;
}
void test_division_by_zero() {
	std::cout << "\ntest division by zero\n";
	try {
		Rational<Number<int>> r1(4, 0);
		Rational<Number<int>> r2(5, 2);
		r1.print();
		r2.print();
		std::cout << "result: ";
		std::cout << r1 / r2;
	}
	catch (DivideByZeroError& e1) {
		std::cout << e1.what() << "\n";
	}
}
// Compound Assignment Operators
void test_addition_cao() {
	std::cout << "\nTest addition (compound assignment operator)\n";
	Rational<Number<int>> a(4, 2);
	Rational<Number<int>> b(5, 2);
	std::cout << a << b;
	a += b;
	std::cout << "result: " << a;
}
void test_substraction_cao() {
	std::cout << "\nTest substraction (compound assignment operator)\n";
	Rational<Number<int>> a(4, 2);
	Rational<Number<int>> b(5, 2);
	std::cout << a << b;
	a -= b;
	std::cout << "result: " << a;
}
void test_multiplication_cao() {
	std::cout << "\nTest multiplication (compound assignment operator)\n";
	Rational<Number<int>> a(4, 2);
	Rational<Number<int>> b(5, 2);
	std::cout << a << b;
	a *= b;
	std::cout << "result: " << a;
}
void test_division_cao() {
	std::cout << "\nTest division (compound assignment operator)\n";
	Rational<Number<int>> a(4, 2);
	Rational<Number<int>> b(5, 2);
	std::cout << a << b;
	a /= b;
	std::cout << "result: " << a;
}
void test_division_by_zero_cao() {
	std::cout << "\ntest division by zero (compound assignment operator)\n";
	try {
		Rational<Number<int>> r1(4, 0);
		Rational<Number<int>> r2(5, 2);
		r1.print();
		r2.print();
		std::cout << "result: ";
		r1 /= r2;
		std::cout << r1;
	}
	catch (DivideByZeroError& e1) {
		std::cout << e1.what() << "\n";
	}
}
//is_zero, positive, negative
void test_zero_neg_pos() {
	std::cout << "\ntest is_pos, neg, zero\n";
	Rational<Number<int>> r1(4, 2);
	std::cout << r1;
	std::cout << "is positive: " << std::boolalpha << r1.is_positive() << "\n";
	std::cout << "is negative: " << std::boolalpha << r1.is_negative() << "\n";
	std::cout << "is zero: " << std::boolalpha << r1.is_zero() << "\n";

	Rational<int> r2(0, 2);
	std::cout << r2;
	std::cout << "is positive: " << std::boolalpha << r2.is_positive() << "\n";
	std::cout << "is negative: " << std::boolalpha << r2.is_negative() << "\n";
	std::cout << "is zero: " << std::boolalpha << r2.is_zero() << "\n";

	Rational<int> r3(-4, 2);
	std::cout << r3;
	std::cout << "is positive: " << std::boolalpha << r3.is_positive() << "\n";
	std::cout << "is negative: " << std::boolalpha << r3.is_negative() << "\n";
	std::cout << "is zero: " << std::boolalpha << r3.is_zero() << "\n";
}
void test_getter() {
	std::cout << "\ntest getter\n";
	Rational<Number<int>> a(4, 2);
	std::cout << a;
	std::cout << "numerator: " << a.get_numerator();
	std::cout << "\ndenominator: " << a.get_denominator() << "\n\n";
}
void test_inverse() {
	Rational<Number<int>> a(4, 2);
	std::cout << "\ntest inverse\n";
	std::cout << a;
	a.inverse();
	std::cout << a;
}
void test_copy_constructor() {
	std::cout << "\ntest copy constructor\n";
	Rational<Number<int>> a;
	Rational<Number<int>> b(40, 8);
	a.print();
	b.print();
	std::cout << "a = b\n";
	a = b;
	a.print();
}
void test_scan() {
	std::cout << "\ntest scan function\n";
	Rational<Number<int>> a;
	try {
		a.scan();
		a.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what();
	}
}

void main() {
	// *******************************************************************************
	test_comparison();
	test_comparison_unequal();

	std::cout << "\n******************************************************************\n";
	test_addition();
	test_substraction();
	test_multiplication();
	test_division();
	test_division_by_zero();

	std::cout << "\n******************************************************************\n";
	test_addition_cao();
	test_substraction_cao();
	test_multiplication_cao();
	test_division_cao();
	test_division_by_zero_cao();

	std::cout << "\n******************************************************************\n";
	test_zero_neg_pos();
	test_getter();
	test_inverse();
	test_copy_constructor();
	test_scan();

	std::cout << "\n******************************************************************\n";
	// *******************************************************************************
}