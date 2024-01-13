//
// Created by Lukas Steininger on 07.02.23.
//

#ifndef EXPRESSION_TREES_TEST_PARSE_SYNTAX_TREE_H
#define EXPRESSION_TREES_TEST_PARSE_SYNTAX_TREE_H

#include "parser.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::stringstream;

class test_parse_syntax_tree {
public:
    static bool test_output_number();
    static bool test_output_expression();
    static bool test_output_nested_expression();
    static bool test_assign_number_and_output();
    static bool test_assign_expression_and_output();
    static bool test_assign_nested_expression_and_output();
    static bool test_exponent();
    static bool test_negative_number();
    static bool test_negative_expression();
    static bool test_reassign_var();
    static bool test_use_later_assigned_var_in_assignment();
    static bool test_use_unassigned_var_in_output();
    static bool test_unregistered_keyword();
    static bool test_division_by_zero_direct();
    static bool test_division_by_zero_var();
    static bool test_invalid_output();
    static bool test_invalid_assignment();
    static bool test_invalid_expression();
    static bool test_print_name_list();
};


#endif //EXPRESSION_TREES_TEST_PARSE_SYNTAX_TREE_H
