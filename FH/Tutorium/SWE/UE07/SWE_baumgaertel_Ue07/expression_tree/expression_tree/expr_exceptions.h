#ifndef EXPR_EXCEPTIONS
#define EXPR_EXCEPTIONS

#include <exception>
#include <string>

namespace xpr {

	class EvaluationException : public std::exception {
	public:
		virtual const char* what() const noexcept {
			return "Evaluation Exception: Unable to evaluate expression tree!\n";
		}
	};

	class VariableNotFoundException : public std::exception {
	public:
		VariableNotFoundException(std::string message) : message(message) {}
		virtual const char* what() const noexcept {
			// converting to c-string because method returns char*
			return message.c_str();
		}
	private:
		std::string message;
	};

}

#endif