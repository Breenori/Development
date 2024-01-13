#ifndef RATIONAL_T_TEST
#define RATIONAL_T_TEST

/*
* ----- Includes. -----
*/
#include "rational_type.h"
#include "number_type.h"

/*
* ----- Prototypes. -----
*/
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
bool test_nelms_zero();
bool test_nelms_one();

bool test_nelms_zero_int();
bool test_nelms_one_int();

bool test_ops_abs();
bool test_ops_divides();
bool test_ops_equals();
bool test_ops_gcd();
bool test_ops_negative();
bool test_ops_zero();
bool test_ops_negate();
bool test_ops_remainder();

bool test_ops_abs_int();
bool test_ops_divides_int();
bool test_ops_equals_int();
bool test_ops_gcd_int();
bool test_ops_negative_int();
bool test_ops_zero_int();
bool test_ops_negate_int();
bool test_ops_remainder_int();


bool test_nr_one();
bool test_nr_two();
bool test_nr_three();
bool test_nr_four();
bool test_nr_five();
bool test_nr_six();
bool test_nr_seven();
bool test_nr_eight();
bool test_nr_nine();

bool test_as_string();
bool test_print();
bool test_operatorassignment();
bool test_constructor();
bool test_scan();
bool test_get_numerator();
bool test_get_denominator();
bool test_is_negative();
bool test_is_positive();
bool test_is_zero();
bool test_inverse();
bool test_normalize();
bool test_add();
bool test_sub();
bool test_mul();
bool test_div();
bool test_op_plus();
bool test_op_minus();
bool test_op_mult();
bool test_op_divi();
bool test_op_plus_assign();
bool test_op_minus_assign();
bool test_op_mult_assign();
bool test_op_divi_assign();
bool test_op_compare_is();
bool test_op_compare_is_not();
bool test_op_compare_smaller_than();
bool test_op_compare_smaller_equal_than();
bool test_op_compare_larger_than();
bool test_op_compare_larger_equal_than();
bool test_op_ostream();
bool test_op_istream();
bool test_custom();

bool test_as_string_nt();
bool test_print_nt();
bool test_operatorassignment_nt();
bool test_constructor_nt();
bool test_scan_nt();
bool test_get_numerator_nt();
bool test_get_denominator_nt();
bool test_is_negative_nt();
bool test_is_positive_nt();
bool test_is_zero_nt();
bool test_inverse_nt();
bool test_normalize_nt();
bool test_add_nt();
bool test_sub_nt();
bool test_mul_nt();
bool test_div_nt();
bool test_op_plus_nt();
bool test_op_minus_nt();
bool test_op_mult_nt();
bool test_op_divi_nt();
bool test_op_plus_assign_nt();
bool test_op_minus_assign_nt();
bool test_op_mult_assign_nt();
bool test_op_divi_assign_nt();
bool test_op_compare_is_nt();
bool test_op_compare_is_not_nt();
bool test_op_compare_smaller_than_nt();
bool test_op_compare_smaller_equal_than_nt();
bool test_op_compare_larger_than_nt();
bool test_op_compare_larger_equal_than_nt();
bool test_op_ostream_nt();
bool test_op_istream_nt();
bool test_custom_nt();

#endif