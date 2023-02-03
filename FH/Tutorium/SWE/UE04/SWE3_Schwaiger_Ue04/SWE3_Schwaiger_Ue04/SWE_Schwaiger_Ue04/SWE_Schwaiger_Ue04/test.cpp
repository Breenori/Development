#include "test.h"


void print_result(rational_t<int> const& other) {
	cout << other.as_string() << "\n";
}


void test_add() {
	rational_t a(1, 5);
	rational_t b(5, 3);
	a.add(b);
	print_result(a);
}
void test_sub() {
	rational_t a(3, 7);
	rational_t b(1, 4);
	a.sub(b);
	print_result(a);
}
void test_mul() {
	rational_t a(4, 3);
	rational_t b(5, 2);
	a.mul(b);
	print_result(a);
}
void test_div() {
	rational_t a(2, 4);
	rational_t b(1, 2);
	a.div(b);
	print_result(a);
}

void test_add_input() {
	cout << "Add\n";
	rational_t a(1, 5);
	rational_t b;
	b.scan();
	try {
		rational_t c = a + b;
		print_result(c);
	}
	catch (std::exception& e) {
		cout << e.what() << "\n";
	}
	cout << "Proceeding with execution... \n\n";

}
void test_sub_input() {
	cout << "Sub\n";
	rational_t a(3, 7);
	rational_t b;
	b.scan();
	try {
		rational_t c = a - b;
		print_result(c);
	}
	catch (std::exception& e) {
		cout << e.what() << "\n";
	}
	cout << "Proceeding with execution... \n\n";

}
void test_mul_input() {
	cout << "Mul\n";
	rational_t a(4, 3);
	rational_t b;
	b.scan();
	try {
		rational_t c = a * b;
		print_result(c);
	}
	catch (std::exception& e) {
		cout << e.what() << "\n";
	}
	cout << "Proceeding with execution... \n\n";

}
void test_div_input() {
	cout << "Div\n";
	rational_t a(2, 4);
	rational_t b;
	b.scan();
	try {
		rational_t c = a / b;
		print_result(c);
	}
	catch (std::exception& e) {
		cout << e.what() << "\n";
	}
	cout << "Proceeding with execution... \n\n";
}


void test_add_op() {
	rational_t a(1, 5);
	rational_t b(5, 3);
	rational_t c = a + b;
	print_result(c);
}
void test_sub_op() {
	rational_t a(3, 7);
	rational_t b(1, 4);
	rational_t c = a - b;
	print_result(c);
}
void test_mul_op() {
	rational_t a(4, 3);
	rational_t b(5, 2);
	rational_t c = a * b;
	print_result(c);
}
void test_div_op() {
	rational_t a(2, 4);
	rational_t b(1, 2);
	rational_t c = a / b;
	print_result(c);
}

void test_add_pass() {
	rational_t a(1, 5);
	rational_t b(5, 3);
	a += b;
	print_result(a);
}
void test_sub_pass() {
	rational_t a(3, 7);
	rational_t b(1, 4);
	a -= b;
	print_result(a);
}
void test_mul_pass() {
	rational_t a(4, 3);
	rational_t b(5, 2);
	a *= b;
	print_result(a);
}
void test_div_pass() {
	rational_t a(2, 4);
	rational_t b(1, 2);
	a /= b;
	print_result(a);
}

void test_compare() {
	rational_t a(1, 3);
	rational_t b(1, 3);
	a.compare(b);
}
void test_not_compare() {
	rational_t a(1, 3);
	rational_t b(2, 3);
	a.not_compare(b);
}
void test_smaller_than() {
	rational_t a(1, 3);
	rational_t b(6, 7);
	a.smaller_than(b);
}
void test_greater_than() {
	rational_t a(5, 6);
	rational_t b(1, 3);
	a.greater_than(b);

}
void test_smaller() {
	rational_t a(6, 5);
	rational_t b(1, 3);
	a.smaller(b);

}
void test_greater() {
	rational_t a(1, 2);
	rational_t b(1, 3);
	a.greater(b);
}

void test_compare_2() {
	rational_t a(1, 3);
	rational_t b(1, 3);
	a.compare(b);
}
void test_not_compare_2() {
	rational_t a(1, 3);
	rational_t b(1, 3);
	a.not_compare(b);
}
void test_smaller_than_2() {
	rational_t a(1, 3);
	rational_t b(1, 3);
	a.smaller_than(b);
}
void test_greater_than_2() {
	rational_t a(6, 3);
	rational_t b(4, 3);
	a.greater_than(b);
}
void test_smaller_2() {
	rational_t a(3, 3);
	rational_t b(2, 3);
	a.smaller(b);
}
void test_greater_2() {
	rational_t a(4, 3);
	rational_t b(1, 3);
	a.greater(b);
}

void test_compare_op() {
	rational_t a(1, 3);
	rational_t b(1, 3);
}
void test_not_compare_op() {
	rational_t a(1, 3);
	rational_t b(2, 3);
}
void test_smaller_than_op() {
	rational_t a(1, 3);
	rational_t b(6, 7);
}
void test_greater_than_op() {
	rational_t a(5, 6);
	rational_t b(1, 3);
}
void test_smaller_op() {
	rational_t a(6, 5);
	rational_t b(1, 3);
}
void test_greater_op() {
	rational_t a(1, 2);
	rational_t b(1, 3);
}

void test_get_numerator() {
	rational_t a(5, 6);
	cout << "Numerator: " << a.get_numerator() << "\n";
}
void test_get_denominator() {
	rational_t a(5, 6);
	cout << "Denominator: " << a.get_denominator() << "\n";
}

void test_is_negative() {
	rational_t a(-1, 5);
	a.is_negative();
}
void test_is_positive() {
	rational_t a(3, 5);
	a.is_positive();
}
void test_is_zero() {
	rational_t a(2, 0);
	a.is_zero();
}


void test_is_negative_2() {
	rational_t a(2, 5);
	a.is_negative();
}
void test_is_positive_2() {
	rational_t a(-1, 3);
	a.is_positive();
}
void test_is_zero_2() {
	rational_t a(1, 1);
	a.is_zero();
}


void test_div_by_zero() {
	rational_t a(2, 4);
	rational_t b(0, 0);
	try {
		rational_t c = a / b;
		print_result(c);
	}
	catch (std::exception& e) {
		cout << e.what() << "\n";
	}
	cout << "Proceeding with execution... \n";
}
void test_div_by_zero_in() {
	rational_t a(2, 4);
	rational_t b;
	b.scan();
	try {
		rational_t c = a / b;
		print_result(c);
	}
	catch (std::exception& e) {
		cout << e.what() << "\n";
	}
	cout << "Proceeding with execution... \n\n";
}

