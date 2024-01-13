#include "rational_t.h"

int rational_t::greatest_common_denominator() const
{
	int result = 1;
	int lower_value = abs(abs(numerator) < abs(denominator) ? numerator : denominator);
	for (size_t i = 2; i <= lower_value; i++) // test each number until max possible number is reached
	{
		if (abs(numerator) % i == 0 && abs(denominator) % i == 0) result = i;
	}

	return result;
}

void rational_t::add(rational_t const& other)
{
	rational_t other_t{ other };

	// get to same denominator
	other_t.numerator *= denominator;
	other_t.denominator *= denominator;

	numerator *= other.denominator;
	denominator *= other.denominator;


	// add
	numerator += other_t.numerator;

	this->normalize();
}

void rational_t::sub(rational_t const& other)
{
	rational_t other_t{ other };

	// get to same denominator
	other_t.numerator *= denominator;
	other_t.denominator *= denominator;

	numerator *= other.denominator;
	denominator *= other.denominator;


	// sub
	numerator -= other_t.numerator;

	this->normalize();
}

void rational_t::mul(rational_t const& other)
{
	numerator *= other.numerator;
	denominator *= other.denominator;

	this->normalize();
}

void rational_t::div(rational_t const& other)
{
	numerator *= other.denominator;
	denominator *= other.numerator;

	if (denominator == 0) {
		throw DivideByZeroError();
	}

	this->normalize();
}

void rational_t::normalize()
{
	if (is_positive()) {
		numerator = abs(numerator);
		denominator = abs(denominator);
	}

	int gcd = greatest_common_denominator();
	numerator /= gcd;
	denominator /= gcd;


}

void rational_t::print(std::ostream& out) const
{
	out << "<" << as_string() << ">";
}

void rational_t::scan(std::istream& in)
{
	std::string input;
	std::string parsed;
	in >> input;

	size_t pos = input.find_first_of("/");

	if (pos) {
		numerator = stoi(input.substr(0, pos)); // split string by /
		denominator = stoi(input.substr(pos + 1));
	}

	if (denominator == 0) {
		throw DivideByZeroError();
	}

	normalize();
}

std::string rational_t::as_string() const
{
	if (denominator == 1)
		return std::to_string(numerator);
	else if (denominator == -1)
		return "-" + std::to_string(numerator);
	else
		return std::to_string(numerator) + "/" + std::to_string(denominator);
}

int rational_t::get_numerator() const
{
	return numerator;
}

int rational_t::get_denominator() const
{
	return denominator;
}

bool rational_t::is_negative() const
{
	return !is_positive();
}

bool rational_t::is_positive() const
{
	return ((numerator >= 0 && denominator >= 0) || (numerator < 0 && denominator < 0));
}

bool rational_t::is_zero() const
{
	return numerator == 0;
}

rational_t::rational_t() : numerator{ 0 }, denominator{ 1 }
{}

rational_t::rational_t(int _numerator) : numerator{ _numerator }, denominator{ 1 }
{}

rational_t::rational_t(int _numerator, int _denominator) : numerator{ _numerator }, denominator{ _denominator }
{
	if (denominator == 0) {
		throw DivideByZeroError();
	}
	normalize();
}

rational_t::rational_t(rational_t const& other) : numerator{ other.numerator }, denominator{ other.denominator }
{}

rational_t& rational_t::operator=(rational_t const& other)
{
	if (&other == this) {
		return *this;
	}

	numerator = other.numerator;
	denominator = other.denominator;

	return *this;
}

bool rational_t::operator==(rational_t const& other) const
{
	double lhs = (numerator / denominator * 1.0);
	double rhs = (other.numerator / denominator * 1.0);

	return lhs == rhs;
}

bool rational_t::operator!=(rational_t const& other) const
{
	return !(*this == other);
}

bool rational_t::operator<(rational_t const& other) const
{
	double lhs = (numerator / denominator * 1.0);
	double rhs = (other.numerator / denominator * 1.0);

	return lhs < rhs;
}

bool rational_t::operator<=(rational_t const& other) const
{
	return (*this == other || *this < other);
}

bool rational_t::operator>(rational_t const& other) const
{
	return !(*this <= other);
}

bool rational_t::operator>=(rational_t const& other) const
{
	return (*this == other || *this > other);
}

rational_t& rational_t::operator+=(rational_t const& other)
{
	add(other);
	return *this;
}

rational_t& rational_t::operator-=(rational_t const& other)
{
	sub(other);
	return *this;
}

rational_t& rational_t::operator*=(rational_t const& other)
{
	mul(other);
	return *this;
}

rational_t& rational_t::operator/=(rational_t const& other)
{
	div(other);
	return *this;
}

rational_t rational_t::operator+(rational_t const& other)
{
	rational_t tmp{ *this };
	tmp.add(other);
	return tmp;
}

rational_t rational_t::operator-(rational_t const& other)
{
	rational_t tmp{ *this };
	tmp.sub(other);
	return tmp;
}

rational_t rational_t::operator*(rational_t const& other)
{
	rational_t tmp{ *this };
	tmp.mul(other);
	return tmp;
}

rational_t rational_t::operator/(rational_t const& other)
{
	rational_t tmp{ *this };
	tmp.div(other);
	return tmp;
}


rational_t operator+(int const& lhs, rational_t const& rhs)
{
	rational_t tmp{ lhs };
	tmp.add(rhs);
	return tmp;
}

rational_t operator-(int const& lhs, rational_t const& rhs)
{
	rational_t tmp{ lhs };
	tmp.sub(rhs);
	return tmp;
}

rational_t operator*(int const& lhs, rational_t const& rhs)
{
	rational_t tmp{ lhs };
	tmp.mul(rhs);
	return tmp;
}

rational_t operator/(int const& lhs, rational_t const& rhs)
{
	rational_t tmp{ lhs };
	tmp.div(rhs);
	return tmp;
}

std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs)
{
	rhs.print(lhs);
	return lhs;
}

std::istream& operator>>(std::istream& lhs, rational_t& rhs)
{
	rhs.scan(lhs);
	return lhs;
}
