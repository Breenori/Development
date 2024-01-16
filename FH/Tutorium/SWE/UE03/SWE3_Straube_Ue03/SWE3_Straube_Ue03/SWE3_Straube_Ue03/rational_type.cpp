/*
* ----- Includes. -----
*/
#include <vector>
#include <regex>
#include <stdexcept>
#include "rational_type.h"

/*
* ----- Usings. -----
*/
using std::endl;
using std::vector;

/*
* ----- Globals. -----
*/
char const PRINT_START_CHAR = '<';
char const PRINT_END_CHAR = '>';
char const RATIONAL_CHAR = '/';
char const NEGATIVE_CHAR = '-';
std::string const RATIONAL_REGEX{ "(^-?\\d+\\/-?\\d+$)" }; // 22/5 || -1/-3

/*
* ----- Functions. -----
*/
/*
* Constructor 
*/
RationalType::RationalType() {
	numerator = 0;
	denominator = 1;
	positive = true;
}

/*
* Overload Constructor
*/
RationalType::RationalType(data_t _numerator, data_t _denominator) : numerator{ _numerator }, denominator{ _denominator } {
	normalize();
}

/*
* Copy Constructor
*/
RationalType::RationalType(RationalType const& other) {
	numerator = other.numerator;
	denominator = other.denominator; 
	positive = other.positive;

	normalize();
}

/*
* Print out the actual fracture.
* rational.print(); || rational.print(out);
*
* return ostream&
*/
ostream& RationalType::print(ostream& out) const {
	out << PRINT_START_CHAR << this->as_string() << PRINT_END_CHAR;

	return out;
}

/*
* Supported formats: -22/3
* Not supported: 2*5-2-22/3/3-5
* rational.scan(myistream) 
*
* return RationalType
*/
void RationalType::scan(istream& in) {
	if (in.good()) {
		string input{ "" };
		vector<string> tmp{ "", "" };
		int count{ 0 };
		std::regex reg(RATIONAL_REGEX);

		while (count < 2 && cin >> input) {
			if (std::regex_search(input, reg)) {
				for (size_t i{ 0 }; i < input.size(); ++i) {
					if (isdigit(input[i])) {
						tmp[count] += input[i];
					}
					else if (input[i] == NEGATIVE_CHAR) {
						positive = !positive;
					}
					else if (input[i] == RATIONAL_CHAR) {
						++count;
					}
				}

				++count;
			}
		}

		if (tmp[0] == "" || tmp[1] == "") {
			cout << "Error: No valid input found." << endl;
		}

		numerator = std::stoi(tmp[0]);
		denominator = std::stoi(tmp[1]);

		normalize();
	}
}

/*
* Give this fracture as a string.
* string mystring { rational.as_string() };
*
* return string
*/
string RationalType::as_string() const {
	string tmp{ "" };
	
	if (is_negative()) {
		tmp += NEGATIVE_CHAR;
		tmp += "(";
	}

	tmp += (denominator == 1 || is_zero())
		? std::to_string(numerator)
		: std::to_string(numerator) + RATIONAL_CHAR + std::to_string(denominator);

	if (is_negative()) {
		tmp += ")";
	}

	return tmp;
}

/*
* Getter numerator.
*
* return data_t
*/
RationalType::data_t RationalType::get_numerator() const {
	return numerator;
}

/*
* Getter denominator.
*
* return data_t
*/
RationalType::data_t RationalType::get_denominator() const {
	return denominator;
}

/*
* Equalize numerator and denominator from this.
* Return equalized nominator from other for further calculations.
*
* return data_t
*/
RationalType::data_t RationalType::equalize(RationalType const& other) {
	data_t other_nomi = other.numerator;

	if (denominator != other.denominator) {
		other_nomi *= denominator;

		numerator *= other.denominator;
		denominator *= other.denominator;
	}

	return other_nomi;
}

/*
* Addition of this LHS with other RHS.
*
* return void
*/
void RationalType::add(RationalType const& other) {
	if (other.is_consistent()) {
		if (other.is_zero())
			return;

		data_t other_nomi = equalize(other);

		if (positive != other.positive) {
			numerator -= other_nomi; 
		}
		else {
			numerator += other_nomi;
		}
	}

	normalize();
}

/*
* Substraction of this LHS with other RHS.
*
* return void
*/
void RationalType::sub(RationalType const& other) {
	if (other.is_consistent()) {
		if (other.is_zero())
			return;

		data_t other_nomi = equalize(other);

		if (positive != other.positive) {
			numerator += other_nomi;
		}
		else {
			numerator -= other_nomi;
		}
	}

	normalize();
}

/*
* Multiplication of this LHS with other RHS.
*
* return void
*/
void RationalType::mul(RationalType const& other) {
	if (other.is_consistent()) { 
		if (!other.is_positive())
			positive = !positive;

		numerator *= other.numerator;
		denominator *= other.denominator;
	}

	normalize();
}

/*
* Division of this LHS with other RHS.
*
* return void
*/
void RationalType::div(RationalType const& other) {
	if (!other.is_zero()) {
		if (other.is_consistent()) {
			if (!other.is_positive())
				positive = !positive;

			numerator *= other.denominator;
			denominator *= other.numerator;
		}

		normalize();
	}
	else {
		throw DivideByZeroError();
	}
}

/*
* Operator overload +.
*
* return RationalType
*/
RationalType RationalType::operator+ (RationalType const& other) {
	RationalType tmp(*this);
	tmp.add(other);
	return tmp;
}

/*
* Operator overload -.
*
* return RationalType
*/
RationalType RationalType::operator- (RationalType const& other) {
	RationalType tmp(*this);
	tmp.sub(other);
	return tmp;
}

/*
* Operator overload *.
*
* return RationalType
*/
RationalType RationalType::operator* (RationalType const& other) {
	RationalType tmp(*this);
	tmp.mul(other);
	return tmp;
}

/*
* Operator overload /.
*
* return RationalType
*/
RationalType RationalType::operator/ (RationalType const& other) {
	RationalType tmp(*this);
	try {
		tmp.div(other);
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}
	return tmp;
}

/*
* Operator overload +=.
*
* return RationalType&
*/
RationalType& RationalType::operator+= (RationalType const& other) {
	add(other);
	return *this;
}

/*
* Operator overload -=.
*
* return RationalType&
*/
RationalType& RationalType::operator-= (RationalType const& other) {
	sub(other);
	return *this;
}

/*
* Operator overload *=.
*
* return RationalType&
*/
RationalType& RationalType::operator*= (RationalType const& other) {
	mul(other);
	return *this;
}

/*
* Operator overload /=.
*
* return RationalType&
*/
RationalType& RationalType::operator/= (RationalType const& other) {
	try {
		div(other);
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}
	return *this;
}

/*
* Operator overload ==.
*
* return bool
*/
bool RationalType::operator== (RationalType const& other) {
	return (this->get_numerator() == other.numerator && this->get_denominator() == other.denominator && this->positive == other.positive);
}

/*
* Operator overload !=.
*
* return bool
*/
bool RationalType::operator!= (RationalType const& other) {
	return !(*this == other);
}

/*
* Operator overload <.
*
* return bool
*/
bool RationalType::operator< (RationalType const& other) {
	return (
		!this->positive && other.positive || ( // -3/2 < +3/2
			this->positive == other.positive && (															
				(this->get_denominator() / this->get_numerator()) < (other.denominator / other.numerator)
			)
		)
	);
}

/*
* Operator overload <=.
*
* return bool
*/
bool RationalType::operator<= (RationalType const& other) {
	return (*this == other || *this < other);
}

/*
* Operator overload >.
*
* return bool
*/
bool RationalType::operator> (RationalType const& other) {
	return (!(*this < other) && !(*this == other));
}

/*
* Operator overload >=.
*
* return bool
*/
bool RationalType::operator>= (RationalType const& other) {
	return (*this == other || *this > other);
}

/*
* Overload assignment operator, copy assignment.
*
* return RationalType&
*/
RationalType& RationalType::operator=(RationalType const& other) {
	if (this == &other) {
		return *this;
	}
	
	numerator = other.numerator;
	denominator = other.denominator;
	positive = other.positive;

	normalize();
	
	return *this;
}

/*
* If fracture is valid. Denominator must not be 0.
*
* return bool
*/
bool RationalType::is_consistent() const {
	return denominator != 0;
}

/*
* If fracture is negative.
*
* return bool
*/
bool RationalType::is_negative() const {
	return !positive;
}

/*
* If fracture is positive.
*
* return bool
*/
bool RationalType::is_positive() const {
	return positive;
}

/*
* If whole fracture is zero.
*
* return bool
*/
bool RationalType::is_zero() const {
	return numerator == 0;
}

/*
* Get the greatest common divider for *this.
*
* return data_t
*/
RationalType::data_t RationalType::get_gcd() const {
	return get_gcd_rec(numerator, denominator);
}

/*
* Recursive helper for get_gcd().
*
* return data_t
*/
RationalType::data_t RationalType::get_gcd_rec(data_t const& num, data_t const& den) const {
	return den == 0 ? num : get_gcd_rec(den, num % den);
}

/*
* Normalize fractures.
* Also takes care of the sign, if there is a minus in numerator or denominator.
*
* return void
*/
void RationalType::normalize() {
	if (is_consistent()) {
		if (!is_zero()) {
			if (numerator < 0) {
				numerator *= -1;
				positive = !positive;
			}

			if (denominator < 0) {
				denominator *= -1;
				positive = !positive;
			}

			// Get gcd.
			data_t gcd{ denominator == 0 ? numerator : get_gcd() };
			numerator /= gcd;
			denominator /= gcd;
		}
	}
	else{
		throw DivideByZeroError();
	}
}

/*
* Operation overload + for lhs != RationalType.
*
* return RationalType
*/
RationalType operator+ (RationalType const& lhs, RationalType const& rhs) {
	RationalType tmp(lhs);
	tmp.add(rhs);
	return tmp;
}

/*
* Operation overload - for lhs != RationalType.
*
* return RationalType
*/
RationalType operator- (RationalType const& lhs, RationalType const& rhs) {
	RationalType tmp(lhs);
	tmp.sub(rhs);
	return tmp;
}

/*
* Operation overload * for lhs != RationalType.
*
* return RationalType
*/
RationalType operator* (RationalType const& lhs, RationalType const& rhs) {
	RationalType tmp(lhs);
	tmp.mul(rhs);
	return tmp;
}

/*
* Operation overload / for lhs != RationalType.
*
* return RationalType
*/
RationalType operator/ (RationalType const& lhs, RationalType const& rhs) {
	RationalType tmp(lhs);
	try {
		tmp.div(rhs);
	}
	catch (DivideByZeroError& e) {
		cout << e.what() << endl;
	}
	return tmp;
}

/*
* Operator overload for ostream of RationalType.
*
* return ostream&
*/
ostream& operator<< (ostream& lhs, RationalType const& rhs) {
	rhs.print(lhs); 	
	return lhs;
}

/*
* Operator overload for istream of RationalType.
*
* return istream&
*/
istream& operator>> (istream& lhs, RationalType& rhs) {
	rhs.scan(lhs);
	return lhs;
}
