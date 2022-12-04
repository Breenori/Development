#include "test.h"
#include<fstream>

void test_addition() {
	rational_t a(3, 7);
	rational_t b(-5, -6);
	a.add(b);
	print_result(a);
}
void test_sub() {
	rational_t a(3, 7);
	rational_t b(5, -6);
	a.sub(b);
	print_result(a);
}
void test_sub_is_null() {
	rational_t a(3, 7);
	rational_t b(3, 7);
	a.sub(b);
	print_result(a);
}
void test_multiplication() {
	rational_t a(5, -2);
	rational_t b(3, 4);
	a.mul(b);
	print_result(a);
}
void test_division() {
	rational_t a(2, 1);
	rational_t b(1, -2);
	a.div(b);
	print_result(a);
}

void test_addition_op() {
	rational_t a(3, 7);
	rational_t b(-5, -6);
	rational_t c = a + b;
	print_result(c);
}
void test_subtraction_op() {
	rational_t a(3, 7);
	rational_t b(5, -6);
	rational_t c = a - b;
	print_result(c);
}
void test_multiplication_op() {
	rational_t a(5, -2);
	rational_t b(3, 4);
	rational_t c = a * b;
	print_result(c);

}
void test_division_op() {
	rational_t a(2, 1);
	rational_t b(1, -2);
	rational_t c = a / b;
	print_result(c);

}

void test_addition_op_ass() {
	rational_t a(3, 7);
	rational_t b(-5, -6);
	a += b;
	print_result(a);
}
void test_sub_op_ass() {
	rational_t a(3, 7);
	rational_t b(5, -6);
	a -= b;
	print_result(a);
}
void test_multiplication_op_ass() {
	rational_t a(5, -2);
	rational_t b(3, 4);
	a *= b;
	print_result(a);
}
void test_division_op_ass() {
	rational_t a(2, 1);
	rational_t b(1, -2);
	a /= b;
	print_result(a);
}

void test_addition_op_int() {
	rational_t a(2, 1);
	int b(21);  //convert 
	rational_t c = a + b;
	//c = b + a;
	print_result(c);
}
void test_sub_op_int() {
	rational_t a(2, 1);
	int b(1);  //convert 
	rational_t c = a - b;

	print_result(c);
}
void test_mul_op_int() {
	rational_t a(2, 1);
	int b(2);  //convert 
	rational_t c = a *b;

	print_result(c);
}
void test_div_op_int() {
	rational_t a(2, 1);
	int b(2);  //convert 
	rational_t c = a / b;

	print_result(c);
}
void test_divide_by_zero() {
	rational_t a(2, 1);
	rational_t b(0, 0);

	try {
		rational_t c = a / b;
		print_result(c);
	}
	catch (DivideByZeroError& e) {
		std::cout << "Div by zero:" << e.what();
	}
	std::cout << "PRoceeding with execution...\n\n";

}
void test_same() {
	// same
	rational_t a(1, 3);
	rational_t b(1, 3);
	if (a == b) {
		print_result(a);
		std::cout << " Is the same as";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	else {
		print_result(a);
		std::cout << " Is not same as";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	//not the same
	rational_t c(1, 3);
	rational_t d(-1, 3);
	if (c == d) {
		print_result(c);
		std::cout << " Is the same as\n";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
		
	}
	
	else {
		print_result(c);
		std::cout << " Is not same as";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}
}
void test_different() {
	// different
	rational_t a(1, 3);
	rational_t b(1, 3);
	if (a != b) {
		print_result(a);
		std::cout << " Is different as";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	else {
		print_result(a);
		std::cout << " Is not different as";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	//not the same
	rational_t c(1, 3);
	rational_t d(-1, 3);
	if (c != d) {
		print_result(c);
		std::cout << " Is  different as\n";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";

	}

	else {
		print_result(c);
		std::cout << " Is not different as";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}

}
void test_smaller() {
	rational_t a(1, 3);
	rational_t b(1, 2);
	if (a < b) {
		print_result(a);
		std::cout << " Is smaller than";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	else {
		print_result(a);
		std::cout << " Is not smaller than";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	//not smaller
	rational_t c(1, 3);
	rational_t d(-1, 3);
	if (c < d) {
		print_result(c);
		std::cout << " Is smaller than";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}
	else {
		print_result(c);
		std::cout << " Is not smaller than";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}

}
void test_smaller_same() {
	rational_t a(1, 3);
	rational_t b(1, 3);
	if (a <= b) {
		print_result(a);
		std::cout << " Is <=";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	else {
		print_result(a);
		std::cout << " Is <=";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	//smaller/same
	rational_t c(1, 3);
	rational_t d(-1, 3);
	if (c <= d) {
		print_result(c);
		std::cout << " Is <=";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}
	else {
		print_result(c);
		std::cout << " Is not  <= ";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}
}
void test_bigger() {
	rational_t a(1, 3);
	rational_t b(1, 2);
	if (a > b) {
		print_result(a);
		std::cout << " Is bigger than";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	else {
		print_result(a);
		std::cout << " Is not bigger than";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	//bigger
	rational_t c(1, 3);
	rational_t d(-1, 3);
	if (c > d) {
		print_result(c);
		std::cout << " Is bigger than";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}
	else {
		print_result(c);
		std::cout << " Is not bigger than";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}
}
void test_bigger_same() {
	rational_t a(1, 3);
	rational_t b(1, 3);
	if (a >= b) {
		print_result(a);
		std::cout << " Is >= ";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	else {
		print_result(a);
		std::cout << " Is not >= ";
		std::cout << "\n";
		print_result(b);
		std::cout << "\n";
	}
	//not  bigger/same
	rational_t c(1, 3);
	rational_t d(1, 2);
	if (c >= d) {
		print_result(c);
		std::cout << "  Is  >= ";;
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}
	else {
		print_result(c);
		std::cout << "  Is not >= ";
		std::cout << "\n";
		print_result(d);
		std::cout << "\n";
	}
}

void test_read_file_not_valid_file() {
	rational_t a(1,1);

	std::ifstream input("new.tt");
	input >> a;
	print_result(a);
}
void test_read_file_valid() {
	rational_t a(1, 1);

	std::ifstream input("new.txt");
	input >> a;
	print_result(a);
}
void test_read_file_false1() {
	rational_t a(1, 1);

	std::ifstream input("false1.txt");
	input >> a;
	print_result(a);
}
void test_read_file_false2() {
	rational_t a(1, 1);

	std::ifstream input("false2.txt");
	input >> a;
	print_result(a);
}
void test_output_negativ() {
	rational_t a(-1, -1);
	print_result(a);
	std::cout << "optimized:";
	a.optimize();
	print_result(a);
}
void test_output_normalize() {
	rational_t a(6, 3);
	print_result(a);
	std::cout << "optimized:";
	a.optimize();
	print_result(a);
}
void test_output_null1() {
	rational_t a(1, 0);
	std::cout << "\n";
	print_result(a);
	std::cout << "optimized:";
	a.optimize();
	print_result(a);
}
void test_output_null2() {
	rational_t a(0, 1);
	print_result(a);
	std::cout << "optimized:";
	a.optimize();
	print_result(a);

}
void test_integer_1() {
	rational_t a(4, 2);
	print_result(a);
	std::cout << "optimized:";
	a.optimize();
	print_result(a);
}
void test_integer_2() {
	rational_t a(5, -5);
	print_result(a);
	std::cout << "optimized:";
	a.optimize();
	print_result(a);
}