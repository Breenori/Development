#ifndef RATIONAL_T
#define RATIONAL_T

/*
* ----- Includes. -----
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>
#include <sstream>
#include "operations.h"
#include "div_by_zero_error.h"

/*
* ----- Usings. -----
*/
using std::ostream;
using std::istream;
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;

/*
* ----- Globals. -----
*/
char const PRINT_START_CHAR = '<';
char const PRINT_END_CHAR = '>';
char const RATIONAL_CHAR = '/';
char const NEGATIVE_CHAR = '-';
std::string const RATIONAL_REGEX{ "(-?[^\\/\\s]+\\/-?[^\\/\\s]+)" }; // 22/5 || -1/-3

/*
* ----- Concept. -----
*/
// Nr: 3.
template<typename S> 
concept NumericType = requires(S t) {
	t + t;
	t - t;
	t * t;
	t / t;
	t += t;
	t -= t;
	t *= t;
	t /= t;
	t == t;
	t != t;
	t < t;
	t <= t;
	t > t;
	t >= t;
	cout << t;
	cin >> t;
	t % t; // No support for double here.
	t = t;
};

/*
* ----- Template-Class. -----
*/
// Nr: 1.
template<NumericType T = int>
class Rational_t {
	T numerator = nelms::zero<T>(); 
	T denominator = nelms::one<T>(); 
	bool positive = true;

public:
	/*
	* Default Constructor
	*/
	Rational_t() {
		numerator = nelms::zero<T>(); 
		denominator = nelms::one<T>(); 
		positive = true;
	}

	/*
	* Overload Constructor one Arg
	*/
	Rational_t(T const& _numerator) : numerator{ _numerator }, denominator{ nelms::one<T>() } { 
		normalize();
	}

	/*
	* Overload Constructor two Arg
	*/
	Rational_t(T const& _numerator, T const& _denominator) : numerator{ _numerator }, denominator{ _denominator } {
		normalize();
	}

	/*
	* Copy Constructor
	*/
	Rational_t(Rational_t<T> const& other) {
		numerator = other.numerator;
		denominator = other.denominator;
		positive = other.positive;

		normalize();
	}

	/*
	* Print out the actual fracture as a string.
	*
	* return ostream&
	*/
	ostream& print(ostream& out = cout) const {
		out << PRINT_START_CHAR << this->as_string() << PRINT_END_CHAR;

		return out;
	}

	/*
	* Print out the actual fracture.
	*
	* return ostream&
	*/
	ostream& print_general(ostream& out = cout) const {
		out << PRINT_START_CHAR;
		this->as_ostream(out); 
		out << PRINT_END_CHAR;

		return out;
	}

	/*
	* Supported formats: -22/3
	* Not supported: 2*5-2-22/3/3-5
	*
	* return void
	*/
	void scan(istream& in = cin) {
		if (in.good()) {
			string input{ "" };
			vector<string> tmp{ "", "" };
			int count{ 0 };
			std::regex reg(RATIONAL_REGEX); 

			while (count < 2 && cin >> input) {
				if (std::regex_search(input, reg)) {
					for (size_t i{ 0 }; i < input.size(); ++i) {
						if (input[i] == NEGATIVE_CHAR) {
							positive = !positive;
						}
						else if (input[i] == RATIONAL_CHAR) {
							++count;
						}
						else {
							tmp[count] += input[i];
						}
					}

					++count;
				}
			}

			if (tmp[0] == "" || tmp[1] == "") {
				cout << "Error: No valid input found." << endl;
			}

			// Convert String to T.
			std::istringstream strstream_num(tmp[0]);
			T num_conv;
			strstream_num >> num_conv;
			numerator = num_conv;

			std::istringstream strstream_den(tmp[1]);
			T den_conv;
			strstream_den >> den_conv;
			denominator = den_conv;

			try {
				normalize();
			}
			catch (DivideByZeroError& e) {
				cout << e.what() << endl;
			}
		}
	}

	/*
	* Give this fracture as a string.
	*
	* return string
	*/
	string as_string() const {
		string tmp{ "" };

		if (is_negative()) {
			tmp += NEGATIVE_CHAR;
			tmp += "(";
		}

		tmp += (denominator == nelms::one<T>() || is_zero())
			? std::to_string(numerator)
			: std::to_string(numerator) + RATIONAL_CHAR + std::to_string(denominator);

		if (is_negative()) {
			tmp += ")";
		}

		return tmp;
	}

	/*
	* Give this fracture as a ostream.
	*
	* return ostream&
	*/
	ostream& as_ostream(ostream& out = cout) const {
		if (is_negative()) {
			out << NEGATIVE_CHAR << "(";
		}

		if (denominator == nelms::one<T>() || is_zero()) {
			out << numerator;
		}
		else {
			out << numerator; 
			out << RATIONAL_CHAR; 
			out << denominator;
		}

		if (is_negative()) {
			out << ")";
		}

		return out;
	}

	/*
	* Getter numerator.
	*
	* return T
	*/
	T get_numerator() const {
		return numerator;
	}

	/*
	* Getter denominator.
	*
	* return T
	*/
	T get_denominator() const {
		return denominator;
	}

	/*
	* Addition of this LHS with other RHS.
	*
	* return void
	*/
	void add(Rational_t<T> const& other) {
		if (other.is_consistent()) {
			if (other.is_zero())
				return;

			T other_nomi = equalize(other);

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
	void sub(Rational_t<T> const& other) {
		if (other.is_consistent()) {
			if (other.is_zero())
				return;

			T other_nomi = equalize(other);

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
	void mul(Rational_t<T> const& other) {
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
	void div(Rational_t<T> const& other) {
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
	* If fracture is negative.
	*
	* return bool
	*/
	bool is_negative() const {
		return !positive;
	}

	/*
	* If fracture is positive.
	*
	* return bool
	*/
	bool is_positive() const {
		return positive;
	}

	/*
	* If whole fracture is zero.
	*
	* return bool
	*/
	bool is_zero() const {
		return ops::is_zero(numerator);
	}

	// Nr: 8
	/*
	* Replace rational number with reciprocal.
	* Change nominator and denominator, if result is not x/zero.
	*
	* return Rational_t<T>&
	*/
	Rational_t<T>& inverse() {
		if (!ops::equals(numerator, denominator)) {
			if (!ops::is_zero(numerator)) {
				T tmp(numerator);
				numerator = denominator;
				denominator = tmp;
			}
			else {
				throw DivideByZeroError();
			}
		}

		return *this;
	}

	/*
	* Overload assignment operator, copy assignment.
	*
	* return Rational_t<T>&
	*/
	Rational_t<T>& operator=(Rational_t<T> const& other) {
		if (this == &other) {
			return *this;
		}

		numerator = other.numerator;
		denominator = other.denominator;
		positive = other.positive;

		normalize();

		return *this;
	}

private:
	/*
	* Equalize numerator and denominator from this.
	* Return equalized numerator from other for further calculations.
	*
	* return T
	*/
	T equalize(Rational_t<T> const& other) {
		T other_nomi = other.numerator;

		if (!ops::equals(denominator, other.denominator)) {
			other_nomi *= denominator;

			numerator *= other.denominator;
			denominator *= other.denominator;
		}

		return other_nomi;
	}

	/*
	* If fracture is valid. Denominator must not be zero.
	*
	* return bool
	*/
	bool is_consistent() const {
		return !ops::is_zero(denominator);
	}

	/*
	* Get the greatest common divider for *this.
	*
	* return T
	*/
	T get_gcd() const {
		return ops::gcd(numerator, denominator);
	}

	/*
	* Normalize fractures.
	* Also takes care of the sign, if there is a minus in numerator or denominator.
	*
	* return void
	*/
	void normalize() {
		if (is_consistent()) {
			if (!is_zero()) {
				if (ops::is_negative(numerator)) {
					// Could use ops::abs(numerator) here, but this is more efficient in combination with this->positive.
					numerator = ops::negate(numerator);
					positive = !positive;
				}

				if (ops::is_negative(denominator)) {
					// Could use ops::abs(numerator) here, but this is more efficient in combination with this->positive.
					denominator = ops::negate(denominator);
					positive = !positive;
				}

				// Get gcd.
				T gcd{ ops::is_zero(denominator) ? numerator : get_gcd() };
				numerator /= gcd;
				denominator /= gcd;
			}
		}
		else {
			throw DivideByZeroError();
		}
	}

	// Nr: 9
	/*
	* Operation overload +.
	*
	* return Rational_t<T>
	*/
	friend inline Rational_t<T> operator+(Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		Rational_t<T> tmp(lhs);
		tmp.add(rhs);
		return tmp;
	}

	/*
	* Operation overload -.
	*
	* return Rational_t<T>
	*/
	friend inline Rational_t<T> operator-(Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		Rational_t<T> tmp(lhs);
		tmp.sub(rhs);
		return tmp;
	}

	/*
	* Operation overload *.
	*
	* return Rational_t<T>
	*/
	friend inline Rational_t<T> operator*(Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		Rational_t<T> tmp(lhs);
		tmp.mul(rhs);
		return tmp;
	}

	/*
	* Operation overload /.
	*
	* return Rational_t<T>
	*/
	friend inline Rational_t<T> operator/(Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		Rational_t<T> tmp(lhs);
		try {
			tmp.div(rhs);
		}
		catch (DivideByZeroError& e) {
			cout << e.what() << endl;
		}
		return tmp;
	}


	/*
	* Operator overload +=.
	*
	* return Rational_t<T>&
	*/
	friend inline Rational_t<T>& operator+=(Rational_t<T>& lhs, Rational_t<T> const& rhs) {
		lhs.add(rhs);
		return lhs;
	}

	/*
	* Operator overload -=.
	*
	* return Rational_t<T>&
	*/
	friend inline Rational_t<T>& operator-=(Rational_t<T>& lhs, Rational_t<T> const& rhs) {
		lhs.sub(rhs);
		return lhs;
	}

	/*
	* Operator overload *=.
	*
	* return Rational_t<T>&
	*/
	friend inline Rational_t<T>& operator*=(Rational_t<T>& lhs, Rational_t<T> const& rhs) {
		lhs.mul(rhs);
		return lhs;
	}

	/*
	* Operator overload /=.
	*
	* return Rational_t<T>&
	*/
	friend inline Rational_t<T>& operator/=(Rational_t<T>& lhs, Rational_t<T> const& rhs) {
		try {
			lhs.div(rhs);
		}
		catch (DivideByZeroError& e) {
			cout << e.what() << endl;
		}
		return lhs;
	}


	/*
	* Operator overload ==.
	*
	* return bool
	*/
	friend inline bool operator== (Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		return (lhs.get_numerator() == rhs.numerator && lhs.get_denominator() == rhs.denominator && lhs.positive == rhs.positive);
	}

	/*
	* Operator overload !=.
	*
	* return bool
	*/
	friend inline bool operator!= (Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		return !(lhs == rhs);
	}

	/*
	* Operator overload <.
	*
	* return bool
	*/
	friend inline bool operator< (Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		return (
			!lhs.positive && rhs.positive || ( // -3/2 < +3/2
				lhs.positive == rhs.positive && (
					(lhs.get_denominator() / lhs.get_numerator()) < (rhs.denominator / rhs.numerator)
				)
			)
		);
	}

	/*
	* Operator overload <=.
	*
	* return bool
	*/
	friend inline bool operator<= (Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		return (lhs == rhs || lhs < rhs);
	}

	/*
	* Operator overload >.
	*
	* return bool
	*/
	friend inline bool operator> (Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		return (!(lhs < rhs) && !(lhs == rhs));
	}

	/*
	* Operator overload >=.
	*
	* return bool
	*/
	friend inline bool operator>= (Rational_t<T> const& lhs, Rational_t<T> const& rhs) {
		return (lhs == rhs || lhs > rhs);
	}


	/*
	* Operator overload for ostream of RationalType.
	*
	* return ostream&
	*/
	friend inline std::ostream& operator<<(std::ostream& lhs, Rational_t<T> const& rhs) {
		rhs.print_general(lhs);
		return lhs;
	}

	/*
	* Operator overload for istream of RationalType.
	*
	* return istream&
	*/
	friend inline std::istream& operator>>(std::istream& lhs, Rational_t<T>& rhs) {
		rhs.scan(lhs);
		return lhs;
	}
};

#endif