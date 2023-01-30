#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>
#include "operations.h"
#include "div_by_zero_error.h"
#include "invalid_input_error.h"
using std::to_string;

template<typename S>
concept numeric = requires(S t) {
	t + t;
	t - t;
	t* t;
	t / t;
	t += t;
	t -= t;
	t *= t;
	t /= t;
	t == t;
	t != t;
	t < t;-
	t > t;
	t <= t;
	t >= t;
	-t;
	std::cout << t;
};

template<numeric T = int>
class rational_t {
private:
	T numerator;
	T denominator;

	//+, -, *, /
	friend inline rational_t<T> operator+(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> temp(lhs);
		temp.add(rhs);
		return temp;
	}
	friend inline rational_t<T> operator-(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> temp(lhs);
		temp.sub(rhs);
		return temp;
	}
	friend inline rational_t<T> operator*(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> temp(lhs);
		temp.mul(rhs);
		return temp;
	}
	friend inline rational_t<T> operator/(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t<T> temp(lhs);
		temp.div(rhs);
		return temp;
	}

	//compound assignment operators
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

	//+, -, *, / with T
	friend inline rational_t<T> operator+(T const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp += rhs;
		return tmp;
	}
	friend inline rational_t<T> operator-(T const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp -= rhs;
		return tmp;
	}
	friend inline rational_t<T> operator*(T const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp *= rhs;
		return tmp;
	}
	friend inline rational_t<T> operator/(T const& lhs, rational_t<T> const& rhs) {
		rational_t<T> tmp(lhs);
		tmp /= rhs;
		return tmp;
	}

	//comparison operators
	friend inline bool operator==(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return	ops::equals(lhs.numerator, rhs.numerator) &&
			ops::equals(lhs.denominator, rhs.denominator);
	}
	friend inline bool operator!=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return	!(lhs == rhs);
	}
	friend inline bool operator<(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		T lhs_v = lhs.get_numerator() / lhs.get_denominator();
		T rhs_v = rhs.get_numerator() / rhs.get_denominator();
		return	lhs_v < rhs_v;
	}
	friend inline bool operator>(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		T lhs_v = lhs.get_numerator() / lhs.get_denominator();
		T rhs_v = rhs.get_numerator() / rhs.get_denominator();
		return	lhs_v > rhs_v;
	}
	friend inline bool operator<=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return lhs < rhs || lhs == rhs;
	}
	friend inline bool operator>=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return lhs > rhs || lhs == rhs;
	}

	friend inline std::ostream& operator<<(std::ostream& lhs, rational_t<T> const& rhs) {
		rhs.print(lhs);
		return lhs;
	}
	friend inline std::istream& operator>>(std::istream& lhs, rational_t<T>& rhs) {
		rhs.scan(lhs);
		return lhs;
	}

	bool is_consistent() const {
		return !ops::is_zero(denominator);
	}

	void normalize() {
		if(is_zero()){
			numerator = nelms::zero<T>();
			denominator = nelms::one<T>();
		}
		else {
			T _gcd = ops::gcd(ops::abs(numerator), ops::abs(denominator));
			if (_gcd > nelms::zero<T>()) {
				numerator /= _gcd;
				denominator /= _gcd;
			}
			if (ops::is_negative(numerator) && ops::is_negative(denominator)) {
				numerator = -numerator;
				denominator = -denominator;
			}
		}
	}

	//read from stream
	bool scan(std::istream& is = std::cin) {
		T n;
		T d;
		char div;
		is >> n;
		if (!is.fail()) {
			is >> div;
			if (div == '/') {
				is >> d;
				if (!is.fail()) {
					numerator = n;
					denominator = d;
					if (!is_consistent()) {
						throw DivideByZeroError();
					}
					return true;
				}
			}
		}
		is.clear();
		is.ignore(1000, '\n');
		throw InvalidInputError();
		return false;
	}

public:
	rational_t() : numerator(nelms::zero<T>()), denominator(nelms::one<T>()) {}
	rational_t(T const& _numerator) : numerator(_numerator), denominator(nelms::one<T>()) {}
	rational_t(T const& _numerator, T const& _denominator){
		if (_denominator == nelms::zero<T>()) {
			throw DivideByZeroError();
		}
		else {
			numerator = _numerator;
			denominator = _denominator;
		}
	}
	rational_t(rational_t<T> const& other) {
		numerator = other.numerator;
		denominator = other.denominator;
	}

	T get_numerator() const {
		return this->numerator;
	}

	T get_denominator() const {
		return this->denominator;
	}

	bool is_negative() const {
		return ops::is_negative(numerator) != ops::is_negative(denominator);
	}

	bool is_positive() const {
		return !is_negative();
	}

	bool is_zero() const {
		return ops::is_zero(numerator);
	}

	void inverse() {
		T temp = numerator;
		numerator = denominator;
		denominator = temp;
		if (!is_consistent()) {
			throw DivideByZeroError();
		}
	}

	void add(rational_t<T> const& other) {
		rational_t<T> temp(other);
		temp.normalize();
		normalize();
		numerator = numerator * temp.denominator + temp.numerator * denominator;
		denominator *= temp.denominator;
		normalize();
	}

	void sub(rational_t<T> const& other) {
		rational_t<T> temp(other);
		temp.numerator = ops::negate(temp.numerator);
		add(temp);
		normalize();
	}

	void mul(rational_t<T> const& other) {
		if (is_zero() || other.is_zero()) {
			numerator = nelms::zero<T>();
			denominator = nelms::one<T>();
		}
		numerator *= other.numerator;
		denominator *= other.denominator;
		normalize();
	}

	void div(rational_t<T> const& other) {
		if (other.is_zero()) {
			throw DivideByZeroError();
		}
		else {
			numerator *= other.denominator;
			denominator *= other.numerator;
			if (!is_consistent()) {
				throw DivideByZeroError();
			}
			normalize();
		}
	}

	std::string as_string()const {
		std::stringstream ss;
		ss << numerator << "/" << denominator;
		return ss.str();
	}

	void print(std::ostream& os) const {
		os << as_string();
	}

	rational_t& operator=(rational_t<T> other) {
		numerator = other.numerator;
		denominator = other.denominator;
		return *this;
	}
};


template<typename T = int>
class number_t {
private:
	T number;

	friend inline number_t<T> operator+(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.add(rhs);
		return tmp;
	}
	friend inline number_t<T> operator-(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.sub(rhs);
		return tmp;
	}
	friend inline number_t<T> operator-(number_t<T> const& lhs) {
		number_t<T> temp(-lhs.get_number());
		return temp;
	}
	friend inline number_t<T> operator*(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.mul(rhs);
		return tmp;
	}
	friend inline number_t<T> operator/(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs);
		tmp.div(rhs);
		return tmp;
	}

	friend inline number_t<T>& operator+=(number_t<T>& lhs, number_t<T> const& rhs) {
		lhs.add(rhs);
		return lhs;
	}
	friend inline number_t<T>& operator-=(number_t<T>& lhs, number_t<T> const& rhs) {
		lhs.sub(rhs);
		return lhs;
	}
	friend inline number_t<T>& operator*=(number_t<T>& lhs, number_t<T> const& rhs) {
		lhs.mul(rhs);
		return lhs;
	}
	friend inline number_t<T>& operator/=(number_t<T>& lhs, number_t<T> const& rhs) {
		lhs.div(rhs);
		return lhs;
	}

	friend inline number_t<T>& operator%(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> temp(lhs.get_number() % rhs.get_number());
		return temp;
	}

	friend inline bool operator==(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number == rhs.number;
	}
	friend inline bool operator!=(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number != rhs.number;
	}
	friend inline bool operator<(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number < rhs.number;
	}
	friend inline bool operator>(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number > rhs.number;
	}
	friend inline bool operator<=(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number < rhs.number || lhs.number == rhs.number;
	}
	friend inline bool operator>=(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number > rhs.number || lhs.number == rhs.number;
	}

	friend inline std::ostream& operator<<(std::ostream& lhs, number_t<T> const& rhs) {
		lhs << rhs.get_number();
		return lhs;
	}
	friend inline std::istream& operator>>(std::istream& lhs, number_t<T>& rhs) {
		T _number;
		lhs >> _number;
		if (!lhs.fail()) {
			rhs.number = _number;
		}
		else {
			rhs.number = nelms::zero<T>();
		}
		return lhs;
	}

public:
	number_t() : number(nelms::zero<T>()) {}
	number_t(T _number) : number(_number) {}
	number_t(number_t<T> const& other) : number(other.number) {}

	T get_number() const{
		return this->number;
	}

	void add(number_t<T> const& other) {
		number = number + other.number;
	}

	void sub(number_t<T> const& other) {
		number = number - other.number;
	}

	void mul(number_t<T> const& other) {
		number = number * other.number;
	}

	void div(number_t<T> const& other) {
		number = number / other.number;
	}

	std::string to_string(number_t<T> const& n) {
		return std::to_string(n.get_number());
	}

	
};

template<>
inline number_t<int>
nelms::one<number_t<int>>() {
	return number_t(1);
}

template<>
inline number_t<int>
nelms::zero<number_t<int>>() {
	return number_t(0);
}