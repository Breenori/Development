#ifndef div_by_zero_h
#define div_by_zero_h
#include <stdexcept>

class DivideByZeroError : public std::exception{
public:
	virtual const char* what() const throw() {
		return "Divide By Zero Error\n";
	}
};

#endif // !
