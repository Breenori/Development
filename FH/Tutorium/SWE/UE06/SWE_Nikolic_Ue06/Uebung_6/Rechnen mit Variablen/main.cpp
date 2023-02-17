#include "test_arithmetic_parser.h"

int main() {
	test_single_char_identifier();
	test_complex_identifier();
	test_invalid_identifier();
	test_unknown_identifier();
	test_identifiers();
	return 0;
}
