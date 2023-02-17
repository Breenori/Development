
#include "test_arithmetic_parser.h"

void main() {
	test_single_value();
	test_single_PExpression();
	test_invalid_start();
	test_invalid_middle();
	test_multiple_closing();
	test_multiple_ops_invalid();
	test_multiple_ops_valid();
	test_multiple_PExpressions();
	test_klapustri();
	test_division_by_zero();
	test_several_expressions();
	test_empty_file();
}