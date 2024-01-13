#ifndef RATIONAL_T_H
#define RATIONAL_T_H
#include <iostream>
#include <fstream>
#include "div_by_zero_error.h"
#include "number_t.h"
//concept
template<typename S>
concept numeric = requires(S v) {
	v + v;
	v += v;
	v - v;
	v -= v;
	v* v;
	v *= v;
	v / v;
	v /= v;
	v == v;
	v != v;
	v < v;
	v > v;
	v <= v;
	v >= v;
	std::cout << v;
	std::cin >> v;
};
template<numeric T = int>
class rational_t {
	//typecasts
	using value_t = T;
	//values
	value_t numerator;
	value_t denominator;
public:
	//constructors
	rational_t() :denominator(nelms::one<T>()), numerator(nelms::one<T>()) {}
	rational_t(value_t const _numerator) :denominator(nelms::one<T>()), numerator(_numerator) {}
	rational_t(value_t const _numerator, value_t const _denominator) :denominator(_denominator), numerator(_numerator) {
		is_consistent();
	}
	rational_t(rational_t<T> const& other) {
		if (other.is_consistent()) {
			this->denominator = other.denominator;
			this->numerator = other.numerator;
		}
	}
	//get-a
	value_t get_numerator()const { return this->numerator; }
	value_t get_denominator()const { return this->denominator; }
	//set-a
	void set_numerator(value_t const _numerator) { this->numerator = _numerator; }
	void set_denominator(value_t const _denominator) { this->denominator = _denominator; }
	//print
	std::ostream& print(std::ostream& out = std::cout)const {
		if (ops::equals<T>(this->denominator, nelms::one<T>()))
			out << "< " << this->numerator << " >";
		else
			out << "< " << this->numerator << "/" << this->denominator << " >";
		return out;
	}
	//scan
	static std::istream& scan(std::istream& in, rational_t<T>& value) {
		value_t _numerator = nelms::zero<T>();
		value_t _denominator = nelms::zero<T>();
		in >> _numerator;
		if (in.good())
		{
			in >> _denominator;
			value = rational_t<T>(_numerator, _denominator);
		}
		else {
			value = rational_t<T>();
		}
		return in;
	}
	//operators
	void add(rational_t<T> const& other) {
		this->normalize();
		rational_t<T> tmp = other;
		tmp.normalize();
		//least common multiple
		value_t l_c_m = lcm(this->denominator, other.denominator);
		//split
		value_t lhsm = l_c_m / this->denominator;
		value_t rhsm = l_c_m / tmp.denominator;
		//mul
		this->numerator *= lhsm;
		this->denominator *= lhsm;
		//refactor
		this->numerator += tmp.numerator * rhsm;
		this->normalize();
	}
	void sub(rational_t<T> const& other) {
		this->normalize();
		rational_t<T> tmp = other;
		tmp.normalize();
		//least common multiple
		value_t l_c_m = lcm(this->denominator, other.denominator);
		//split
		value_t lhsm = l_c_m / this->denominator;
		value_t rhsm = l_c_m / tmp.get_denominator();
		//mul
		this->numerator *= lhsm;
		this->denominator *= lhsm;
		this->numerator -= tmp.numerator * rhsm;
		this->normalize();
	}
	void mul(rational_t<T> const& other) {
		this->denominator *= other.denominator;
		this->numerator *= other.numerator;
		this->is_consistent();
		this->normalize();
	}
	void div(rational_t<T> const& other) {
		this->denominator *= other.numerator;
		this->numerator *= other.denominator;
		this->is_consistent();
		this->normalize();
	}
	//helper
	void inverse() {
		if (!ops::equals(numerator, denominator) && !ops::is_zero<T>(this->denominator) && !ops::equals(numerator, nelms::zero<T>()))
		{
			T tmp = this->numerator;
			this->numerator = this->denominator;
			this->denominator = tmp;
		}
		else {
			throw DivideByZeroError();
		}
	}
	void normalize() {
		//absolut values
		T _numerator = ops::abs<T>(this->numerator);
		T _denominator = ops::abs<T>(this->denominator);
		//negate
		if (ops::is_negative(this->denominator) && ops::is_negative(this->numerator)) {
			this->denominator = ops::negate(this->denominator);
			this->numerator = ops::negate(this->numerator);
		}
		//simplify
		value_t g_c_d = ops::gcd(_numerator, _denominator);
		if (this->denominator == this->numerator || (g_c_d != this->denominator && g_c_d != this->numerator) || ops::divides(this->numerator, this->denominator)) {
			this->denominator /= g_c_d;
			this->numerator /= g_c_d;
		}
	}
	//cpy-swap-idiom
	rational_t<T>& operator=(rational_t<T> const& rhs) {
		if (*this != rhs) {
			this->numerator = rhs.get_numerator();
			this->denominator = rhs.get_denominator();
		}
		return *this;
	}
private:
	//operations
	friend inline rational_t<T> operator+(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		tmp.add(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator-(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		tmp.sub(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator*(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		tmp.mul(rhs);
		return tmp;
	}
	friend inline rational_t<T> operator/(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		tmp.div(rhs);
		return tmp;
	}
	//assign
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
	//compare
	friend inline bool operator==(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return lhs.numerator / (lhs.denominator * 1.0) == rhs.numerator / (rhs.denominator * 1.0);
	}
	friend inline bool operator!=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return !(lhs == rhs);
	}
	friend inline bool operator<(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return lhs.numerator / (lhs.denominator * 1.0) < rhs.numerator / (rhs.denominator * 1.0);
	}
	friend inline bool operator>(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return lhs.numerator / (lhs.denominator * 1.0) > rhs.numerator / (rhs.denominator * 1.0);
	}
	friend inline bool operator<=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return (lhs < rhs) || (lhs == rhs);
	}
	friend inline bool operator>=(rational_t<T> const& lhs, rational_t<T> const& rhs) {
		return (lhs > rhs) || (lhs == rhs);
	}
	//iostream
	friend inline std::ostream& operator<<(std::ostream& lhs, rational_t<T> const& rhs) {
		rhs.print(lhs);
		return lhs;
	}
	friend inline std::istream& operator>>(std::istream& lhs, rational_t<T>& rhs) {
		rhs.scan(lhs, rhs);
		return lhs;
	}
	//helper
	bool is_consistent() const {
		if (ops::is_zero(denominator))
		{
			throw DivideByZeroError();
		}
		return true;
	}
	static value_t lcm(value_t const& a, value_t const& b) {
		return a * b / ops::gcd(a, b);
	}
	//non-member-functions
	//operators
	friend inline rational_t<T> operator+(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(rhs);
		rational_t left = rational_t(lhs);
		tmp.add(left);
		return tmp;
	}
	friend inline rational_t<T> operator-(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		rational_t left = rational_t(rhs);
		tmp.sub(left);
		return tmp;
	}
	friend inline rational_t<T> operator*(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(rhs);
		rational_t left = rational_t(lhs);
		tmp.mul(left);
		return tmp;
	}
	friend inline rational_t<T> operator/(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		rational_t left = rational_t(rhs);
		tmp.div(left);
		return tmp;
	}
	//assign
	friend inline bool operator==(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
		rational_t tmp(lhs);
		return tmp == rhs;
	}
	friend inline bool operator<(rational_t<T>::value_t const& lhs, rational_t<T> const& rhs) {
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
};
#endif // !RATIONAL_T_H
