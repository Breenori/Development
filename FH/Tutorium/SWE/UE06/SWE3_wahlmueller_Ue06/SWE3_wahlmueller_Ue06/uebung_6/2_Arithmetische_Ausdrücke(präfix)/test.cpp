#include "test.h"
//präfix

//user input single numbers
void test_1() {

	cout << "Test 1\n";

	ArithmeticParser p;
	string test{ "+ 4" };
	istringstream instr{ test };

	try {
		cout << "Input: " << test << "\n";
		cout << "Output (Exp_output 4): " << p.parse(instr);
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";

	ArithmeticParser p_2;
	string test_2{ "- 0 4" };
	istringstream instr_2{ test_2 };

	try {
		cout << "Input: " << test_2 << "\n";
		cout << "Output (Exp_output -4): " << p_2.parse(instr_2);
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";

	ArithmeticParser p_3;
	string in;
	cin >> in;
	istringstream in_str{ in };

	try {
		cout << "Input: " << in << "\n";
		cout << "Output (Exp_output ?): " << p_3.parse(in_str);
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

}

//test wrong & empty
void test_2() {

	cout << "Test 2\n";

	string test{ "())" };
	ArithmeticParser p;
	istringstream instr{ test };

	try {
		cout << "Input: " << test << "\n";
		cout << "Output (Exp_output Exception): " << p.parse(instr);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_2{ "" };
	ArithmeticParser p_2;
	istringstream instr_2{ test_2 };

	try {
		cout << "Input: " << test_2 << "\n";
		cout << "Output (Exp_output Exception): " << p_2.parse(instr_2);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

}

//div_by_zero
void test_3() {

	cout << "Test 3\n";

	string test{ "/ 5 0" };
	ArithmeticParser p;
	istringstream instr{ test };

	try {
		cout << "Input: " << test << "\n";
		cout << "Output (Exp_output Exception): " << p.parse(instr);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

}

//operator
void test_4() {

	cout << "Test 4\n";

	string test{ "+ 5 5" };
	ArithmeticParser p;
	istringstream instr{ test };

	try {
		cout << "Input: " << test << "\n";
		cout << "Output (Exp_output 10): " << p.parse(instr);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_2{ "- 3 8" };
	ArithmeticParser p_2;
	istringstream instr_2{ test_2 };

	try {
		cout << "Input: " << test_2 << "\n";
		cout << "Output (Exp_output -5): " << p_2.parse(instr_2);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_3{ "* 3 5" };
	ArithmeticParser p_3;
	istringstream instr_3{ test_3 };

	try {
		cout << "Input: " << test_3 << "\n";
		cout << "Output (Exp_output 15): " << p_3.parse(instr_3);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_4{ "/ 5 5" };
	ArithmeticParser p_4;
	istringstream instr_4{ test_4 };

	try {
		cout << "Input: " << test_4 << "\n";
		cout << "Output (Exp_output 1): " << p_4.parse(instr_4);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

}

void test_5() {

	cout << "Test 5\n";

	string test{ "/ + 4 9 + 17 2" };
	ArithmeticParser p;
	istringstream instr{ test };

	try {
		cout << "Input: " << test << "\n";
		cout << "Output (Exp_output 0,684211): " << p.parse(instr);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_2{ "+ - 0 5 - 0 5" };
	ArithmeticParser p_2;
	istringstream instr_2{ test_2 };

	try {
		cout << "Input: " << test_2 << "\n";
		cout << "Output (Exp_output -10): " << p_2.parse(instr_2);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

}