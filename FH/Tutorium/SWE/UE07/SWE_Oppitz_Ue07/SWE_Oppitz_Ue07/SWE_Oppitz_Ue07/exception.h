#ifndef EXEPTION_H

#include <exception>
#include <string>
#include "pfc_scanner.h"

struct parser_exception : std::runtime_error {
	explicit parser_exception(std::string const& m) : std::runtime_error{ m } {
	}
};

class DivByZeroException : public std::exception {
public:
	virtual const char* what() const noexcept {
		return "Division by zero!\n";
	}
};

class VariableAlreadyExist : public std::exception {
public:
	virtual const char* what() const noexcept {
		return "Variable already exists!\n";
	}
};

class UndefinedVariable : public std::exception {
public:
	virtual const char* what() const noexcept {
		return "Undefined Variable!\n";
	}
};



#endif // !EXEPTION_H



