#pragma once
#include <exception>

class div_by_zero : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Error! Division by Zero.";
	}
};

class unvalid_input : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Error! Input not valid.";
	}
};
