#ifndef NUMBER
#define NUMBER

#include "div_by_zero.h"

template<typename T>
class Number {
private:
	T value;
	friend inline std::ostream& operator<<(std::ostream& lhs, Number<T> const& rhs) {
		lhs << rhs.value;
		return lhs;
	}
	friend inline Number<T> operator+(Number<T> const& lhs, Number<T> const& rhs) {
		Number<T> tmp(lhs); // Copy Constructor
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
	friend inline Number<T> operator/(Number<T> const& lhs, Number<T> const& rhs) {
		Number<T> tmp(lhs);
		tmp.value /= rhs.value;
		return tmp;
	}
	
	friend inline bool operator==(Number<T> const& lhs, Number<T> const& rhs) {
		return lhs.value == rhs.value;
	}
	friend inline bool operator!=(Number<T> const& lhs, Number<T> const& rhs) {
		return lhs.value != rhs.value;
	}
	
	friend inline bool operator<(Number<T> const& lhs, Number<T> const& rhs) {
		return lhs.value < rhs.value;
	}
	friend inline bool operator<=(Number<T> const& lhs, Number<T> const& rhs) {
		return (lhs == rhs) || (lhs < rhs);
	}
	friend inline bool operator>(Number<T> const& lhs, Number<T> const& rhs) {
		return lhs.value > rhs.value;
	}
	friend inline bool operator>=(Number<T> const& lhs, Number<T> const& rhs) {
		return (lhs == rhs) || (lhs > rhs);
	}

	friend inline Number<T>& operator+=(Number<T>& lhs, Number<T> const& rhs) {
		lhs.value += rhs.value;
		return lhs;
	}
	friend inline Number<T>& operator-=(Number<T>& lhs, Number<T> const& rhs) {
		lhs.value -= rhs.value;
		return lhs;
	}
	friend inline Number<T>& operator*=(Number<T> & lhs, Number<T> const& rhs) {
		lhs.value *= rhs.value;
		return lhs;
	}
	friend inline Number<T>& operator/=(Number<T>& lhs, Number<T> const& rhs) {
		if (rhs == 0 && lhs != 0) {
			throw DivideByZeroError();
		}
		lhs.value /= rhs.value;
		return lhs;
	}
	
	friend inline Number<T> operator%(Number<T> const& lhs, Number<T> const& rhs) {
		if (rhs == 0|| lhs == 0) {
			return 0;
		}
		Number<T> tmp = lhs.value % rhs.value;
		return tmp;
	}

public:
	Number() {

	}
	// conversion constructor
	Number(T const & value_) : value(value_) {

	}
	Number(Number<T> const& other) : value(other.value) {

	}


};


#endif