#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <stdexcept>
#include "operations.h"
#include "div_by_zero_error.h"

template<typename T = int>
class number_t
{
	//value
	T number;
public:
	//constructors
	number_t<T>() :number(nelms::zero<T>()) {};
	number_t<T>(T const& a) :number(a) {};
	//cpy
	number_t<T>(number_t<T> const& src) { this->number = src.number; };
	//destructor
	~number_t<T>() = default;
	//get-a
	T get_number_t()const {
		return this->number;
	}
	void set_number_t(T a)const {
		this->number = a;
	}
	number_t<T>& operator=(number_t<T> const& rhs) {
		if (*this != rhs) {
			this->number = rhs.number;
		}
		return *this;
	}
private:
	//operations
	friend inline number_t<T> operator+(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T>tmp{ lhs };//cpy
		tmp.number += rhs.number;
		return tmp;
	}
	friend inline number_t<T> operator-(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T>tmp{ lhs };//cpy
		tmp.number -= rhs.number;
		return tmp;
	}
	friend inline number_t<T> operator*(number_t<T> const& lhs, number_t<T> const& rhs) {
		number_t<T>tmp{ lhs };//cpy
		tmp.number *= rhs.number;
		return tmp;
	}
	friend inline number_t<T> operator/(number_t<T> const& lhs, number_t<T> const& rhs) {
		if (rhs.number == nelms::zero<T>()) {
			throw DivideByZeroError();
		}
		number_t<T>tmp{ lhs };//cpy
		tmp.number /= rhs.number;
		return tmp;
	}
	//assign
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
		if (rhs.number == nelms::zero<T>()) {
			throw DivideByZeroError();
		}
		lhs.number /= rhs.number;
		return lhs;
	}
	//compare
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
	//iostream
	friend inline std::ostream& operator <<(std::ostream& lhs, number_t<T> const& rhs) {
		lhs << rhs.number;
		return lhs;
	}
	friend inline std::istream& operator >>(std::istream& lhs, number_t<T>& rhs) {
		lhs >> rhs.number;
		return lhs;
	}
};
//specialisation
namespace nelms {
	template<>inline number_t<int> one() {
		number_t<int> tmp(std::integral_constant<int, 1>::value);
		return tmp;
	}
	template<>inline number_t<int> zero() {
		number_t<int> tmp(0);
		return tmp;
	}
};
namespace ops {
	template<>inline number_t<int> remainder(number_t<int> const& a, number_t<int> const& b) {
		number_t<int> tmp(ops::remainder<int>(a.get_number_t(), b.get_number_t()));
		return tmp;
	}
};