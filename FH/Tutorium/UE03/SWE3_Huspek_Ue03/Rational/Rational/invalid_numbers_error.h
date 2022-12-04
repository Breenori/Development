#pragma once
#include <exception>

class InvalidInputError : public std::exception {
public:
	virtual char const* what() const throw() {
		return "Invalid input Custom Error!";
	}
};