#pragma once

#include "operations.h"
#include "number_t.h"
#include "rational_t.h"

#include <string>
#include <iostream>
using std::string;
using std::cout;

template<typename T>
class operations_test {
public:

	using f_pointer_singular = bool (*)(T const&, T const&, T&);
	using f_pointer_singular_b = bool (*)(T const&, bool const, bool&);
	using f_pointer_multiple = bool (*)(T const&, T const&, T const&, T&);
	using f_pointer_multiple_b = bool (*)(T const&, T const&, bool const, bool&);

	//singleton --------------
	static operations_test<T>& get_instance() {
		static operations_test<T> instance;

		return instance;
	}
	operations_test(operations_test<T> const& src) = delete;
	void operator=(operations_test<T>const& src) = delete;
	//------------------




	//singular operations----------------
	static bool test_abs(T const& input, T const& output, T& actual_output) {
		actual_output = ops::abs(input);
		return actual_output == output;
	}

	static bool test_is_zero(T const& input, bool const output, bool& actual_output) {
		actual_output = ops::is_zero(input);
		return actual_output == output;
	}

	static bool test_is_negative(T const& input, bool const output, bool& actual_output) {
		actual_output = ops::is_negative(input);
		return actual_output == output;
	}

	static bool test_negate(T const& input, T const& output, T& actual_output) {
		actual_output = ops::negate(input);
		return actual_output == output;
	}

	//------------------------

	//operations with multiple parameters
	static bool test_divides(T const& input_1, T const& input_2, bool const output, bool& actual_output) {
		actual_output = ops::divides(input_1, input_2);
		return actual_output == output;
	}

	static bool test_equals(T const& input_1, T const& input_2, bool const output, bool& actual_output) {
		actual_output = ops::equals(input_1, input_2);
		return actual_output == output;
	}

	static bool test_gcd(T const& input_1, T const& input_2, T const& output, T& actual_output) {
		actual_output = ops::gcd(input_1, input_2);
		return actual_output == output;
	}

	static bool test_remainder(T const& input_1, T const& input_2, T const& output, T& actual_output) {
		actual_output = ops::remainder(input_1, input_2);
		return actual_output == output;
	}

	//----------------------------------

	//Base functions
	void test_operations(string const& descr, T const& input_1, T const& input_2, T const& output, f_pointer_multiple const& test) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		T actual_output;

		bool result = test(input_1, input_2 ,output, actual_output);

		cout << "Input_1: " << input_1 << std::endl;
		cout << "Input_2: " << input_2 << std::endl;
		cout << "expected output: " << output << std::endl;
		cout << "actual output: " << actual_output << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		cout << std::endl;

	}

	void test_operations(string const& descr, T const& input_1, T const& input_2, bool const output, f_pointer_multiple_b const& test) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		bool actual_output;

		bool result = test(input_1, input_2 ,output, actual_output);

		cout << "Input_1: " << input_1 << std::endl;
		cout << "Input_2: " << input_2 << std::endl;
		cout << "expected output: " << (output ? "true" : "false") << std::endl;
		cout << "actual output: " << (actual_output ? "true" : "false") << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		cout << std::endl;

	}

	void test_operations(string const& descr, T const& input, T const& output, f_pointer_singular const& test) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		T actual_output;

		bool result = test(input, output, actual_output);

		cout << "Input: " << input << std::endl;
		cout << "expected output: " << output << std::endl;
		cout << "actual output: " << actual_output << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		cout << std::endl;

	}

	void test_operations(string const& descr, T const& input, bool const output, f_pointer_singular_b const& test) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		bool actual_output;

		bool result = test(input, output, actual_output);

		cout << "Input: " << input << std::endl;
		cout << "expected output: " << (output ? "true" : "false") << std::endl;
		cout << "actual output: " << (actual_output ? "true" : "false") << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		cout << std::endl;

	}

private:

	operations_test() {
		test_count = 0;
	}

	size_t test_count;
};

template<typename T>
class nelms_test {
public:

	//Singleton-------------
	static nelms_test& get_instance() {
		static nelms_test instance;
		return instance;
	}
	nelms_test(nelms_test<T> const& src) = delete;
	void operator=(nelms_test<T>const& src) = delete;
	//------------------


	void test_zero(string const& descr, T const output) {
		cout << descr << std::endl;
		T actual_output = nelms::zero<T>();

		bool result = (actual_output == output);

		cout << "expected output: " << output<< std::endl;
		cout << "actual output: " << actual_output<< std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		cout << std::endl;

	}

	void test_one(string const& descr, T const output) {
		cout << descr << std::endl;
		T actual_output = nelms::one<T>();

		bool result = (actual_output == output);

		cout << "expected output: " << output << std::endl;
		cout << "actual output: " << actual_output << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		cout << std::endl;

	}



private:
	nelms_test() {

	}
};