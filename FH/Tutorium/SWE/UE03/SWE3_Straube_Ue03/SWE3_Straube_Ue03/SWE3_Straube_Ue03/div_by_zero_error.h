#ifndef DIV_BY_ZERO
#define DIV_BY_ZERO

/*
* ----- Includes. -----
*/
#include <exception>

/*
* ----- Class. -----
*/
class DivideByZeroError : public std::exception {
public:
	virtual char const* what() const throw() { 
		return "Error: No valid fracture - division by 0.";
	}
};

#endif // !DIV_BY_ZERO
