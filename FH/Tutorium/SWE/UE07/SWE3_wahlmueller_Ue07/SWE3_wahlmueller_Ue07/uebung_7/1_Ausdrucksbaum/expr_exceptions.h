#ifndef EXPR_EXCEPTIONS_H
#define EXPR_EXCEPTIONS_H

#include <exception>
#include <iostream>

#include <string>

using std::exception;
using std::string;

using std::runtime_error;

namespace xpr {

	//exceptions
	class EvaluationException :public exception {
	public:
		virtual const char * what() const noexcept {

			return "Evatuation exception: Unable to evaluate expression tree!\n";

		}
	};

	class VariableNotFoundException : public exception {
	public:
		VariableNotFoundException(string message) : message(message) {};
		virtual const char* what() const noexcept {

			return message.c_str();

		}


	private:
		string message;

	};

	class div_by_zero_error :public exception {
	public:
		virtual char const* what() const throw() {

			return "Error div by zero!";

		}
	};

	class ParserException final : public runtime_error {
	public:
		explicit ParserException(string const& message) : runtime_error{ message } { }

	};

};


#endif