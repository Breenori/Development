#pragma once
#include <iostream>
#include <string>
#include "exceptions.h"

using std::cin;
using std::cout;
using std::string;

template <typename T>
concept numeric = requires(T v) {
	v + v; // T requires operator +
	v - v;
	v* v;
	v / v;
	v% v;
	v == v;
	v != v;
	v < v;
	v > v;
	std::cout << v;
	
};
namespace nelms { //neutral elements 

	//neutrales Element für 0
	template <typename T> inline T zero() {
		return T();
	}

	template <>inline int zero() {
		return 0;
	}
}



template <numeric T = int> 
class rational_t {
public:

	rational_t<T>(T _num = 0, T _den = 0) : num{ _num }, den{ _den } {}//constructor
	rational_t(rational_t <T>const& other); //copy constructor
	~rational_t();

	void add(rational_t<T> const& other);
	void sub(rational_t<T> const& other);
	void mul(rational_t<T> const& other);
	void div(rational_t<T> const& other);



	bool compare(rational_t<T> const& other);
	bool not_compare(rational_t<T> const& other);
	bool smaller_than(rational_t<T> const& other);
	bool greater_than(rational_t<T> const& other);
	bool smaller(rational_t<T> const& other);
	bool greater(rational_t<T> const& other);





	string as_string() const;
	void scan(std::istream& in = cin);
	T get_numerator();
	T get_denominator();

	void is_negative();
	void is_positive();
	void is_zero();


	rational_t<T>& operator=(rational_t<T> const& other) {
		if (this == &other) {
			return *this;
		}

		num = other.num;
		den = other.den;

		noramlize();

		return *this;
	}


private:

	T num; //numerator (zähler)
	T den; //denominator (nenner)

	void is_consistent();
	void noramlize();
	void print(std::ostream& out = cout)const;
	//Kehrwert
	rational_t<T> inverse()const;

	friend inline rational_t<T> operator+(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
			temp.add(other);
			return temp;
	}
	friend inline rational_t<T> operator-(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.sub(other);
		return temp;
	}
	friend inline rational_t<T> operator*(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.mul(other);
		return temp;
	}
	friend inline rational_t<T> operator/(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.div(other);
		return temp;
	}

	friend inline rational_t<T> operator+=(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.add(other);
		return *temp;

	}
	friend inline rational_t<T> operator-=(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.sub(other);
		return *temp;

	}
	friend inline rational_t<T>operator*=(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.mul(other);
		return *temp;

	}
	friend inline rational_t<T> operator/=(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.div(other);
		return *temp;
	}


	friend inline rational_t<T> operator==(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.compare(other);
		return *temp;
	
	}
	friend inline rational_t<T> operator!=(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.not_compare(other);
		return *temp;
	}
	friend inline rational_t<T> operator<=(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.smaller_than(other);
		return *temp;


	}
	friend inline rational_t<T> operator>=(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.greater_than(other);
		return *temp;
	}
	friend inline rational_t<T> operator<(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.smaller(other);
		return *temp;
	}
	friend inline rational_t<T> operator>(rational_t<T> const& lhs, rational_t<T> const& other) {
		rational_t<T> temp(lhs);
		temp.greater(other);
		return *temp;
	}


	friend inline std::ostream& operator<< (std::ostream& out, rational_t<T> const& other);
	friend inline std::istream& operator>>(std::istream& in, rational_t<T> const& other);




};

template <numeric T>
class number_t {


};

