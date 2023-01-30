#ifndef rational_h
#define rational_h

#include "div_by_zero_error.h"
#include "operations.h"
#include <iostream>
#include <string>
#include <sstream>


template<typename S>
concept numeric = requires(S n) {
	n + n;
	n - n;
	n* n;
	n / n;
	n% n;

	n == n;
	n < n;
	n > n;

	std::cout << n;
	std::cin >> n;
};

template <numeric T = int>
class rational_t
{
private:
	T numerator;
	T denominator;

	friend inline rational_t<T>& operator+=(rational_t<T>& lhs, rational_t<T> const& rhs)
	{
		lhs.add(rhs);
		return lhs;
	}

	friend inline rational_t<T>& operator-=(rational_t<T>& lhs, rational_t<T> const& rhs)
	{
		lhs.sub(rhs);
		return lhs;
	}

	friend inline rational_t<T>& operator*=(rational_t<T>& lhs, rational_t<T> const& rhs)
	{
		lhs.mul(rhs);
		return lhs;
	}

	friend inline rational_t<T>& operator/=(rational_t<T>& lhs, rational_t<T> const& rhs)
	{
		lhs.div(rhs);
		return lhs;
	}

	friend inline rational_t<T> operator+(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		rational_t<T> tmp{ lhs };
		tmp.add(rhs);
		return tmp;
	}

	friend inline rational_t<T> operator-(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		rational_t<T> tmp{ lhs };
		tmp.sub(rhs);
		return tmp;
	}

	friend inline rational_t<T> operator*(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		rational_t<T> tmp{ lhs };
		tmp.mul(rhs);
		return tmp;
	}

	friend inline rational_t<T> operator/(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		rational_t<T> tmp{ lhs };
		tmp.div(rhs);
		return tmp;
	}

	friend inline bool operator==(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		// bring to same denominator
		T numerator_lhs = lhs.numerator * rhs.denominator;
		T numerator_rhs = rhs.numerator * lhs.denominator;

		return numerator_lhs == numerator_rhs;
	}

	friend inline bool operator!=(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		return !(ops::equals(lhs, rhs));
	}

	friend inline bool operator<(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		// bring to same denominator
		T numerator_lhs = lhs.numerator * rhs.denominator;
		T numerator_rhs = rhs.numerator * lhs.denominator;

		return numerator_lhs < numerator_rhs;
	}

	friend inline bool operator<=(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		return (ops::equals(lhs, rhs) || lhs < rhs);
	}

	friend inline bool operator>(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		return !(lhs <= rhs);
	}

	friend inline bool operator>=(rational_t<T> const& lhs, rational_t<T> const& rhs)
	{
		return (ops::equals(lhs, rhs) || lhs > rhs);
	}

	friend inline std::ostream& operator<<(std::ostream& lhs, rational_t<T> const& rhs)
	{
		rhs.print(lhs);
		return lhs;
	}

	friend inline std::istream& operator>>(std::istream& lhs, rational_t<T>& rhs)
	{
		rhs.scan(lhs);
		return lhs;
	}

public:

	rational_t() : numerator{ 0 }, denominator{ 1 }
	{}

	rational_t(T _numerator) : numerator{ _numerator }, denominator{ 1 }
	{}

	rational_t(T _numerator, T _denominator) : numerator{ _numerator }, denominator{ _denominator }
	{
		if (!is_consistent()) {
			throw DivideByZeroError();
		}
		normalize();
	}

	rational_t(rational_t<T> const& other) : numerator{ other.numerator }, denominator{ other.denominator }
	{}



	void print(std::ostream& out) const
	{
		out << "<" << as_string() << ">";
	}

	void scan(std::istream& in)
	{
		in >> numerator;
		char slash;
		in >> slash;
		in >> denominator;

		if (!is_consistent()) {
			throw DivideByZeroError();
		}

		normalize();
	}

	std::string as_string() const
	{
		std::stringstream rational_string;

		if (ops::equals(denominator, nelms::one<T>()))
			rational_string << numerator;
		else if (ops::equals(denominator, nelms::zero<T>() -nelms::one<T>()))
			rational_string<< "-" << numerator;
		else
			rational_string << numerator << "/" << denominator;

		return rational_string.str();
	}

	T get_numerator() const
	{
		return numerator;
	}

	T get_denominator() const
	{
		return denominator;
	}

	// this operator can't be implemented as friend operator:
	rational_t<T>& operator=(rational_t<T> const& other)
	{
		if (ops::equals(other, *this)) {
			return *this;
		}

		numerator = other.numerator;
		denominator = other.denominator;

		return *this;
	}


	void normalize()
	{
		if (is_positive()) {
			numerator = ops::abs(numerator);
			denominator = ops::abs(denominator);
		}

		T gcd = ops::gcd(numerator, denominator);
		numerator = numerator / gcd;
		denominator = denominator / gcd;
	}

	bool is_negative() const
	{
		return ((ops::is_negative(numerator) && !ops::is_negative(denominator)) || (!ops::is_negative(numerator) && ops::is_negative(denominator)));
	}

	bool is_positive() const
	{
		return !is_negative();
	}

	bool is_zero() const
	{
		return ops::is_zero(*this);
	}

private:

	bool is_consistent() const {
		return !ops::equals(denominator, nelms::zero<T>());
	}

	void add(rational_t const& other)
	{
		rational_t other_t{ other };

		// get to same denominator
		other_t.numerator = other_t.numerator * denominator;
		other_t.denominator = other_t.denominator * denominator;

		numerator = numerator * other.denominator;
		denominator = denominator * other.denominator;


		// add
		numerator = numerator + other_t.numerator;

		normalize();
	}

	void sub(rational_t const& other)
	{
		rational_t other_t{ other };

		// get to same denominator
		other_t.numerator = other_t.numerator * denominator;
		other_t.denominator = other_t.denominator * denominator;

		numerator = numerator * other.denominator;
		denominator = denominator * other.denominator;

		// sub
		numerator = numerator - other_t.numerator;

		normalize();
	}

	void mul(rational_t const& other)
	{
		numerator = numerator* other.numerator;
		denominator = denominator*other.denominator;

		normalize();
	}

	void div(rational_t const& other)
	{
		numerator = numerator * other.denominator;
		denominator = denominator * other.numerator;

		if (!is_consistent()) {
			throw DivideByZeroError();
		}

		normalize();
	}


};


#endif // !rational_h



