#pragma once

#include <iostream>
#include <string>
#include "operations.h"

#include "div_by_zero_error.h"

using std::string;

//create concept for type
template<typename S>
concept numeric = requires(S t) {
	t + t;
	t += t;
	t - t;
	t -= t;
	t* t;
	t *= t;
	t / t;
	t /= t;
	t == t;
	t != t;
	t < t;
	t > t;
	t <= t;
	t >= t;
	std::cout << t;
	std::cin >> t;
};


template<numeric T = int>
class rational_t
{
public:

	//set value t to use template type
	using value_t = T;

	//getter-------------
	value_t get_numerator()const {
		return this->numerator;
	}
	value_t get_denominator()const {
		return this->denominator;
	}
	//-------------------------
	//constructors-------------
	rational_t() {
		this->denominator = nelms::one<T>();
		this->numerator = nelms::one<T>();
	}
	rational_t(value_t const num) {
		this->numerator = num;
		this->denominator = nelms::one<T>();
	}
	rational_t(value_t const num, value_t const denom) {
		this->denominator = denom;
		this->numerator = num;
		is_consistent();
	}
	rational_t(rational_t<T> const& src) {
		if (src.is_consistent()) {
			this->denominator = src.get_denominator();
			this->numerator = src.get_numerator();
		}
	}
	//----------------------------

	void inverse() {
		//swap denom and num if num not zero 
		if (!(ops::equals<T>(this->numerator, nelms::zero<T>()))) {
			T temp = this->numerator;
			this->numerator = this->denominator;
			this->denominator = temp;
		}
		else
			throw DivideByZeroError();
	}

	static std::istream& scan(std::istream& in, rational_t<T>& rt) {
		value_t n = 0;
		value_t d = 0;
		//create different rationals based on input
		in >> n;
		if (in.good())
		{
			in >> d;
			if (!ops::equals(d, nelms::zero<T>()))
			{
				rt = rational_t<T>(n, d);
			}
			else
				rt = rational_t<T>(n);
		}
		else {
			rt = rational_t<T>();
		}

		return in;
	}
	std::ostream& print(std::ostream& out = std::cout)const {
		if (ops::equals<T>(this->denominator, nelms::one<T>()))
			out << "< " << this->numerator << " >";
		else
			out << "< " << this->numerator << "/" << this->denominator << " >";
		return out;
	}

	void normalize() {

		T a = ops::abs<T>(this->numerator);
		T b = ops::abs<T>(this->denominator);


		//check for smaller numbers using euclidian algo
		value_t g = ops::gcd(a, b);
		if ((g != this->denominator && g != this->numerator) || this->denominator == this->numerator || ops::divides(this->numerator, this->denominator)) {

			this->denominator /= g;
			this->numerator /= g;

		}
		//if both numbers are negative set to positive 
		if (ops::is_negative(this->denominator) && ops::is_negative(this->numerator)) {
			this->denominator = ops::negate(this->denominator);
			this->numerator = ops::negate(this->numerator);

		}
	}

	void add(rational_t<T> const& other) {
		this->normalize();
		rational_t<T> r = other;
		r.normalize();

		value_t l = lcm(this->denominator, other.denominator);

		value_t lm = l / this->denominator;
		value_t rm = l / r.get_denominator();

		this->numerator *= lm;
		this->denominator *= lm;

		this->numerator += r.numerator * rm;
		this->normalize();
	}
	void sub(rational_t<T> const& other) {
		this->normalize();
		rational_t<T> r = other;
		r.normalize();

		value_t l = lcm(this->denominator, other.denominator);

		value_t lm = l / this->denominator;
		value_t rm = l / r.get_denominator();

		*this *= {lm, lm};
		this->numerator -= r.numerator * rm;
		this->normalize();
	}
	void mul(rational_t<T> const& other) {
		this->denominator *= other.get_denominator();
		this->numerator *= other.get_numerator();
		this->is_consistent();
		this->normalize();
	}
	void div(rational_t<T> const& other) {

		this->denominator *= other.get_numerator();
		this->numerator *= other.get_denominator();
		this->is_consistent();
		this->normalize();
	}

	rational_t<T>& operator=(rational_t<T> const& rhs) {
		if (*this == rhs) {
			return *this;
		}
		this->denominator = rhs.get_denominator();
		this->numerator = rhs.get_numerator();
		return *this;
	}


private:

	value_t numerator;
	value_t denominator;


	bool is_consistent() const {
		if (ops::is_zero(denominator))
			throw DivideByZeroError();
		return true;
	}

	//least common multiple is a times b divided by their gcd
	static value_t lcm(value_t a, value_t b) {
		return a * b / ops::gcd(a, b);

	}

	//operator overloads defined as barton nackman----------------
	friend inline rational_t<T> operator+(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t result(lhs);
		result.add(rhs);
		return result;
	}
	friend inline rational_t<T> operator-(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t result(lhs);
		result.sub(rhs);
		return result;
	}
	friend inline rational_t<T> operator*(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t result(lhs);
		result.mul(rhs);
		return result;
	}
	friend inline rational_t<T> operator/(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t result(lhs);
		result.div(rhs);
		return result;
	}

	friend inline rational_t<T>& operator+=(rational_t<T>& lhs, rational_t<T> const& rhs) {
		lhs.add(rhs);
		return lhs;
	}
	friend inline rational_t<T>& operator-=(rational_t<T>& lhs, rational_t<T> const& rhs) {
		lhs.sub(rhs);
		return lhs;
	}
	friend inline rational_t<T>& operator*=(rational_t<T>& lhs, rational_t<T> const& rhs) {
		lhs.mul(rhs);
		return lhs;
	}
	friend inline rational_t<T>& operator/=(rational_t<T>& lhs, rational_t<T> const& rhs) {
		lhs.div(rhs);
		return lhs;
	}


	friend inline bool operator==(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return lhs.numerator / (lhs.denominator * 1.0) == rhs.get_numerator() / (rhs.get_denominator() * 1.0);
	}
	friend inline bool operator!=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return !(lhs == rhs);
	}
	friend inline bool operator<(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return lhs.numerator / (lhs.denominator * 1.0) < rhs.get_numerator() / (rhs.get_denominator() * 1.0);
	}
	friend inline bool operator>(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return lhs.numerator / (lhs.denominator * 1.0) > rhs.get_numerator() / (rhs.get_denominator() * 1.0);
	}
	friend inline bool operator<=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return (lhs < rhs) || (lhs == rhs);
	}
	friend inline bool operator>=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return (lhs > rhs) || (lhs == rhs);
	}

	//------------------------------------

	//operator overloads for lhs being a variable of type T

	friend inline rational_t<T> operator+(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t result(rhs);
		rational_t l = rational_t(lhs);
		result.add(l);
		return result;
	}

	friend inline rational_t<T> operator-(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t result(lhs);
		rational_t l = rational_t(rhs);
		result.sub(l);
		return result;
	}
	friend inline rational_t<T> operator*(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t result(rhs);
		rational_t l = rational_t(lhs);
		result.mul(l);
		return result;
	}
	friend inline rational_t<T> operator/(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t result(lhs);
		rational_t l = rational_t(rhs);
		result.div(l);
		return result;
	}

	friend inline bool operator==(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		return tmp == rhs;
	}
	friend inline bool operator<(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs)
	{
		rational_t tmp(lhs);
		return tmp < rhs;
	}

	friend inline bool operator>(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		return tmp > rhs;
	}
	friend inline bool operator!=(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		return tmp != rhs;
	}
	friend inline bool operator<=(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		return tmp <= rhs;
	}
	friend inline bool operator>=(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		return tmp >= rhs;
	}

	//------------------------------------------

	//overloading stream operators using Barton Nackman

	friend inline std::ostream& operator<<(std::ostream& lhs, rational_t<T> const& rhs) {
		rhs.print(lhs);
		return lhs;
	}

	friend inline std::istream& operator>>(std::istream& lhs, rational_t<T>& rhs) {
		rhs.scan(lhs, rhs);
		return lhs;
	}

};

