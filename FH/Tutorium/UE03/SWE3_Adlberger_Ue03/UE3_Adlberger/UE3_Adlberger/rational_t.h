#ifndef rational_t_h
#define rational_t_h
#include <iostream>
#include <string>

class rational_t
{
	int zaehler;
	int nenner;

public:
	rational_t(int _zaehler = 0, int nenner = 1);
	
	rational_t(rational_t const& other);
	rational_t();

	void add(rational_t const& other);
	void sub(rational_t const& other);
	void mul(rational_t const& other);
	void div(rational_t const& other);

	void scan(std::ifstream& in, int& n, int& z)const;
	void print(std::ostream& os)const;
	std::string as_string()const;
	int get_numerator()const;
	int get_denominator()const;
	bool is_negative(int& const x);
	bool is_positive(int& const x);
	bool is_zero(int& const x);
	void optimize();

	bool operator==(rational_t const& other);
	bool operator!=(rational_t const& other);
	bool operator<(rational_t const& other);
	bool operator<=(rational_t const& other);
	bool operator>(rational_t const& other);
	bool operator>=(rational_t const& other);

	rational_t operator+(rational_t const& other);
	rational_t operator-(rational_t const& other);
	rational_t operator*(rational_t const& other);
	rational_t operator/(rational_t const& other);

	rational_t& operator+=(rational_t const& other);
	rational_t& operator-=(rational_t const& other);
	rational_t& operator*=(rational_t const& other);
	rational_t& operator/=(rational_t const& other);


	rational_t &operator=(rational_t const& other);
private:
	bool is_consistent()const;
	void normalize(int& z, int& n);

};
std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
std::ifstream& operator>>(std::ifstream& lhs, rational_t const& rhs);
void print_result(rational_t const& rational);

//non-Member-Operator
rational_t operator+(int const& lhs, rational_t const& rhs);
rational_t operator-(int const& lhs, rational_t const& rhs);
rational_t operator*(int const& lhs, rational_t const& rhs);
rational_t operator/(int const& lhs, rational_t const& rhs);
#endif // !rational_t_h
