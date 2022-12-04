#include "rational_t.h"
#include "test.h"
#include <stdexcept>
#include"div_by_zero_error.h"
#include <fstream>
#include<iostream>

int main() {

	std::cout << "Testing number operations: \n";
	test_addition();
	test_sub();
	test_multiplication();
	test_division();
	std::cout << "subtraction is null\n";
	test_sub_is_null();

	std::cout << "\n Testing operator overloading: \n";
	test_addition_op();
	test_subtraction_op();
	test_multiplication_op();
	test_division_op();
	std::cout << "\n Testing operator overloading (incl. assign): \n";
	test_addition_op_ass();
	test_sub_op_ass();
	test_multiplication_op_ass();
	test_division_op_ass();

	std::cout << "\n Testing operator overloading with int: \n";
	test_addition_op_int();
	test_sub_op_int();
	test_mul_op_int();
	test_div_op_int();
	std::cout << "\nTest by division zero:\n";
	test_divide_by_zero();
	std::cout << "\n Testing operator overloading with comparison: \n";
	test_same();
	std::cout << "\n";
	test_different();
	std::cout << "\n";
	test_smaller();
	std::cout << "\n";
	test_smaller_same();
	std::cout << "\n";
	test_bigger();
	std::cout << "\n";
	test_bigger_same();

	std::cout << "Testing Read file:";
	std::cout << "\nNot valid:";
	 test_read_file_not_valid_file();
	std::cout << "\nValid:";
	test_read_file_valid();
	std::cout << "Wrong rational number in file:\n";
	std::cout << "letter in file\n\n";
	//letter in file
	void test_read_file_false1();
	std::cout << "\n\nNo '/' in file\n\n";
	// not / in file
	void test_read_file_false2();

	std::cout << "Testing output:\n";
	std::cout << "\ndenominator and numerator are negative :\n";
	test_output_negativ();
	
	std::cout << "\nnormalize output:\n";
	test_output_normalize();
	std::cout << "\ndenominator is null:\n";
	test_output_null1();
	std::cout << "\nnumerator is null:\n";
	test_output_null2();
	std::cout << "\nTest integer:\n";
	 test_integer_1();
	 std::cout << "\n";
	 test_integer_2();

}