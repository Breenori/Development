#include "test_arithmetic_parser.h"

int main() {
	test_negative_value_invalid();
	test_negative_value_valid();
	test_invalid_start();
	test_invalid_middle();
	test_too_many_ops();
	test_several_expressions();
	complex_expression();
	complex_expression_2();
	test_division_by_zero();
	test_empty_file();

	return 0;
}
