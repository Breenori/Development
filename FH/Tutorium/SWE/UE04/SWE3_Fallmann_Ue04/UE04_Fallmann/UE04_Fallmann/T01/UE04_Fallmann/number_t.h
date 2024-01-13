#pragma once

#include <ostream>
#include <istream>

#include "div_by_zero_error.h"
#include "operations.h"


using namespace nelms;




template<typename T = int>
class number_t
{
public:
	number_t<T>() :number(nelms::zero<T>()) {}
	number_t<T>(T const& n) : number(n) {}
	number_t<T>(number_t<T> const& src) {
		this->number = src.number;
	}

	T get_number() const{
		return this->number;
	}

	~number_t<T>() = default;


private:

	T number;

	friend inline number_t<T> operator+(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number + rhs.number;
	}

	friend inline number_t<T> operator-(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number - rhs.number;
	}

	friend inline number_t<T> operator*(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number * rhs.number;
	}

	friend inline number_t<T> operator/(number_t<T> const& lhs, number_t<T> const& rhs) {
		if (rhs.number == 0) {
			throw DivideByZeroError();
		}
		return lhs.number / rhs.number;
	}

	friend inline number_t<T> operator+=(number_t<T> & lhs, number_t<T> const& rhs) {
		lhs.number += rhs.number;
		return lhs;
	}

	friend inline number_t<T> operator-=(number_t<T> & lhs, number_t<T> const& rhs) {
		lhs.number -= rhs.number;
		return lhs;
	}

	friend inline number_t<T> operator*=(number_t<T> & lhs, number_t<T> const& rhs) {
		lhs.number *= rhs.number;
		return lhs;
	}

	friend inline number_t<T> operator/=(number_t<T> & lhs, number_t<T> const& rhs) {
		if (rhs.number == 0) {
			throw DivideByZeroError();
		}
		lhs.number /= rhs.number;
		return lhs;
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
		return lhs.number <= rhs.number;
	}

	friend inline bool operator>=(number_t<T> const& lhs, number_t<T> const& rhs) {
		return lhs.number >= rhs.number;
	}

	friend inline std::ostream& operator <<(std::ostream& lhs, number_t<T> const& rhs) {
		lhs << rhs.number;
		return lhs;
	}

	friend inline std::istream& operator >>(std::istream& lhs, number_t<T>& rhs) {
		lhs >> rhs.number;
		return lhs;
	}
};


//extend namespaces defined in operations.h to make them compatible with number_t
namespace nelms {

	template<>
	inline number_t<int> one() {
		number_t<int> tmp(std::integral_constant<int, 1>::value);
		return tmp;
	}

	template<>
	inline number_t<int> zero() {
		number_t<int> tmp(0);
		return tmp;
	}
};

namespace ops {
	template<>
	inline number_t<int> remainder(number_t<int> const& a, number_t<int> const& b) {
		number_t<int> res(ops::remainder<int>(a.get_number(), b.get_number()));
		return res;
	}
};
