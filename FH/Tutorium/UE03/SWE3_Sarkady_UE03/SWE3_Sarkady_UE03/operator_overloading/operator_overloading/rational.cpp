#include "rational.h"
#include "div_by_zero.h"
#include <iostream>

int gcd(int n, int d);

rational_t::rational_t()
	: rational_t{ 0 } {
}
rational_t::rational_t(int _numerator) {
	numerator = _numerator;
	denominator = 1;
}
rational_t::rational_t(int _numerator, int _denominator) {
	numerator = _numerator;
	denominator = _denominator;
	if (!is_consistent()) {
		throw DivideByZeroError();
	}
	normalize();
}
rational_t::rational_t(rational_t const& other)
	:
	rational_t{other.numerator, other.denominator}
{
}

int rational_t::get_numerator() const {
	return this->numerator;
}
int rational_t::get_denominator() const {
	return this->denominator;
}

bool rational_t::is_negative() const {
	return numerator < 0 || denominator < 0;
}
bool rational_t::is_positive() const {
	return numerator > 0 && denominator > 0;
}
bool rational_t::is_zero() const {
	return numerator == 0;
}

// Operator Overloading:
// Copy-and-Swap idiom
rational_t& rational_t::operator=(rational_t other) {
	std::swap(numerator, other.numerator);
	std::swap(denominator, other.denominator);
	return *this;
}
// comparison operators:
bool rational_t::operator==(rational_t const& other) const {
	return numerator == other.numerator && denominator == other.denominator;
}
bool rational_t::operator!=(rational_t const& other) const {
	return !(*this == other);
}
bool rational_t::operator<(rational_t const& other) const {
	return numerator * other.denominator < other.numerator* denominator;
}
bool rational_t::operator<=(rational_t const& other) const {
	return (*this == other) || (*this < other);
}
bool rational_t::operator>(rational_t const& other) const {
	return numerator * other.denominator > other.numerator* denominator;
}
bool rational_t::operator>=(rational_t const& other) const {
	return (*this == other) || (*this > other);
}
// compound assignment operators:
rational_t& rational_t::operator+=(rational_t const& other) {
	numerator = (numerator * other.denominator) + (other.numerator * denominator);
	denominator *= other.denominator;
	return normalize();
}
rational_t& rational_t::operator-=(rational_t const& other) {
	numerator = (numerator * other.denominator) - (other.numerator * denominator);
	denominator *= other.denominator;
	return normalize();
}
rational_t& rational_t::operator*=(rational_t const& other) {
	numerator = numerator * other.numerator;
	denominator = denominator * other.denominator;
	return normalize();
}
rational_t& rational_t::operator/=(rational_t const& other) {
	numerator *= other.denominator;
	denominator *= other.numerator;
	if (!is_consistent()) {
		throw DivideByZeroError();
	}
	return normalize();
}
// arithmetic operators:
rational_t rational_t::operator+(rational_t const& other) {
	return rational_t{ *this } += other;
}
rational_t rational_t::operator-(rational_t const& other) {
	return rational_t{ *this } -= other;
}
rational_t rational_t::operator*(rational_t const& other) {
	return rational_t{ *this } *= other;
}
rational_t rational_t::operator/(rational_t const& other){
	return rational_t{ *this } /= other;
}
rational_t rational_t::operator+(int const& other) {
	rational_t temp(other);
	return rational_t{ *this } += temp;
}
rational_t rational_t::operator-(int const& other) {
	rational_t temp(other);
	return rational_t{ *this } -= temp;
}
rational_t rational_t::operator*(int const& other) {
	rational_t temp(other);
	return rational_t{ *this } *= temp;
}
rational_t rational_t::operator/(int const& other) {
	rational_t temp(other);
	return rational_t{ *this } /= temp;
}

std::string rational_t::as_string() const {
	return denominator < 0 ? std::to_string(numerator) + " " + std::to_string(denominator) :
			std::to_string(numerator) + " / " + std::to_string(denominator);

}

void rational_t::print(std::ostream& os) const {
	os << numerator << ":" << denominator << "\n";
}
void rational_t::scan(std::istream& is) const {
	int num;
	int denom;
	std::cout << "Enter two numbers: \n";
	is >> num >> denom;
	numerator = num;
	denominator = denom;
	// why doesn't this work? const function?
	 //if(!is_consistent()) {
	if (denominator == 0) {
		throw DivideByZeroError();
	}
}
std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs) {
	rhs.print(lhs);
	return lhs;
}
std::istream& operator>>(std::istream& lhs, rational_t const& rhs) {
	rhs.scan(lhs);
	return lhs;
}
bool rational_t::is_consistent() {
	return denominator != 0;
}
int gcd(int n, int d) {
	if (d == 0) {
		return n;
	}
	return gcd(d, n % d);
}
rational_t& rational_t::normalize() {
	if (denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	}
	int denom = gcd(numerator, denominator);
	numerator /= denom;
	denominator /= denom;
	return *this;
}
rational_t operator+(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	return rational_t{ lhs } += rhs;
}
rational_t operator-(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	return rational_t{ lhs } -= rhs;
}
rational_t operator*(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	return rational_t{ lhs } *= rhs;
}
rational_t operator/(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	return rational_t{ lhs } /= rhs;
}
