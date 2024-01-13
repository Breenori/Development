#include "test_rational_extended.h"

#pragma once
#include "rational_extended.h"

//constructor rational_t mit double und int
void test_task_1() {
	std::cout << "TESTS TASK 1: \n";
	test_constructor1();
	test_constructor2();
	test_constructor3();
	test_constructor3_invalid_input();
	test_copy_constructor();

	test_get_numerator();
	test_get_denominator();

	rational_t rat(3, 4);
	rational_t rat2(-3, 4);
	rational_t rat3(3, -4);
	rational_t rat4(-3, -4);
	test_is_negative(rat);
	test_is_negative(rat2);
	test_is_negative(rat3);
	test_is_negative(rat4);
	test_is_positive(rat);
	test_is_positive(rat2);
	test_is_positive(rat3);
	test_is_positive(rat4);
	rational_t rat5(0, 5);
	test_is_zero(rat);
	test_is_zero(rat5);

	test_constructor1_double();
	test_constructor2_double();
	test_constructor3_double();
	test_constructor3_invalid_input_double();
	test_copy_constructor_double();

	test_get_numerator_double();
	test_get_denominator_double();

	rational_t<double> ratd(3.5, 4.34);
	rational_t<double> ratd2(-3.23, 4.779);
	rational_t<double> ratd3(3.87, -4.99);
	rational_t<double> ratd4(-3.22, -4.1);
	test_is_negative(ratd);
	test_is_negative(ratd2);
	test_is_negative(ratd3);
	test_is_negative(ratd4);
	test_is_positive(ratd);
	test_is_positive(ratd2);
	test_is_positive(ratd3);
	test_is_positive(ratd4);
	rational_t<double> ratd5(0.0, 5.6);
	test_is_zero(ratd);
	test_is_zero(ratd5);

	std::cout << "\n";
}
//constructor mit rational_t von number_t
void test_task_2(){
	std::cout << "TESTS TASK 2: \n";
	test_constructor1_number_t();
	test_constructor2_number_t();
	test_constructor3_number_t();
	test_constructor3_invalid_input_number_t();
	test_copy_constructor_number_t();
	std::cout << "\n";
}
//tests number_t
void test_task_4(){
	std::cout << "TEST TASK 4: \n";
	test_get_numerator_number_t();
	test_get_denominator_number_t();

	test_add_number_t();
	test_sub_number_t();
	test_mul_number_t();
	test_div_number_t();

	test_assignment_op_number_t();
	test_equal_op_number_t();
	test_not_equal_op_number_t();
	test_greater_op_number_t();
	test_greater_or_equal_op_number_t();
	test_less_op_number_t();
	test_less_or_equal_op_number_t();

	rational_t<number_t<int>> ratn(3, 4);
	rational_t<number_t<int>> ratn2(-3, 4);
	rational_t<number_t<int>> ratn3(3, -4);
	rational_t<number_t<int>> ratn4(-3, -4);
	test_is_negative(ratn);
	test_is_negative(ratn2);
	test_is_negative(ratn3);
	test_is_negative(ratn4);
	test_is_positive(ratn);
	test_is_positive(ratn2);
	test_is_positive(ratn3);
	test_is_positive(ratn4);
	rational_t<number_t<int>> ratn5(0, 5);
	test_is_zero(ratn);
	test_is_zero(ratn5);

	test_write_to_stream_number_t();
	test_read_from_stream_number_t();
	std::cout << "\n";
}

void test_task_8()
{
	std::cout << "TESTS TASK 8:\n";
	test_inverse();
	test_inverse_double();
	test_inverse_number_t();
	std::cout << "\n";
}

void test_task_9(){
	std::cout << "TESTS TASK 9:\n";
	test_assignment_op();
	test_assignment_op_double();

	test_equal_op();
	test_equal_op_double();

	test_not_equal_op();
	test_not_equal_op_double();

	test_greater_op();
	test_greater_op_double();
	test_greater_or_equal_op();
	test_greater_or_equal_op_double();
	test_less_op();
	test_less_op_double();
	test_less_or_equal_op();
	test_less_or_equal_op_double();

	test_add();
	test_add_double();
	test_sub();
	test_sub_double();
	test_mul();
	test_mul_double();
	test_div();
	test_div_double();

	test_write_to_stream();
	test_write_to_stream_double();

	test_read_from_stream();
	test_read_from_stream_double();
}


//Test with T=int
void test_constructor1() {
	std::cout << "Test case test_constructor1:\n";
	std::cout << "Expected: 0/1\n";
	rational_t rat;
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor2() {
	std::cout << "Test case test_constructor2:\n";
	std::cout << "Expected: -5/1\n";
	rational_t rat(-5);
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor3() {
	std::cout << "Test case test_constructor3:\n";
	std::cout << "Expected: 12/5\n";
	rational_t rat(12, 5);
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor3_invalid_input() {
	std::cout << "Test case test_constructor3_invalid_input:\n";
	std::cout << "Expected: Divide by Zero Custom Error!\n";
	try {
		rational_t rat(3, 0);
	}
	catch (DivideByZeroError& ex) {
		std::cout << "Actual: " << ex.what() << "\n";
	}
	std::cout << "Success\n\n";
}
void test_copy_constructor() {
	std::cout << "Test case test_copy_constructor:\n";
	rational_t rat(6, 7);
	std::cout << "Expected: " << rat << "\n";
	rational_t rat2(rat);
	std::cout << "Actual: " << rat2 << "\n";
	std::cout << "Success\n\n";
}

void test_get_numerator() {
	std::cout << "Test case test_get_numerator:\n";
	rational_t rat(6, 20);
	std::cout << rat;
	std::cout << "Expected: 6\nActual: " << rat.get_numerator() << "\n\n";
}
void test_get_denominator() {
	std::cout << "Test case test_get_denominator:\n";
	rational_t rat(6, 20);
	std::cout << rat;
	std::cout << "Expected: 20\nActual: " << rat.get_denominator() << "\n\n";
}
void test_inverse() {
	std::cout << "Test case test_inverse:\n";
	rational_t rat(3, -5);
	std::cout << rat << "\n";
	rat.inverse();
	std::cout << "Expected: -5/3\nActual: " << rat << "\n";
	std::cout << "Success\n\n";
}

void test_add() {
	std::cout << "Test case test_add:\n";
	rational_t rat(4, 5);
	rational_t rat2(-2, 3);
	rational_t result = rat + rat2;
	std::cout << rat << " + " << rat2 << " = \n";
	std::cout << "Expected: 2/15\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t rat3(2, 3);
	result = rat3 + rat2;
	std::cout << rat3 << " + " << rat2 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t rat4(0, 3);
	result = rat2 + rat4;
	std::cout << rat2 << " + " << rat4 << " = \n";
	std::cout << "Expected: -2/3\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	std::cout << rat4 << " + " << rat2 << " = \n";
	rat4 += rat2;
	std::cout << "Expected: -2/3\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	int x = 5;
	result = x + rat;
	std::cout << x << " + " << rat << " = \n";
	std::cout << "Expected: 29/5\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_sub() {
	std::cout << "Test case test_sub:\n";
	rational_t rat(4, 5);
	rational_t rat2(-2, 3);
	rational_t result = rat - rat2;
	std::cout << rat << " - " << rat2 << " = \n";
	std::cout << "Expected: 22/15\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t rat3(2, 3);
	std::cout << rat3 << " - " << rat3 << " = \n";
	rat3 -= rat3;
	std::cout << "Expected: 0/1\nActual: " << rat3 << "\n";
	std::cout << "Success\n\n";

	rational_t rat4(0, 3);
	result = rat2 - rat4;
	std::cout << rat2 << " - " << rat4 << " = \n";
	std::cout << "Expected: -2/3\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t rat5(5, 6);
	result = rat4 - rat5;
	std::cout << rat4 << " - " << rat5 << " = \n";
	std::cout << "Expected: -5/6\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	int x = 5;
	result = x - rat;
	std::cout << x << " - " << rat << " = \n";
	std::cout << "Expected: 21/5\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_mul() {
	std::cout << "Test case test_mul:\n";
	rational_t rat1(12, 4);
	rational_t rat2(3, 2);
	rational_t result = rat1 * rat2;
	std::cout << rat1 << " * " << rat2 << " = \n";
	std::cout << "Expected: 9/2\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t rat3(0, 1);
	result = rat1 * rat3;
	std::cout << rat1 << " * " << rat3 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	result = rat3 * rat1;
	std::cout << rat3 << " * " << rat1 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t rat4(7, -8);
	rational_t rat5(-5, 3);
	std::cout << rat4 << " * " << rat5 << " = \n";
	rat4 *= rat5;
	std::cout << "Expected: 35/24\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	int x = 13;
	result = x * rat5;
	std::cout << x << " * " << rat5 << " = \n";
	std::cout << "Expected: -65/3\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_div() {
	std::cout << "Test case test_div:\n";
	rational_t rat1(12, 4);
	rational_t rat2(3, 2);
	rational_t result = rat1 / rat2;
	std::cout << rat1 << " / " << rat2 << " = \n";
	std::cout << "Expected: 2/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t rat3(0, 1);
	std::cout << rat1 << " / " << rat3 << " = \n";
	std::cout << "Expected: Divide by Zero Custom Error!\nActual: ";
	try {
		result = rat1 / rat3;
		std::cout << result << "\n";
	}
	catch (DivideByZeroError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "Success\n\n";

	result = rat3 / rat1;
	std::cout << rat3 << " / " << rat1 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t rat4(7, -8);
	rational_t rat5(-5, 3);
	std::cout << rat4 << " / " << rat5 << " = \n";
	rat4 /= rat5;
	std::cout << "Expected: 21/40\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	int x = 13;
	result = x / rat5;
	std::cout << x << " / " << rat5 << " = \n";
	std::cout << "Expected: 39/-5\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}

void test_assignment_op() {
	std::cout << "Test case test_assignment_op:\n";
	rational_t rat(4, 7);
	std::cout << "Expected: " << rat << "\n";
	rational_t rat2 = rat;
	std::cout << "Actual: " << rat2 << "\n";
	std::cout << "Success\n\n";
}

//comparison operators tests
void test_equal_op() {
	std::cout << "Test case test_equal_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(19, 7);
	rational_t rat3(8, 5);
	std::cout << rat.as_string() << " == " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat == rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " == " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat == rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_not_equal_op() {
	std::cout << "Test case test_not_equal_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(19, 7);
	rational_t rat3(8, 5);
	std::cout << rat.as_string() << " != " << rat2.as_string() << "\nExpected: 0 \nActual: " << (rat != rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " != " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat != rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_less_op() {
	std::cout << "Test case test_less_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(22, 7);
	rational_t rat3(8, 5);
	std::cout << rat.as_string() << " < " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat < rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " < " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat < rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_less_or_equal_op() {
	std::cout << "Test case test_less_or_equal_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(19, 7);
	rational_t rat3(8, 5);
	rational_t rat4(8, 2);
	std::cout << rat.as_string() << " <= " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat <= rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " <= " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat <= rat3) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " <= " << rat4.as_string() << "\nExpected: 1 \nActual: " << (rat <= rat4) << "\n";
	std::cout << "Success\n\n";
}
void test_greater_op() {
	std::cout << "Test case test_greater_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(22, 7);
	rational_t rat3(8, 5);
	std::cout << rat.as_string() << " > " << rat2.as_string() << "\nExpected: 0 \nActual: " << (rat > rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " > " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat > rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_greater_or_equal_op() {
	std::cout << "Test case test_greater_or_equal_op:\n";
	rational_t rat(19, 7);
	rational_t rat2(19, 7);
	rational_t rat3(8, 5);
	rational_t rat4(8, 2);
	std::cout << rat.as_string() << " >= " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat >= rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " >= " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat >= rat3) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " >= " << rat4.as_string() << "\nExpected: 0 \nActual: " << (rat >= rat4) << "\n";
	std::cout << "Success\n\n";
}

void test_write_to_stream() {
	std::cout << "Test case test_write_to_stream:\n";
	rational_t rat(24, 6);
	std::cout << "Expected: 24/6\nActual: " << rat << "\n";
	std::cout << "Success\n\n";
	std::ofstream out{ "print_rational.txt" };
	out << rat;
	std::cout << "Printed to print_rational.txt\n";
	std::cout << "Success\n\n";
}

void test_read_from_stream(){
	std::cout << "Test case test_read_from_stream:\n";
	rational_t rat;
	try {
		std::cout << "Expected: ";
		std::cin >> rat;
		std::cout << "Actual: " << rat << "\n";
		std::cout << "Success\n\n";
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}

	std::ifstream in("rational.txt");
	try {
		std::cout << "Expected: 43/8\n";
		in >> rat;
		std::cout << "Actual: " << rat << "\n";
		std::cout << "Success\n\n";
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "\n";
}

//Tests with T=double
void test_constructor1_double() {
	std::cout << "Test case test_constructor1_double:\n";
	std::cout << "Expected: 0.0/1.0\n";
	rational_t<double> rat;
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor2_double() {
	std::cout << "Test case test_constructor2_double:\n";
	std::cout << "Expected: -5.4/1.0\n";
	rational_t<double> rat(-5.4);
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor3_double() {
	std::cout << "Test case test_constructor3_double:\n";
	std::cout << "Expected: 12.1/5.3\n";
	rational_t<double> rat(12.1, 5.3);
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor3_invalid_input_double() {
	std::cout << "Test case test_constructor3_invalid_input_double:\n";
	std::cout << "Expected: Divide by Zero Custom Error!\n";
	try {
		rational_t<double> rat(3.1, 0);
	}
	catch (DivideByZeroError& ex) {
		std::cout << "Actual: " << ex.what() << "\n";
	}
	std::cout << "Success\n\n";
}
void test_copy_constructor_double() {
	std::cout << "Test case test_copy_constructor_double:\n";
	rational_t<double> rat(6.8, 7.3);
	std::cout << "Expected: " << rat << "\n";
	rational_t<double> rat2(rat);
	std::cout << "Actual: " << rat2 << "\n";
	std::cout << "Success\n\n";
}

void test_get_numerator_double() {
	std::cout << "Test case test_get_numerator_double:\n";
	rational_t<double> rat(6.1, 20.5);
	std::cout << rat << "\n";
	std::cout << "Expected: 6.1\nActual: " << rat.get_numerator() << "\n\n";
	std::cout << "Success\n\n";
}
void test_get_denominator_double() {
	std::cout << "Test case test_get_denominator_double:\n";
	rational_t<double> rat(6.1, 20.5);
	std::cout << rat << "\n";
	std::cout << "Expected: 20.5\nActual: " << rat.get_denominator() << "\n\n";
	std::cout << "Success\n\n";
}

//Tests unabhängig T 
template <typename T>
void test_is_negative(rational_t<T> const& rat) {
	std::cout << "Test case test_is_negative:\n";
	if (rat.is_negative()) {
		std::cout << rat.as_string() << " was expected to be negative and is negative.\n";
	}
	else {
		std::cout << rat.as_string() << " was expected not to be negative and isn't negative.\n";
	}
	std::cout << "Success\n\n";
}

template <typename T>
void test_is_positive(rational_t<T> const& rat) {
	std::cout << "Test case test_is_positive:\n";
	if (rat.is_positive()) {
		std::cout << rat.as_string() << " was expected to be positive and is positive.\n";
	}
	else {
		std::cout << rat.as_string() << " was expected not to be positive and isn't positive.\n";
	}
	std::cout << "Success\n\n";
}

template <typename T>
void test_is_zero(rational_t<T> const& rat) {
	std::cout << "Test case test_is_zero:\n";
	if (rat.is_zero()) {
		std::cout << rat.as_string() << " was expected to be zero and is zero.\n";
	}
	else {
		std::cout << rat.as_string() << " was expected not to be zero and isn't zero.\n";
	}
	std::cout << "Success\n\n";
}

void test_inverse_double() {
	std::cout << "Test case test_inverse_double:\n";
	rational_t<double> rat(3.4, -5.6);
	std::cout << rat << "\n";
	rat.inverse();
	std::cout << "Expected: -5.6/3.4\nActual: " << rat << "\n";
	std::cout << "\n";
}

void test_add_double() {
	std::cout << "Test case test_add_double:\n";
	rational_t<double> rat(4.5, 5.8);
	rational_t<double> rat2(-2.2, 3.6);
	rational_t<double> result = rat + rat2;
	std::cout << rat << " + " << rat2 << " = \n";
	std::cout << "Expected: 3.44/20.88\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat3(2.2, 3.6);
	result = rat3 + rat2;
	std::cout << rat3 << " + " << rat2 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat4(0.0, 3.4);
	result = rat2 + rat4;
	std::cout << rat2 << " + " << rat4 << " = \n";
	std::cout << "Expected: -2.2/3.6\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	std::cout << rat4 << " + " << rat2 << " = \n";
	rat4 += rat2;
	std::cout << "Expected: -2.2/3.6\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	double x = 5.7;
	result = x + rat;
	std::cout << x << " + " << rat << " = \n";
	std::cout << "Expected: 37.56/5.8\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_sub_double() {
	std::cout << "Test case test_sub_double:\n";
	rational_t<double> rat(4.5, 5.8);
	rational_t<double> rat2(-2.2, 3.6);
	rational_t<double> result = rat - rat2;
	std::cout << rat << " - " << rat2 << " = \n";
	std::cout << "Expected: 28.96/20.88\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat3(2.2, 3.6);
	std::cout << rat3 << " - " << rat3 << " = \n";
	rat3 -= rat3;
	std::cout << "Expected: 0/1\nActual: " << rat3 << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat4(0.0, 3.4);
	result = rat2 - rat4;
	std::cout << rat2 << " - " << rat4 << " = \n";
	std::cout << "Expected: -2.2/3.6\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat5(5.5, 6.7);
	result = rat4 - rat5;
	std::cout << rat4 << " - " << rat5 << " = \n";
	std::cout << "Expected: -5.5/6.7\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	double x = 5.4;
	result = x - rat;
	std::cout << x << " - " << rat << " = \n";
	std::cout << "Expected: 26.82/5.8\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_mul_double() {
	std::cout << "Test case test_mul_double:\n";
	rational_t<double> rat1(12.5, 4.3);
	rational_t<double> rat2(3.8, 2.48);
	rational_t<double> result = rat1 * rat2;
	std::cout << rat1 << " * " << rat2 << " = \n";
	std::cout << "Expected: 47.5/10.664\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat3(0.0, 1.2);
	result = rat1 * rat3;
	std::cout << rat1 << " * " << rat3 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	result = rat3 * rat1;
	std::cout << rat3 << " * " << rat1 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat4(7.4, -8.6);
	rational_t<double> rat5(-5.3, 3.78);
	std::cout << rat4 << " * " << rat5 << " = \n";
	rat4 *= rat5;
	std::cout << "Expected: 39.22/32.508\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	double x = 13.54;
	result = x * rat5;
	std::cout << x << " * " << rat5 << " = \n";
	std::cout << "Expected: -71.762/3.78\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_div_double() {
	std::cout << "Test case test_div_double:\n";
	rational_t<double> rat1(12.5, 4.3);
	rational_t<double> rat2(3.8, 2.48);
	rational_t<double> result = rat1 / rat2;
	std::cout << rat1 << " / " << rat2 << " = \n";
	std::cout << "Expected: 31/16.34\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat3(0.0, 1.2);
	std::cout << rat1 << " / " << rat3 << " = \n";
	std::cout << "Expected: Divide by Zero Custom Error!\nActual: ";
	try {
		result = rat1 / rat3;
		std::cout << result << "\n";
	}
	catch (DivideByZeroError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "Success\n\n";
	result = rat3 / rat1;
	std::cout << rat3 << " / " << rat1 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<double> rat4(7.4, -8.6);
	rational_t<double> rat5(-5.3, 3.78);
	std::cout << rat4 << " / " << rat5 << " = \n";
	rat4 /= rat5;
	std::cout << "Expected: 27.972/45.58\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	double x = 13.54;
	result = x / rat5;
	std::cout << x << " / " << rat5 << " = \n";
	std::cout << "Expected: 51.1812/-5.3\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}

void test_assignment_op_double() {
	std::cout << "Test case test_assignment_op_double:\n";
	rational_t<double> rat(4.5, 7.2);
	std::cout << "Expected: " << rat << "\n";
	rational_t<double> rat2 = rat;
	std::cout << "Actual: " << rat2 << "\n";
	std::cout << "Success\n\n";
}

//comparison operators tests
void test_equal_op_double() {
	std::cout << "Test case test_equal_op_double:\n";
	rational_t<double> rat(19.5, 7.66);
	rational_t<double> rat2(19.5, 7.66);
	rational_t<double> rat3(19.4, 7.88);
	std::cout << rat.as_string() << " == " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat == rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " == " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat == rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_not_equal_op_double() {
	std::cout << "Test case test_not_equal_op_double:\n";
	rational_t<double> rat(19.5, 7.66);
	rational_t<double> rat2(19.5, 7.66);
	rational_t<double> rat3(19.4, 7.88);
	std::cout << rat.as_string() << " != " << rat2.as_string() << "\nExpected: 0 \nActual: " << (rat != rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " != " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat != rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_less_op_double() {
	std::cout << "Test case test_less_op_double:\n";
	rational_t<double> rat(19.5, 7.2);
	rational_t<double> rat2(22.5, 7.2);
	rational_t<double> rat3(8.4, 5.5);
	std::cout << rat.as_string() << " < " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat < rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " < " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat < rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_less_or_equal_op_double() {
	std::cout << "Test case test_less_or_equal_op_double:\n";
	rational_t<double> rat(19.44, 7.9);
	rational_t<double> rat2(19.44, 7.9);
	rational_t<double> rat3(8.32, 5.4);
	rational_t<double> rat4(8.32, 2.2);
	std::cout << rat.as_string() << " <= " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat <= rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " <= " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat <= rat3) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " <= " << rat4.as_string() << "\nExpected: 1 \nActual: " << (rat <= rat4) << "\n";
	std::cout << "Success\n\n";
}
void test_greater_op_double() {
	std::cout << "Test case test_greater_op_double:\n";
	rational_t<double> rat(19.5, 7.2);
	rational_t<double> rat2(22.5, 7.2);
	rational_t<double> rat3(8.4, 5.5);
	std::cout << rat.as_string() << " > " << rat2.as_string() << "\nExpected: 0 \nActual: " << (rat > rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " > " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat > rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_greater_or_equal_op_double() {
	std::cout << "Test case test_greater_or_equal_op_double:\n";
	rational_t<double> rat(19.44, 7.9);
	rational_t<double> rat2(19.44, 7.9);
	rational_t<double> rat3(8.32, 5.4);
	rational_t<double> rat4(8.32, 2.2);
	std::cout << rat.as_string() << " >= " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat >= rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " >= " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat >= rat3) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " >= " << rat4.as_string() << "\nExpected: 0 \nActual: " << (rat >= rat4) << "\n";
	std::cout << "Success\n\n";
}

void test_write_to_stream_double() {
	std::cout << "Test case test_write_to_stream_double:\n";
	rational_t<double> rat(24.8, 6.77);
	std::cout << "Expected: 24.8/6.77\nActual:" << rat << "\n";
	std::cout << "Success\n";
	std::ofstream out{ "print_rational_double.txt" };
	out << rat;
	std::cout << "Printed to print_rational_double.txt\n";
	std::cout << "Success\n\n";
}

void test_read_from_stream_double() {
	std::cout << "Test case test_read_from_stream_double:\n";
	rational_t<double> rat;
	try {
		std::cout << "Expected: ";
		std::cin >> rat;
		std::cout << "Actual: " << rat << "\n";
		std::cout << "Success\n\n";
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}

	std::ifstream in("rational_double.txt");
	try {
		std::cout << "Expected: 2.5/7.8 \n";
		in >> rat;
		std::cout << "Actual: " << rat << "\n";
		std::cout << "Success\n\n";
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "\n";
}

//Tests with T=number_t<int>
void test_constructor1_number_t() {
	std::cout << "Test case test_constructor1_number_t:\n";
	std::cout << "Expected: 0/1\n";
	rational_t<number_t<int>> rat;
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor2_number_t() {
	std::cout << "Test case test_constructor2_number_t:\n";
	std::cout << "Expected: -5/1\n";
	rational_t<number_t<int>> rat(-5);
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor3_number_t() {
	std::cout << "Test case test_constructor3_number_t:\n";
	std::cout << "Expected: 12/5\n";
	rational_t<number_t<int>> rat(12, 5);
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}
void test_constructor3_invalid_input_number_t() {
	std::cout << "Test case test_constructor3_invalid_input_number_t:\n";
	std::cout << "Expected: Divide by Zero Custom Error!\n";
	try {
		rational_t<number_t<int>> rat(3, 0);
	}
	catch (DivideByZeroError& ex) {
		std::cout << "Acutal: " << ex.what() << "\n";
	}
	std::cout << "Success\n\n";
}
void test_copy_constructor_number_t() {
	std::cout << "Test case test_copy_constructor_number_t:\n";
	rational_t<number_t<int>> rat(6, 7);
	std::cout << "Expected: " << rat << "\n";
	rational_t<number_t<int>> rat2(rat);
	std::cout << "Actual: " << rat2 << "\n";
	std::cout << "Success\n\n";
}

void test_get_numerator_number_t() {
	std::cout << "Test case test_get_numerator_number_t:\n";
	rational_t<number_t<int>> rat(6, 20);
	std::cout << rat << "\n";
	std::cout << "Expected: 6\n";
	std::cout << "Actual: " << rat.get_numerator() << "\n";
	std::cout << "Success\n\n";
}
void test_get_denominator_number_t() {
	std::cout << "Test case test_get_denominator_number_t:\n";
	rational_t<number_t<int>> rat(6, 20);
	std::cout << rat << "\nExpected: 20\n";
	std::cout << "Actual: " << rat.get_denominator() << "\n";
	std::cout << "Success\n\n";
}
void test_inverse_number_t() {
	std::cout << "Test case test_inverse_number_t:\n";
	rational_t<number_t<int>> rat(3, -5);
	std::cout << rat << "\n";
	std::cout << "Expected: -5/3\n";
	rat.inverse();
	std::cout << "Actual: " << rat << "\n";
	std::cout << "Success\n\n";
}

void test_add_number_t() {
	std::cout << "Test case test_add_number_t:\n";
	rational_t<number_t<int>> rat(4, 5);
	rational_t<number_t<int>> rat2(-2, 3);
	rational_t<number_t<int>> result = rat + rat2;
	std::cout << rat << " + " << rat2 << " = \n";
	std::cout << "Expected: 2/15\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat3(2, 3);
	result = rat3 + rat2;
	std::cout << rat3 << " + " << rat2 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat4(0, 3);
	result = rat2 + rat4;
	std::cout << rat2 << " + " << rat4 << " = \n";
	std::cout << "Expected: -2/3\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	std::cout << rat4 << " + " << rat2 << " = \n"; 
	rat4 += rat2;
	std::cout << "Expected: -2/3\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	int x = 5;
	result = x + rat;
	std::cout << x << " + " << rat << " = \n";
	std::cout << "Expected: 29/5\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_sub_number_t() {
	std::cout << "Test case test_sub_number_t:\n";
	rational_t<number_t<int>> rat(4, 5);
	rational_t<number_t<int>> rat2(-2, 3);
	rational_t<number_t<int>> result = rat - rat2;
	std::cout << rat << " - " << rat2 << " = \n";
	std::cout << "Expected: 22/15\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat3(2, 3);
	std::cout << rat3 << " - " << rat3 << " = \n";
	rat3 -= rat3;
	std::cout << "Expected: 0/1\nActual: " << rat3 << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat4(0, 3);
	result = rat2 - rat4;
	std::cout << rat2 << " - " << rat4 << " = \n";
	std::cout << "Expected: -2/3\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat5(5, 6);
	result = rat4 - rat5;
	std::cout << rat4 << " - " << rat5 << " = \n";
	std::cout << "Expected: -5/6\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	int x = 5;
	result = x - rat;
	std::cout << x << " - " << rat << " = \n";
	std::cout << "Expected: 21/5\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_mul_number_t() {
	std::cout << "Test case test_mul_number_t:\n";
	rational_t<number_t<int>> rat1(12, 4);
	rational_t<number_t<int>> rat2(3, 2);
	rational_t<number_t<int>> result = rat1 * rat2;
	std::cout << rat1 << " * " << rat2 << " = \n";
	std::cout << "Expected: 9/2\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat3(0, 1);
	result = rat1 * rat3;
	std::cout << rat1 << " * " << rat3 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	result = rat3 * rat1;
	std::cout << rat3 << " * " << rat1 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat4(7, -8);
	rational_t<number_t<int>> rat5(-5, 3);
	std::cout << rat4 << " * " << rat5 << " = \n";
	rat4 *= rat5;
	std::cout << "Expected: 35/24\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	int x = 13;
	result = x * rat5;
	std::cout << x << " * " << rat5 << " = \n";
	std::cout << "Expected: -65/3\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}
void test_div_number_t() {
	std::cout << "Test case test_div_number_t:\n";
	rational_t<number_t<int>> rat1(12, 4);
	rational_t<number_t<int>> rat2(3, 2);
	rational_t<number_t<int>> result = rat1 / rat2;
	std::cout << rat1 << " / " << rat2 << " = \n";
	std::cout << "Expected: 2/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat3(0, 1);
	std::cout << rat1 << " / " << rat3 << " = \n";
	std::cout << "Expected: Divide by Zero Custom Error!\nActual: ";
	try {
		result = rat1 / rat3;
		std::cout << result << "\n";
	}
	catch (DivideByZeroError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "Success\n\n";

	result = rat3 / rat1;
	std::cout << rat3 << " / " << rat1 << " = \n";
	std::cout << "Expected: 0/1\nActual: " << result << "\n";
	std::cout << "Success\n\n";

	rational_t<number_t<int>> rat4(7, -8);
	rational_t<number_t<int>> rat5(-5, 3);
	std::cout << rat4 << " / " << rat5 << " = \n";
	rat4 /= rat5;
	std::cout << "Expected: 21/40\nActual: " << rat4 << "\n";
	std::cout << "Success\n\n";

	int x = 13;
	result = x / rat5;
	std::cout << x << " / " << rat5 << " = \n";
	std::cout << "Expected: 39/-5\nActual: " << result << "\n";
	std::cout << "Success\n\n";
}

void test_assignment_op_number_t() {
	std::cout << "Test case test_assignment_op_number_t:\n";
	rational_t<number_t<int>> rat(4, 7);
	std::cout << "Expected: " << rat << "\n";
	rational_t<number_t<int>> rat2 = rat;
	std::cout << "Actual: " << rat2 << "\n";
	std::cout << "Success\n\n";
}

//comparison operators tests
void test_equal_op_number_t() {
	std::cout << "Test case test_equal_op_number_t:\n";
	rational_t<number_t<int>> rat(19, 7);
	rational_t<number_t<int>> rat2(19, 7);
	rational_t<number_t<int>> rat3(8, 5);
	std::cout << rat.as_string() << " == " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat == rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " == " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat == rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_not_equal_op_number_t() {
	std::cout << "Test case test_not_equal_op_number_t:\n";
	rational_t<number_t<int>> rat(19, 7);
	rational_t<number_t<int>> rat2(19, 7);
	rational_t<number_t<int>> rat3(8, 5);
	std::cout << rat.as_string() << " != " << rat2.as_string() << "\nExpected: 0 \nActual: " << (rat != rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " != " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat != rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_less_op_number_t() {
	std::cout << "Test case test_less_op_number_t:\n";
	rational_t<number_t<int>> rat(19, 7);
	rational_t<number_t<int>> rat2(22, 7);
	rational_t<number_t<int>> rat3(8, 5);
	std::cout << rat.as_string() << " < " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat < rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " < " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat < rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_less_or_equal_op_number_t() {
	std::cout << "Test case test_less_or_equal_op_number_t:\n";
	rational_t<number_t<int>> rat(19, 7);
	rational_t<number_t<int>> rat2(19, 7);
	rational_t<number_t<int>> rat3(8, 5);
	rational_t<number_t<int>> rat4(8, 2);
	std::cout << rat.as_string() << " <= " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat <= rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " <= " << rat3.as_string() << "\nExpected: 0 \nActual: " << (rat <= rat3) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " <= " << rat4.as_string() << "\nExpected: 1 \nActual: " << (rat <= rat4) << "\n";
	std::cout << "Success\n\n";
}
void test_greater_op_number_t() {
	std::cout << "Test case test_greater_op_number_t:\n";
	rational_t<number_t<int>> rat(19, 7);
	rational_t<number_t<int>> rat2(22, 7);
	rational_t<number_t<int>> rat3(8, 5);
	std::cout << rat.as_string() << " > " << rat2.as_string() << "\nExpected: 0 \nActual: " << (rat > rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " > " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat > rat3) << "\n";
	std::cout << "Success\n\n";
}
void test_greater_or_equal_op_number_t() {
	std::cout << "Test case test_greater_or_equal_op_number_t:\n";
	rational_t<number_t<int>> rat(19, 7);
	rational_t<number_t<int>> rat2(19, 7);
	rational_t<number_t<int>> rat3(8, 5);
	rational_t<number_t<int>> rat4(8, 2);
	std::cout << rat.as_string() << " >= " << rat2.as_string() << "\nExpected: 1 \nActual: " << (rat >= rat2) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " >= " << rat3.as_string() << "\nExpected: 1 \nActual: " << (rat >= rat3) << "\n";
	std::cout << "Success\n\n";
	std::cout << rat.as_string() << " >= " << rat4.as_string() << "\nExpected: 0 \nActual: " << (rat >= rat4) << "\n";
	std::cout << "Success\n\n";
}

void test_write_to_stream_number_t() {
	std::cout << "Test case test_write_to_stream_number_t:\n";
	rational_t<number_t<int>> rat(24, 6);
	std::cout << "Expected: 24/6\nActual: " << rat << "\n";
	std::cout << "Success\n";
	std::ofstream out{ "print_rational_number_t.txt" };
	out << rat;
	std::cout << "Printed to print_rational_number_t.txt\nSuccess\n\n";
}

void test_read_from_stream_number_t() {
	std::cout << "Test case test_read_from_stream_number_t:\n";
	rational_t<number_t<>> rat;
	try {
		std::cout << "Expected: ";
		std::cin >> rat;
		std::cout << "Actual: " << rat << "\n";
		std::cout << "Success\n\n";
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}

	std::ifstream in("rational_number_t.txt");
	try {
		std::cout << "Expected: 4/7\n";
		in >> rat;
		std::cout << "Actual: " << rat << "\n";
		std::cout << "Success\n\n";
	}
	catch (InvalidInputError& ex) {
		std::cout << ex.what() << "\n";
	}
	std::cout << "\n";
}