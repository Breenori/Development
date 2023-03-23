#ifndef expr_exception_h
#define expr_exception_h

#include <exception>
#include <string>

namespace xpr {

	class EvaluationException : public std::exception {

	public:
		virtual const char* what() const noexcept {
			return "Evaluation Exception: Unable to evaluate expression!";
		}

	};

	class DivisionByZeroException : public std::exception {
	public:
		DivisionByZeroException(std::string message) : message(message) {}
		virtual const char* what() const noexcept {
			return message.c_str();
		}
	private:
		std::string message;
	};

	class VariableNotFoundException : public std::exception {
	public:
		VariableNotFoundException(std::string message) : message(message) {}
		virtual const char* what() const noexcept {
			return message.c_str(); // macht aus std::string einen c-string (0 als terminierungssymbol)
		}

	private:
		std::string message;
	};


}

#endif