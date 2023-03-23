#pragma once

#include <exception>
#include <string>
#include <stdexcept>

namespace xpr
{

	class EvaluationException :public std::exception
	{
	public:
		virtual const char* what() const noexcept {
			return "Evaluation Exception: Unable to evaluate exception tree!\n";
		}
	};

	class VariableNotFoundException :public std::exception
	{
	public:
		VariableNotFoundException(std::string message) : message(message) {}
		virtual const char* what() const noexcept {
			return message.c_str();
		}

	private:
		std::string message;
	};

	class DivByZeroException :public std::exception
	{
	public:
		DivByZeroException(std::string message) : message(message) {}
		virtual const char* what() const noexcept {
			return message.c_str();
		}

	private:
		std::string message;
	};

	class ParserException :public std::exception
	{
	public:
		ParserException(std::string message) : message(message) {}
		virtual const char* what() const noexcept {
			return message.c_str();
		}

	private:
		std::string message;
	};
	


}
