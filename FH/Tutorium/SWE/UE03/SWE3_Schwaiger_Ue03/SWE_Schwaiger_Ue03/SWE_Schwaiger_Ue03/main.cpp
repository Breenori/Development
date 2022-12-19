#include "rational_test.h"

int main() {
	/*
	cout << "Testing normal operations: \n";
	test_add();
	test_sub();
	test_mul();
	test_div();
	cout << " \n\n";
	*/

	/*cout << "Testing overloading operations: \n";
	test_add_op();
	test_sub_op();
	test_mul_op();
	test_div_op();

	cout << "\n\n";
	cout << "Testing overloading operations with assignment: \n";
	test_add_pass();
	test_sub_pass();
	test_mul_pass();
	test_div_pass();*/
	//cout << "\n\n";

	/*cout << "Testing normal operatins with input \n";
	test_add_input();
	test_sub_input();
	test_mul_input();
	test_div_input();*/

	//cout << "Testing compare operators: \n\n";
	//test_compare();
	//test_not_compare();
	//test_smaller_than();
	//test_greater_than();
	//test_smaller();
	//test_greater();
	//cout << " \n\n";

	//cout << "\n Second round: \n";
	//test_compare_2();
	//test_not_compare_2();
	//test_smaller_than_2();
	//test_greater_than_2();
	//test_smaller_2();
	//test_greater_2();
	//cout << " \n\n";

	
	cout << "Testing compare operators overloaded:\n\n";
	test_compare_op();
	test_not_compare_op();
	test_smaller_than_op();
	test_greater_than_op();
	test_smaller_op();
	test_greater_op();
	cout << " \n\n";

	//cout << "Testing getter:\n";
	//test_get_numerator();
	//test_get_denominator();
	//cout << " \n\n";

	cout << "Testing zero, positive, negative: \n ";
	test_is_negative();
	test_is_positive();
	test_is_zero();
	

	//cout << "Testing div by zero with and without input:\n";
	//test_div_by_zero();
	//test_div_by_zero_in();
	
	return 0;
}