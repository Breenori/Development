#pragma once
#include <exception>
class DivideByZeroError : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Division by zero error.rational_t: Denominator is zero.\n";
	}
};

