#include "test_rational_t.h"

//test for all calculations with different overloaded operators.
void test_all_calculations(){
	std::cout << "Testing all operation methods: \n";
	rational_t a1(5, 4);
	rational_t b1(3, 2);
	rational_t a2(8, 2);
	rational_t b2(9, 5);
	rational_t a3(-5, 12);
	rational_t b3(4, 3);

	std::cout << "\nAddition: \n";
	test_addition(a1, b1);
	test_addition(a2, b2);
	test_addition(a3, b3);
	std::cout << "\nSubtraction: \n";
	test_subtraction(a1, b1);
	test_subtraction(a2, b2);
	test_subtraction(a3, b3);
	std::cout << "\nMultiplication: \n";
	test_multiplication(a1, b1);
	test_multiplication(a2, b2);
	test_multiplication(a3, b3);
	std::cout << "\nDivision: \n";
	test_division(a1, b1);
	test_division(a2, b2);
	test_division(a3, b3);
}
void test_addition(rational_t first, rational_t const& second){
	first.add(second);
	rational_t::print_result(first);
}
void test_subtraction(rational_t first, rational_t const& second) {
	first.sub(second);
	rational_t::print_result(first);
}
void test_multiplication(rational_t first, rational_t const& second) {
	first.mul(second);
	rational_t::print_result(first);
}
void test_division(rational_t first, rational_t const & second) {
	first.div(second);
	rational_t::print_result(first);
}

void test_all_calculations_op(){
	std::cout << "\nTesting all operations with overloaded operator: \n";
	rational_t a1(5, 4);
	rational_t b1(3, 2);
	rational_t a2(8, 2);
	rational_t b2(9, 5);
	rational_t a3(-5, 12);
	rational_t b3(4, 3);

	std::cout << "\nAddition: \n";
	test_addition_op(a1, b1);
	test_addition_op(a2, b2);
	test_addition_op(a3, b3);
	std::cout << "\nSubtraction: \n";
	test_subtraction_op(a1, b1);
	test_subtraction_op(a2, b2);
	test_subtraction_op(a3, b3);
	std::cout << "\nMultiplication: \n";
	test_multiplication_op(a1, b1);
	test_multiplication_op(a2, b2);
	test_multiplication_op(a3, b3);
	std::cout << "\nDivision: \n";
	test_division_op(a1, b1);
	test_division_op(a2, b2);
	test_division_op(a3, b3);
}
void test_addition_op(rational_t const & first, rational_t const& second){
	rational_t c = first + second;
	rational_t::print_result(c);
}
void test_subtraction_op(rational_t const & first, rational_t const& second){
	rational_t c = first - second;
	rational_t::print_result(c);
}
void test_multiplication_op(rational_t const & first, rational_t const & second){
	rational_t c = first * second;
	rational_t::print_result(c);
}
void test_division_op(rational_t const & first, rational_t const & second){
	rational_t c = first / second;
	rational_t::print_result(c);
}

void test_all_calculations_op_assign(){
	std::cout << "Testing all operations with overloaded assign and operator: \n";
	rational_t a1(5, 4);
	rational_t b1(3, 2);
	rational_t a2(8, 2);
	rational_t b2(9, 5);
	rational_t a3(-5, 12);
	rational_t b3(4, 3);

	std::cout << "\nAddition: \n";
	test_addition_op_assign(a1, b1);
	test_addition_op_assign(a2, b2);
	test_addition_op_assign(a3, b3);
	std::cout << "\nSubtraction: \n";
	test_subtraction_op_assign(a1, b1);
	test_subtraction_op_assign(a2, b2);
	test_subtraction_op_assign(a3, b3);
	std::cout << "\nMultiplication: \n";
	test_multiplication_op_assign(a1, b1);
	test_multiplication_op_assign(a2, b2);
	test_multiplication_op_assign(a3, b3);
	std::cout << "\nDivision: \n";
	test_division_op_assign(a1, b1);
	test_division_op_assign(a2, b2);
	test_division_op_assign(a3, b3);
}
void test_addition_op_assign(rational_t first, rational_t second){
	first += second;
	rational_t::print_result(first);
}
void test_subtraction_op_assign(rational_t first, rational_t second){
	first -= second;
	rational_t::print_result(first);
}
void test_multiplication_op_assign(rational_t first, rational_t const & second){
	first *= second;
	rational_t::print_result(first);
}
void test_division_op_assign(rational_t first, rational_t const & second){
	first /= second;
	rational_t::print_result(first);
}

void test_all_calculations_op_int(){
	std::cout << "Testing the calculations of an rational object with an int in both directions: \n";
	std::cout << "Addition: \n";
	test_addition_op_int();
	std::cout << "\nSubtraction: \n";
	test_subtraction_op_int();
	std::cout << "\nMultiplication: \n";
	test_multiplication_op_int();
	std::cout << "\nDivision: \n";
	test_division_op_int();
}
void test_addition_op_int(){
	rational_t a(-5, 12);
	int b = 5;
	rational_t c = a + b;
	rational_t d = b + a;
	rational_t::print_result(c);
	rational_t::print_result(d);

}
void test_subtraction_op_int(){
	rational_t a(-5, 12);
	int b = 5;
	rational_t c = a - b;
	rational_t d = b - a;
	rational_t::print_result(c);
	rational_t::print_result(d);
}
void test_multiplication_op_int(){
	rational_t a(-5, 12);
	int b = 5;
	rational_t c = a * b;
	rational_t d = b * a;
	rational_t::print_result(c);
	rational_t::print_result(d);
}
void test_division_op_int(){
	rational_t a(-5, 12);
	int b = 5;
	rational_t c = a / b;
	rational_t d = b / a;
	rational_t::print_result(c);
	rational_t::print_result(d);
}

//divide by zero exception
void test_divide_by_zero() {
	rational_t a(2, 1);
	rational_t b(0, 0);
	try {
		b.div(a);

	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}
	std::cout << "Processing with execution ... \n\n";
}

//scan and print elements - the overload output operator << is tested in all calculation functions
//(they call print_result() where the << operator is used)
void test_scan_print(){
	std::cout << "Testing the scan and print function: \n";
	rational_t a;
	rational_t b;
	rational_t c;
	rational_t d;

	std::ifstream ifs1("test_scan1.txt");
	std::ifstream ifs2("test_scan2.txt");
	std::ifstream ifs3("test_scan3.txt");
	std::ifstream ifs4("test_scan4.txt");

	a.scan(ifs1);
	rational_t::print_result(a);
	b.scan(ifs2);
	rational_t::print_result(b);
	c.scan(ifs3);
	rational_t::print_result(c);
	d.scan(ifs4);
	rational_t::print_result(d);
}

//logical operators
void test_all_logical_operators(){
	std::cout << "Testing all logical operators: \n";
	std::cout << "\nTesting equal (==): \n";
	test_equal();
	std::cout << "\nTesting unequal (!=): \n";
	test_unequal();
	std::cout << "\nTesting smaller (<): \n";
	test_smaller();
	std::cout << "\nTesting smaller or equal (<=): \n";
	test_smaller_or_equal();
	std::cout << "\nTesting bigger (>): \n";
	test_bigger();
	std::cout << "\nTesting bigger or equal (>=): \n";
	test_bigger_or_equal();
}
void test_equal(){
	rational_t a(5, 4);
	rational_t b(3, 2);
	rational_t c(10, 8);

	if (a == b) {
		std::cout << "a" << a << " is the same as b" << b << "\n";
	}
	else{
		std::cout << "a" << a << " is not the same as b" << b << "\n";
	}
	if(a == c){
		std::cout << "a" << a << " is the same as c" << c << "\n";
	}
	else{
		std::cout << "a" << a << " is not the same as c" << c << "\n";
	}
}
void test_unequal(){
	rational_t a(5, 4);
	rational_t b(3, 2);
	rational_t c(10, 8);

	if (a != b) {
		std::cout << "a" << a << " is not the same as b" << b << "\n";
	}
	else{
		std::cout << "a" << a << " is the same as b" << b << "\n";
	}
	if (a != c) {
		std::cout << "a" << a << " is not the same as c" << c << "\n";
	}
	else{
		std::cout << "a" << a << " is the same as c" << c << "\n";
	}
}
void test_smaller() {
	rational_t a(2, 3);
	rational_t b(5, 4);
	rational_t c(1, 8);

	if (a < b) {
		std::cout << "a" << a << " is smaller than b" << b << "\n";
	}
	else{
		std::cout << "a" << a << " is not smaller than b" << b << "\n";
	}
	if (a < c) {
		std::cout << "a" << a << " is smaller than c" << c << "\n";
	}
	else{
		std::cout << "a" << a << " is not smaller than c" << c << "\n";
	}
}
void test_smaller_or_equal() {
	rational_t a(2, 3);
	rational_t b(4, 6);
	rational_t c(7, 8);

	if (a <= b) {
		std::cout << "a" << a << " is smaller or equal b" << b << "\n";
	}
	if (a <= c) {
		std::cout << "a" << a << " is smaller or equal c" << c << "\n";
	}
}
void test_bigger() {
	rational_t a(2, 3);
	rational_t b(5, 4);
	rational_t c(1, 8);

	if (a > b) {
		std::cout << "a" << a << " is bigger than b" << b << "\n";
	}
	else{
		std::cout << "a" << a << " is not bigger than b" << b << "\n";
	}
	if (a > c) {
		std::cout << "a" << a << " is bigger than c" << c << "\n";
	}
	else{
		std::cout << "a" << a << " is not bigger than c" << c << "\n";
	}
}
void test_bigger_or_equal() {
	rational_t a(2, 3);
	rational_t b(4, 6);
	rational_t c(1, 8);

	if (a >= b) {
		std::cout << "a" << a << " is bigger or equal b" << b << "\n";
	}
	if (a >= c) {
		std::cout << "a" << a << " is bigger or equal c" << c << "\n";
	}
}

void test_example_from_instruction(){
	std::cout << "Testing the calculations from the instruction: \n\n";
	rational_t r(-1, 2);

	std::cout << r * -10 << "\n"
		<< r * rational_t(20, -2) << "\n";

	r = 7;

	std::cout << r + rational_t(2, 3) << "\n"
		<< 10 / r / 2 + rational_t(6, 5) << "\n";
}
