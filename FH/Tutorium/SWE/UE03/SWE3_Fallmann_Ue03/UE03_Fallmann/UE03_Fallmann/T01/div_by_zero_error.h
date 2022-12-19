#pragma once

#include <exception>

class DivideByZeroError : public std::exception
{
public:
	virtual char const* what() const throw() {
		return "Divide by 0 Error!\n";
	}


private:

};