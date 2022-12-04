#include "rational_t.h"
#include <sstream>

rational_t::rational_t() {
	numerator = 1;
	denominator = 1;
}

rational_t::rational_t(int _numerator, int _denominator) : numerator{ _numerator }, denominator{ _denominator }{
	//initalizing numerator and denominator
}

rational_t::rational_t(int _numerator) { 
	numerator = _numerator;
	denominator = 1;
}

rational_t::rational_t(rational_t const & other) {
	numerator = other.numerator;
	denominator = other.denominator;
}


void rational_t::test_normalize() {
	normalize();
}


void rational_t::normalize() {
	if (is_consistent()) {
		int gcd{ this->get_gcd() }; // greatest common divider
		this->numerator = this->numerator / gcd; //divide by gcd
		this->denominator = this->denominator / gcd;
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
	}
}

int rational_t::get_gcd()const { //euklidsch' algorithm
	if (!is_zero()) {
		int m{ this->numerator };
		int n{ this->denominator };
		int r{ m % n };
		if (r < 0) { // turn r into positive number
			r = r * (-1);
		}
		while (r > 0) {
			m = n;
			n = r;
			r = m % n;
		}
	int g = n;
	return g;
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return 0;
	}
}

bool rational_t::is_consistent() { // check if denominator not 0
	bool consistent{ true };
	if (this->denominator==0) {
		consistent = false;
	}
	return consistent;
}

void rational_t::print(std::ostream& out)const {
	if (!is_zero()) {
		if (this->denominator == 1) { // division by 1 means whole number without break
			if (this->denominator < 0 && this->numerator < 0) {
				out << "<" << this->numerator+(this->numerator*2) << ">"; // turn numerator into positive number
			}
			else {
				out << "<" << this->numerator << ">"; // print only numerator
			}
		}
		else {
			out << "<" << this->numerator << "/" << this->denominator << ">"; //print both
		}
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
	}
	
}

void rational_t::scan(std::istream& in) {
	std::string rational;
	std::string first_no;
	std::string second_no;
	in >> rational; // read string
		
	if (rational[0] == '<' && rational[rational.size() - 1] == '>') {
		size_t pos = rational.find('/'); // find pos of divider
		size_t start1 = 0; //enhance idx if minus
		size_t start2 = 0;
		if (rational[1] == '-') {
			++start1; //if minus in first number
		}
		if (rational[pos+1] == '-') {
			++start2; // if minus in second number
		}
		if (pos == -1) {
			for (size_t i = 1+start1; i < rational.size() - 1;++i) {
				if (rational[i] >= '0' && rational[i] <= '9') {
					first_no += rational[i];
				}
			}
			std::stringstream s1; //convert into integer
			s1 << first_no;
			s1 >> this->numerator;
			this->denominator = 1;
			if (start1 == 1) {
				this->numerator =this->numerator - (2*this->numerator);
			}
		}
		else {
			for (size_t i = 1+ start1; i < pos; ++i) {
				if (rational[i] >= '0' && rational[i] <= '9') {
					first_no += rational[i]; //build first number
				}
			}
			for (size_t i = pos + 1+ start2; i < rational.size() - 1;++i) {
				if (rational[i] >= '0' && rational[i] <= '9') {
					second_no += rational[i]; // build second number
				}
			}
			//convert into integer:
			std::stringstream s1;
			std::stringstream s2;
			s1 << first_no;
			s1 >> this->numerator;
			s2 << second_no;
			s2 >> this->denominator;
			if (start1 == 1) {// if minus found --> change into negative numbers
				this->numerator=this->numerator - (2*this->numerator); 
			}
			if (start2 == 1) {
				this->denominator=this->denominator - (2*this->denominator);
			}
		}
	}
	else {
		std::cout << "Error! Invalid Data!";
	}
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
	}
}

std::string rational_t::as_string() const {
	std::string _numerator = std::to_string(this->numerator);
	std::string _denominator = std::to_string(this->denominator);
	std::string number = "<" + _numerator + "/" + _denominator + ">";
	return number;
}

int rational_t::get_numerator() const {
	return this->numerator;
}

int rational_t::get_denominator() const {
	return this->denominator;
}

bool rational_t::is_zero() const {
	return this->denominator == 0;
}

bool rational_t::is_negative() const {
	bool negative{ false };
	if (this->denominator < 0 || this->numerator < 0) {
		negative = true;
	}
	return negative;
}

bool rational_t::is_positive() const {
	return this->denominator > 0 && this->numerator > 0;
}

//overloading operator = ----------------------------------------------------------------------------------------------------------------------------------------
rational_t& rational_t::operator=(rational_t other) {
	std::swap(numerator, other.numerator);
	std::swap(denominator, other.denominator);
	return *this; 
}
//overloading compare operators
bool rational_t::operator<(rational_t const& other) {
	rational_t& temp(*this);
	if (is_consistent()) {
		double result_temp = temp.numerator * 1.0 / temp.denominator*1.0;
		double result_other = other.numerator * 1.0 / other.denominator * 1.0;
		if (result_temp < result_other) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return false;
	}
}

bool rational_t::operator>(rational_t const& other) {
	rational_t& temp(*this);
	if (is_consistent()) {
		double result_temp = temp.numerator * 1.0 / temp.denominator * 1.0;
		double result_other = other.numerator * 1.0 / other.denominator * 1.0;
		if (result_temp > result_other) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return false;
	}
}

bool rational_t::operator<=(rational_t const& other) {
	rational_t& temp(*this);
	if (is_consistent()) {
		double result_temp = temp.numerator * 1.0 / temp.denominator * 1.0;
		double result_other = other.numerator * 1.0 / other.denominator * 1.0;
		if (result_temp <= result_other) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return false;
	}
}

bool rational_t::operator>=(rational_t const& other) {
	rational_t& temp(*this);
	if (is_consistent()) {
		double result_temp = temp.numerator * 1.0 / temp.denominator * 1.0;
		double result_other = other.numerator * 1.0 / other.denominator * 1.0;
		if (result_temp >= result_other) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return false;
	}
}

bool rational_t::operator==(rational_t const& other) {
	rational_t& temp(*this);
	if(is_consistent()) {
		return (temp.numerator == other.numerator) && (temp.denominator == other.denominator);
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return false;
	}
}

bool rational_t::operator!=(rational_t const& other) {
	rational_t& temp(*this);
	if (is_consistent()) {
		return (temp.numerator != other.numerator) || (temp.denominator != other.denominator);
	}
	else {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return false;
	}
}

// basic arithmetics ------------------------------------------------------------------------------------------------------------------------------------------
void rational_t::mul(rational_t const& other) {
	numerator = numerator * other.numerator;
	denominator = denominator * other.denominator;
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
	}
	else {
		normalize();
	}
}

void rational_t::div(rational_t const& other) {
	numerator = numerator * other.denominator;
	denominator = denominator * other.numerator;
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
	}
	else {
		normalize();
	}
}

void rational_t::add(rational_t const& other) {
	numerator = numerator*other.denominator;
	int temp = denominator;
	denominator = denominator * other.denominator;
	numerator = numerator + (other.numerator*temp);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
	}
	else {
		normalize();
	}
}

void rational_t::sub(rational_t const& other) {
	numerator = numerator * other.denominator;
	int temp = denominator;
	denominator = denominator * other.denominator;
	numerator = numerator - (other.numerator * temp);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
	}
	else {
		normalize();
	}
}

// basic arithmetics - overload ------------------------------------------------------------------------------------------------------------------------------------------------
rational_t rational_t::operator+(rational_t const& other) {
	rational_t temp(*this);
	temp.add(other);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return temp;
	}
	else {
		normalize();
		return temp;
	}
	
}

rational_t rational_t::operator-(rational_t const& other) {
	rational_t temp(*this);
	temp.sub(other);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return temp;
	}
	else {
		normalize();
		return temp;
	}
}

rational_t rational_t::operator/(rational_t const& other) {
	rational_t temp(*this);
	temp.div(other);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return temp;
	}
	else {
		normalize();
		return temp;
	}
}

rational_t rational_t::operator*(rational_t const& other) {
	rational_t temp(*this);
	temp.mul(other);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return temp;
	}
	else {
		normalize();
		return temp;
	}
}

// overload compound assignment operators---------------------------------------------------------------------------------------------------------------------------------------------
rational_t& rational_t::operator+=(rational_t const& other) {
	add(other);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return  *this;;
	}
	else {
		normalize();
		return  *this;;
	}
}


rational_t& rational_t::operator-=(rational_t const& other) {
	sub(other);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return  *this;;
	}
	else {
		normalize();
		return  *this;;
	}
}

rational_t& rational_t::operator/=(rational_t const& other) {
	div(other);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return  *this;;
	}
	else {
		normalize();
		return  *this;;
	}
}

rational_t& rational_t::operator*=(rational_t const& other) {
	mul(other);
	if (!is_consistent()) {
		throw DivideByZeroError();
		std::cout << "Error! Division by Zero!";
		return  *this;;
	}
	else {
		normalize();
		return  *this;;
	}
}

// Overloading << and >> ------------------------------------------------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, rational_t const& number) {
	number.print(out);
	return out;
}

std::istream& operator>>(std::istream& in, rational_t & number) {
	number.scan(in);
	return in;
}





