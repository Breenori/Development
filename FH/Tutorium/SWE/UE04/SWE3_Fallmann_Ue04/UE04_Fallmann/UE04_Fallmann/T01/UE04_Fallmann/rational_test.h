#pragma once


#include "operations.h"
#include "number_t.h"
#include "rational_t.h"

#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::string;


template<typename T>
class rational_test {
public:
	using f_pointer_arith = bool(*)(rational_t<T> const&, rational_t<T> const&, rational_t<T> const&, rational_t<T>&);
	using f_pointer_comp = bool(*)(rational_t<T> const&, rational_t<T> const&, bool const, bool&);
	using f_pointer_constr = bool(*)(rational_t<T> const&, rational_t<T>&, T const, T const);


	//singleton-----------------------------------
	static rational_test<T>& get_instance() {

		static rational_test<T> instance;
		return instance;
	}

	rational_test(rational_test<T> const& src) = delete;
	void operator=(rational_test<T>const& src) = delete;
	//---------------------------------------------------------

	//testing arithmetic operations
	static bool test_add(rational_t<T> const& input_1, rational_t<T> const& input_2, rational_t<T> const& expected_output, rational_t<T>& output) {
		output = rational_t<T>(input_1);
		output += input_2;
		return output == expected_output;
	}

	static bool test_sub(rational_t<T> const& input_1, rational_t<T> const& input_2, rational_t<T> const& expected_output, rational_t<T>& output) {
		output = rational_t<T>(input_1);
		output -= input_2;
		return output == expected_output;
	}

	static bool test_mul(rational_t<T> const& input_1, rational_t<T> const& input_2, rational_t<T> const& expected_output, rational_t<T>& output) {
		output = rational_t<T>(input_1);
		output *= input_2;
		return output == expected_output;
	}

	static bool test_div(rational_t<T> const& input_1, rational_t<T> const& input_2, rational_t<T> const& expected_output, rational_t<T>& output) {
		output = rational_t<T>(input_1);
		output /= input_2;
		return output == expected_output;
	}

	//-------------------------------
	//testing comparison Operations
	static bool test_not_equal(rational_t<T> const& lhs, rational_t<T> const& rhs, bool const expected, bool& actual_output) {
		actual_output = (lhs != rhs);
		return actual_output == expected;
	}
	static bool test_smaller(rational_t<T> const& lhs, rational_t<T> const& rhs, bool const expected, bool& actual_output) {
		actual_output = (lhs < rhs);
		return actual_output == expected;
	}
	static bool test_bigger(rational_t<T> const& lhs, rational_t<T> const& rhs, bool const expected, bool& actual_output) {
		actual_output = (lhs > rhs);
		return actual_output == expected;
	}
	static bool test_smaller_equal(rational_t<T> const& lhs, rational_t<T> const& rhs, bool const expected, bool& actual_output) {
		actual_output = (lhs <= rhs);
		return actual_output == expected;
	}
	static bool test_bigger_equal(rational_t<T> const& lhs, rational_t<T> const& rhs, bool const expected, bool& actual_output) {
		actual_output = (lhs >= rhs);
		return actual_output == expected;
	}
	//------------------------------
	//testing constructors
	static bool test_int_constr(rational_t<T> const& expected_output, rational_t<T>& output, T const num = 1, T const denom = 1) {
		output = rational_t(num);
		return output == expected_output;
	}

	static bool test_int_constr_default(rational_t<T> const& expected_output, rational_t<T>& output, T const num = 1, T const denom = 1) {
		output = rational_t();
		return output == expected_output;
	}

	static bool test_int_constr_rat(rational_t<T> const& expected_output, rational_t<T>& output, T const num = 1, T const denom = 1) {
		output = rational_t(num, denom);
		return output == expected_output;
	}

	static bool test_constr(rational_t<T> const& expected_output, rational_t<T>& output, T const num = 1, T const denom = 1) {
		output = rational_t<T>(num);
		return output == expected_output;
	}

	static bool test_constr_rat(rational_t<T> const& expected_output, rational_t<T>& output, T const num = 1, T const denom = 1) {
		output = rational_t<T>(num, denom);
		return output == expected_output;
	}

	static bool test_constr_default(rational_t<T> const& expected_output, rational_t<T>& output, T const num = 1, T const denom = 1) {
		output = rational_t<T>();
		return output == expected_output;
	}
	//---------------


	void test_inverse(string const& descr, rational_t<T> const& input,rational_t<T> const& output) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		rational_t<T> actual_output(input);
		string error = "";

		bool result = false;

		try {
			actual_output.inverse();
		}
		catch (DivideByZeroError& e) {
			error = "Division by zero error occured";
		}
		result = output == actual_output;
		cout << "Input: " << input << std::endl;
		cout << "expected output: " << output << std::endl;
		cout << "actual output: " << actual_output << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		if (error != "") {
			cout << error << std::endl;
		}
		cout << std::endl;

	}

	void test_scan(string const& descr, string const & input, rational_t<T> const& output) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		rational_t<T> actual_output;
		string error = "";

		bool result = false;

		try {
			std::istringstream in(input);
			rational_t<T>::scan(in, actual_output);
			result = actual_output == output;
		}
		catch (DivideByZeroError& e) {
			error = "Division by zero error occured";
		}

		cout << "Input: " << input << std::endl;
		cout << "expected output: " << output << std::endl;
		cout << "actual output: " << actual_output << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		if (error != "") {
			cout << error << std::endl;
		}
		cout << std::endl;

	}

	//Base functions
	void test_rational(string const& descr, rational_t<T> const& input_1, rational_t<T> const& input_2, rational_t<T> const& output, f_pointer_arith const& test) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		rational_t<T> actual_output;
		string error = "";

		bool result = false;

		try {
			result = test(input_1, input_2, output, actual_output);
		}
		catch (DivideByZeroError& e) {
			error = "Division by zero error occured";
		}

		cout << "Input_1: " << input_1 << std::endl;
		cout << "Input_2: " << input_2 << std::endl;
		cout << "expected output: " << output << std::endl;
		cout << "actual output: " << actual_output << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		if (error != "") {
			cout << error << std::endl;
		}
		cout << std::endl;

	}

	void test_rational(string const& descr, rational_t<T> const& input_1, rational_t<T> const& input_2, bool const output, f_pointer_comp const& test) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		bool actual_output;
		string error = "";

		bool result = false;

		try {
			result = test(input_1, input_2, output,actual_output);
		}
		catch (DivideByZeroError& e) {
			error = "Division by zero error occured";
		}

		cout << "Input_1: " << input_1 << std::endl;
		cout << "Input_2: " << input_2 << std::endl;
		cout << "expected output: " << (output ? "true" : "false") << std::endl;
		cout << "actual output: " << (actual_output ? "true" : "false") << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		if (error != "") {
			cout << error << std::endl;
		}
		cout << std::endl;

	}

	void test_rational(string const& descr, rational_t<T> const& output, f_pointer_constr const& test, T num = nelms::one<T>(), T denom = nelms::one<T>()) {
		cout << "Test " << ++this->test_count << " :\n";
		cout << descr << std::endl;
		rational_t<T> actual_output;
		string error = "";

		bool result = false;

		try {
			result = test(output, actual_output, num, denom);
		}
		catch (DivideByZeroError& e) {
			error = "Division by zero error occured";
		}

		cout << "expected output: " << output << std::endl;
		cout << "actual output: " << actual_output << std::endl;
		cout << (result ? "success" : "failure") << std::endl;
		if (error != "") {
			cout << error << std::endl;
		}
		cout << std::endl;

	}

	//-----------------------------------
private:

	rational_test() {
		test_count = 0;
	};

	size_t test_count;


};
