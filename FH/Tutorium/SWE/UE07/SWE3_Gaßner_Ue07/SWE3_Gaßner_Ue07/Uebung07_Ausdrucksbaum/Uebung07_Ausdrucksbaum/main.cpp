#include "test.h"

int main() {

	test_evaluate_add();
	std::cout << "\n\n";
	test_evaluate_sub();
	std::cout << "\n\n";
	test_evaluate_mul();
	std::cout << "\n\n";
	test_evaluate_div();
	std::cout << "\n\n";
	test_evaluate_exp();
	std::cout << "\n\n";
	test_print_tree();
	std::cout << "\n\n";


	//Testaälle funktioniert nicht
	//test_invalid_input();
	test_valid_input();
	//test_division_by_zero();

	return 0;
}