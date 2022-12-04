#ifndef RATIONAL_T_H
#define RATIONAL_T_H

#include <iostream>
#include <string>
#include <fstream>
#include"divided_by_zero.h"

class rational_t {
	int numerator; 
	int denominator;

	friend std::ostream& operator<<(std::ostream& out, rational_t const& number);
	friend std::istream& operator>>(std::istream& in, rational_t & number);

public:
	rational_t();
	rational_t(int numerator);
	rational_t(int _numerator, int _denominator); 
	rational_t(rational_t const& other);
	void print(std::ostream & out = std::cout)const;
	void scan(std::istream& in = std::cin);
	void test_normalize(); // only for testing normalize function
	std::string as_string() const; // convert rational number into string
	int get_numerator() const;
	int get_denominator() const;
	bool is_negative() const;
	bool is_positive() const;
	bool is_zero() const;
	
	//assignment operator
	rational_t& operator=(rational_t other);
	
	//compare operators
	bool operator<(rational_t const& other);
	bool operator>(rational_t const &other);
	bool operator<=(rational_t const&other);
	bool operator>=(rational_t const&other);
	bool operator==(rational_t const& other);
	bool operator!=(rational_t const& other);
	
	//basic arithmetics
	void add(rational_t const& other);
	void sub(rational_t const& other);
	void mul(rational_t const& other);
	void div(rational_t const& other);
	
	//basic arithmetics - overload
	rational_t operator+(rational_t const & other);
	rational_t operator-(rational_t const& other);
	rational_t operator/(rational_t const& other);
	rational_t operator*(rational_t const& other);

	//basic assignments - compound assignments overload
	rational_t& operator+=(rational_t const& other);
	rational_t& operator-=(rational_t const& other);
	rational_t& operator/=(rational_t const& other);
	rational_t& operator*=(rational_t const& other);


private:
	void normalize();
	int get_gcd()const;
	bool is_consistent();


};
// overloading operators << and >>
std::ostream& operator<<(std::ostream& out, rational_t const& number);
std::istream& operator>>(std::istream& in, rational_t & number);


#endif // !RATIONAL_T_H

