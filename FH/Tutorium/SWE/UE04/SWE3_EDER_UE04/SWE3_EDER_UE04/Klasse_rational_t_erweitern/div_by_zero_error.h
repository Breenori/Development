#ifndef DIV_BY_ZERO_ERROR_H
#define DIV_BY_ZERO_ERROR_H
#include <exception>

class DivideByZeroError : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Divide By Zero Error.";
	}
};
#endif // !DIV_BY_ZERO_ERROR.H
