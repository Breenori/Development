
#include <iostream>

#include "arithmetic_variable_parser_test.h"

int main()
{
	int test_cnt = 0;

	std::cout << "Test " << ++test_cnt << ":\n";
	test_with_var();


	std::cout << "Test " << ++test_cnt << ":\n";
	test_var_non_existant();


	std::cout << "Test " << ++test_cnt << ":\n";
	test_updated_var();


	std::cout << "Test " << ++test_cnt << ":\n";
	test_delete_var();
}
