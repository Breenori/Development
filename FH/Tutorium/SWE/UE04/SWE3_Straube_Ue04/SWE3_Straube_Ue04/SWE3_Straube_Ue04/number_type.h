#ifndef NUMBER_T_H
#define NUMBER_T_H

/*
* ----- Includes. -----
*/
#include <iostream>
#include <fstream>
#include "operations.h"

/*
* ----- Usings. -----
*/
using std::ostream;
using std::istream;
using std::to_string;

/*
* ----- Template-Class. -----
*/
// Nr: 2 & 4.
template<typename T = int>
class Number_t {
private:
	T value;

public:
	// Default Constructor.
	Number_t() {
		//
	}

	// Conversion Constructor.
	Number_t(T const& _value) : value(_value) {
		//
	}

	// Copy Constructor.
	Number_t(Number_t<T> const& other) : value(other.value) {
		//
	}

	// Concept +,-,*,/ erfüllt
	friend inline Number_t<T> operator+(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		Number_t<T> tmp(lhs);
		tmp.value += rhs.value; 
		return tmp;
	}
	friend inline Number_t<T> operator-(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		Number_t<T> tmp(lhs);
		tmp.value -= rhs.value;
		return tmp;
	}
	friend inline Number_t<T> operator*(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		Number_t<T> tmp(lhs);
		tmp.value *= rhs.value;
		return tmp;
	}
	friend inline Number_t<T> operator/(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		Number_t<T> tmp(lhs);
		tmp.value /= rhs.value;
		return tmp;
	}

	// Concept ==, !=, <, >, <=, >=.
	friend inline bool operator==(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		return lhs.value == rhs.value;
	}
	friend inline bool operator!=(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		return lhs.value != rhs.value;
	}
	friend inline bool operator<(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		return lhs.value < rhs.value;
	}
	friend inline bool operator<=(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		return lhs.value <= rhs.value;
	}
	friend inline bool operator>(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		return lhs.value > rhs.value;
	}
	friend inline bool operator>=(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		return lhs.value >= rhs.value;
	}

	// Concept +=,-=,*=,/=.
	friend inline Number_t<T>& operator+=(Number_t<T>& lhs, Number_t<T> const& rhs) {
		lhs.value += rhs.value;
		return lhs;
	}
	friend inline Number_t<T>& operator-=(Number_t<T>& lhs, Number_t<T> const& rhs) {
		lhs.value -= rhs.value;
		return lhs;
	}
	friend inline Number_t<T>& operator*=(Number_t<T>& lhs, Number_t<T> const& rhs) {
		lhs.value *= rhs.value;
		return lhs;
	}
	friend inline Number_t<T>& operator/=(Number_t<T>& lhs, Number_t<T> const& rhs) {
		lhs.value /= rhs.value;
		return lhs;
	}

	// Concept <<, >>.
	friend inline ostream& operator<<(ostream& lhs, Number_t<T> const& rhs) {
		lhs << rhs.value;
		return lhs;
	}
	friend inline istream& operator>>(istream& lhs, Number_t<T>& rhs) {
		lhs >> rhs.value;
		return lhs;
	}

	// Concept %.
	friend inline Number_t<T> operator%(Number_t<T> const& lhs, Number_t<T> const& rhs) {
		Number_t<T> tmp(lhs);
		tmp.value = ops::remainder(lhs.value, rhs.value);
		return tmp;
	}
};

// Nr: 7.
namespace nelms {
	template<>
	inline Number_t<int> zero() {
		return Number_t(0);
	}
	template<>
	inline Number_t<int> one() {
		return Number_t(1);
	}
}

#endif