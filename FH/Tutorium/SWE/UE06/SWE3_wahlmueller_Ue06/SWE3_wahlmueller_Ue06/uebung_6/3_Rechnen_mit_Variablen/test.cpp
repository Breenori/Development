#include "test.h"
//map_vars

//user input single numbers
void test_1(){

	cout << "Test 1\n";

	ArithmeticParser p;
	string test{ "x" };
	istringstream instr{ test };

	try {
		cout << "Input: " << test << " = 4" << "\n";
		p.set_variables("x", 4);
		cout << "Output (Exp_output 4): " << p.parse(instr);
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (variable_exception& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";

	ArithmeticParser p_2;
	string test_2{ "y" };
	istringstream instr_2{ test_2 };

	try {
		cout << "Input: " << test_2 << " = -4" << "\n";
		p_2.set_variables("y", -4);
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
		cout << "Input: " << in << " x = 12, y = 4, z = -8" << "\n";
		p_3.set_variables("z", -8);
		p_3.set_variables("x", 12);
		p_3.set_variables("y", 4);
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
void test_2(){

	cout << "Test 2\n";

	string test{ "5-y" };
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
	string test_2{ "l-k" };
	ArithmeticParser p_2;
	istringstream instr_2{ test_2 };

	try {
		cout << "Input: " << test_2  << " k = 5" << "\n";
		p_2.set_variables("k", 4);
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

	string test{ "5/x" };
	ArithmeticParser p;
	istringstream instr{ test };

	try {
		cout << "Input: " << test << " x = 0" << "\n";
		p.set_variables("x", 0);
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

//operator
void test_4(){

	cout << "Test 4\n";

	string test{ "5+x" };
	ArithmeticParser p;
	istringstream instr{ test };

	try {
		cout << "Input: " << test << " x = 5" << "\n";
		p.set_variables("x", 5);
		cout << "Output (Exp_output 10): " << p.parse(instr);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_2{ "y-8" };
	ArithmeticParser p_2;
	istringstream instr_2{ test_2 };

	try {
		cout << "Input: " << test_2 << " y = 3" << "\n";
		p_2.set_variables("y", 3);
		cout << "Output (Exp_output -5): " << p_2.parse(instr_2);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_3{ "3*z" };
	ArithmeticParser p_3;
	istringstream instr_3{ test_3 };

	try {
		cout << "Input: " << test_3 << " z = 5" << "\n";
		p_3.set_variables("z", 5);
		cout << "Output (Exp_output 15): " << p_3.parse(instr_3);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_4{ "5/a" };
	ArithmeticParser p_4;
	istringstream instr_4{ test_4 };

	try {
		cout << "Input: " << test_4 << " a = 5" << "\n";
		p_4.set_variables("a", 5);
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

	string test{ "a+(b*c+(d-e))/c" };
	ArithmeticParser p;
	istringstream instr{ test };

	try {
		cout << "Input: " << test << " a = 8, b = 7, c = 5, d = 2, e = 9" << "\n";
		p.set_variables("a", 8);
		p.set_variables("b", 7);

		p.set_variables("c", 5);
		p.set_variables("d", 2);

		p.set_variables("e", 9);
		cout << "Output (Exp_output 13,6): " << p.parse(instr);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

	cout << "\n\n";
	string test_2{ "negative_zahl+negativ" };
	ArithmeticParser p_2;
	istringstream instr_2{ test_2 };

	try {
		cout << "Input: " << test_2 << " negative_zahl = -5 negativ = -5" << "\n";
		p_2.set_variables("negative_zahl", -5);
		p_2.set_variables("negativ", -5);
		cout << "Output (Exp_output -10): " << p_2.parse(instr_2);
	}

	catch (ParserException& e) {
		cout << e.what() << "\n";
	}

	catch (div_by_zero_error& e) {
		cout << e.what() << "\n";
	}

}