#pragma once
#include <iostream>
#include "rational_t.h"
#include "pfc-mini.hpp"
#include "Div_by_Zero.h"
//overall
#pragma region Integrated_Tests
bool test_routine();
void test_block_helper();
void test_block_operators();
void test_block_overloading();
void test_block_cmpnd_assgn_op();
void test_block_cmpr_op();
void test_block_etc();
void test_block_lhs_rhs_op();
void test_constructor();
#pragma endregion
#pragma region Unit_Tests
//constructors
void test_cpy();
void test_constr_one_arg();
void test_constr_two_arg();
//helper
void test_get_num();
void test_get_denom();
void test_set_num();
void test_set_denom();
void test_asstr();
void test_is_neg();
void test_is_pos();
void test_is_zer();
//operators
void test_add();
void test_sub();
void test_mul();
void test_div();
//overloading
void test_add_op();
void test_sub_op();
void test_mul_op();
void test_div_op();
//compound assignment operators
void test_add_op_ass();
void test_sub_op_ass();
void test_mul_op_ass();
void test_div_op_ass();
//compare operators
void test_same_op();
void test_not_same_op();
void test_smaller_op();
void test_smaller_same_op();
void test_bigger_op();
void test_bigger_same_op();
//cpy swap idiom
void test_cpy_swap_idiom();
void test_is_consis();
void test_gcd();
void test_norm();
//lhs & rhs compatibility
void test_lhs_rhs_add();
void test_lhs_rhs_sub();
void test_lhs_rhs_mul();
void test_lhs_rhs_div();
//exception
void test_div_by_zero_exc();
void test_scan();
#pragma endregion

