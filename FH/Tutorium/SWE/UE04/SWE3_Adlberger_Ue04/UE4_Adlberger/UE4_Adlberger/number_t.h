#ifndef number_t_h
#define number_t_h

#include "operations.h"
#include "rational_t.h"
template<typename T>
class number_t {

private:
	T value;


	friend inline std::ostream& operator<<(std::ostream& lhs, number_t<T> const& rhs) {
		lhs << rhs.value;
		return lhs;
	}
	friend inline std::ifstream& operator>>(std::ostream& lhs, number_t<T> const& rhs) {
		lhs >> rhs.value;

		return lhs;
	}

	friend inline number_t<T> operator+(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs); //copy
		tmp.value += rhs.value;
		return tmp;
	}
	friend inline number_t<T> operator-(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs); //copy
		tmp.value -= rhs.value;
		return tmp;
	}
	friend inline number_t<T> operator*(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs); //copy
		tmp.value *= rhs.value;
		return tmp;
	}
	friend inline number_t<T> operator/(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs); //copy
		tmp.value /= rhs.value;
		return tmp;
	}

	friend inline number_t<T> operator+=(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs); //copy
		tmp.value += rhs.value;
		return tmp;
	}
	friend inline number_t<T> operator-=(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs); //copy
		tmp.value -= rhs.value;
		return tmp;
	}
	friend inline number_t<T> operator*=(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs); //copy
		tmp.value *= rhs.value;
		return tmp;
	}
	friend inline number_t<T> operator/=(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T> tmp(lhs); //copy
		tmp.value /= rhs.value;
		return tmp;
	}


	friend inline bool operator==(number_t<T> const& lhs, number_t<T> const& rhs) {
		return (lhs.value == rhs.value);
	}
	friend inline bool operator!=(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.value != rhs.value;
	}
	friend inline bool operator<(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.value < rhs.value;
	}
	friend inline bool operator<=(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.value <= rhs.value;
	}
	friend inline bool operator>(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.value > rhs.value;
	}
	friend inline bool operator>=(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.value >= rhs.value;
	}

public:
	number_t() {
	}
	number_t(T const& _value) :value(_value) {  //conversion destructor
		//std::cout << "Conversion Constructor\n";
	}
	number_t(number_t<T> const& other) : value(other.value) {
	}


};
namespace nelms {
	template<> inline number_t<int> zero() {
		return number_t(0);
	}
	template<> inline number_t<int> one() {
		return number_t(1);
	}
}
#endif // !number_t_h
