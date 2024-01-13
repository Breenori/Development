

#include <iostream>

#include "prefix_parser_test.h"

int main()
{
    int test_cnt = 0;

    std::cout << "Test "<<++test_cnt<<"\n";
    test_inv_file();


    std::cout << "Test " << ++test_cnt << "\n";
    test_working_file();


    std::cout << "Test " << ++test_cnt << "\n";
    test_simple_expr();


    std::cout << "Test " << ++test_cnt << "\n";
    test_neg_nrs();


    std::cout << "Test " << ++test_cnt << "\n";
    test_mult_div();


    std::cout << "Test " << ++test_cnt << "\n";
    test_add_sub();


    std::cout << "Test " << ++test_cnt << "\n";
    neg_test_simple_expr();

    std::cout << "Test " << ++test_cnt << "\n";
    neg_test_mult_div();

    std::cout << "Test " << ++test_cnt << "\n";
    neg_test_div_by_zero();
}

