/*
* ----- Includes. -----
*/
#include "rational_type_test.h"

int main() {
	test_as_string();
	test_print();
	test_operatorassignment();
	test_constructor();
	test_scan();
	test_get_numerator();
	test_get_denominator();
	test_normalize();
	test_add();
	test_sub();
	test_mul();
	test_div();
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
	test_custom();

	return 0;
}