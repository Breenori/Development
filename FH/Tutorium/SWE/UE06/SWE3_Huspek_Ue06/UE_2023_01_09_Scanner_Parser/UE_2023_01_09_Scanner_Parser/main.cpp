#include "arithmetic_parser.h"
#include "test_parser_infix.h"
int main() {
	test_parse_from_file();
	test_parse_from_string();
	return 0;
}