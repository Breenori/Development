#include "rational_t.h"

//getter functions----
rational_t::value_t rational_t::get_numerator()const
{
	return this->numerator;
}

rational_t::value_t rational_t::get_denominator()const
{
	return this->denominator;
}
//-----

//constructor functions-----
rational_t::rational_t()
{
	this->denominator = 1;
	this->numerator = 1;
}

rational_t::rational_t(value_t const num) :rational_t()
{
	this->numerator = num;
}

rational_t::rational_t(value_t const num, value_t const denom) :rational_t()
{
	this->denominator = denom;
	this->numerator = num;
	is_consistent();
}

rational_t::rational_t(rational_t const& src)
{
	if (src.is_consistent()) {
		this->denominator = src.get_denominator();
		this->numerator = src.get_numerator();
	}
}
//-------------

std::istream& rational_t::scan(std::istream& in, rational_t& rt)
{
	value_t n = 0;
	value_t d = 0;
	//create different rationals based on input
	in >> n;
	if (in.good())
	{
		in >> d;
		if (in.good())
		{
			rt = rational_t(n, d);
		}
		rt = rational_t(n);
	}
	else {
		rt = rational_t();
	}

	return in;
}

//use as string for printing
std::ostream& rational_t::print(std::ostream& out)const
{
	out << "< " << this->as_string() << " >";
	return out;
}

//normalize rational 
void rational_t::normalize()
{
	//check for smaller numbers using euclidian algo
	value_t g = gcd(this->numerator, this->denominator);
	if (g != this->denominator) {

		this->denominator /= g;
		this->numerator /= g;

	}
	if (is_negative(this->denominator) && is_negative(this->numerator)) {
		*this *= rational_t( -1,-1);
	}
}


void rational_t::add(rational_t const& other)
{
	this->normalize();
	rational_t r = other;
	r.normalize();

	value_t l = lcm(this->denominator, other.denominator);

	value_t lm = l / this->denominator;
	value_t rm = l / r.get_denominator();

	//*this *= rational_t(lm, lm);
	this->numerator *= lm;
	this->denominator *= lm;
	this->numerator += r.numerator * rm;
	this->normalize();
}

void rational_t::sub(rational_t const& other)
{
	this->normalize();
	rational_t r = other;
	r.normalize();

	value_t l = lcm(this->denominator, other.denominator);

	value_t lm = l / this->denominator;
	value_t rm = l / r.get_denominator();

	*this *= {lm, lm};
	this->numerator -= r.numerator * rm;
	this->normalize();
}

void rational_t::mul(rational_t const& other)
{
	this->denominator *= other.get_denominator();
	this->numerator *= other.get_numerator();
	this->is_consistent();
	this->normalize();
}

void rational_t::div(rational_t const& other)
{

	this->denominator *= other.get_numerator();
	this->numerator *= other.get_denominator();
	this->is_consistent();
	this->normalize();
}

rational_t rational_t::operator+(rational_t const& r1)
{
	rational_t result(*this);
	result.add(r1);
	return result;
}

rational_t rational_t::operator-(rational_t const& r1)
{
	rational_t result(*this);
	result.sub(r1);
	return result;
}

rational_t rational_t::operator*(rational_t const& r1)
{
	rational_t result(*this);
	result.mul(r1);
	return result;
}

rational_t rational_t::operator/(rational_t const& r1)
{
	rational_t result(*this);
	result.div(r1);
	return result;
}

rational_t& rational_t::operator+=(rational_t const& r1)
{
	this->add(r1);
	return *this;
}

rational_t& rational_t::operator-=(rational_t const& r1)
{
	this->sub(r1);
	return *this;
}

rational_t& rational_t::operator*=(rational_t const& r1)
{
	this->mul(r1);
	return *this;
}

rational_t& rational_t::operator/=(rational_t const& r1)
{
	this->div(r1);
	return *this;
}

rational_t& rational_t::operator=(rational_t const& other)
{
	if (this == &other) {
		return *this;
	}
	this->denominator = other.get_denominator();
	this->numerator = other.get_numerator();
	return *this;
}

bool rational_t::operator==(rational_t const& r1)const
{
	return this->numerator / (this->denominator * 1.0) == r1.get_numerator() / (r1.get_denominator() * 1.0);
}

bool rational_t::operator!=(rational_t const& r1)const
{
	return !(*this == r1);
}

bool rational_t::operator<(rational_t const& r1)const
{
	return this->numerator / (this->denominator * 1.0) < r1.get_numerator() / (r1.get_denominator() * 1.0);
}

bool rational_t::operator>(rational_t const& r1)const
{
	return this->numerator / (this->denominator * 1.0) > r1.get_numerator() / (r1.get_denominator() * 1.0);
}

bool rational_t::operator<=(rational_t const& r1)const
{
	return (*this < r1) || (*this == r1);
}

bool rational_t::operator>=(rational_t const& r1)const
{
	return (*this > r1) || (*this == r1);
}



bool rational_t::is_positive(value_t const i)
{
	return i > 0;
}

bool rational_t::is_negative(value_t const i)
{
	return i < 0;
}

bool rational_t::is_zero(value_t const i)
{
	return i == 0;
}

string rational_t::as_string() const
{
	string result = "";
	if (denominator == 1) {
		result = std::to_string(numerator);
	}
	else {
		result = std::to_string(numerator) + '/' + std::to_string(denominator);
	}
	return result;
}

bool rational_t::is_consistent() const
{
	if (is_zero(denominator))
		throw DivideByZeroError();
	return true;
}

//euclidian algorithm
rational_t::value_t rational_t::gcd(value_t a, value_t b)
{
	if (a % b > 0) {
		value_t tmp = a % b;
		a = b;
		b = tmp;
		gcd(a, b);
	}
	return b;
}

rational_t::value_t rational_t::lcm(value_t a, value_t b)
{
	return a * b / gcd(a, b);

}



rational_t operator+(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t result(rhs);
	rational_t l = rational_t(lhs);
	result.add(l);
	return result;
}

rational_t operator-(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t result(lhs);
	rational_t l = rational_t(rhs);
	result.sub(l);
	return result;
}

rational_t operator*(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t result(rhs);
	rational_t l = rational_t(lhs);
	result.mul(l);
	return result;
}

rational_t operator/(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t result(lhs);
	rational_t l = rational_t(rhs);
	result.div(l);
	return result;
}

bool operator==(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t tmp(lhs);
	return lhs == rhs;
}

bool operator<(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t tmp(lhs);
	return lhs < rhs;
}

bool operator>(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t tmp(lhs);
	return lhs > rhs;
}

bool operator!=(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t tmp(lhs);
	return lhs != rhs;
}

bool operator<=(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t tmp(lhs);
	return lhs <= rhs;
}

bool operator>=(rational_t::value_t const& lhs, rational_t const& rhs)
{
	rational_t tmp(lhs);
	return lhs >= rhs;
}



std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs)
{
	rhs.print(lhs);
	return lhs;
}

std::istream& operator>>(std::istream& lhs, rational_t& rhs)
{
	rhs.scan(lhs, rhs);
	return lhs;
}
