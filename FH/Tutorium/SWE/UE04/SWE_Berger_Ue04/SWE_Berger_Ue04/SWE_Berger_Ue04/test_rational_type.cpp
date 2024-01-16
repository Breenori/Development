#include "test_rational_type.h"
#include "rational_type.h"

template<typename S>
void print_result(rational_t<S> const& rational_t) {
	std::cout << rational_t << "\n";
}

void test_number(){
	Number<int> a(42);
	Number<double> b(21.42);
	Number<int> c = 72;
	std::cout << "Printing numbers ...\n" << a << "\n" << b << "\n" << c << "\n";
}
void test_inverse() {
	std::cout << "Testing method invers ...\n";
	rational_t<Number<int>> a(3, 4);
	print_result(a);
	a.rational_t::inverse();
	print_result(a);
}

//void test_string() {
//	std::cout << "Testing initialization of string ...\n";
//	rational_t<Number<std::string>>("2", "1");
//
//}

void test_all_calculations() {
	std::cout << "Testing all operation methods: \n";
	rational_t<Number<int>> a1(5, 4);
	rational_t<Number<int>> b1(3, 2);
	rational_t<Number<int>> a2(8, 2);
	rational_t<Number<int>> b2(9, 5);
	rational_t<Number<int>> a3(-5, 12);
	rational_t<Number<int>> b3(4, 3);

	std::cout << "\nAddition: \n";
	test_addition(a1, b1);
	test_addition(a2, b2);
	test_addition(a3, b3);
	std::cout << "\nSubtraction: \n";
	test_subtraction(a1, b1);
	test_subtraction(a2, b2);
	test_subtraction(a3, b3);
	std::cout << "\nMultiplication: \n";
	test_multiplication(a1, b1);
	test_multiplication(a2, b2);
	test_multiplication(a3, b3);
	std::cout << "\nDivision: \n";
	test_division(a1, b1);
	test_division(a2, b2);
	test_division(a3, b3);
}
void test_addition(rational_t<Number<int>> first, rational_t<Number<int>> const& second) {
	first.add(second);
	print_result(first);
}
void test_subtraction(rational_t<Number<int>> first, rational_t<Number<int>> const& second) {
	first.sub(second);
	print_result(first);
}
void test_multiplication(rational_t<Number<int>> first, rational_t<Number<int>> const& second) {
	first.mul(second);
	print_result(first);
}
void test_division(rational_t<Number<int>> first, rational_t<Number<int>> const& second) {
	first.div(second);
	print_result(first);
}

void test_all_calculations_op() {
	std::cout << "\nTesting all operations with overloaded operator: \n";
	rational_t<Number<int>> a1(5, 4);
	rational_t<Number<int>> b1(3, 2);
	rational_t<Number<int>> a2(8, 2);
	rational_t<Number<int>> b2(9, 5);
	rational_t<Number<int>> a3(-5, 12);
	rational_t<Number<int>> b3(4, 3);

	std::cout << "\nAddition: \n";
	test_addition_op(a1, b1);
	test_addition_op(a2, b2);
	test_addition_op(a3, b3);
	std::cout << "\nSubtraction: \n";
	test_subtraction_op(a1, b1);
	test_subtraction_op(a2, b2);
	test_subtraction_op(a3, b3);
	std::cout << "\nMultiplication: \n";
	test_multiplication_op(a1, b1);
	test_multiplication_op(a2, b2);
	test_multiplication_op(a3, b3);
	std::cout << "\nDivision: \n";
	test_division_op(a1, b1);
	test_division_op(a2, b2);
	test_division_op(a3, b3);
}
void test_addition_op(rational_t<Number<int>> const& first, rational_t<Number<int>> const& second) {
	rational_t<Number<int>> c = first + second;
	print_result(c);
}
void test_subtraction_op(rational_t<Number<int>> const& first, rational_t<Number<int>> const& second) {
	rational_t<Number<int>> c = first - second;
	print_result(c);
}
void test_multiplication_op(rational_t<Number<int>> const& first, rational_t<Number<int>> const& second) {
	rational_t<Number<int>> c = first * second;
	print_result(c);
}
void test_division_op(rational_t<Number<int>> const& first, rational_t<Number<int>> const& second) {
	rational_t<Number<int>> c = first / second;
	print_result(c);
}

void test_all_calculations_op_assign() {
	std::cout << "Testing all operations with overloaded assign and operator: \n";
	rational_t<Number<int>> a1(5, 4);
	rational_t<Number<int>> b1(3, 2);
	rational_t<Number<int>> a2(8, 2);
	rational_t<Number<int>> b2(9, 5);
	rational_t<Number<int>> a3(-5, 12);
	rational_t<Number<int>> b3(4, 3);

	std::cout << "\nAddition: \n";
	test_addition_op_assign(a1, b1);
	test_addition_op_assign(a2, b2);
	test_addition_op_assign(a3, b3);
	std::cout << "\nSubtraction: \n";
	test_subtraction_op_assign(a1, b1);
	test_subtraction_op_assign(a2, b2);
	test_subtraction_op_assign(a3, b3);
	std::cout << "\nMultiplication: \n";
	test_multiplication_op_assign(a1, b1);
	test_multiplication_op_assign(a2, b2);
	test_multiplication_op_assign(a3, b3);
	std::cout << "\nDivision: \n";
	test_division_op_assign(a1, b1);
	test_division_op_assign(a2, b2);
	test_division_op_assign(a3, b3);
}
void test_addition_op_assign(rational_t<Number<int>> first, rational_t<Number<int>> second) {
	first += second;
	print_result(first);
}
void test_subtraction_op_assign(rational_t<Number<int>> first, rational_t<Number<int>> second) {
	first -= second;
	print_result(first);
}
void test_multiplication_op_assign(rational_t<Number<int>> first, rational_t<Number<int>> const& second) {
	first *= second;
	print_result(first);
}
void test_division_op_assign(rational_t<Number<int>> first, rational_t<Number<int>> const& second) {
	first /= second;
	print_result(first);
}

void test_all_logical_operators() {
	std::cout << "Testing all logical operators: \n";
	std::cout << "\nTesting equal (==): \n";
	test_equal();
	std::cout << "\nTesting unequal (!=): \n";
	test_unequal();
	std::cout << "\nTesting smaller (<): \n";
	test_smaller();
	std::cout << "\nTesting smaller or equal (<=): \n";
	test_smaller_or_equal();
	std::cout << "\nTesting bigger (>): \n";
	test_bigger();
	std::cout << "\nTesting bigger or equal (>=): \n";
	test_bigger_or_equal();

}
void test_equal() {
	rational_t<Number<int>> a(5, 4);
	rational_t<Number<int>> b(3, 2);
	rational_t<Number<int>> c(10, 8);

	if (a == b) {
		std::cout << "a" << a << " is the same as b" << b << "\n";
	}
	else {
		std::cout << "a" << a << " is not the same as b" << b << "\n";
	}
	if (a == c) {
		std::cout << "a" << a << " is the same as c" << c << "\n";
	}
	else {
		std::cout << "a" << a << " is not the same as c" << c << "\n";
	}
}
void test_unequal() {
	rational_t<Number<int>> a(5, 4);
	rational_t<Number<int>> b(3, 2);
	rational_t<Number<int>> c(10, 8);

	if (a != b) {
		std::cout << "a" << a << " is not the same as b" << b << "\n";
	}
	else {
		std::cout << "a" << a << " is the same as b" << b << "\n";
	}
	if (a != c) {
		std::cout << "a" << a << " is not the same as c" << c << "\n";
	}
	else {
		std::cout << "a" << a << " is the same as c" << c << "\n";
	}
}
void test_smaller() {
	rational_t<Number<int>> a(2, 3);
	rational_t<Number<int>> b(5, 4);
	rational_t<Number<int>> c(1, 8);

	if (a < b) {
		std::cout << "a" << a << " is smaller than b" << b << "\n";
	}
	else {
		std::cout << "a" << a << " is not smaller than b" << b << "\n";
	}
	if (a < c) {
		std::cout << "a" << a << " is smaller than c" << c << "\n";
	}
	else {
		std::cout << "a" << a << " is not smaller than c" << c << "\n";
	}
}
void test_smaller_or_equal() {
	rational_t<Number<int>> a(2, 3);
	rational_t<Number<int>> b(4, 6);
	rational_t<Number<int>> c(7, 8);

	if (a <= b) {
		std::cout << "a" << a << " is smaller or equal b" << b << "\n";
	}
	if (a <= c) {
		std::cout << "a" << a << " is smaller or equal c" << c << "\n";
	}
}
void test_bigger() {
	rational_t<Number<int>> a(2, 3);
	rational_t<Number<int>> b(5, 4);
	rational_t<Number<int>> c(1, 8);

	if (a > b) {
		std::cout << "a" << a << " is bigger than b" << b << "\n";
	}
	else {
		std::cout << "a" << a << " is not bigger than b" << b << "\n";
	}
	if (a > c) {
		std::cout << "a" << a << " is bigger than c" << c << "\n";
	}
	else {
		std::cout << "a" << a << " is not bigger than c" << c << "\n";
	}
}
void test_bigger_or_equal() {
	rational_t<Number<int>> a(2, 3);
	rational_t<Number<int>> b(4, 6);
	rational_t<Number<int>> c(1, 8);

	if (a >= b) {
		std::cout << "a" << a << " is bigger or equal b" << b << "\n";
	}
	if (a >= c) {
		std::cout << "a" << a << " is bigger or equal c" << c << "\n";
	}
}

void test_divide_by_zero() {
	rational_t<Number<int>> a(2, 1);
	rational_t<Number<int>> b(0, 0);
	try {
		b.div(a);

	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}
	std::cout << "Processing with execution ... \n\n";
}
