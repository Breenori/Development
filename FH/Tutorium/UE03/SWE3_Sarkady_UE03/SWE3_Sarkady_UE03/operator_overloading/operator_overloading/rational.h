#ifndef rational_h
#define rational_h

#include <iostream>
#include <string>
#include "rational.h"

class rational_t {
	mutable int numerator;
	mutable int denominator;

public:
	rational_t();
	rational_t(int _numerator);
	rational_t(int _numerator, int _denominator);
	rational_t(rational_t const& other);

	int get_numerator() const;
	int get_denominator() const;

	bool is_negative() const;
	bool is_positive() const;
	bool is_zero() const;

	// Operator Overloading:
	rational_t& operator=(rational_t other);

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
	rational_t operator+(int const& other);
	rational_t operator-(int const& other);
	rational_t operator*(int const& other);
	rational_t operator/(int const& other);

	std::string as_string() const;

	void print(std::ostream& os = std::cout) const;
	void scan(std::istream& is = std::cin) const;

	friend std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
	friend std::istream& operator>>(std::istream& lhs, rational_t const& rhs);

private:
	bool is_consistent();
	rational_t& normalize();
};

// non member operator
rational_t operator+(int const& lhs, rational_t const& rhs);
rational_t operator-(int const& lhs, rational_t const& rhs);
rational_t operator*(int const& lhs, rational_t const& rhs);
rational_t operator/(int const& lhs, rational_t const& rhs);

std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
std::istream& operator>>(std::istream& lhs, rational_t const& rhs);
#endif // !rational_h