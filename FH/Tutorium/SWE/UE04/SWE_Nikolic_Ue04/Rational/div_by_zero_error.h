#ifndef div_by_zero_error_h
#define div_by_zero_error_h

#include <exception>

class DivideByZeroError : public std::exception {
public:
	virtual char const* what() const throw() {
		return "Divide by 0 Error\n";
	}
};

#endif // !div_by_zero_error_h

