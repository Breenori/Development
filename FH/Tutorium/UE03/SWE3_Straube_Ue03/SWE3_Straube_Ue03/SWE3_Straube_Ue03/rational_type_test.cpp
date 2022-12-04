/*
* ----- Includes. -----
*/
#include "rational_type_test.h"

/*
* ----- Usings. -----
*/
using std::endl;

/*
* ----- Functions. -----
*/

bool test_as_string() {
	cout << "--- test_as_string:" << endl;

	RationalType r(-1, 2);
	cout << "- Output (Expect -1/2): " << r << endl;

	cout << endl;
	return true;
}

bool test_print() {
	cout << "--- test_print:" << endl;

	RationalType r(-1, 2);
	cout << "- Output (Expect -1/2): " << endl; 
	r.print(); cout << endl;

	cout << endl;
	return true;
}

bool test_operatorassignment() {
	cout << "--- test_operatorassignment:" << endl;

	RationalType r(-1, 2);

	// Assign.
	int ti{ 7 };
	r = ti;
	cout << "- Output (Expect 7): " << r << endl;

	// Copy assign.
	RationalType trt(3, 4);
	r = trt;
	cout << "- Output (Expect 3/4): " << r << endl;

	cout << endl;
	return true;
}

bool test_constructor() {
	cout << "--- test_constructor:" << endl;

	RationalType r(-1, 2);
	cout << "- Output (Expect -1/2): " << r << endl;

	RationalType r2;
	cout << "- Output (Expect 0): " << r2 << endl;

	RationalType r3(7);
	cout << "- Output (Expect 7): " << r3 << endl;

	RationalType r4(r);
	cout << "- Output (Expect -1/2): " << r4 << endl;

	cout << "- Output (Expect Error): " << endl;
	try {
		RationalType r5(1, 0);
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}

	cout << endl;
	return true;
}

bool test_scan() {
	cout << "--- test_scan:" << endl;

	RationalType r;

	cout << "User Input (3/4):" << endl; r.scan();
	cout << "- Output (Expect User Input): " << r << endl;

	cout << "User Input (3 4):" << endl; r.scan();
	cout << "- Output (Expect redo): " << r << endl;

	cout << "User Input (3):" << endl; r.scan();
	cout << "- Output (Expect redo): " << r << endl;

	cout << "User Input (3/1):" << endl; r.scan();
	cout << "- Output (Expect User Input): " << r << endl;

	cout << endl;
	return true;
}

bool test_get_numerator() {
	cout << "--- test_get_numerator:" << endl;

	RationalType r(11, 15);
	cout << "- Output (Expect 11): " << r.get_numerator() << endl;

	cout << endl;
	return true;
}

bool test_get_denominator() {
	cout << "--- test_get_denominator:" << endl;

	RationalType r(11, 15);
	cout << "- Output (Expect 15): " << r.get_denominator()<< endl;

	cout << endl;
	return true;
}

bool test_normalize() {
	cout << "--- test_normalize:" << endl;

	RationalType r(3, 15);
	cout << "- Output (Expect 1/5): " << r << endl;

	r = { 42, 28 };
	cout << "- Output (Expect 3/2): " << r << endl;

	r = { 1, -3 };
	cout << "- Output (Expect -1/3): " << r << endl;

	r = { -1, -3 };
	cout << "- Output (Expect 1/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_add() {
	cout << "--- test_add:" << endl;

	RationalType r(4, 3); 
	RationalType r2(1, 3);
	r.add(r2);
	cout << "- Output (Expect 5/3): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.add(r2);
	cout << "- Output (Expect -5/3): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.add(r2);
	cout << "- Output (Expect -1): " << r << endl;

	r = {-1, 3};
	r2 = {1, 3};
	r.add(r2);
	cout << "- Output (Expect 0): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.add(r2);
	cout << "- Output (Expect 11/10): " << r << endl;

	r = {};
	r2 = {};
	r.add(r2);
	cout << "- Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.add(r2);
	cout << "- Output (Expect 4): " << r << endl;

	cout << endl;
	return true;
}

bool test_sub() {
	cout << "--- test_sub:" << endl;

	RationalType r(1, 3);
	RationalType r2(8, 3);
	r.sub(r2);
	cout << "- Output (Expect -7/3): " << r << endl;

	r = { 8, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Output (Expect 7/3): " << r << endl;


	r = { 1, 3 };
	r2 = { -8, 3 };
	r.sub(r2);
	cout << "- Output (Expect 3): " << r << endl;

	r = { 8, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Output (Expect 3): " << r << endl;


	r = { -1, 3 };
	r2 = { -8, 3 };
	r.sub(r2);
	cout << "- Output (Expect 7/3): " << r << endl;

	r = { -8, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Output (Expect -7/3): " << r << endl;


	r = { -1, 3 };
	r2 = { 8, 3 };
	r.sub(r2);
	cout << "- Output (Expect -3): " << r << endl;

	r = { -8, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Output (Expect -3): " << r << endl;


	r = { 1, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Output (Expect 0): " << r << endl;

	r = { 1, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Output (Expect 2/3): " << r << endl;


	r = { 0, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Output (Expect -1/3): " << r << endl;

	r = { -1, 3 };
	r2 = { 0, 3 };
	r.sub(r2);
	cout << "- Output (Expect -1/3): " << r << endl;


	r = {};
	r2 = {};
	r.sub(r2);
	cout << "- Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.sub(r2);
	cout << "- Output (Expect 10): " << r << endl;

	cout << endl;
	return true;
}

bool test_mul() {
	cout << "--- test_mul:" << endl;

	RationalType r(1, 2);
	RationalType r2(1, 3);
	r.mul(r2);
	cout << "- Output (Expect 1/6): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.mul(r2);
	cout << "- Output (Expect 4/9): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.mul(r2);
	cout << "- Output (Expect -4/9): " << r << endl;

	r = { -1, 3 };
	r2 = { 1, 3 };
	r.mul(r2);
	cout << "- Output (Expect -1/9): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.mul(r2);
	cout << "- Output (Expect 6/25): " << r << endl;

	r = {};
	r2 = {};
	r.mul(r2);
	cout << "- Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.mul(r2);
	cout << "- Output (Expect -21): " << r << endl;

	cout << endl;
	return true;
}

bool test_div() {
	cout << "--- test_div:" << endl;

	RationalType r(1, 2);
	RationalType r2(1, 3);
	r.div(r2);
	cout << "- Output (Expect 3/2): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.div(r2);
	cout << "- Output (Expect 4): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.div(r2);
	cout << "- Output (Expect -1/4): " << r << endl;

	r = { -1, 3 };
	r2 = { 1, 3 };
	r.div(r2);
	cout << "- Output (Expect -1): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.div(r2);
	cout << "- Output (Expect 3/8): " << r << endl;


	cout << "- Output (Expect Error): " << endl;
	try {
		r = {};
		r2 = {};
		r.div(r2);
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}

	r = { 7 };
	r2 = { -3 };
	r.div(r2);
	cout << "- Output (Expect -7/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_plus() {
	cout << "--- test_op_plus:" << endl;

	RationalType r(1, 2);
	RationalType r2(1, 3);
	cout << "- Output (Expect 5/6): " << r + r2 << endl;

	int r3 = 3;
	cout << "- Output (Expect 7/2): " << r + r3 << endl;

	cout << "- Output (Expect 7/2): " << r3 + r << endl;

	cout << "- Output (Expect 23/6): " << r3 + r + r2 << endl;

	cout << endl;
	return true;
}

bool test_op_minus() {
	cout << "--- test_op_minus:" << endl;

	RationalType r(1, 2);
	RationalType r2(1, 3);
	cout << "- Output (Expect 1/6): " << r - r2 << endl;

	int r3 = 3;
	cout << "- Output (Expect -5/2): " << r - r3 << endl;

	cout << "- Output (Expect 5/2): " << r3 - r << endl;

	cout << "- Output (Expect 13/6): " << r3 - r - r2 << endl;

	cout << endl;
	return true;
}

bool test_op_mult() {
	cout << "--- test_op_mult:" << endl;

	RationalType r(1, 2);
	RationalType r2(1, 3);
	cout << "- Output (Expect 1/6): " << r * r2 << endl;

	int r3 = 3;
	cout << "- Output (Expect 3/2): " << r * r3 << endl;

	cout << "- Output (Expect 3/2): " << r3 * r << endl;

	cout << "- Output (Expect 1/2): " << r3 * r * r2 << endl;

	cout << endl;
	return true;
}

bool test_op_divi() {
	cout << "--- test_op_divi:" << endl;

	RationalType r(1, 2);
	RationalType r2(1, 3);
	cout << "- Output (Expect 3/2): " << r / r2 << endl;

	int r3 = 3;
	cout << "- Output (Expect 1/6): " << r / r3 << endl;

	cout << "- Output (Expect 6): " << r3 / r << endl;

	cout << "- Output (Expect 18): " << r3 / r / r2 << endl;

	cout << "- Output (Expect Error): " << endl;
	cout << r / 0 << endl;

	cout << "- Output (Expect 0): " << 0 / r << endl;

	cout << endl;
	return true;
}

bool test_op_plus_assign() {
	cout << "--- test_op_plus_assign:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	r += r2;
	cout << "- Output (Expect 22/15): " << r << endl;

	r = { 1, 3 };
	int r3 = 3;
	r += r3;
	cout << "- Output (Expect 10/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_minus_assign() {
	cout << "--- test_op_minus_assign:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	r -= r2;
	cout << "- Output (Expect 2/15): " << r << endl;

	r = { 1, 3 };
	int r3 = 3;
	r -= r3;
	cout << "- Output (Expect -8/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_mult_assign() {
	cout << "--- test_op_mult_assign:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	r *= r2;
	cout << "- Output (Expect 8/15): " << r << endl;

	r = { 1, 3 };
	int r3 = 3;
	r *= r3;
	cout << "- Output (Expect 1): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_divi_assign() {
	cout << "--- test_op_divi_assign:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	r /= r2;
	cout << "- Output (Expect 6/5): " << r << endl;

	r = { 1, 3 };
	int r3 = 3;
	r /= r3;
	cout << "- Output (Expect 1/9): " << r << endl;

	cout << "- Output (Expect Error): " << endl;
	r /= 0;
	cout << r << endl;

	cout << endl;
	return true;
}

bool test_op_compare_is() {
	cout << "--- test_op_compare_is:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	cout << "- Output (Expect false): " << (r == r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Output (Expect true): " << (r == r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Output (Expect true): " << (r == r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_is_not() {
	cout << "--- test_op_compare_is_not:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	cout << "- Output (Expect true): " << (r != r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Output (Expect false): " << (r != r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Output (Expect false): " << (r != r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_smaller_than() {
	cout << "--- test_op_compare_smaller_than:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	cout << "- Output (Expect false): " << (r < r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Output (Expect false): " << (r < r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Output (Expect false): " << (r < r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_smaller_equal_than() {
	cout << "--- test_op_compare_smaller_equal_than:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	cout << "- Output (Expect false): " << (r <= r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Output (Expect true): " << (r <= r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Output (Expect true): " << (r <= r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_larger_than() {
	cout << "--- test_op_compare_larger_than:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	cout << "- Output (Expect true): " << (r > r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Output (Expect false): " << (r > r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Output (Expect false): " << (r > r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_larger_equal_than() {
	cout << "--- test_op_compare_larger_equal_than:" << endl;

	RationalType r(4, 5);
	RationalType r2(2, 3);
	cout << "- Output (Expect true): " << (r >= r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Output (Expect true): " << (r >= r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Output (Expect true): " << (r >= r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_ostream() {
	cout << "--- test_op_ostream:" << endl;

	cout << "- Output (Expect 9/4): " << RationalType(9, 4) << endl;

	cout << endl;
	return true;
}

bool test_op_istream() {
	cout << "--- test_op_istream (enter a fracture format n/d):" << endl;

	RationalType r;
	cin >> r;
	cout << "- Output (Expect User Input): " << r << endl;

	cout << endl;
	return true;
}

bool test_custom() {
	cout << "--- test_custom:" << endl;

	RationalType r(-1, 2);

	cout << r * -10 << endl
		<< r * RationalType(20, -2) << endl;

	r = 7;

	cout << r + RationalType(2, 3) << endl
		<< 10 / r / 2 + RationalType(6, 5) << endl;

	cout << endl;
	return true;
}