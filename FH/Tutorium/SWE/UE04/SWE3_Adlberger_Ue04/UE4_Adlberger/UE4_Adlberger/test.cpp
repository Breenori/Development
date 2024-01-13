#include "test.h"
#include "rational_t.h"
#include "number_t.h"
#include <string>


void test_addition() {
	rational_t<> a(3, 7);
	rational_t<>b(-5, -6);
	a.add(b);
	print_result(a);

}
void test_sub() {
	rational_t<> a(3, 7);
	rational_t<> b(5, -6);
	a.sub(b);
	print_result(a);
}

void test_multiplication() {
	rational_t<> a(5, -2);
	rational_t<> b(3, 4);
	a.mul(b);
	print_result(a);
}
void test_division() {
	rational_t<> a(2, 1);
	rational_t<> b(1, -2);
	a.div(b);
	print_result(a);
}


//number_t <int> tests
void test_addition_num() {
	rational_t<number_t<int>>a(3, 7);
	rational_t<number_t<int>>b(-5, -6);
	a.add(b);

	print_result(a);

}
void test_subtraction_num() {
	rational_t<number_t<int>>a(3, 7);
	rational_t<number_t<int>>b(5, -6);
	a.sub(b);
	print_result(a);

}
void test_multiplication_num() {
	rational_t<number_t<int>>a(5, -2);
	rational_t<number_t<int>>b(3, 4);
	a.mul(b);
	print_result(a);
}

void test_division_num() {
	rational_t<number_t<int>>a(2, 1);
	rational_t<number_t<int>>b(1, -2);
	a.div(b);
	print_result(a);
}
void test_number_t() {
	test_addition_num();
	test_subtraction_num();
	test_multiplication_num();
	test_division_num();
}

void test_concept() {

//	rational_t<std::string> a('s', 't');
	
}

void test_same() {
	// same
	rational_t <number_t<int>> a(1, 3);
	rational_t<number_t<int>> b(1, 3);
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
	rational_t<number_t<int>> c(1, 3);
	rational_t<number_t<int>> d(-1, 3);
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
	rational_t<number_t<int>> a(1, 3);
	rational_t<number_t<int>> b(1, 3);
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
	rational_t<number_t<int>> c(1, 3);
	rational_t<number_t<int>> d(-1, 3);
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
	rational_t<number_t<int>> a(1, 3);
	rational_t<number_t<int>> b(1, 2);
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
	rational_t<number_t<int>> c(1, 3);
	rational_t<number_t<int>> d(-1, 3);
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
	rational_t<number_t<int>> a(1, 3);
	rational_t<number_t<int>> b(1, 3);
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
	rational_t<number_t<int>> c(1, 3);
	rational_t<number_t<int>> d(-1, 3);
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
	rational_t<number_t<int>> a(1, 3);
	rational_t<number_t<int>> b(1, 2);
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
	rational_t<number_t<int>> c(1, 3);
	rational_t<number_t<int>> d(-1, 3);
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
	rational_t<number_t<int>> a(1, 3);
	rational_t<number_t<int>> b(1, 3);
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
	rational_t<number_t<int>> c(1, 3);
	rational_t<number_t<int>> d(1, 2);
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
void test_number_class() {
	 test_same();
	 test_different();
	 test_smaller();
	 test_smaller_same();
	 test_bigger();
	 test_bigger_same();


}

void test_addition_op_ass() {
	rational_t<> a(3, 7);
	rational_t<> b(-5, -6);
	a += b;
	print_result(a);
}
void test_addition_op() {
	rational_t<> a(3, 7);
	rational_t<> b(-5, -6);
	rational_t<> c = a + b;
	print_result(c);
}
void test_subtraction_op() {
	rational_t<> a(3, 7);
	rational_t<> b(5, -6);
	rational_t<> c = a - b;
	print_result(c);
}
void test_multiplication_op() {
	rational_t<> a(5, -2);
	rational_t<> b(3, 4);
	rational_t<> c = a * b;
	print_result(c);

}
void test_division_op() {
	rational_t<> a(2, 1);
	rational_t<> b(1, -2);
	rational_t<> c = a / b;
	print_result(c);

}


void test_sub_op_ass() {
	rational_t<> a(3, 7);
	rational_t<> b(5, -6);
	a -= b;
	print_result(a);
}
void test_multiplication_op_ass() {
	rational_t<> a(5, -2);
	rational_t<> b(3, 4);
	a *= b;
	print_result(a);
}
void test_division_op_ass() {
	rational_t<> a(2, 1);
	rational_t<> b(1, -2);
	a /= b;
	print_result(a);
}

void test_addition_op_int() {
	rational_t<number_t<int>> a(2, 1);
	int b(21);  //convert 
	rational_t<number_t<int>> c = b+ a;
	//c = b + a;
	print_result(c);
}
void test_sub_op_int() {
	rational_t<number_t<int>> a(2, 1);
	int b(1);  //convert 
	rational_t<number_t<int>> c = b - a;

	print_result(c);
}
void test_mul_op_int() {
	rational_t<number_t<int>> a(2, 1);
	int b(2);  //convert 
	rational_t<number_t<int>> c = b * a;

	print_result(c);
}
void test_div_op_int() {
	rational_t<number_t<int>> a(2, 1);
	int b(2);  //convert 
	rational_t<number_t<int>> c = b / a;

	print_result(c);
}
void test_operators() {
	 test_addition_op();
	 test_subtraction_op();
	 test_multiplication_op();
	 test_division_op();
	 std::cout << "op assign:\n";
	//op assign
	 test_addition_op_ass();
	 test_sub_op_ass();
	 test_multiplication_op_ass();
	 test_division_op_ass();
	 //with int
	 std::cout << "op with int:\n";
	  test_addition_op_int();
	  test_sub_op_int();
	  test_mul_op_int();
	  test_div_op_int();
}

void test_inverse() {
	rational_t<number_t<int>> b(1, 3);
	print_result(b);
	std::cout << "--->";
	b.inverse();
	print_result(b);
}




//scan
void test_read_file_not_valid_file() {
	rational_t<> a(1, 1);

	std::ifstream input("new.tt");
	input >> a;
	print_result(a);
}
void test_read_file_valid() {
	rational_t<> a(1, 1);

	std::ifstream input("new.txt");
	input >> a;
	print_result(a);
}
void test_read_file_false1() {
	rational_t<> a(1, 1);

	std::ifstream input("false1.txt");
	input >> a;
	print_result(a);
}
void test_read_file_false2() {
	rational_t<> a(1, 1);

	std::ifstream input("false2.txt");
	input >> a;
	print_result(a);
}
