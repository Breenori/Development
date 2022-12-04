#include "test_rational.h"

void test_constructor1() {
	std::cout << "Test case test_constructor1:\n";
	rational_t rat;
	rat.print();
	std::cout << "\n";
}
void test_constructor2() {
	std::cout << "Test case test_constructor2:\n";
	rational_t rat(-5);
	rat.print();
	std::cout << "\n";
}
void test_constructor3() {
	std::cout << "Test case test_constructor3:\n";
	rational_t rat(12, 5);
	rat.print();
	std::cout << "\n";
}
void test_constructor3_invalid_input() {
	std::cout << "Test case test_constructor3_invalid_input:\n";
	try {
		rational_t rat(3, 0);
	}
	catch (DivideByZeroError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "\n";
}
void test_copy_constructor() {
	std::cout << "Test case test_copy_constructor:\n";
	rational_t rat(6, 7);
	rat.print();
	rational_t rat2(rat);
	rat2.print();
	std::cout << "\n";
}

void test_normalize() {
	std::cout << "Test case test_normalize:\n";
	rational_t rat(24, 8);
	rat.print();
	rat += 0;
	rat.print();
	std::cout << "\n";
}

void test_scan() {
	std::cout << "Test case test_scan:\n" << "Please enter a rational: ";
	rational_t rat;
	try {
		rat.scan();
		rat.print();
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "\n";
}

void test_get_numerator() {
	std::cout << "Test case test_get_numerator:\n";
	rational_t rat(6, 20);
	rat.print();
	std::cout << " Numerator: " << rat.get_numerator() << "\n\n";
}
void test_get_denominator() {
	std::cout << "Test case test_get_denominator:\n";
	rational_t rat(6, 20);
	rat.print();
	std::cout << " Denominator: " << rat.get_denominator() << "\n\n";
}

void test_is_negative(rational_t const& rat) {
	std::cout << "Test case test_is_negative:\n";
	if (rat.is_negative()) {
		std::cout << rat.as_string() << " is negative.\n";
	}
	else {
		std::cout << rat.as_string() << " is not negative.\n";
	}
	std::cout << "\n";
}
void test_is_positive(rational_t const& rat) {
	std::cout << "Test case test_is_positive:\n";
	if (rat.is_positive()) {
		std::cout << rat.as_string() << " is positive.\n";
	}
	else {
		std::cout << rat.as_string() << " is not positive.\n";
	}
	std::cout << "\n";
}
void test_is_zero(rational_t const& rat) {
	std::cout << "Test case test_is_zero:\n";
	if (rat.is_zero()) {
		std::cout << rat.as_string() << " is zero.\n";
	}
	else {
		std::cout << rat.as_string() << " is not zero.\n";
	}
	std::cout << "\n";
}

//assignment operator test
void test_assignment_op() {
	std::cout << "Test case test_assignment_op:\n";
	rational_t rat(4, 7);
	rat.print();
	rational_t rat2 = rat;
	rat2.print();
	std::cout << "\n";
}

//comparison operators tests
void test_equal_op() {
	std::cout << "Test case test_equal_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(19, 7);
	rational_t rat3(8, 5);
	std::cout << rat.as_string() << " == " << rat2.as_string() << ": " << (rat == rat2) << "\n";
	std::cout << rat.as_string() << " == " << rat3.as_string() << ": " << (rat == rat3) << "\n";
	std::cout << "\n";
}
void test_not_equal_op() {
	std::cout << "Test case test_not_equal_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(19, 7);
	rational_t rat3(8, 5);
	std::cout << rat.as_string() << " != " << rat2.as_string() << ": " << (rat != rat2) << "\n";
	std::cout << rat.as_string() << " != " << rat3.as_string() << ": " << (rat != rat3) << "\n";
	std::cout << "\n";
}
void test_less_op() {
	std::cout << "Test case test_less_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(22, 7);
	rational_t rat3(8, 5);
	std::cout << rat.as_string() << " < " << rat2.as_string() << ": " << (rat < rat2) << "\n";
	std::cout << rat.as_string() << " < " << rat3.as_string() << ": " << (rat < rat3) << "\n";
	std::cout << "\n";
}
void test_less_or_equal_op() {
	std::cout << "Test case test_less_or_equal_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(19, 7);
	rational_t rat3(8, 5);
	rational_t rat4(8, 2);
	std::cout << rat.as_string() << " <= " << rat2.as_string() << ": " << (rat <= rat2) << "\n";
	std::cout << rat.as_string() << " <= " << rat3.as_string() << ": " << (rat <= rat3) << "\n";
	std::cout << rat.as_string() << " <= " << rat4.as_string() << ": " << (rat <= rat4) << "\n";
	std::cout << "\n";
}
void test_greater_op() {
	std::cout << "Test case test_greater_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(22, 7);
	rational_t rat3(8, 5);
	std::cout << rat.as_string() << " > " << rat2.as_string() << ": " << (rat > rat2) << "\n";
	std::cout << rat.as_string() << " > " << rat3.as_string() << ": " << (rat > rat3) << "\n";
	std::cout << "\n";
}
void test_greater_or_equal_op() {
	std::cout << "Test case test_greater_or_equal_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(19, 7);
	rational_t rat3(8, 5);
	rational_t rat4(8, 2);
	std::cout << rat.as_string() << " >= " << rat2.as_string() << ": " << (rat >= rat2) << "\n";
	std::cout << rat.as_string() << " >= " << rat3.as_string() << ": " << (rat >= rat3) << "\n";
	std::cout << rat.as_string() << " >= " << rat4.as_string() << ": " << (rat >= rat4) << "\n";
	std::cout << "\n";
}

//arithmetic functions tests
void test_add() {
	std::cout << "Test case test_add:\n";
	rational_t rat(4, 5);
	rational_t rat2(-2, 3);
	rational_t result = rat + rat2;
	std::cout << rat << " + " << rat2 << " = " << result << "\n";

	rational_t rat3(2, 3);
	result = rat3 + rat2;
	std::cout << rat3 << " + " << rat2 << " = " << result << "\n";

	rational_t rat4(0, 3);
	result = rat2 + rat4;
	std::cout << rat2 << " + " << rat4 << " = " << result << "\n";

	std::cout << rat4 << " + " << rat2 << " = ";
	rat4 += rat2;
	std::cout << rat4 << "\n";

	int x = 5;
	result = x + rat;
	std::cout << x << " + " << rat << " = " << result << "\n";
	std::cout << "\n";
}
void test_sub() {
	std::cout << "Test case test_sub:\n";
	rational_t rat(4, 5);
	rational_t rat2(-2, 3);
	rational_t result = rat - rat2;
	std::cout << rat << " - " << rat2 << " = " << result << "\n";

	rational_t rat3(2, 3);
	std::cout << rat3 << " - " << rat3 << " = ";
	rat3 -= rat3;
	std::cout << rat3 << "\n";

	rational_t rat4(0, 3);
	result = rat2 - rat4;
	std::cout << rat2 << " - " << rat4 << " = " << result << "\n";

	rational_t rat5(5, 6);
	result = rat4 - rat5;
	std::cout << rat4 << " - " << rat5 << " = " << result << "\n";

	int x = 5;
	result = x - rat;
	std::cout << x << " - " << rat << " = " << result << "\n";
	std::cout << "\n";
}
void test_mul() {
	std::cout << "Test case test_mul:\n";
	rational_t rat1(12, 4);
	rational_t rat2(3, 2);
	rational_t result = rat1 * rat2;
	std::cout << rat1 << " * " << rat2 << " = " << result << "\n";

	rational_t rat3(0, 1);
	result = rat1 * rat3;
	std::cout << rat1 << " * " << rat3 << " = " << result << "\n";

	result = rat3 * rat1;
	std::cout << rat3 << " * " << rat1 << " = " << result << "\n";

	rational_t rat4(7, -8);
	rational_t rat5(-5, 3);
	std::cout << rat4 << " * " << rat5 << " = ";
	rat4 *= rat5;
	std::cout << rat4 << "\n";

	int x = 13;
	result = x * rat5;
	std::cout << x << " * " << rat5 << " = " << result << "\n";
	std::cout << "\n";
}
void test_div() {
	std::cout << "Test case test_div:\n";
	rational_t rat1(12, 4);
	rational_t rat2(3, 2);
	rational_t result = rat1 / rat2;
	std::cout << rat1 << " / " << rat2 << " = " << result << "\n";

	rational_t rat3(0, 1);
	std::cout << rat1 << " / " << rat3 << " = ";
	try {
		result = rat1 / rat3;
		std::cout << result << "\n";
	}
	catch (DivideByZeroError& ex) {
		std::cout << ex.what() << "\n";
	}

	result = rat3 / rat1;
	std::cout << rat3 << " / " << rat1 << " = " << result << "\n";

	rational_t rat4(7, -8);
	rational_t rat5(-5, 3);
	std::cout << rat4 << " / " << rat5 << " = ";
	rat4 /= rat5;
	std::cout << rat4 << "\n";

	int x = 13;
	result = x / rat5;
	std::cout << x << " / " << rat5 << " = " << result << "\n";
	std::cout << "\n";
}

//<< >>
void test_write_to_stream() {
	std::cout << "Test case test_write_to_stream:\n";
	rational_t rat(24, 6);
	std::cout << rat << "\n";
	std::ofstream out{"print_rational.txt"};
	out << rat;
	std::cout << "\n";
}
void test_read_from_stream() {
	std::cout << "Test case test_read_from_stream:\n";
	rational_t rat;
	try {
		std::cin >> rat;
		std::cout << rat << "\n";
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}

	std::ifstream in("rational.txt");
	try {
		in >> rat;
		std::cout << rat << "\n";
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "\n";
}