
#include <iostream>
#include <string>
#include <sstream>

#include "arithmetic_parser_test.h"

int main()
{
	int test_cnt = 0;

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	test_inv_file();


	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	test_working_file();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	test_simple_expr();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	test_neg_nrs();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	test_p_expr();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	test_mult_div();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	test_add_sub();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	neg_test_simple_expr();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	neg_test_term();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	neg_test_mult_div();

	std::cout << "Test " << ++test_cnt << ":" << std::endl;
	neg_test_div_by_zero();

}

