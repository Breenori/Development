#pragma once
#include <iostream>
#include <string>
#include "exceptions.h"

using std::cin;
using std::cout;
using std::string;

namespace nelms { //neutral elements 

	//neutrales Element für 0
	template <typename T> inline T zero() {
		return T();
	}

	template <>inline int zero() {
		return 0;
	}
}



class rational_t {
public:

	rational_t(int _num = 0, int _den = 0 ); //constructor
	rational_t(rational_t const& other); //copy constructor
	~rational_t();

	void add(rational_t const& other);
	void sub(rational_t const& other);
	void mul(rational_t const& other);
	void div(rational_t const& other);

	rational_t operator+(rational_t const& other);
	rational_t operator-(rational_t const& other);
	rational_t operator*(rational_t const& other);
	rational_t operator/(rational_t const& other);

	rational_t& operator=(rational_t const& other);

	rational_t operator+=(rational_t const& other);
	rational_t operator-=(rational_t const& other);
	rational_t operator*=(rational_t const& other);
	rational_t operator/=(rational_t const& other);

	bool compare(rational_t const& other);
	bool not_compare(rational_t const& other);
	bool smaller_than(rational_t const& other);
	bool greater_than(rational_t const& other);
	bool smaller(rational_t const& other);
	bool greater(rational_t const& other);


	rational_t operator==(rational_t const& other);
	rational_t operator!=(rational_t const& other);
	rational_t operator<=(rational_t const& other);
	rational_t operator>=(rational_t const& other);
	rational_t operator<(rational_t const& other);
	rational_t operator>(rational_t const& other);



	


	string as_string() const;
	void scan(std::istream& in = cin);
	int get_numerator();
	int get_denominator();

	void is_negative();
	void is_positive();
	void is_zero();


		

private:

	int num; //numerator (zähler)
	int den; //denominator (nenner)

	void is_consistent();
	void noramlize();
	void print(std::ostream& out = cout)const;

	//int gdc();


};

std::ostream& operator<< (std::ostream& out, rational_t const& other);
std::istream& operator>>(std::istream& in, rational_t const& other);

