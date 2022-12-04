#ifndef test_h
#define div_by zero_h
#include "rational_t.h"
#include"div_by_zero_error.h"

//test _invoice types
void test_addition();
void test_sub();
void test_sub_is_null();
void test_multiplication();
void test_division();
//op
void test_addition_op();
void test_subtraction_op();
void test_multiplication_op();
void test_division_op();

//op assign
void test_addition_op_ass();
void test_sub_op_ass();
void test_multiplication_op_ass();
void test_division_op_ass();

//test with int
void test_addition_op_int();
void test_sub_op_int();
void test_mul_op_int();
void test_div_op_int();



void test_divide_by_zero();
//test compare op
void test_same();	
void test_different();
void test_smaller();
void test_smaller_same();
void test_bigger();
void test_bigger_same();

//test read
void test_read_file_not_valid_file();
void test_read_file_valid();
//letter in file
void test_read_file_false1();
// not / in file
void test_read_file_false2();
// test ausgabe
//denominator and numerator are negative
void test_output_negativ();
// fracture must be shortened
void test_output_normalize();
//can be output as an integervoid test_integer_1();
void test_integer_2();
//denominator is 0
void test_output_null1();

//numerator is 0 
void test_output_null2();
#endif