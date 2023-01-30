#ifndef div_by_zero_error_h
#define div_by_zero_error_h

#include <exception>
class divide_by_zero_error : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Divide By Zero Error";
	}
};


#endif
