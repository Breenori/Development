#ifndef div_by_zero_error_h
#define div_by_zero_error_h

#include<exception>

class DivideByZeroError :public std::exception {
public:
	virtual const char* what() const throw() {
		return "Divide by Zero Error";
	}
};
#endif // !div_by_zero_error_h
