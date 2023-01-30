#ifndef number_h
#define number_h

#include <iostream>
#include <string>
#include "operations.h"
#include <fstream>



template<typename T>
class Number {
private:
	T value;

	//friend inline operator overloading
	friend inline std::ostream& operator<<(std::ostream& lhs, Number<T> const& rhs) {
		lhs << rhs.value;
		return lhs;
	}
	
	friend inline Number<T> operator+(Number<T> const& lhs, Number<T> const& rhs) {
		Number<T> tmp(lhs);
		tmp.value += rhs.value;
		return tmp;
	}

	friend inline Number<T> operator-(Number<T> const& lhs, Number<T> const& rhs) {
		Number<T> tmp(lhs);
		tmp.value -= rhs.value;
		return tmp;
	}
	friend inline Number<T> operator*(Number<T> const& lhs, Number<T> const& rhs) {
		Number<T> tmp(lhs);
		tmp.value *= rhs.value;
		return tmp;
	}
	friend inline Number<T>operator/(Number<T> const& lhs, Number<T> const& rhs) {
		Number<T> tmp(lhs);
		tmp.value /= rhs.value;
		return tmp;
	}

	//arithmetic + assign operator
	friend inline Number<T> operator+=(Number<T> & lhs, Number<T> const& rhs) {
		lhs.value += rhs.value;
		return lhs;
	}
	friend inline Number<T> operator-=(Number<T>& lhs, Number<T> const& rhs) {
		lhs.value -= rhs.value;
		return lhs;
	}
	friend inline Number<T> operator*=(Number<T>& lhs, Number<T> const& rhs) {
		lhs.value *= rhs.value;
		return lhs;
	}
	friend inline Number<T> operator/=(Number<T>& lhs, Number<T> const& rhs) {
		lhs.value /= rhs.value;
		return lhs;
	}

	//modulo
	friend inline Number<T> operator%(Number<T>const& lhs, Number<T> const& rhs) {
		if (rhs.value == nelms::zero<T>()) {
			try {
				throw divide_by_zero_error();
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}
		}
		else {
			Number<T> tmp = lhs.value % rhs.value;
			return tmp;
		}
	}

	//logical operators
	friend inline bool operator==(Number<T> const& lhs, Number<T> const& rhs) {
		return ops::equals(lhs.value, rhs.value);
	}
	friend inline bool operator!= (Number<T> const& lhs, Number<T> const& rhs) {
		return !ops::equals(lhs.value, rhs.value);
	}
	friend inline bool operator< (Number<T> const& lhs, Number<T> const& rhs) {
		return lhs.value < rhs.value;
	}
	friend inline bool operator> (Number<T> const& lhs, Number<T> const& rhs) {
		return lhs.value > rhs.value;
	}
	friend inline bool operator<= (Number<T> const& lhs, Number<T> const& rhs) {
		return lhs.value <= rhs.value;
	}
	friend inline bool operator >= (Number<T> const& lhs, Number<T> const& rhs) {
		return lhs.value >= rhs.value;
	}
	


public:
	Number() {
	}

	Number(T const& _value) : value(_value) {
	}

	Number(Number<T> const& other) : value(other.value) {
	}
};

namespace nelms {

	template<> inline Number<int> one() {
		Number<int> o(1);
		return o;
	}

	template<> inline Number<int> zero() {
		Number<int> z(0);
		return z;
	}

};

#endif