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
	test_simple_operations();
	test_nonsense();
	test_custom();

	return 0;
}