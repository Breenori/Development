#ifndef rational_type_h
#define rational_type_h

#include "operations.h"
#include "number.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include "div_by_zero_error.h"
#include <type_traits>

template<typename T>
concept NumericType = requires(T v) {
	v + v; //T requires operator +
	v - v;
	v * v;
	v / v;
	v += v;
	v -= v;
	v *= v;
	v /= v;
	v % v;
	v == v;
	v != v;
	v < v;
	v > v;
	v <= v;
	v >= v;
	std::cout << v;
};

template<NumericType T = int>
class rational_t {

public:
	//constructor and destructor
	rational_t() {
	}
	rational_t(T _numerator) : numerator(_numerator), denominator(nelms::one<T>) {
	}
	rational_t(T _numerator, T _denominator) : numerator(_numerator), denominator(_denominator) {
	}
	rational_t(rational_t const& other) : numerator(other.numerator), denominator(other.denominator) {
	}
	~rational_t() {
	}

	void inverse() {
		T tmp = numerator;
		numerator = denominator;
		denominator = tmp;
	}

	//calculations
	void add(rational_t<T> const& other) {
		if (this->is_consistent() && other.is_consistent()) {
			this->normalize();

			T other_numerator_copy = 0;

			if (!ops::equals(denominator, other.denominator)) {
				T gcd = ops::gcd(denominator, other.denominator);
				T lcm = ops::lcm(denominator, other.denominator, gcd);
				T mult_denom = lcm / denominator;
				T mult_other_denom = lcm / other.denominator;
				numerator *= mult_denom;
				other_numerator_copy = other.numerator;
				other_numerator_copy *= mult_other_denom;
				denominator = lcm;
			}
			numerator += other_numerator_copy;
			this->normalize();
		}
	}
	void sub(rational_t<T> const& other) {
		if (this->is_consistent() && other.is_consistent()) {
			this->normalize();
			T other_numerator_copy;

			if (!ops::equals(denominator, other.denominator)) {
				T gcd = ops::gcd(denominator, other.denominator);
				T lcm = ops::lcm(denominator, other.denominator, gcd);
				if (ops::is_negative(lcm)) {
					lcm *= (-1);
				}
				T mult_denom = lcm / denominator;
				T mult_o_denom = lcm / other.denominator;
				numerator *= mult_denom;
				other_numerator_copy = other.numerator * mult_denom;
				denominator = lcm;
			}
			numerator -= other_numerator_copy;
			this->normalize();
		}
	}
	void mul(rational_t<T> const& other) {
		if (this->is_consistent() && other.is_consistent()) {
			numerator *= other.numerator;
			denominator *= other.denominator;
			this->normalize();
		}

	}
	void div(rational_t<T> const& other) {
		if (this->is_consistent() && other.is_consistent()) {
			numerator *= other.denominator;
			denominator *= other.numerator;
			this->normalize();
		}
	}

	//force error functions
	void force_error(T const denom) {
		if (ops::is_zero(denom)) {
			throw divide_by_zero_error();
		}
	}
	double force_error() {
		double value;
		if (ops::is_zero(denominator)) {
			throw divide_by_zero_error();
		}
		else {
			value = static_cast<double>(numerator) / denominator;
		}
		return value;
	}


	//print and scan
	static void print_result(rational_t const& other) {
		std::cout << other << "\n";
	}
	void print(std::ostream& os)const {
		os << "<" << numerator << "/" << denominator << ">";
	}


	//logical operators
	bool operator==(rational_t const &other) {
		rational_t tmp1(*this);
		rational_t tmp2(other);
		tmp1.normalize();
		tmp2.normalize();
		return ops::equals(tmp1.numerator, tmp2.numerator) && ops::equals(tmp1.denominator, tmp2.denominator);
	}
	bool operator!=(rational_t const& other) {
		rational_t tmp1(*this);
		rational_t tmp2(other);
		tmp1.normalize();
		tmp2.normalize();
		return !ops::equals(tmp1.numerator, tmp2.numerator) || !ops::equals(tmp1.denominator, tmp2.denominator);
	}
	bool operator<(rational_t const& other) {
		rational_t tmp1(*this);
		rational_t tmp2(other);
		tmp1.normalize();
		tmp2.normalize();
		return tmp1.numerator < tmp2.numerator;
	}
	bool operator>(rational_t const& other) {
		rational_t tmp1(*this);
		rational_t tmp2(other);
		tmp1.normalize();
		tmp2.normalize();
		return tmp1.numerator > tmp2.numerator;
	}
	bool operator<=(rational_t const& other) {
		rational_t tmp1(*this);
		rational_t tmp2(other);
		tmp1.normalize();
		tmp2.normalize();
		return tmp1.numerator <= tmp2.numerator;
	}
	bool operator>=(rational_t const& other) {
		rational_t tmp1(*this);
		rational_t tmp2(other);
		tmp1.normalize();
		tmp2.normalize();
		return tmp1.numerator >= tmp2.numerator;
	}

	

private:
	T numerator;
	T denominator;

	//operator overloading BARTON NACKMANN Trick
	friend inline rational_t<T> operator+(rational_t<T> const& lhs, rational_t<T> const rhs) {
		rational_t<T> tmp(lhs);
		tmp.add(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator-(rational_t<T> const& lhs, rational_t<T> const rhs) {
		rational_t<T> tmp(lhs);
		tmp.sub(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator*(rational_t<T> const& lhs, rational_t<T> const rhs) {
		rational_t<T> tmp(lhs);
		tmp.mul(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator/(rational_t<T> const& lhs, rational_t<T> const rhs) {
		rational_t<T> tmp(lhs);
		tmp.div(rhs);
		return tmp;
	}

	friend inline rational_t<T> operator+=(rational_t<T> & lhs, rational_t<T> const rhs) {
		lhs.add(rhs);
		return lhs;
	}
	friend inline rational_t<T> operator-=(rational_t<T> & lhs, rational_t<T> const rhs) {
		lhs.sub(rhs);
		return lhs;
	}
	friend inline rational_t<T> operator*=(rational_t<T> & lhs, rational_t<T> const rhs) {
		lhs.mul(rhs);
		return lhs;
	}
	friend inline rational_t<T> operator/=(rational_t<T> & lhs, rational_t<T> const rhs) {
		lhs.div(rhs);
		return rhs;
	}

	

	friend inline std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs) {
		rhs.print(lhs);
		return lhs;
	}
	friend inline std::istream& operator>>(std::istream& lhs, rational_t const& rhs) {
		rhs.scan(lhs);
		return lhs;
	}


	//consistency and normalization
	bool is_consistent()const {
		return ops::is_zero(this->denominator) ? false : true;
	}
	void normalize() {
		if (!ops::is_zero(numerator) && !ops::is_zero(denominator)) {
			if (ops::is_negative(numerator) && ops::is_negative(denominator)) {
				numerator *= (-1);
				denominator *= (-1);
			}
			T gcd = ops::gcd(numerator, denominator);
			numerator /= gcd;
			denominator /= gcd;
		}
	}
};





#endif
