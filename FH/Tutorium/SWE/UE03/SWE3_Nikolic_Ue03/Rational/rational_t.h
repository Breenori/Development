#ifndef rational_h
#define rational_h

#include "div_by_zero_error.h"
#include <iostream>
#include <string>

class rational_t
{
	int numerator;
	int denominator;

	friend rational_t operator+(int const& lhs, rational_t const& rhs);
	friend rational_t operator-(int const& lhs, rational_t const& rhs);
	friend rational_t operator*(int const& lhs, rational_t const& rhs);
	friend rational_t operator/(int const& lhs, rational_t const& rhs);

public:
	rational_t();
	rational_t(int _numerator);
	rational_t(int _numerator, int _denominator);
	rational_t(rational_t const& other);

	void normalize();

	void print(std::ostream& out) const;
	void scan(std::istream& in);
	std::string as_string() const;

	int get_numerator() const;
	int get_denominator() const;

	bool is_negative() const;
	bool is_positive() const;
	bool is_zero() const;

	rational_t& operator=(rational_t const& other);

	bool operator==(rational_t const& other) const;
	bool operator!=(rational_t const& other) const;
	bool operator<(rational_t const& other) const;
	bool operator<=(rational_t const& other) const;
	bool operator>(rational_t const& other) const;
	bool operator>=(rational_t const& other) const;

	rational_t& operator+=(rational_t const& other);
	rational_t& operator-=(rational_t const& other);
	rational_t& operator*=(rational_t const& other);
	rational_t& operator/=(rational_t const& other);

	rational_t operator+(rational_t const& other);
	rational_t operator-(rational_t const& other);
	rational_t operator*(rational_t const& other);
	rational_t operator/(rational_t const& other);


private:
	int greatest_common_denominator() const;
	void add(rational_t const& other);
	void sub(rational_t const& other);
	void mul(rational_t const& other);
	void div(rational_t const& other);
};

rational_t operator+(int const& lhs, rational_t const& rhs);
rational_t operator-(int const& lhs, rational_t const& rhs);
rational_t operator*(int const& lhs, rational_t const& rhs);
rational_t operator/(int const& lhs, rational_t const& rhs);

std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
std::istream& operator>>(std::istream& lhs, rational_t& rhs);


#endif // !rational_h



