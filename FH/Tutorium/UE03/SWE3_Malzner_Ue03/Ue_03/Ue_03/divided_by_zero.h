#ifndef DIVIDE_BY_ZERO_H
#define DIVIDE_BY_ZERO_H

#include <stdexcept>

class DivideByZeroError : public std::exception {

public: 
	virtual char const* what() const throw() {
		return "Error! Division by Zero";
	}
};


#endif // !DIVIDE_BY_ZERO_H

