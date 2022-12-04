#pragma once
#include "rational.h"
#include <fstream>

void test_constructor1();
void test_constructor2();
void test_constructor3();
void test_constructor3_invalid_input();
void test_copy_constructor();

void test_normalize();
void test_scan();

void test_get_numerator();
void test_get_denominator();

void test_is_negative(rational_t const& rat);
void test_is_positive(rational_t const& rat);
void test_is_zero(rational_t const& rat);

//assignment operator test
void test_assignment_op();

//comparison operators tests
void test_equal_op();
void test_not_equal_op();
void test_less_op();
void test_less_or_equal_op();
void test_greater_op();
void test_greater_or_equal_op();

//arithmetic functions tests
void test_add();
void test_sub();
void test_mul();
void test_div();

//<< >>
void test_write_to_stream();
void test_read_from_stream();