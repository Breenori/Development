#ifndef test_rational_type_h
#define test_rational_type_h

#include "rational_type.h"
#include "number.h"
#include <fstream>
#include <ostream>

void test_number();
void test_inverse();
void test_string();

void test_all_calculations();
void test_addition(rational_t<Number<int>> first, rational_t<Number<int>> const& second);
void test_subtraction(rational_t<Number<int>> first, rational_t<Number<int>> const& second);
void test_multiplication(rational_t<Number<int>> first, rational_t<Number<int>> const& second);
void test_division(rational_t<Number<int>> first, rational_t<Number<int>> const& second);

void test_all_calculations_op();
void test_addition_op(rational_t<Number<int>> const& first, rational_t<Number<int>> const& second);
void test_subtraction_op(rational_t<Number<int>> const& first, rational_t<Number<int>> const& second);
void test_multiplication_op(rational_t<Number<int>> const& first, rational_t<Number<int>> const& second);
void test_division_op(rational_t<Number<int>> const& first, rational_t<Number<int>> const& second);

void test_all_calculations_op_assign();
void test_addition_op_assign(rational_t<Number<int>> first, rational_t<Number<int>> second);
void test_subtraction_op_assign(rational_t<Number<int>> first, rational_t<Number<int>> second);
void test_multiplication_op_assign(rational_t<Number<int>> first, rational_t<Number<int>> const& second);
void test_division_op_assign(rational_t<Number<int>> first, rational_t<Number<int>> const& second);

void test_all_logical_operators();
void test_equal();
void test_unequal();
void test_smaller();
void test_smaller_or_equal();
void test_bigger();
void test_bigger_or_equal();

void test_divide_by_zero();





#endif

