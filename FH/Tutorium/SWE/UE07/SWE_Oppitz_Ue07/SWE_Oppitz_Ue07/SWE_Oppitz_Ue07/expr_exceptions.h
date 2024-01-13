#ifndef expr_exceptions_h
#define expr_exceptions_h

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
		VariableNotFoundException(std::string message): message(message){}

		virtual const char* what() const noexcept {
			return message.c_str();
		}

	private:
		std::string message;
	};

	class DivByZeroException : public std::exception {
	public:
		virtual const char* what() const noexcept {
			return "Division by zero!\n";
		}
	};


}


#endif // !expr_exceptions_h
