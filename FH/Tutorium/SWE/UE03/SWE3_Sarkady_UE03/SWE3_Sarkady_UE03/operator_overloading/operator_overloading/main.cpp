#include "rational.h"
#include "div_by_zero.h"

// Comparison operators:
void test_comparison_operators_equal() {
	// ==
	std::cout << "test equal to\n";
	rational_t r1(8, 4);
	rational_t r2(4, 2);
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
void test_comparison_operators_unequal() {
	// ==
	std::cout << "\n\ntest equal to\n";
	rational_t r1(8, 5);
	rational_t r2(4, 2);
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
// Arithmetic operators:
// compound assignment operators
void test_add_cao() {
	std::cout << "\ntest addition (compound assignment operator)\n";
	rational_t r1(4, 2);
	rational_t r2(5, 2);
	r1.print();
	r2.print();
	std::cout << "result: ";
	r1 += r2;
	std::cout << r1;
}
void test_sub_cao() {
	std::cout << "\ntest substraction (compound assignment operator)\n";
	rational_t r1(4, 2);
	rational_t r2(5, 2);
	r1.print();
	r2.print();
	std::cout << "result: ";
	r1 -= r2;
	r1.print();
}
void test_mul_cao() {
	std::cout << "\ntest multiplication (compound assignment operator)\n";
	rational_t r1(4, 2);
	rational_t r2(5, 2);
	r1.print();
	r2.print();
	std::cout << "result: ";
	r1 *= r2;
	std::cout << r1;
}
void test_div_cao() {
	std::cout << "\ntest division (compound assignment operator)\n";
	try {
		rational_t r1(4, 2);
		rational_t r2(5, 2);
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
void test_div_by_zero_cao() {
	std::cout << "\ntest division by zero (compound assignment operator)\n";
	try {
		rational_t r1(4, 0);
		rational_t r2(5, 2);
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
// Member function
void test_m_add() {
	std::cout << "\ntest addition\n";
	rational_t r1(4, 2);
	rational_t r2(5, 2);
	r1.print();
	r2.print();
	std::cout << "result: ";
	std::cout << r1 + r2;
}
void test_m_sub() {
	std::cout << "\ntest substraction\n";
	rational_t r1(4, 2);
	rational_t r2(5, 2);
	r1.print();
	r2.print();
	std::cout << "result: ";
	std::cout << r1 - r2;
}
void test_m_mul() {
	std::cout << "\ntest multiplication\n";
	rational_t r1(4, 2);
	rational_t r2(5, 2);
	r1.print();
	r2.print();
	std::cout << "result: ";
	std::cout << r1 * r2;
}
void test_m_div() {
	std::cout << "\ntest division\n";
	rational_t r1(4, 2);
	rational_t r2(5, 2);
	r1.print();
	r2.print();
	std::cout << "result: ";
	std::cout << r1 / r2;
}
void test_m_div_by_zero() {
	std::cout << "\ntest division by zero\n";
	try {
		rational_t r1(4, 0);
		rational_t r2(5, 2);
		r1.print();
		r2.print();
		std::cout << "result: ";
		std::cout << r1 / r2;
	}
	catch (DivideByZeroError& e1) {
		std::cout << e1.what() << "\n";
	}
}
// rational_t + int
void test_m_add_int() {
	std::cout << "\ntest addition with int\n";
	rational_t r1(4, 2);
	int r2 = 4;
	r1.print();
	std::cout << r2;
	std::cout << "\nresult: ";
	std::cout << r1 + r2;
}
void test_m_sub_int() {
	std::cout << "\ntest substraction with int\n";
	rational_t r1(4, 2);
	int r2 = 4;
	std::cout << r1 << r2 << "\nresult: ";
	std::cout << r1 - r2;
}
void test_m_mul_int() {
	std::cout << "\ntest multiplication with int\n";
	rational_t r1(4, 2);
	int r2 = 4;
	std::cout << r1 << r2 << "\nresult: ";
	std::cout << r1 * r2;
}
void test_m_div_int() {
	std::cout << "\ntest division with int\n";
	rational_t r1(4, 2);
	int r2 = 4;
	std::cout << r1 << r2 << "\nresult: ";
	std::cout << r1 / r2;
}
void test_m_div_by_zero_int() {
	std::cout << "\ntest division by zero with int\n";
	try {
		rational_t r1(4, 2);
		int r2 = 0;
		std::cout << r1 << r2 << "\nresult: ";
		std::cout << r1 / r2;
	}
	catch (DivideByZeroError& e1) {
		std::cout << e1.what() << "\n";
	}
}
// Non Member function 
void test_add_int_lhs() {
	std::cout << "\ntest addition with int lhs\n";
	int r1 = 4;
	rational_t r2(4, 2);
	std::cout << r1 << r2 << "result: ";
	std::cout << r1 + r2;
}
void test_sub_int_lhs() {
	std::cout << "\ntest substraction with int lhs\n";
	int r1 = 4;
	rational_t r2(4, 2);
	std::cout << r1 << r2 << "result: ";
	std::cout << r1 - r2;
}
void test_mul_int_lhs() {
	std::cout << "\ntest multiplication with int lhs\n";
	int r1 = 4;
	rational_t r2(4, 2);
	std::cout << r1 << r2 << "result: ";
	std::cout << r1 * r2;
}
void test_div_int_lhs() {
	std::cout << "\ntest division with int lhs\n";
	int r1 = 4;
	rational_t r2(4, 2);
	std::cout << r1 << r2 << "result: ";
	std::cout << r1 / r2 << "\n";
}
void test_div_by_zero_int_lhs() {
	std::cout << "\ntest division by zero with int lhs\n";
	try {
		int r1 = 0;
		rational_t r2(4, 2);
		std::cout << r1 << r2 << "result: ";
		std::cout << r1 / r2 << "\n";
	}
	catch (DivideByZeroError& e1) {
		std::cout << e1.what() << "\n";
	}
}
// is_zero, positive, negative
void test_zero_neg_pos() {
	std::cout << "test is_pos, neg, zero\n";
	rational_t r1(4, 2);
	std::cout << r1;
	std::cout << "is positive: " << std::boolalpha << r1.is_positive() << "\n";
	std::cout << "is negative: " << std::boolalpha << r1.is_negative() << "\n";
	std::cout << "is zero: " << std::boolalpha << r1.is_zero() << "\n";

	rational_t r2(0, 2);
	std::cout << r2;
	std::cout << "is positive: " << std::boolalpha << r2.is_positive() << "\n";
	std::cout << "is negative: " << std::boolalpha << r2.is_negative() << "\n";
	std::cout << "is zero: " << std::boolalpha << r2.is_zero() << "\n";

	rational_t r3(-4, 2);
	std::cout << r3;
	std::cout << "is positive: " << std::boolalpha << r3.is_positive() << "\n";
	std::cout << "is negative: " << std::boolalpha << r3.is_negative() << "\n";
	std::cout << "is zero: " << std::boolalpha << r3.is_zero() << "\n";
}
void test_as_string() {
	std::cout << "\ntest as string\n";
	rational_t a(4, 2);
	std::cout << "a: " << a.get_numerator();
	std::cout << "\nb: " << a.get_denominator() << "\n";
	std::cout << a.as_string() << "\n";
}
void test_scan() {
	std::cout << "\ntest scan function\n";
	rational_t a;
	try {
		a.scan();
		a.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what();
	}
}
void test_copy_constructor() {
	std::cout << "\ntest copy constructor\n";
	rational_t a;
	rational_t b(40,8);
	a.print();
	b.print();
	std::cout << "a = b\n";
	a = b;
	a.print();
}
void test_getter() {
	std::cout << "\ntest getter\n";
	rational_t a(4, 2);
	std::cout << a;
	std::cout << "numerator: " << a.get_numerator();
	std::cout << "\ndenominator: " << a.get_denominator() << "\n";
}

void main() {
	test_comparison_operators_equal();
	test_comparison_operators_unequal();
	
	test_add_cao();
	test_sub_cao();
	test_mul_cao();
	test_div_cao();
	test_div_by_zero_cao();

	test_m_add();
	test_m_sub();
	test_m_mul();
	test_m_div();
	test_m_div_by_zero();

	test_m_add_int();
	test_m_sub_int();
	test_m_mul_int();
	test_m_div_int();
	test_m_div_by_zero_int();

	test_add_int_lhs();
	test_sub_int_lhs();
	test_mul_int_lhs();
	test_div_int_lhs();
	test_div_by_zero_int_lhs();

	test_zero_neg_pos();
	test_copy_constructor();
	test_getter();
	test_as_string();
	test_scan();
}