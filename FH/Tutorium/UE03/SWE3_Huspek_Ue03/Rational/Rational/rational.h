#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "div_by_zero_error.h"
#include "invalid_numbers_error.h"

class rational_t
{
	int numerator;
	int denominator;

public:
	rational_t();
	rational_t(int const numerator);
	rational_t(int const numerator, int const denominator);
	rational_t(rational_t const& other);	//Copy-constructor

	int get_numerator() const;
	int get_denominator() const;

	bool is_negative() const;
	bool is_positive() const;
	bool is_zero() const;

	void print(std::ostream& os = std::cout) const;
	bool scan(std::istream& is = std::cin);
	std::string as_string()const;

	//assignment operator
	rational_t& operator=(rational_t const& other);

	//comparison operators
	bool operator==(rational_t const& other) const;
	bool operator!=(rational_t const& other) const;
	bool operator<(rational_t const& other) const;
	bool operator>(rational_t const& other) const;
	bool operator<=(rational_t const& other) const;
	bool operator>=(rational_t const& other) const;

	//compound assignment operators
	rational_t& operator+=(rational_t const& other);
	rational_t& operator-=(rational_t const& other);
	rational_t& operator*=(rational_t const& other);
	rational_t& operator/=(rational_t const& other);

	//+, -, *, /
	rational_t operator+(rational_t const& other) const;
	rational_t operator-(rational_t const& other) const;
	rational_t operator*(rational_t const& other) const;
	rational_t operator/(rational_t const& other) const;

private:
	bool is_consistent() const;
	void normalize();
};

//helping functions
int gcd(int const& a, int const& b);
int to_positive(int const& a);

//+, -, *, / with int
rational_t operator+(int const& lhs, rational_t const& rhs);
rational_t operator-(int const& lhs, rational_t const& rhs);
rational_t operator*(int const& lhs, rational_t const& rhs);
rational_t operator/(int const& lhs, rational_t const& rhs);

std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
std::istream& operator>>(std::istream& lhs, rational_t& rhs);