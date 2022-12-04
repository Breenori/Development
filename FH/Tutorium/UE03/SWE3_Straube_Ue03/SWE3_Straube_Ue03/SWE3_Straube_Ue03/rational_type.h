#ifndef RATIONAL_T
#define RATIONAL_T

/*
* ----- Includes. -----
*/
#include <iostream>
#include <fstream>
#include <string>
#include "div_by_zero_error.h"

/*
* ----- Usings. -----
*/
using std::ostream;
using std::istream;
using std::cout;
using std::cin;
using std::string;

/*
* ----- Class. -----
*/
class RationalType{
public:
	// 1.
	using data_t = int;

	// 12.
	RationalType();
	RationalType(data_t _numerator, data_t _denominator = 1); 
	RationalType(RationalType const& other);

	// 6.
	ostream& print(ostream& out = cout) const;

	// 7.
	void scan(istream& in = cin);

	// 8.
	string as_string() const; 

	// 10.
	data_t get_numerator() const;
	data_t get_denominator() const;

	// 0.
	void add(RationalType const& other);
	void sub(RationalType const& other);
	void mul(RationalType const& other);
	void div(RationalType const& other);

	// 16.
	RationalType operator+ (RationalType const& other);
	RationalType operator- (RationalType const& other);
	RationalType operator* (RationalType const& other);
	RationalType operator/ (RationalType const& other);

	// 15.
	RationalType& operator+= (RationalType const& other);
	RationalType& operator-= (RationalType const& other);
	RationalType& operator*= (RationalType const& other);
	RationalType& operator/= (RationalType const& other);

	// 14.
	bool operator== (RationalType const& other);
	bool operator!= (RationalType const& other);
	bool operator< (RationalType const& other);
	bool operator<= (RationalType const& other);
	bool operator> (RationalType const& other);
	bool operator>= (RationalType const& other);

	// 13.
	RationalType& operator=(RationalType const& other);

private:
	data_t numerator = 0;
	data_t denominator = 1;
	bool positive = true;

	data_t equalize(RationalType const& other);

	// 4.
	bool is_consistent() const;

	// 11.
	bool is_negative() const;
	bool is_positive() const;
	bool is_zero() const;

	// 5.
	data_t get_gcd() const;
	data_t get_gcd_rec(data_t const& num, data_t const& den) const;
	void normalize();
};

// 16.
RationalType operator+ (RationalType const& lhs, RationalType const& rhs);
RationalType operator- (RationalType const& lhs, RationalType const& rhs);
RationalType operator* (RationalType const& lhs, RationalType const& rhs);
RationalType operator/ (RationalType const& lhs, RationalType const& rhs);

// 17. 
ostream& operator<< (ostream& lhs, RationalType const& rhs);
istream& operator>> (istream& lhs, RationalType& rhs);

#endif