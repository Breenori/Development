#pragma once
#include "rational_extended.h"

void test_task_1();
void test_task_2();
void test_task_4();
void test_task_8();
void test_task_9();

//Tests with T=int
void test_constructor1();
void test_constructor2();
void test_constructor3();
void test_constructor3_invalid_input();
void test_copy_constructor();

void test_get_numerator();
void test_get_denominator();
void test_inverse();

void test_add();
void test_sub();
void test_mul();
void test_div();
void test_assignment_op();

void test_equal_op();
void test_not_equal_op();
void test_less_op();
void test_less_or_equal_op();
void test_greater_op();
void test_greater_or_equal_op();

void test_write_to_stream();
void test_read_from_stream();

//Tests with T=double
void test_constructor1_double();
void test_constructor2_double();
void test_constructor3_double();
void test_constructor3_invalid_input_double();
void test_copy_constructor_double();

void test_get_numerator_double();
void test_get_denominator_double();

void test_inverse_double();

void test_add_double();
void test_sub_double();
void test_mul_double();
void test_div_double();

void test_assignment_op_double();

void test_equal_op_double();
void test_not_equal_op_double();
void test_less_op_double();
void test_less_or_equal_op_double();
void test_greater_op_double();
void test_greater_or_equal_op_double();

void test_write_to_stream_double();
void test_read_from_stream_double();

// Tests independent T
template <typename T>
void test_is_negative(rational_t<T> const& rat);

template <typename T>
void test_is_positive(rational_t<T> const& rat);

template <typename T>
void test_is_zero(rational_t<T> const& rat);

//Tests with T=number_t<int>
void test_constructor1_number_t();
void test_constructor2_number_t();
void test_constructor3_number_t();
void test_constructor3_invalid_input_number_t();
void test_copy_constructor_number_t();

void test_get_numerator_number_t();
void test_get_denominator_number_t();
void test_inverse_number_t();

void test_add_number_t();
void test_sub_number_t();
void test_mul_number_t();
void test_div_number_t();

void test_assignment_op_number_t();

void test_equal_op_number_t();
void test_not_equal_op_number_t();
void test_less_op_number_t();
void test_less_or_equal_op_number_t();
void test_greater_op_number_t();
void test_greater_or_equal_op_number_t();

void test_write_to_stream_number_t();
void test_read_from_stream_number_t();