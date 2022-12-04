#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Div_by_Zero.h"
class rational_t
{
	//rationals
	int numerator;//zähler
	int denominator;//nenner
public:
	//constructors
	//default
	//rational_t();
	rational_t(int _numerator = 0, int _denominator = 1);
	//rational_t(int _numerator);
	//cpy
	rational_t(rational_t const& other);
	// cpy init??
	//rational_t(rational_t const& other);
	//deconstructor
	~rational_t(){}
	//get
	int get_numerator()const;
	int get_denominator()const;
	//set
	void set_numerator(int numerator);
	void set_denominator(int denominator);
	//return str
	std::string as_string() const;
	//helper
	bool is_negative()const;
	bool is_positive()const;
	bool is_zero()const;
	//operators
	void add(rational_t const& other);
	void sub(rational_t const& other);
	void mul(rational_t const& other);
	void div(rational_t const& other);
	//overloading
	rational_t operator+(rational_t const& c1);
	rational_t operator-(rational_t const& c1);
	rational_t operator*(rational_t const& c1);
	rational_t operator/(rational_t const& c1);
	//compound assignment operators
	rational_t& operator+=(rational_t const& c1);
	rational_t& operator-=(rational_t const& c1);
	rational_t& operator*=(rational_t const& c1);
	rational_t& operator/=(rational_t const& c1);
	//compare operators
	bool operator==(rational_t const& c1)const;
	bool operator!=(rational_t const& c1)const;
	bool operator<(rational_t const& c1)const;
	bool operator<=(rational_t const& c1)const;
	bool operator>(rational_t const& c1)const;
	bool operator>=(rational_t const& c1)const;
	//1. Copy-Assignment Idiom
	//rational_t& operator=(rational_t const& other);
	//2. Copy-and-Swap Idiom
	rational_t& operator=(rational_t other);
	//print
	void print(std::ostream& out = std::cout)const;
	static void print_result(std::ostream& out, rational_t& c1);
	//scan
	void scan(std::istream& in = std::cin)const;
private:
	//friending
	friend std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
	friend std::istream& operator>>(std::istream& lhs, rational_t const& rhs);
	//helper
	bool is_consistent()const;
	static int gcd(int _numerator, int _denominator);
	//canonical form
	void normalize();
};
//non-member-foos
//lhs compatibility
rational_t operator+(int const& lhs, rational_t const& rhs);
rational_t operator-(int const& lhs, rational_t const& rhs);
rational_t operator*(int const& lhs, rational_t const& rhs);
rational_t operator/(int const& lhs, rational_t const& rhs);
//rhs compatibility
rational_t operator+(rational_t const& lhs,int const&rhs);
rational_t operator-(rational_t const& lhs,int const&rhs);
rational_t operator*(rational_t const& lhs,int const&rhs);
rational_t operator/(rational_t const& lhs,int const&rhs);
//fstream
std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
std::istream& operator>>(std::istream& lhs, rational_t const& rhs);


