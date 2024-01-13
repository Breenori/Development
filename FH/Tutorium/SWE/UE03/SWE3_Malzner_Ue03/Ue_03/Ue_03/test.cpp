#include "test.h"

void test_1_print_console() {
	try {
		std::cout << "Test 1: print on console:\n";
		rational_t number1(10, 5);
		number1.print();
		std::cout << "\n";
		rational_t number2(5, 1);
		number2.print();
	}
	catch(DivideByZeroError & e){
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_2_print_in_file() {
	try {
		std::cout << "Test 2: print in file:\n\tSee File in directory!";
		std::ofstream out{ "output.txt" };
		rational_t number1(10, 5);
		number1.print(out);
		out << "\n";
		rational_t number2(5, 1);
		number2.print(out);
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_3_scan_from_file() {
	try {
		std::cout << "Test 3: scan from file input.txt\n";
		std::ifstream in("input.txt");
		rational_t number;
		number.scan(in);
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_4_scan_from_empty_file() {
	try {
		std::cout << "Test 4: scan from empty file empty.txt\n";
		std::ifstream in("empty.txt");
		rational_t number;
		number.scan(in);
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_5_invalid_input_from_file() {
	try {
		std::cout << "Test 5: scan from invalid file invalid.txt\n";
		std::ifstream in("invalid.txt");
		rational_t number;
		number.scan(in);
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_6_invalid_input_from_file() {
	try {
		std::cout << "Test 6: scan from invalid file invalid2.txt\n";
		std::ifstream in("invalid2.txt");
		rational_t number;
		number.scan(in);
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
	
}

void test_7_negative_numbers_from_file() {
	try {
		std::cout << "Test 7: scan negative numbers from file negative1.txt\n";
		std::ifstream in("negative1.txt");
		rational_t number;
		number.scan(in);
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_8_negative_numbers_from_file() {
	try {
		std::cout << "Test 8: scan negative numbers from file negative2.txt\n";
		std::ifstream in("negative2.txt");
		rational_t number;
		number.scan(in);
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_9_division_by_zero_from_file() {
	try {
		std::cout << "Test 9: Division by Zero from File zero.txt\n";
		std::ifstream in("zero.txt");
		rational_t number;
		number.scan(in);
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_10_invalid_input_from_console() {
	try {
		std::cout << "Test 10: Invalid Input from Console\n";
		rational_t number;
		number.scan();
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_11_valid_input_from_console() {
	try {
		std::cout << "Test 11: Valid Input from Console\n";
		rational_t number;
		number.scan();
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_12_division_by_zero_from_console() {
	try {
		std::cout << "Test 12: Division by Zero from Console\n";
		rational_t number;
		number.scan();
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_13_normalize() {
	try {
		std::cout << "Test 13: Normalization\n";
		rational_t number(10, 5);
		number.test_normalize();
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_14_normalize() {
	try {
		std::cout << "Test 14: Normalization\n";
		rational_t number(9555, 143);
		number.test_normalize();
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_15_normalize() {
	try {
		std::cout << "Test 15: Normalization\n";
		rational_t number(-18, -3);
		number.test_normalize();
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_16_invalid_output_on_console() {
	try {
		std::cout << "Test 16: Invalid Output on Console\n";
		rational_t number(4, 0);
		number.test_normalize();
		number.print();
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_17_to_string() {
	std::cout << "Test 17: as_string\n";
	rational_t number(-4, 5);
	std::string number_as_string = number.as_string();
	std::cout << number_as_string;
}

void test_18_get_numerator_denominator() {
	std::cout << "Test 18: get Numerator / Separator\n";
	rational_t number(4, 5);
	int _num = number.get_numerator();
	int _denom = number.get_denominator();
	std::cout << '<' << _num << '/' << _denom << '>';
}

void test_19_copy_constructor() {
	std::cout << "Test 19: Copy-Constructor\n";
	rational_t other1(3,5);
	rational_t number1(other1);
	number1.print();
	std::cout << "\n";
	rational_t other2(3, 5);
	rational_t number2 = other2;
	number2.print();
}

void test_20_overload_compare_operators() {
	try {
		std::cout << "Test 20: Overloading Compare Operators\n";
		rational_t other(-1, 2);
		rational_t number(1, 3);
		// <
		if (number < other) {
			std::cout << "Number < Other\n";
		}
		else {
			std::cout << "Other < Number\n";
		}
		// >
		if (number > other) {
			std::cout << "Number > Other\n";
		}
		else {
			std::cout << "Other > Number\n";
		}
		// <=
		if (number <= other) {
			std::cout << "Number <= Other\n";
		}
		else {
			std::cout << "Other <= Number\n";
		}
		// >=
		if (number >= other) {
			std::cout << "Number >= Other\n";
		}
		else {
			std::cout << "Other >= Number\n";
		}
		//==
		if (number == other) {
			std::cout << "Number == Other\n";
		}
		else {
			std::cout << "Number!= Other\n";
		}
		//!=
		if (number != other) {
			std::cout << "Number != Other\n";
		}
		else {
			std::cout << "Number== Other\n";
		}
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_21_overload_compare_operators() {
	try{
	std::cout << "Test 21: Overloading Compare Operators\n";
	rational_t other(3, 17);
	rational_t number(2, 9);
	rational_t other2(2, 3);
	rational_t number2(2, 3);
	rational_t number3(3, 0);
	// <
	if (number < other) {
		std::cout << "Number < Other\n";
	}
	else {
		std::cout << "Other < Number\n";
	}
	// >
	if (number > other) {
		std::cout << "Number > Other\n";
	}
	else {
		std::cout << "Other > Number\n";
	}
	// <=
	if (number <= other) {
		std::cout << "Number <= Other\n";
	}
	else {
		std::cout << "Other <= Number\n";
	}
	// >=
	if (number >= other) {
		std::cout << "Number >= Other\n";
	}
	else {
		std::cout << "Other >= Number\n";
	}
	//==
	if (number2 == other2) {
		std::cout << "Number == Other\n";
	}
	else {
		std::cout << "Number!= Other\n";
	}
	//!=
	if (number3 != other2) {
		std::cout << "Number != Other\n";
	}
	else {
		std::cout << "Number== Other\n";
	}
}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_22_basic_arithmetics() {
	try {
		std::cout << "Test 22: Basic Arithmetics\n";
		rational_t number1(1, 3);
		rational_t number2(1, 3);
		rational_t number3(1, 3);
		rational_t number4(1, 3);
		rational_t other(1, 5);
		number1.mul(other);
		number1.print();
		std::cout << "\n";
		number2.div(other);
		number2.print();
		std::cout << "\n";
		number3.add(other);
		number3.print();
		std::cout << "\n";
		number4.sub(other);
		number4.print();
		std::cout << "\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_23_basic_arithmetics() {
	try {
		std::cout << "Test 23: Basic Arithmetics\n";
		rational_t number1(-2, 7);
		rational_t number2(-2, 7);
		rational_t number3(-2, 7);
		rational_t number4(-2, 7);
		rational_t other(2, 9);
		number1.mul(other);
		number1.print();
		std::cout << "\n";
		number2.div(other);
		number2.print();
		std::cout << "\n";
		number3.add(other);
		number3.print();
		std::cout << "\n";
		number4.sub(other);
		number4.print();
		std::cout << "\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_24_basic_arithmetics() {
	try {
		std::cout << "Test 24: Basic Arithmetics\n";
		rational_t number1(-2, 7);
		rational_t number2(-2, 7);
		rational_t number3(-2, 7);
		rational_t number4(-2, 7);
		rational_t other(2, 0);
		number1.mul(other);
		number1.print();
		std::cout << "\n";
		number2.div(other);
		number2.print();
		std::cout << "\n";
		number3.add(other);
		number3.print();
		std::cout << "\n";
		number4.sub(other);
		number4.print();
		std::cout << "\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_25_basic_arithmetics_overload() {
	std::cout << "Test 25: Basic Arithmetics Overload\n";
	try {
		rational_t number(-2, 7);
		rational_t other(2, 0);
		rational_t result1 = number + other;
		result1.print(); std::cout << "\n";
		rational_t result2 = number - other;
		result2.print(); std::cout << "\n";
		rational_t result3 = number / other;
		result3.print(); std::cout << "\n";
		rational_t result4 = number * other;
		result4.print(); std::cout << "\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_26_basic_arithmetics_overload() {
	std::cout << "Test 26: Basic Arithmetics Overload\n";
	try {
		rational_t number(-2, 7);
		rational_t other(2, 9);
		rational_t result1 = number + other;
		result1.print(); std::cout << "\n";
		rational_t result2 = number - other;
		result2.print(); std::cout << "\n";
		rational_t result3 = number / other;
		result3.print(); std::cout << "\n";
		rational_t result4 = number * other;
		result4.print(); std::cout << "\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_27_basic_arithmetic_compound_assignment() {
	std::cout << "Test 27: Basic Arithmetics Compound Assignment\n";
	try {
		rational_t number1(-2, 7);
		rational_t number2(-2, 7);
		rational_t number3(-2, 7);
		rational_t number4(-2, 7);
		rational_t other(2, 9);
		number1 += other;
		number1.print(); std::cout << "\n";
		number2 -= other;
		number2.print(); std::cout << "\n";
		number3 /= other; 
		number3.print(); std::cout << "\n";
		number4 *= other; 
		number4.print(); std::cout << "\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_28_basic_arithmetic_compound_assignment() {
	std::cout << "Test 28: Basic Arithmetics Compound Assignment\n";
	try {
		rational_t number1(-2, 7);
		rational_t number2(-2, 7);
		rational_t number3(-2, 7);
		rational_t number4(-2, 7);
		rational_t other(2, 0);
		number1 += other;
		number1.print(); std::cout << "\n";
		number2 -= other;
		number2.print(); std::cout << "\n";
		number3 /= other;
		number3.print(); std::cout << "\n";
		number4 *= other;
		number4.print(); std::cout << "\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_29_overloading_output() {
	std::cout << "Test 29: Overloading Output Operator\n";
	try {
		rational_t number1(-2, 7);
		std::cout << number1 << "\n\n";
		rational_t number2(3, 5);
		std::cout << number2 << "\n\n";
		rational_t number3(3, 0);
		std::cout << number3 << "\n\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}

void test_30_overloading_input() {
	std::cout << "Test 30: Overloading Input Operator\n";
	try {
		rational_t number1(2,1);
		std::cin >> number1;
		rational_t number2(3, 5);
		std::cin >> number2;
		rational_t number3(3, 0);
		std::cin >> number3;
		std::cout << number1 << "  " << number2 << "  " << number3 << "\n";
	}
	catch (DivideByZeroError& e) {
		std::cout << e.what() << "\n";
		std::cout << "Dominator 0 ....";
	}
}




