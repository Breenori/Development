#ifndef RATIONAL_T_H
#define RATIONAL_T_H

#include <iostream>
#include <string>
#include <fstream>
#include <istream>




class rational_t{
private:
	int numerator;
	int denominator;

	//helper functions
	static int gcd(int const first, int const second);
	static int lcm(int const first, int const second);
	std::string as_string();

	//consistency and normalization
	bool is_consistent()const;
	void normalize();
	bool is_negative()const;
	bool is_positive()const;
	bool is_zero()const;



public:
	//constructor and destructor
	rational_t();
	rational_t(int _numerator);
	rational_t(int _numerator, int _denominator);
	rational_t(rational_t const& other);
	~rational_t();

	//methods to calculate
	void add(rational_t const & other);
	void sub(rational_t const & other);
	void mul(rational_t const & other);
	void div(rational_t const & other);
	double force_error()const;
	static void force_error(int const denom);

	//getter
	int get_numerator()const;
	int get_denominator()const;

	//print and scan function
	void print(std::ostream& os = std::cout)const;
	void scan(std::istream& ifs);
	static void print_result(rational_t const& other);
	

	//Operator overloading
	rational_t operator+(rational_t const& other)const;
	rational_t operator-(rational_t const& other)const;
	rational_t operator*(rational_t const& other)const;
	rational_t operator/(rational_t const& other)const;

	rational_t& operator+=(rational_t & other);
	rational_t& operator-=(rational_t & other);
	rational_t& operator*=(rational_t const& other);
	rational_t& operator/=(rational_t const& other);

	rational_t& operator=(rational_t other);

	//logical operators
	bool operator==(const rational_t& other) const;
	bool operator!=(const rational_t& other) const;
	bool operator<(const rational_t& other)const;
	bool operator<=(const rational_t& other)const;
	bool operator>(const rational_t& other)const;
	bool operator>=(const rational_t& other)const;

};

//Non-member-operator
rational_t operator+(int const& lhs, rational_t & rhs);
rational_t operator-(int const& lhs, rational_t & rhs);
rational_t operator*(int const& lhs, rational_t const& rhs);
rational_t operator/(int const& lhs, rational_t const& rhs);

std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
std::istream& operator>>(std::istream& lhs, rational_t & rhs);



#endif