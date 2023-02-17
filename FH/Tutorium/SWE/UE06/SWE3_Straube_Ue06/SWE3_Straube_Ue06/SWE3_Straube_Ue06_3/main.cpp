/*
* ----- Includes. -----
*/
#include "arithmetic_parser_test.h"

/*
* return int
*/
int main() {
	test_division_zero();
	test_empty();
	test_single_numbers();
	test_multiple_usage();
	test_variables_only();
	test_parenthesis();
	test_nonsense();
	test_custom();

	return 0;
}