#include "rational.h"

rational_t::rational_t() {
	this->numerator = 0;
	this->denominator = 1;
}
rational_t::rational_t(int const numerator) {
	this->numerator = numerator;
	this->denominator = 1;
}
rational_t::rational_t(int const numerator, int const denominator) {
	this->numerator = numerator;
	this->denominator = denominator;
	if (!is_consistent()) {
		throw DivideByZeroError();
	}
}
rational_t::rational_t(rational_t const& other) {
	numerator = other.numerator;
	denominator = other.denominator;
}

int rational_t::get_numerator() const {
	return numerator;
}

int rational_t::get_denominator() const {
	return denominator;
}

bool rational_t::is_negative() const {
	return numerator < 0 != denominator < 0;
}

bool rational_t::is_positive() const {
	return numerator < 0 == denominator < 0;
}

bool rational_t::is_zero() const {
	return numerator == 0;
}

void rational_t::print(std::ostream& os) const {
	os << this->as_string();
}

bool rational_t::scan(std::istream& is) {
	int n;
	int d;
	char div;
	is >> n;
	if(!is.fail()){
		is >> div;
		if (div == '/') {
			is >> d;
			if (!is.fail()) {
				numerator = n;
				denominator = d;
				if (!is_consistent()) {
					throw DivideByZeroError();
				}
				return true;
			}
		}
	}
	is.clear();
	is.ignore(1000, '\n');
	throw InvalidInputError();
	return false;
}

std::string rational_t::as_string() const {
	return std::to_string(numerator) + "/" + std::to_string(denominator);
}

bool rational_t::is_consistent() const {
	return denominator != 0;
}

void rational_t::normalize() {
	int _gcd = gcd(to_positive(numerator), to_positive(denominator));
	if (_gcd > 1) {
		numerator /= _gcd;
		denominator /= _gcd;
	}
	if (numerator < 0 && denominator < 0) {
		numerator = -numerator;
		denominator = -denominator;
	}
}

int gcd(int const& a, int const& b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

int to_positive(int const& a) {
	if (a < 0) {
		return -a;
	}
	return a;
}

//assignment operator
rational_t& rational_t::operator=(rational_t const& other) {
	if (*this != other) {
		numerator = other.numerator;
		denominator = other.denominator;
	}
	return *this;
}

//comparison operators
bool rational_t::operator==(rational_t const& other) const {
	return numerator == other.numerator && denominator == other.denominator;
}
bool rational_t::operator!=(rational_t const& other) const {
	return !(*this == other);
}
bool rational_t::operator<(rational_t const& other) const {
	return numerator / denominator < other.numerator / other.denominator;
}
bool rational_t::operator>(rational_t const& other) const {
	return !(*this < other);
}
bool rational_t::operator<=(rational_t const& other) const {
	return *this < other || *this == other;
}
bool rational_t::operator>=(rational_t const& other) const {
	return *this > other || *this == other;
}

//compound assignment operators
rational_t& rational_t::operator+=(rational_t const& other) {
	numerator = numerator * other.denominator + other.numerator * denominator;
	denominator *= other.denominator;
	normalize();
	return *this;
}
rational_t& rational_t::operator-=(rational_t const& other) {
	rational_t temp(other);
	temp.numerator = -temp.numerator;
	*this += temp;
	normalize();
	return *this;
}
rational_t& rational_t::operator*=(rational_t const& other) {
	if (this->is_zero() || other.is_zero()) {
		numerator = 0;
		denominator = 1;
		return *this;
	}
	numerator *= other.numerator;
	denominator *= other.denominator;
	normalize();
	return *this;
}
rational_t& rational_t::operator/=(rational_t const& other) {
	if (other.is_zero()) {
		throw DivideByZeroError();
	}
	else {
		numerator = numerator * other.denominator;
		denominator = denominator * other.numerator;
		if (!is_consistent()) {
			throw DivideByZeroError();
		}
		normalize();
	}
	return *this;
}

//+, -, *, /
rational_t rational_t::operator+(rational_t const& other) const {
	rational_t tmp(*this);
	tmp += other;
	return tmp;
}
rational_t rational_t::operator-(rational_t const& other) const {
	rational_t tmp(*this);
	tmp -= other;
	return tmp;
}
rational_t rational_t::operator*(rational_t const& other) const {
	rational_t tmp(*this);
	tmp *= other;
	return tmp;
}
rational_t rational_t::operator/(rational_t const& other) const {
	rational_t tmp(*this);
	tmp /= other;
	return tmp;
}

//+, -, *, / with int
rational_t operator+(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	tmp += rhs;
	return tmp;
}
rational_t operator-(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	tmp -= rhs;
	return tmp;
}
rational_t operator*(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	tmp *= rhs;
	return tmp;
}
rational_t operator/(int const& lhs, rational_t const& rhs) {
	rational_t tmp(lhs);
	tmp /= rhs;
	return tmp;
}

//<< >>
std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs) {
	rhs.print(lhs);
	return lhs;
}
std::istream& operator>>(std::istream& lhs, rational_t& rhs) {
	rhs.scan(lhs);
	return lhs;
}