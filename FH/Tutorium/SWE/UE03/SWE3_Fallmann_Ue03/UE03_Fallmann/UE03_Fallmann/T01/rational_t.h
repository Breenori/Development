#pragma once

#include <iostream>
#include <string>

#include "div_by_zero_error.h"

using std::string;

class rational_t
{
public:

	using value_t = int;

	value_t get_numerator()const;
	value_t get_denominator()const;

	rational_t();
	rational_t(value_t const num);
	rational_t(value_t const num, value_t const denom);
	rational_t(rational_t const& src);

	static std::istream& scan(std::istream& in, rational_t& rt);
	std::ostream& print(std::ostream& out = std::cout)const;

	void normalize();

	void add(rational_t const& other);
	void sub(rational_t const& other);
	void mul(rational_t const& other);
	void div(rational_t const& other);

	rational_t operator+(rational_t const& r1);
	rational_t operator-(rational_t const& r1);
	rational_t operator*(rational_t const& r1);
	rational_t operator/(rational_t const& r1);

	rational_t& operator+=(rational_t const& r1);
	rational_t& operator-=(rational_t const& r1);
	rational_t& operator*=(rational_t const& r1);
	rational_t& operator/=(rational_t const& r1);


	rational_t& operator=(rational_t const& other);

	bool operator==(rational_t const& r1)const;
	bool operator!=(rational_t const& r1)const;
	bool operator<(rational_t const& r1)const;
	bool operator>(rational_t const& r1)const;
	bool operator<=(rational_t const& r1)const;
	bool operator>=(rational_t const& r1)const;







private:

	value_t numerator;
	value_t denominator;

	static bool is_positive(value_t const i);
	static bool is_negative(value_t const i);
	static bool is_zero(value_t const i);


	bool is_consistent() const;

	static value_t gcd(value_t a, value_t b);
	static value_t lcm(value_t a, value_t b);

	string as_string()const;




};


rational_t operator+(rational_t::value_t const& lhs, rational_t const& rhs);
rational_t operator-(rational_t::value_t const& lhs, rational_t const& rhs);
rational_t operator*(rational_t::value_t const& lhs, rational_t const& rhs);
rational_t operator/(rational_t::value_t const& lhs, rational_t const& rhs);

bool operator==(rational_t::value_t const& lhs, rational_t const& rhs);
bool operator<(rational_t::value_t const& lhs, rational_t const& rhs);
bool operator>(rational_t::value_t const& lhs, rational_t const& rhs);
bool operator!=(rational_t::value_t const& lhs, rational_t const& rhs);
bool operator<=(rational_t::value_t const& lhs, rational_t const& rhs);
bool operator>=(rational_t::value_t const& lhs, rational_t const& rhs);

std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);

std::istream& operator>>(std::istream& lhs, rational_t & rhs);

