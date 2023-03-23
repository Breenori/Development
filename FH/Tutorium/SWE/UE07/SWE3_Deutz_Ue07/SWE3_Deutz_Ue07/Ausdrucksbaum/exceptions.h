#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class VariableNotFound : public std::exception {
public:
	VariableNotFound(std::string message) : message(message) {}

	virtual const char* what() const noexcept {
		return message.c_str();
	}

public:
	std::string message;

};

class ParserException : public std::exception {
public:
	ParserException(std::string message) : message(message) {}

	virtual const char* what() const noexcept {
		return message.c_str();
	}

public:
	std::string message;

};

class EvaluationException : public std::exception {
public:
	EvaluationException(std::string message) : message(message) {}

	virtual const char* what() const noexcept {
		return message.c_str();
	}

public:
	std::string message;

};

// stream exception
class StreamException : public std::exception {
public:
	virtual char const* what() const throw() {
		return "Problem with stream occured!\n";
	}
};

class DivisionByZero : public std::exception {
public:
	virtual char const* what() const throw() {
		return "Division by Zero occured!\n";
	}
};

#endif // !EXCEPTIONS_H