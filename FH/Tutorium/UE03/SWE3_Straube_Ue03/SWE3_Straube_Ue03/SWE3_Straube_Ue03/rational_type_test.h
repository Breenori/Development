#ifndef RATIONAL_T_TEST
#define RATIONAL_T_TEST

/*
* ----- Includes. -----
*/
#include "rational_type.h"

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

bool test_as_string();
bool test_print();
bool test_operatorassignment();
bool test_constructor();
bool test_scan();
bool test_get_numerator();
bool test_get_denominator();
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

#endif