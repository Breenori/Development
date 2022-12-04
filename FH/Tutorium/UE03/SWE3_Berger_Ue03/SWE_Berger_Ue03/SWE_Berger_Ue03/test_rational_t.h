#ifndef TEST_RATIONAL_T_H
#define TEST_RATIONAL_T_H

#include "div_by_zero_error.h"
#include "rational_t.h"

void test_all_calculations();
void test_addition(rational_t first, rational_t const& second);
void test_subtraction(rational_t first, rational_t const& second);
void test_multiplication(rational_t first, rational_t const& second);
void test_division(rational_t first, rational_t const & second);

void test_all_calculations_op();
void test_addition_op(rational_t const& first, rational_t const& second);
void test_subtraction_op(rational_t const& first, rational_t const& second);
void test_multiplication_op(rational_t const& first, rational_t const& second);
void test_division_op(rational_t const& first, rational_t const& second);

void test_all_calculations_op_assign();
void test_addition_op_assign(rational_t first, rational_t second);
void test_subtraction_op_assign(rational_t first, rational_t second);
void test_multiplication_op_assign(rational_t first, rational_t const&  second);
void test_division_op_assign(rational_t first, rational_t const& second);

void test_all_calculations_op_int();
void test_addition_op_int();
void test_subtraction_op_int();
void test_multiplication_op_int();
void test_division_op_int();

void test_divide_by_zero();

void test_scan_print();

void test_all_logical_operators();
void test_equal();
void test_unequal();
void test_smaller();
void test_smaller_or_equal();
void test_bigger();
void test_bigger_or_equal();

void test_example_from_instruction();










#endif
