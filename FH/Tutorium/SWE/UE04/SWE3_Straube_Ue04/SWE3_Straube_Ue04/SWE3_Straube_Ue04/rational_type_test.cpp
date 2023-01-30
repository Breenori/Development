/*
* ----- Includes. -----
*/
#include "rational_type_test.h"
#include "number_type.h"

/*
* ----- Usings. -----
*/
using std::endl;

/*
* ----- Functions. -----
*/

/*
* --- Tests Task. ---
*/
bool test_nr_one() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 1) Test generic datatype rational_t<T> mit T = int." << endl;

	test_constructor();
	test_as_string();
	test_print();
	test_scan();
	test_get_numerator();
	test_get_denominator();
	test_is_negative();
	test_is_positive();
	test_normalize();
	test_add();
	test_sub();
	test_mul();
	test_div();
	test_custom();

	cout << endl << endl;
	return 0;
}

bool test_nr_two() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 2) Test creation of rational_t<number_t<T>>." << endl;

	test_constructor_nt();

	cout << endl << endl;
	return 0;
}

bool test_nr_three() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 3) Create concepts for rational_t<T>." << endl;

	Rational_t r(-1, 2);
	cout << "- Input: Default datatype -1/2; Output (Expect -1/2): " << r << endl;

	Rational_t<int> l(-1, 2);
	cout << "- Input: Int datatype -1/2; Output (Expect -1/2): " << l << endl;

	cout << "- Input: Double datatype -1/2; Output (Compilererror: Concept not fulfilled). The relevant passage has been commented out #test_nr_three." << endl;
	//try {
	//	Rational_t<double> m('1', '2');
	//}
	//catch (std::exception& e) {
	//	cout << e.what() << endl;
	//}

	cout << endl << endl;
	return 0;
}

bool test_nr_four() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 4) Test concepts and methods for rational_t<T> with number_t<T>. Please also see test_nr_two for constructors and test_nr_nine for operators." << endl;

	test_as_string_nt();
	test_print_nt();
	test_scan_nt();
	test_get_numerator_nt();
	test_get_denominator_nt();
	test_is_negative_nt();
	test_is_positive_nt();
	test_normalize_nt();
	test_add_nt();
	test_sub_nt();
	test_mul_nt();
	test_div_nt();
	test_custom_nt();

	cout << endl << endl;
	return 0;
}

bool test_nr_five() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 5) Test ops default." << endl;

	test_ops_abs();
	test_ops_divides();
	test_ops_equals();
	test_ops_gcd();
	test_ops_negative();
	test_ops_zero();
	test_ops_negate();
	test_ops_remainder();

	cout << endl << endl;
	return 0;
}

bool test_nr_six() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 6) Test nelms default." << endl;

	test_nelms_zero();
	test_nelms_one();

	cout << endl << endl;
	return 0;
}

bool test_nr_seven() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 7) Test ops and nelms for int." << endl;

	test_nelms_zero_int();
	test_nelms_one_int();

	test_ops_abs_int();
	test_ops_divides_int();
	test_ops_equals_int();
	test_ops_gcd_int();
	test_ops_negative_int();
	test_ops_zero_int();
	test_ops_negate_int();
	test_ops_remainder_int();

	cout << endl << endl;
	return 0;
}

bool test_nr_eight() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 8) Test inverse." << endl;

	test_inverse();
	test_inverse_nt();

	cout << endl << endl;
	return 0;
}

bool test_nr_nine() {
	cout << "----- " << __func__ << ":" << endl;
	cout << "----- 9) Test operation friend inline." << endl;

	test_operatorassignment();
	test_op_plus();
	test_op_minus();
	test_op_mult();
	test_op_divi();
	test_op_plus_assign();
	test_op_minus_assign();
	test_op_mult_assign();
	test_op_divi_assign();
	test_op_compare_is();
	test_op_compare_is_not();
	test_op_compare_smaller_than();
	test_op_compare_smaller_equal_than();
	test_op_compare_larger_than();
	test_op_compare_larger_equal_than();
	test_op_ostream();
	test_op_istream();

	test_operatorassignment_nt();
	test_op_plus_nt();
	test_op_minus_nt();
	test_op_mult_nt();
	test_op_divi_nt();
	test_op_plus_assign_nt();
	test_op_minus_assign_nt();
	test_op_mult_assign_nt();
	test_op_divi_assign_nt();
	test_op_compare_is_nt();
	test_op_compare_is_not_nt();
	test_op_compare_smaller_than_nt();
	test_op_compare_smaller_equal_than_nt();
	test_op_compare_larger_than_nt();
	test_op_compare_larger_equal_than_nt();
	test_op_ostream_nt();
	test_op_istream_nt();

	cout << endl << endl;
	return 0;
}


/*
* --- Tests nelms default ---
*/

bool test_nelms_zero() {
	cout << "--- " << __func__ << ":" << endl;

	cout << "- Input: Number_t<int>; Output (Expect 0): " << nelms::zero<Number_t<int>>() << endl;

	cout << endl;
	return 0;
}

bool test_nelms_one() {
	cout << "--- " << __func__ << ":" << endl;

	cout << "- Input: Number_t<int>; Output (Expect 1): " << nelms::one<Number_t<int>>() << endl;

	cout << endl;
	return 0;
}


/*
* --- Tests nelms int ---
*/

bool test_nelms_zero_int() {
	cout << "--- " << __func__ << ":" << endl;

	cout << "- Input: int; Output (Expect 0): " << nelms::zero<int>() << endl;

	cout << endl;
	return 0;
}

bool test_nelms_one_int() {
	cout << "--- " << __func__ << ":" << endl;

	cout << "- Input: Number_t<int>; Output (Expect 1): " << nelms::one<int>() << endl;

	cout << endl;
	return 0;
}


/*
* --- Tests ops default ---
*/

bool test_ops_abs() {
	cout << "--- " << __func__ << ":" << endl;

	Number_t<int> rn(-4);
	cout << "- Input: Number_t<int> -4; Output (Expect 4): " << ops::abs(rn) << endl;
	rn = 0;
	cout << "- Input: Number_t<int> 0; Output (Expect 0): " << ops::abs(rn) << endl;

	cout << endl;
	return 0;
}

bool test_ops_divides() {
	cout << "--- " << __func__ << ":" << endl;

	Number_t<int> ln(10);
	Number_t<int> rn(2);
	cout << "- Input: Number_t<int> 10, 2; Output (Expect true): " << (ops::divides(ln, rn) ? "true" : "false") << endl;
	cout << "- Input: Number_t<int> 2, 10; Output (Expect false): " << (ops::divides(rn, ln) ? "true" : "false") << endl;
	cout << "- Input: Number_t<int> 10, 0; Output (Expect false): " << (ops::divides(ln, Number_t<int>(0)) ? "true" : "false") << endl;

	cout << endl;
	return 0;
}

bool test_ops_equals() {
	cout << "--- " << __func__ << ":" << endl;

	Number_t<int> ln(10);
	Number_t<int> rn(2);
	cout << "- Input: Number_t<int> 10, 2; Output (Expect false): " << (ops::equals(ln, rn) ? "true" : "false") << endl;

	ln = 2;
	cout << "- Input: Number_t<int> 2, 2; Output (Expect true): " << (ops::equals(ln, rn) ? "true" : "false") << endl;

	cout << endl;
	return 0;
}

bool test_ops_gcd() {
	cout << "--- " << __func__ << ":" << endl;

	Number_t<int> ln(25);
	Number_t<int> rn(10);
	cout << "- Input: Number_t<int> 25, 10; Output (Expect 5): " << ops::gcd(ln, rn) << endl;
	cout << "- Input: Number_t<int> 10, 25; Output (Expect 5): " << ops::gcd(rn, ln) << endl;

	cout << endl;
	return 0;
}

bool test_ops_negative() {
	cout << "--- " << __func__ << ":" << endl;

	Number_t<int> ln(10);
	cout << "- Input: Number_t<int> 10; Output (Expect false): " << (ops::is_negative(ln) ? "true" : "false") << endl;
	ln = -2;
	cout << "- Input: Number_t<int> -2; Output (Expect true): " << (ops::is_negative(ln) ? "true" : "false") << endl;
	ln = 0;
	cout << "- Input: Number_t<int> 0; Output (Expect false): " << (ops::is_negative(ln) ? "true" : "false") << endl;

	cout << endl;
	return 0;
}

bool test_ops_zero() {
	cout << "---- " << __func__ << ":" << endl;

	test_is_zero_nt();

	return 0;
}

bool test_ops_negate() {
	cout << "--- " << __func__ << ":" << endl;

	Number_t<int> rn(25);
	cout << "- Input: Number_t<int> 25; Output (Expect -25): " << ops::negate(rn) << endl;
	rn = -5;
	cout << "- Input: Number_t<int> -5; Output (Expect 5): " << ops::negate(rn) << endl;
	rn = 0;
	cout << "- Input: Number_t<int> 0; Output (Expect 0): " << ops::negate(rn) << endl;

	cout << endl;
	return 0;
}

bool test_ops_remainder() {
	cout << "--- " << __func__ << ":" << endl;

	Number_t<int> ln(23);
	Number_t<int> rn(6);
	cout << "- Input: Number_t<int> 23 % 6; Output (Expect 5): " << ops::remainder(ln, rn) << endl;
	cout << "- Input: Number_t<int> 6 % 23; Output (Expect 6): " << ops::remainder(rn, ln) << endl;

	rn = 0;
	cout << "- Input: Number_t<int> 23 % 0; Output (Expect 23): " << ops::remainder(ln, rn) << endl;
	cout << "- Input: Number_t<int> 0 % 23; Output (Expect 0): " << ops::remainder(rn, ln) << endl;

	cout << endl;
	return 0;
}


/*
* --- Tests ops int ---
*/

bool test_ops_abs_int() {
	cout << "--- " << __func__ << ":" << endl;

	int i{ -4 };
	cout << "- Input: int -4; Output (Expect 4): " << ops::abs(i) << endl;
	i = 0;
	cout << "- Input: int 0; Output (Expect 0): " << ops::abs(i) << endl;

	cout << endl;
	return 0;
}

bool test_ops_divides_int() {
	cout << "--- " << __func__ << ":" << endl;

	int l(10);
	int r(2);
	cout << "- Input: int 10, 2; Output (Expect true): " << (ops::divides(l, r) ? "true" : "false") << endl;
	cout << "- Input: int 2, 10; Output (Expect false): " << (ops::divides(r, l) ? "true" : "false") << endl;
	cout << "- Input: int 10, 0; Output (Expect false): " << (ops::divides(l, 0) ? "true" : "false") << endl;

	cout << endl;
	return 0;
}

bool test_ops_equals_int() {
	cout << "--- " << __func__ << ":" << endl;

	int l(10);
	int r(2);
	cout << "- Input: Number_t<int> 10, 2; Output (Expect false): " << (ops::equals(l, r) ? "true" : "false") << endl;

	l = 2;
	cout << "- Input: Number_t<int> 2, 2; Output (Expect true): " << (ops::equals(l, r) ? "true" : "false") << endl;

	cout << endl;
	return 0;
}

bool test_ops_gcd_int() {
	cout << "--- " << __func__ << ":" << endl;

	int l(25);
	int r(10);
	cout << "- Input: int 25, 10; Output (Expect 5): " << ops::gcd(l, r) << endl;
	cout << "- Input: int 10, 25; Output (Expect 5): " << ops::gcd(r, l) << endl;

	cout << endl;
	return 0;
}

bool test_ops_negative_int() {
	cout << "--- " << __func__ << ":" << endl;

	int l(10);
	cout << "- Input: Number_t<int> 10; Output (Expect false): " << (ops::is_negative(l) ? "true" : "false") << endl;
	l = -2;
	cout << "- Input: Number_t<int> -2; Output (Expect true): " << (ops::is_negative(l) ? "true" : "false") << endl;
	l = 0;
	cout << "- Input: Number_t<int> 0; Output (Expect false): " << (ops::is_negative(l) ? "true" : "false") << endl;

	cout << endl;
	return 0;
}

bool test_ops_zero_int() {
	cout << "---- " << __func__ << ":" << endl;

	test_is_zero();

	return 0;
}

bool test_ops_negate_int() {
	cout << "--- " << __func__ << ":" << endl;

	int r(25);
	cout << "- Input: int 25; Output (Expect -25): " << ops::negate(r) << endl;
	r = -5;
	cout << "- Input: int -5; Output (Expect 5): " << ops::negate(r) << endl;
	r = 0;
	cout << "- Input: int 0; Output (Expect 0): " << ops::negate(r) << endl;

	cout << endl;
	return 0;
}

bool test_ops_remainder_int() {
	cout << "--- " << __func__ << ":" << endl;

	int l(23);
	int r(6);
	cout << "- Input: int 23 % 6; Output (Expect 5): " << ops::remainder(l, r) << endl;
	cout << "- Input: int 6 % 23; Output (Expect 6): " << ops::remainder(r, l) << endl;

	r = 0;
	cout << "- Input: int 23 % 0; Output (Expect 23): " << ops::remainder(l, r) << endl;
	cout << "- Input: int 0 % 23; Output (Expect 0): " << ops::remainder(r, l) << endl;

	cout << endl;
	return 0;
}


/*
* --- Tests Rational_t && Rational_t<int> ---
*/

bool test_as_string() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(-1, 2);
	cout << "- Input: -1/2; Output (Expect -1/2): " << r << endl;

	cout << endl;
	return true;
}

bool test_print() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(-1, 2);
	cout << "- Input: -1/2;  Output (Expect -1/2): " << endl; 
	r.print(); cout << endl;

	cout << endl;
	return true;
}

bool test_operatorassignment() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(-1, 2);

	// Assign.
	int ti{ 7 };
	r = ti;
	cout << "- Input: r = int(7); Output (Expect 7): " << r << endl;

	// Copy assign.
	Rational_t<int> trt(3, 4);
	r = trt;
	cout << "- Input: r = rationalt<int>(3,4); Output (Expect 3/4): " << r << endl;

	cout << endl;
	return true;
}

bool test_constructor() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t r(-1, 2);
	cout << "- Input: -1/2 without datatype int; Output (Expect -1/2): " << r << endl;

	Rational_t<int> r6(-1, 2);
	cout << "- Input: -1/2; Output (Expect -1/2): " << r6 << endl;

	Rational_t<int> r2;
	cout << "- Input: ''; Output (Expect 0): " << r2 << endl;

	Rational_t<int> r3(7);
	cout << "- Input: 7; Output (Expect 7): " << r3 << endl;

	Rational_t<int> r4(r);
	cout << "- Input: r(-1/2); Output (Expect -1/2): " << r4 << endl;

	cout << "- Input: 1/0; Output (Expect Error): " << endl;
	try {
		Rational_t<int> r5(1, 0);
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}

	cout << endl;
	return true;
}

bool test_scan() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r;

	cout << "User Input (3/4):" << endl; r.scan();
	cout << "- Output (Expect user input): " << r << endl;

	cout << "User Input (3 4 then 3/4):" << endl; r.scan();
	cout << "- Output (Expect redo): " << r << endl;

	cout << "User Input (3 then 3/1):" << endl; r.scan();
	cout << "- Output (Expect redo): " << r << endl;

	cout << "User Input (3/1):" << endl; r.scan();
	cout << "- Output (Expect user input): " << r << endl;

	cout << endl;
	return true;
}

bool test_get_numerator() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(11, 15);
	cout << "- Input: 11/15; Output (Expect 11): " << r.get_numerator() << endl;

	cout << endl;
	return true;
}

bool test_get_denominator() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(11, 15);
	cout << "- Input: 11/15; Output (Expect 15): " << r.get_denominator()<< endl;

	cout << endl;
	return true;
}

bool test_is_negative() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(11, 15);
	cout << "- Input: 11/15; Output (Expect false): " << (r.is_negative() ? "true" : "false") << endl;

	Rational_t<int> l(-11, 15);
	cout << "- Input: -11/15; Output (Expect true): " << (l.is_negative() ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_is_positive() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(11, 15);
	cout << "- Input: 11/15; Output (Expect true): " << (r.is_positive() ? "true" : "false") << endl;

	Rational_t<int> l(-11, 15);
	cout << "- Input: -11/15; Output (Expect false): " << (l.is_positive() ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_is_zero() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(0, 15);
	cout << "- Input: 0/15; Output (Expect true): " << (r.is_zero() ? "true" : "false") << endl;

	Rational_t<int> l(-11, 15);
	cout << "- Input: -11/15; Output (Expect false): " << (l.is_zero() ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_inverse() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(2, 3);
	cout << "- Input: 2/3; Output (Expect 3/2): " << r.inverse() << endl;

	Rational_t<int> l(0, 15);
	cout << "- Input: 0/15; Output (Expect Error): " << endl;
	try {
		cout << l.inverse() << endl;
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}

	cout << endl;
	return true;
}

bool test_normalize() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(3, 15);
	cout << "- Input: 3/15; Output (Expect 1/5): " << r << endl;

	r = { 42, 28 };
	cout << "- Input: 42/28; Output (Expect 3/2): " << r << endl;

	r = { 1, -3 };
	cout << "- Input: 1/-3; Output (Expect -1/3): " << r << endl;

	r = { -1, -3 };
	cout << "- Input: -1/-3; Output (Expect 1/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_add() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 3);
	Rational_t<int> r2(1, 3);
	r.add(r2);
	cout << "- Input: 4/3 add 1/3; Output (Expect 5/3): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.add(r2);
	cout << "- Input: -4/3 add -1/3; Output (Expect -5/3): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.add(r2);
	cout << "- Input: 1/3 add -4/3; Output (Expect -1): " << r << endl;

	r = {-1, 3};
	r2 = {1, 3};
	r.add(r2);
	cout << "- Input: -1/3 add 1/3; Output (Expect 0): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.add(r2);
	cout << "- Input: 3/10 add 4/5; Output (Expect 11/10): " << r << endl;

	r = {};
	r2 = {};
	r.add(r2);
	cout << "- Input: '' add ''; Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.add(r2);
	cout << "- Input: 7 add -3; Output (Expect 4): " << r << endl;

	cout << endl;
	return true;
}

bool test_sub() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(1, 3);
	Rational_t<int> r2(8, 3);
	r.sub(r2);
	cout << "- Input: 1/3 sub 8/3; Output (Expect -7/3): " << r << endl;

	r = { 8, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Input: 8/3 sub 1/3; Output (Expect 7/3): " << r << endl;


	r = { 1, 3 };
	r2 = { -8, 3 };
	r.sub(r2);
	cout << "- Input: 1/3 sub -8/3; Output (Expect 3): " << r << endl;

	r = { 8, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Input: 8/3 sub -1/3; Output (Expect 3): " << r << endl;


	r = { -1, 3 };
	r2 = { -8, 3 };
	r.sub(r2);
	cout << "- Input: -1/3 sub -8/3; Output (Expect 7/3): " << r << endl;

	r = { -8, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Input: -8/3 sub -1/3; Output (Expect -7/3): " << r << endl;


	r = { -1, 3 };
	r2 = { 8, 3 };
	r.sub(r2);
	cout << "- Input: -1/3 sub 8/3; Output (Expect -3): " << r << endl;

	r = { -8, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Input: -8/3 sub 1/3; Output (Expect -3): " << r << endl;


	r = { 1, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Input: 1/3 sub 1/3; Output (Expect 0): " << r << endl;

	r = { 1, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Input: 1/3 sub -1/3; Output (Expect 2/3): " << r << endl;


	r = { 0, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Input: 0/3 sub 1/3; Output (Expect -1/3): " << r << endl;

	r = { -1, 3 };
	r2 = { 0, 3 };
	r.sub(r2);
	cout << "- Input: -1/3 sub 0/3; Output (Expect -1/3): " << r << endl;


	r = {};
	r2 = {};
	r.sub(r2);
	cout << "- Input: '' sub ''; Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.sub(r2);
	cout << "- Input: 7 sub -3; Output (Expect 10): " << r << endl;

	cout << endl;
	return true;
}

bool test_mul() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(1, 2);
	Rational_t<int> r2(1, 3);
	r.mul(r2);
	cout << "- Input: 1/2 mul 1/3; Output (Expect 1/6): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.mul(r2);
	cout << "- Input: -4/3 mul -1/3; Output (Expect 4/9): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.mul(r2);
	cout << "- Input: 1/3 mul -4/3; Output (Expect -4/9): " << r << endl;

	r = { -1, 3 };
	r2 = { 1, 3 };
	r.mul(r2);
	cout << "- Input: -1/3 mul 1/3; Output (Expect -1/9): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.mul(r2);
	cout << "- Input: 3/10 mul 4/5; Output (Expect 6/25): " << r << endl;

	r = {};
	r2 = {};
	r.mul(r2);
	cout << "- Input: '' mul ''; Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.mul(r2);
	cout << "- Input: 7 mul -3; Output (Expect -21): " << r << endl;

	cout << endl;
	return true;
}

bool test_div() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(1, 2);
	Rational_t<int> r2(1, 3);
	r.div(r2);
	cout << "- Input: 1/2 div 1/3; Output (Expect 3/2): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.div(r2);
	cout << "- Input: -4/3 div -1/3; Output (Expect 4): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.div(r2);
	cout << "- Input: 1/3 div -1/3; Output (Expect -1/4): " << r << endl;

	r = { -1, 3 };
	r2 = { 1, 3 };
	r.div(r2);
	cout << "- Input: -1/3 div 1/3; Output (Expect -1): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.div(r2);
	cout << "- Input: 3/10 div 4/5; Output (Expect 3/8): " << r << endl;


	cout << "- Input: '' div ''; Output (Expect Error): " << endl;
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
	cout << "- Input: 7 div -3; Output (Expect -7/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_plus() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(1, 2);
	Rational_t<int> r2(1, 3);
	cout << "- Input: 1/2 + 1/3; Output (Expect 5/6): " << r + r2 << endl;

	int r3 = 3;
	cout << "- Input: 1/2 + int(3); Output (Expect 7/2): " << r + r3 << endl;

	cout << "- Input: int(3) + 1/2; Output (Expect 7/2): " << r3 + r << endl;

	cout << "- Input: int(3) + 1/2 + 1/3; Output (Expect 23/6): " << r3 + r + r2 << endl;

	cout << endl;
	return true;
}

bool test_op_minus() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(1, 2);
	Rational_t<int> r2(1, 3);
	cout << "- Input: 1/2 - 1/3; Output (Expect 1/6): " << r - r2 << endl;

	int r3 = 3;
	cout << "- Input: 1/2 - int(3); Output (Expect -5/2): " << r - r3 << endl;

	cout << "- Input: int(3) - 1/2; Output (Expect 5/2): " << r3 - r << endl;

	cout << "- Input: int(3) - 1/2 - 1/3; Output (Expect 13/6): " << r3 - r - r2 << endl;

	cout << endl;
	return true;
}

bool test_op_mult() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(1, 2);
	Rational_t<int> r2(1, 3);
	cout << "- Input: 1/2 * 1/3; Output (Expect 1/6): " << r * r2 << endl;

	int r3 = 3;
	cout << "- Input: 1/2 * int(3); Output (Expect 3/2): " << r * r3 << endl;

	cout << "- Input: int(3) * 1/2; Output (Expect 3/2): " << r3 * r << endl;

	cout << "- Input: int(3) * 1/2 * 1/3; Output (Expect 1/2): " << r3 * r * r2 << endl;

	cout << endl;
	return true;
}

bool test_op_divi() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(1, 2);
	Rational_t<int> r2(1, 3);
	cout << "- Input: 1/2 / 1/3; Output (Expect 3/2): " << r / r2 << endl;

	int r3 = 3;
	cout << "- Input: 1/2 / int(3); Output (Expect 1/6): " << r / r3 << endl;

	cout << "- Input: int(3) / 1/2; Output (Expect 6): " << r3 / r << endl;

	cout << "- Input: int(3) / 1/2 / 1/3; Output (Expect 18): " << r3 / r / r2 << endl;

	cout << "- Input: 1/2 / int(0); Output (Expect Error): " << endl;
	cout << r / 0 << endl;

	cout << "- Input: int(0) / 1/2; Output (Expect 0): " << 0 / r << endl;

	cout << endl;
	return true;
}

bool test_op_plus_assign() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	r += r2;
	cout << "- Input: 4/5 += 2/3; Output (Expect 22/15): " << r << endl;

	r = { 1, 3 };
	int r3 = 3;
	r += r3;
	cout << "- Input: 1/3 += int(3); Output (Expect 10/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_minus_assign() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	r -= r2;
	cout << "- Input: 4/5 -= 2/3; Output (Expect 2/15): " << r << endl;

	r = { 1, 3 };
	int r3 = 3;
	r -= r3;
	cout << "- Input: 1/3 -= int(3); Output (Expect -8/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_mult_assign() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	r *= r2;
	cout << "- Input: 4/5 *= 2/3; Output (Expect 8/15): " << r << endl;

	r = { 1, 3 };
	int r3 = 3;
	r *= r3;
	cout << "- Input: 1/3 *= int(3); Output (Expect 1): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_divi_assign() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	r /= r2;
	cout << "- Input: 4/5 /= 2/3; Output (Expect 6/5): " << r << endl;

	r = { 1, 3 };
	int r3 = 3;
	r /= r3;
	cout << "- Input: 1/3 /= int(3); Output (Expect 1/9): " << r << endl;

	cout << "- Input: 1/3 /= int(0); Output (Expect Error): " << endl;
	r /= 0;
	cout << r << endl;

	cout << endl;
	return true;
}

bool test_op_compare_is() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	cout << "- Input: 4/5 == 2/3; Output (Expect false): " << (r == r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 == 4/5; Output (Expect true): " << (r == r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Input: 3/1 == int(3); Output (Expect true): " << (r == r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_is_not() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	cout << "- Input: 4/5 != 2/3; Output (Expect true): " << (r != r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 != 4/5; Output (Expect false): " << (r != r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Input: 3/1 != int(3); Output (Expect false): " << (r != r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_smaller_than() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	cout << "- Input: 4/5 < 2/3; Output (Expect false): " << (r < r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 < 4/5; Output (Expect false): " << (r < r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Input: 3/1 < int(3); Output (Expect false): " << (r < r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_smaller_equal_than() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	cout << "- Input: 4/5 <= 2/3; Output (Expect false): " << (r <= r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 <= 4/5; Output (Expect true): " << (r <= r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Input: 3/1 <= int(3); Output (Expect true): " << (r <= r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_larger_than() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	cout << "- Input: 4/5 > 2/3; Output (Expect true): " << (r > r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 > 4/5; Output (Expect false): " << (r > r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Input: 3/1 > int(3); Output (Expect false): " << (r > r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_larger_equal_than() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(4, 5);
	Rational_t<int> r2(2, 3);
	cout << "- Input: 4/5 >= 2/3; Output (Expect true): " << (r >= r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 >= 4/5; Output (Expect true): " << (r >= r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	int r3 = 3;
	cout << "- Input: 3/1 >= int(3); Output (Expect true): " << (r >= r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_ostream() {
	cout << "--- " << __func__ << ":" << endl;

	cout << "- Input: 9/4; Output (Expect 9/4): " << Rational_t<int>(9, 4) << endl;

	cout << endl;
	return true;
}

bool test_op_istream() {
	cout << "--- " << __func__ << " (enter a fracture format n/d):" << endl;

	Rational_t<int> r;
	cin >> r;
	cout << "- Input: ...; Output (Expect normalized user input): " << r << endl;

	cout << endl;
	return true;
}

bool test_custom() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<int> r(-1, 2);

	cout << r * -10 << endl
		<< r * Rational_t(20, -2) << endl;

	r = 7;

	cout << r + Rational_t(2, 3) << endl
		<< 10 / r / 2 + Rational_t(6, 5) << endl;

	cout << endl;
	return true;
}


/*
* --- Tests Rational_t<Number_t<int>> ---
*/

bool test_as_string_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(-1, 2);
	cout << "- Input: -1/2; Output (Expect -1/2): " << r << endl;

	cout << endl;
	return true;
}

bool test_print_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(-1, 2);
	cout << "- Input: -1/2;  Output (Expect -1/2): " << endl;
	r.print_general(); cout << endl;

	cout << endl;
	return true;
}

bool test_operatorassignment_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(-1, 2);

	// Assign.
	Number_t<int> ti{ 7 };
	r = ti;
	cout << "- Input: r = Number_t<int>(7); Output (Expect 7): " << r << endl;

	// Copy assign.
	Rational_t<Number_t<int>> trt(3, 4);
	r = trt;
	cout << "- Input: r = rationalt<Number_t<int>>(3,4); Output (Expect 3/4): " << r << endl;

	cout << endl;
	return true;
}

bool test_constructor_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(-1, 2);
	cout << "- Input: -1/2; Output (Expect -1/2): " << r << endl;

	Rational_t<Number_t<int>> r2;
	cout << "- Input: ''; Output (Expect 0): " << r2 << endl;

	Rational_t<Number_t<int>> r3(7);
	cout << "- Input: 7; Output (Expect 7): " << r3 << endl;

	Rational_t<Number_t<int>> r4(r);
	cout << "- Input: r(-1/2); Output (Expect -1/2): " << r4 << endl;

	cout << "- Input: 1/0; Output (Expect Error): " << endl;
	try {
		Rational_t<Number_t<int>> r5(1, 0);
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}

	cout << endl;
	return true;
}

bool test_scan_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r;

	cout << "User Input (3/4):" << endl; r.scan();
	cout << "- Output (Expect user input): " << r << endl;

	cout << "User Input (3 4 then 3/4):" << endl; r.scan();
	cout << "- Output (Expect redo): " << r << endl;

	cout << "User Input (3 then 3/1):" << endl; r.scan();
	cout << "- Output (Expect redo): " << r << endl;

	cout << "User Input (3/1):" << endl; r.scan();
	cout << "- Output (Expect user input): " << r << endl;

	cout << endl;
	return true;
}

bool test_get_numerator_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(11, 15);
	cout << "- Input: 11/15; Output (Expect 11): " << r.get_numerator() << endl;

	cout << endl;
	return true;
}

bool test_get_denominator_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(11, 15);
	cout << "- Input: 11/15; Output (Expect 15): " << r.get_denominator() << endl;

	cout << endl;
	return true;
}

bool test_is_negative_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(11, 15);
	cout << "- Input: 11/15; Output (Expect false): " << (r.is_negative() ? "true" : "false") << endl;

	Rational_t<Number_t<int>> l(-11, 15);
	cout << "- Input: -11/15; Output (Expect true): " << (l.is_negative() ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_is_positive_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(11, 15);
	cout << "- Input: 11/15; Output (Expect true): " << (r.is_positive() ? "true" : "false") << endl;

	Rational_t<Number_t<int>> l(-11, 15);
	cout << "- Input: -11/15; Output (Expect false): " << (l.is_positive() ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_is_zero_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(0, 15);
	cout << "- Input: 0/15; Output (Expect true): " << (r.is_zero() ? "true" : "false") << endl;

	Rational_t<Number_t<int>> l(-11, 15);
	cout << "- Input: -11/15; Output (Expect false): " << (l.is_zero() ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_inverse_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(2, 3);
	cout << "- Input: 2/3; Output (Expect 3/2): " << r.inverse() << endl;

	Rational_t<Number_t<int>> l(0, 15);
	cout << "- Input: 0/15; Output (Expect Error): " << endl;
	try {
		cout << l.inverse() << endl;
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}

	cout << endl;
	return true;
}

bool test_normalize_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(3, 15);
	cout << "- Input: 3/15; Output (Expect 1/5): " << r << endl;

	r = { 42, 28 };
	cout << "- Input: 42/28; Output (Expect 3/2): " << r << endl;

	r = { 1, -3 };
	cout << "- Input: 1/-3; Output (Expect -1/3): " << r << endl;

	r = { -1, -3 };
	cout << "- Input: -1/-3; Output (Expect 1/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_add_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 3);
	Rational_t<Number_t<int>> r2(1, 3);
	r.add(r2);
	cout << "- Input: 4/3 add 1/3; Output (Expect 5/3): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.add(r2);
	cout << "- Input: -4/3 add -1/3; Output (Expect -5/3): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.add(r2);
	cout << "- Input: 1/3 add -4/3; Output (Expect -1): " << r << endl;

	r = { -1, 3 };
	r2 = { 1, 3 };
	r.add(r2);
	cout << "- Input: -1/3 add 1/3; Output (Expect 0): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.add(r2);
	cout << "- Input: 3/10 add 4/5; Output (Expect 11/10): " << r << endl;

	r = {};
	r2 = {};
	r.add(r2);
	cout << "- Input: '' add ''; Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.add(r2);
	cout << "- Input: 7 add -3; Output (Expect 4): " << r << endl;

	cout << endl;
	return true;
}

bool test_sub_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(1, 3);
	Rational_t<Number_t<int>> r2(8, 3);
	r.sub(r2);
	cout << "- Input: 1/3 sub 8/3; Output (Expect -7/3): " << r << endl;

	r = { 8, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Input: 8/3 sub 1/3; Output (Expect 7/3): " << r << endl;


	r = { 1, 3 };
	r2 = { -8, 3 };
	r.sub(r2);
	cout << "- Input: 1/3 sub -8/3; Output (Expect 3): " << r << endl;

	r = { 8, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Input: 8/3 sub -1/3; Output (Expect 3): " << r << endl;


	r = { -1, 3 };
	r2 = { -8, 3 };
	r.sub(r2);
	cout << "- Input: -1/3 sub -8/3; Output (Expect 7/3): " << r << endl;

	r = { -8, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Input: -8/3 sub -1/3; Output (Expect -7/3): " << r << endl;


	r = { -1, 3 };
	r2 = { 8, 3 };
	r.sub(r2);
	cout << "- Input: -1/3 sub 8/3; Output (Expect -3): " << r << endl;

	r = { -8, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Input: -8/3 sub 1/3; Output (Expect -3): " << r << endl;


	r = { 1, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Input: 1/3 sub 1/3; Output (Expect 0): " << r << endl;

	r = { 1, 3 };
	r2 = { -1, 3 };
	r.sub(r2);
	cout << "- Input: 1/3 sub -1/3; Output (Expect 2/3): " << r << endl;


	r = { 0, 3 };
	r2 = { 1, 3 };
	r.sub(r2);
	cout << "- Input: 0/3 sub 1/3; Output (Expect -1/3): " << r << endl;

	r = { -1, 3 };
	r2 = { 0, 3 };
	r.sub(r2);
	cout << "- Input: -1/3 sub 0/3; Output (Expect -1/3): " << r << endl;


	r = {};
	r2 = {};
	r.sub(r2);
	cout << "- Input: '' sub ''; Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.sub(r2);
	cout << "- Input: 7 sub -3; Output (Expect 10): " << r << endl;

	cout << endl;
	return true;
}

bool test_mul_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(1, 2);
	Rational_t<Number_t<int>> r2(1, 3);
	r.mul(r2);
	cout << "- Input: 1/2 mul 1/3; Output (Expect 1/6): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.mul(r2);
	cout << "- Input: -4/3 mul -1/3; Output (Expect 4/9): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.mul(r2);
	cout << "- Input: 1/3 mul -4/3; Output (Expect -4/9): " << r << endl;

	r = { -1, 3 };
	r2 = { 1, 3 };
	r.mul(r2);
	cout << "- Input: -1/3 mul 1/3; Output (Expect -1/9): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.mul(r2);
	cout << "- Input: 3/10 mul 4/5; Output (Expect 6/25): " << r << endl;

	r = {};
	r2 = {};
	r.mul(r2);
	cout << "- Input: '' mul ''; Output (Expect 0): " << r << endl;

	r = { 7 };
	r2 = { -3 };
	r.mul(r2);
	cout << "- Input: 7 mul -3; Output (Expect -21): " << r << endl;

	cout << endl;
	return true;
}

bool test_div_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(1, 2);
	Rational_t<Number_t<int>> r2(1, 3);
	r.div(r2);
	cout << "- Input: 1/2 div 1/3; Output (Expect 3/2): " << r << endl;

	r = { -4, 3 };
	r2 = { -1, 3 };
	r.div(r2);
	cout << "- Input: -4/3 div -1/3; Output (Expect 4): " << r << endl;

	r = { 1, 3 };
	r2 = { -4, 3 };
	r.div(r2);
	cout << "- Input: 1/3 div -1/3; Output (Expect -1/4): " << r << endl;

	r = { -1, 3 };
	r2 = { 1, 3 };
	r.div(r2);
	cout << "- Input: -1/3 div 1/3; Output (Expect -1): " << r << endl;

	r = { 3, 10 };
	r2 = { 4, 5 };
	r.div(r2);
	cout << "- Input: 3/10 div 4/5; Output (Expect 3/8): " << r << endl;


	cout << "- Input: '' div ''; Output (Expect Error): " << endl;
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
	cout << "- Input: 7 div -3; Output (Expect -7/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_plus_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(1, 2);
	Rational_t<Number_t<int>> r2(1, 3);
	cout << "- Input: 1/2 + 1/3; Output (Expect 5/6): " << r + r2 << endl;

	Number_t<int> r3 = 3;
	cout << "- Input: 1/2 + Number_t<int>(3); Output (Expect 7/2): " << r + r3 << endl;

	cout << "- Input: Number_t<int>(3) + 1/2; Output (Expect 7/2): " << r3 + r << endl;

	cout << "- Input: Number_t<int>(3) + 1/2 + 1/3; Output (Expect 23/6): " << r3 + r + r2 << endl;

	cout << endl;
	return true;
}

bool test_op_minus_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(1, 2);
	Rational_t<Number_t<int>> r2(1, 3);
	cout << "- Input: 1/2 - 1/3; Output (Expect 1/6): " << r - r2 << endl;

	Number_t<int> r3 = 3;
	cout << "- Input: 1/2 - Number_t<int>(3); Output (Expect -5/2): " << r - r3 << endl;

	cout << "- Input: Number_t<int>(3) - 1/2; Output (Expect 5/2): " << r3 - r << endl;

	cout << "- Input: Number_t<int>(3) - 1/2 - 1/3; Output (Expect 13/6): " << r3 - r - r2 << endl;

	cout << endl;
	return true;
}

bool test_op_mult_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(1, 2);
	Rational_t<Number_t<int>> r2(1, 3);
	cout << "- Input: 1/2 * 1/3; Output (Expect 1/6): " << r * r2 << endl;

	Number_t<int> r3 = 3;
	cout << "- Input: 1/2 * Number_t<int>(3); Output (Expect 3/2): " << r * r3 << endl;

	cout << "- Input: Number_t<int>(3) * 1/2; Output (Expect 3/2): " << r3 * r << endl;

	cout << "- Input: Number_t<int>(3) * 1/2 * 1/3; Output (Expect 1/2): " << r3 * r * r2 << endl;

	cout << endl;
	return true;
}

bool test_op_divi_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(1, 2);
	Rational_t<Number_t<int>> r2(1, 3);
	cout << "- Input: 1/2 / 1/3; Output (Expect 3/2): " << r / r2 << endl;

	Number_t<int> r3 = 3;
	cout << "- Input: 1/2 / Number_t<int>(3); Output (Expect 1/6): " << r / r3 << endl;

	cout << "- Input: Number_t<int>(3) / 1/2; Output (Expect 6): " << r3 / r << endl;

	cout << "- Input: Number_t<int>(3) / 1/2 / 1/3; Output (Expect 18): " << r3 / r / r2 << endl;

	cout << "- Input: 1/2 / Number_t<int>(0); Output (Expect Error): " << endl;
	cout << r / Number_t<int>(0) << endl;

	cout << "- Input: Number_t<int>(0) / 1/2; Output (Expect 0): " << Number_t<int>(0) / r << endl;

	cout << endl;
	return true;
}

bool test_op_plus_assign_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	r += r2;
	cout << "- Input: 4/5 += 2/3; Output (Expect 22/15): " << r << endl;

	r = { 1, 3 };
	Number_t<int> r3 = 3;
	r += r3;
	cout << "- Input: 1/3 += Number_t<int>(3); Output (Expect 10/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_minus_assign_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	r -= r2;
	cout << "- Input: 4/5 -= 2/3; Output (Expect 2/15): " << r << endl;

	r = { 1, 3 };
	Number_t<int> r3 = 3;
	r -= r3;
	cout << "- Input: 1/3 -= Number_t<int>(3); Output (Expect -8/3): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_mult_assign_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	r *= r2;
	cout << "- Input: 4/5 *= 2/3; Output (Expect 8/15): " << r << endl;

	r = { 1, 3 };
	Number_t<int> r3 = 3;
	r *= r3;
	cout << "- Input: 1/3 *= Number_t<int>(3); Output (Expect 1): " << r << endl;

	cout << endl;
	return true;
}

bool test_op_divi_assign_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	r /= r2;
	cout << "- Input: 4/5 /= 2/3; Output (Expect 6/5): " << r << endl;

	r = { 1, 3 };
	Number_t<int> r3 = 3;
	r /= r3;
	cout << "- Input: 1/3 /= Number_t<int>(3); Output (Expect 1/9): " << r << endl;

	cout << "- Input: 1/3 /= Number_t<int>(0); Output (Expect Error): " << endl;
	r /= Number_t<int>(0);
	cout << r << endl;

	cout << endl;
	return true;
}

bool test_op_compare_is_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	cout << "- Input: 4/5 == 2/3; Output (Expect false): " << (r == r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 == 4/5; Output (Expect true): " << (r == r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	Number_t<int> r3 = 3;
	cout << "- Input: 3/1 == Number_t<int>(3); Output (Expect true): " << (r == r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_is_not_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	cout << "- Input: 4/5 != 2/3; Output (Expect true): " << (r != r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 != 4/5; Output (Expect false): " << (r != r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	Number_t<int> r3 = 3;
	cout << "- Input: 3/1 != Number_t<int>(3); Output (Expect false): " << (r != r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_smaller_than_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	cout << "- Input: 4/5 < 2/3; Output (Expect false): " << (r < r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 < 4/5; Output (Expect false): " << (r < r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	Number_t<int> r3 = 3;
	cout << "- Input: 3/1 < Number_t<int>(3); Output (Expect false): " << (r < r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_smaller_equal_than_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	cout << "- Input: 4/5 <= 2/3; Output (Expect false): " << (r <= r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 <= 4/5; Output (Expect true): " << (r <= r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	Number_t<int> r3 = 3;
	cout << "- Input: 3/1 <= Number_t<int>(3); Output (Expect true): " << (r <= r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_larger_than_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	cout << "- Input: 4/5 > 2/3; Output (Expect true): " << (r > r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 > 4/5; Output (Expect false): " << (r > r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	Number_t<int> r3 = 3;
	cout << "- Input: 3/1 > Number_t<int>(3); Output (Expect false): " << (r > r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_compare_larger_equal_than_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(4, 5);
	Rational_t<Number_t<int>> r2(2, 3);
	cout << "- Input: 4/5 >= 2/3; Output (Expect true): " << (r >= r2 ? "true" : "false") << endl;

	r2 = r;
	cout << "- Input: 2/3 >= 4/5; Output (Expect true): " << (r >= r2 ? "true" : "false") << endl;

	r = { 3, 1 };
	Number_t<int> r3 = 3;
	cout << "- Input: 3/1 >= Number_t<int>(3); Output (Expect true): " << (r >= r3 ? "true" : "false") << endl;

	cout << endl;
	return true;
}

bool test_op_ostream_nt() {
	cout << "--- " << __func__ << ":" << endl;

	cout << "- Input: 9/4; Output (Expect 9/4): " << Rational_t<Number_t<int>>(9, 4) << endl;

	cout << endl;
	return true;
}

bool test_op_istream_nt() {
	cout << "--- " << __func__ << " (enter a fracture format n/d):" << endl;

	Rational_t<Number_t<int>> r;
	cin >> r;
	cout << "- Input: ...; Output (Expect normalized user input): " << r << endl;

	cout << endl;
	return true;
}

bool test_custom_nt() {
	cout << "--- " << __func__ << ":" << endl;

	Rational_t<Number_t<int>> r(-1, 2);
	Rational_t<Number_t<int>> l(20, -2);

	cout << r * Number_t<int> (-10) << endl
		<< r * l << endl;

	r = Number_t<int>{ 7 };
	l = Rational_t<Number_t<int>>(2, 3);
	Rational_t<Number_t<int>> m(6, 5);

	cout << r + l << endl
		<< Number_t<int>(10) / r / Number_t<int>(2) + m << endl;

	cout << endl;
	return true;
}