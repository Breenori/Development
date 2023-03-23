#ifndef rational_h
#define rational_h

#include <iostream>
#include <string>
#include "div_by_zero.h"
#include "operations.h"

template <typename T>
concept NumericType = requires(T v) {
	v + v; // T requires operator +
	v - v;
	v * v;
	v / v;

	v == v;
	v != v;
	v % v;

	v < v;
	v > v;
	v <= v;
	v >= v;

	v += v;
	v -= v;
	v /= v;
	v *= v;
	std::cout << v;
};
template<NumericType T = int>
class Rational {
	 T numerator;
	 T denominator;

	// operator overloading:
	// Barton Nackman Trick
	friend inline bool operator==(Rational<T> const& lhs, Rational<T> const& rhs) {
		bool fun = ops::equals<T>(lhs.numerator, rhs.numerator) && ops::equals<T>(lhs.denominator, rhs.denominator);
		return fun;
	}
	
	friend inline bool operator!=(Rational<T> const& lhs, Rational<T> const& rhs) {
		bool fun = !(lhs == rhs);
		return fun;
	}
	
	friend inline bool operator<(Rational<T> const& lhs, Rational<T> const& rhs) {
		return lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator < nelms::zero<T>();
	}
	
	friend inline bool operator<=(Rational<T> const& lhs, Rational<T> const& rhs) {
		return (lhs == rhs) || (lhs < rhs);
	}
	
	friend inline bool operator>(Rational<T> const& lhs, Rational<T> const& rhs) {
		return lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator > nelms::zero<T>();
	}
	
	friend inline bool operator>=(Rational<T> const& lhs, Rational<T> const& rhs) {
		return (lhs == rhs) || (lhs > rhs);
	}
	
	// compound assignment operators
	friend inline Rational<T>& operator+=(Rational<T> & lhs, Rational<T> const& rhs) {
		lhs.numerator = (lhs.numerator * rhs.denominator) + (lhs.denominator * rhs.numerator);
		lhs.denominator *= rhs.denominator;
		return lhs.normalize();
	}
	
	friend inline Rational<T>& operator-=(Rational<T> & lhs, Rational<T> const& rhs) {
		lhs.numerator = (lhs.numerator * rhs.denominator) - (lhs.denominator * rhs.numerator);
		lhs.denominator *= rhs.denominator;
		return lhs.normalize();
	}
	
	friend inline Rational<T>& operator*=(Rational<T> & lhs, Rational<T> const& rhs) {
		lhs.numerator *= rhs.numerator;
		lhs.denominator *= rhs.denominator;
		return lhs.normalize();
	}
	
	friend inline Rational<T>& operator/=(Rational<T> & lhs, Rational<T> const& rhs) {
		lhs.numerator *= rhs.denominator;
		lhs.denominator *= rhs.numerator;
		if (!lhs.is_consistent() && rhs.is_consistent()) {
			throw DivideByZeroError();
		}
		return lhs.normalize();
	}
	
	// arithmetic operators
	friend inline Rational<T> operator+(Rational<T> const& lhs, Rational<T> const& rhs) {
		Rational<T> tmp(lhs);
		return tmp += rhs;
	}
	
	friend inline Rational<T> operator-(Rational<T> const& lhs, Rational<T> const& rhs) {
		Rational<T> tmp(lhs);
		return tmp -= rhs;
	}
	
	friend inline Rational<T> operator*(Rational<T> const& lhs, Rational<T> const& rhs) {
		Rational<T> tmp(lhs);
		return tmp *= rhs;
	}
	
	friend inline Rational<T> operator/(Rational<T> const& lhs, Rational<T> const& rhs) {
		Rational<T> tmp(lhs);
		return tmp /= rhs;
	}
	
	// stream operators
	friend inline std::ostream& operator<<(std::ostream& lhs, Rational<T> const& rhs) {
		rhs.print(lhs);
		return lhs;
	}
	
	friend inline std::istream& operator>>(std::istream& lhs, Rational<T> const& rhs) {
		rhs.scan(lhs);
		return lhs;
	}

public:
	Rational<T> operator=(Rational<T>& lhs) {
		/*numerator = lhs.numerator;
		denominator = lhs.denominator;*/
		std::swap(numerator, lhs.numerator);
		std::swap(denominator, lhs.denominator);
		return *this;
	}
	
	// Default Constructor
	Rational() : Rational(nelms::zero<T>()) {}
	
	// Conversion Constructor
	Rational(T const& _numerator) : numerator(_numerator), denominator(nelms::one<T>()) {}
	
	// Conversion Constructor
	Rational(T const& _numerator, T const& _denominator) : numerator(_numerator), denominator(_denominator) {
		if (!is_consistent()) {
			throw DivideByZeroError();
		}
		normalize();
	}
	
	// Copy Constructor
	Rational(Rational<T> const& other) : numerator(other.numerator), denominator(other.denominator) {}

	T get_numerator() const {
		return this->numerator;
	}
	
	T get_denominator() const {
		return this->denominator;
	}

	bool is_negative() const {
		return ops::is_negative<T>(numerator) || ops::is_negative<T>(denominator);
	}
	
	bool is_positive() const {
		return !is_negative();
	}

	bool is_zero() const {
		return numerator == nelms::zero<T>();
	}

	bool is_consistent() const {
		//return denominator != 0;
		return !ops::is_zero<T>(denominator);
	}

	// reduce a fraction
	Rational<T>& normalize() {
		if (ops::is_negative<T>(denominator)) {
			ops::negate<T>(denominator);
			ops::negate<T>(numerator);
		}
		T denom = ops::gcd(numerator, denominator);
		numerator /= denom;
		denominator /= denom;
		return*this;
	}
	void inverse() {
		T tmp = this->numerator;
		numerator = denominator;
		denominator = tmp;
	}

	// this can't work (i think) !!! -> explained in Lösungsidee (probably)
	std::string as_string() const {
		return denominator < 0 ? std::to_string(numerator) + " " + std::to_string(denominator) :
			std::to_string(numerator) + " / " + std::to_string(denominator);
	}

	void print(std::ostream& os = std::cout) const {
		os << numerator << ":" << denominator << "\n";
	}

	// read two numbers and create a rational number
	void scan(std::istream& is = std::cin) {
		int num;
		int denom;
		std::cout << "Enter two numbers: \n";
		is >> num >> denom;
		numerator = num;
		denominator = denom;
		// why doesn't this work? const function?
		 //if(!is_consistent()) {
		if (denominator == 0) {
			throw DivideByZeroError();
		}
	}

	friend std::ostream& operator<<(std::ostream& lhs, Rational<T> const& rhs);
	friend std::istream& operator>>(std::istream& lhs, Rational<T> const& rhs);
};
#endif
