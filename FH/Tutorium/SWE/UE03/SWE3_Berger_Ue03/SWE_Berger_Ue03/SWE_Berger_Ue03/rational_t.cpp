#include "rational_t.h"
#include "div_by_zero_error.h"

//constructors
//default constructor
rational_t::rational_t() : numerator(0), denominator(1){
}
//constructor with numerator only
rational_t::rational_t(int _numerator){
	numerator = _numerator;
	denominator = 1;
}
//constructor with numerator and denominator
rational_t::rational_t(int _numerator, int _denominator){
	numerator = _numerator;
	denominator = _denominator;
}
//copy constructor
rational_t::rational_t(rational_t const& other){
	numerator = other.numerator;
	denominator = other.denominator;
}
//destructor
rational_t::~rational_t(){
	
}

//functions of consistency and and normalization, casts because int division might cut the number behind the comma to zero
bool rational_t::is_consistent()const{
	return this->denominator == 0 ? false : true;
}
bool rational_t::is_negative()const{
	return (static_cast<double>(numerator) / static_cast<double>(denominator)) < 0 ? true : false;
}
bool rational_t::is_positive()const{
	return (static_cast<double>(numerator) / static_cast<double>(denominator)) > 0 ? true : false;
}
bool rational_t::is_zero()const {
	return (static_cast<double>(numerator) / static_cast<double>(denominator)) == 0 ? true : false;
}
void rational_t::normalize(){
	if (numerator != 0 && denominator != 0) {
		if (numerator < 0 && denominator < 0) {
			numerator *= (-1);
			denominator *= (-1);
		}
		int gcd = rational_t::gcd(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;
	}
}

//calculation functions
void rational_t::add(rational_t const & other){
	if (this->is_consistent() && other.is_consistent()) {
		this->normalize();

		int other_numerator_copy = 0;

		if (denominator != other.denominator) { //rational objects need to get multiplied, so that they have the same denominator
			int gcd = rational_t::gcd(denominator, other.denominator);
			int lcm = rational_t::lcm(denominator, other.denominator);
			int mult_denom = lcm / denominator;
			int mult_o_denom = lcm / other.denominator;
			numerator *= mult_denom;
			other_numerator_copy = other.numerator;
			other_numerator_copy *= mult_o_denom;
			denominator = lcm;
		}
		numerator += other_numerator_copy;
	}
}
void rational_t::sub(rational_t const & other){
	if (this->is_consistent() && other.is_consistent()) {
		this->normalize();

		int other_numerator_copy = 0;

		if (denominator != other.denominator) {
			int gcd = rational_t::gcd(denominator, other.denominator);
			int lcm = rational_t::lcm(denominator, other.denominator);
			if(lcm < 0){
				lcm *= (-1);
			}
			int mult_denom = lcm / denominator;
			int mult_o_denom = lcm / other.denominator;
			numerator *= mult_denom;
			other_numerator_copy = other.numerator * mult_o_denom;
			denominator = lcm;
		}
		numerator -= other_numerator_copy;
	}

}
void rational_t::mul(rational_t const& other) {
	if (this->is_consistent() && other.is_consistent()) {
		numerator *= other.numerator;
		denominator *= other.denominator;
		this->normalize();
	}
}
void rational_t::div(rational_t const & other) {
	if (this->is_consistent() && other.is_consistent()) {
		numerator *= other.denominator;
		denominator *= other.numerator;
		this->normalize();
	}
	else{
		throw divide_by_zero_error();
	}
}

//helper functions
int rational_t::gcd(int const first, int const second){
	int smaller_number = 0;
	int bigger_number = 0;
	if(first <= second){
		smaller_number = first;
		bigger_number = second;
	}
	else{
		smaller_number = second;
		bigger_number = first;
	}

	if(smaller_number == 0){
		try {
			force_error(smaller_number);
		}
		catch (std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}
	else {
		int rest = bigger_number % smaller_number;
		if (rest == 0) {
			return smaller_number;
		}

		while (rest != 0) {
			rest = bigger_number % smaller_number;
			bigger_number = smaller_number;
			smaller_number = rest;
		}

		return bigger_number;
	}
	return 0;
}
int rational_t::lcm(int const first, int const second){
	int gcd = rational_t::gcd(first, second);
	return first * second / gcd;

}

std::string rational_t::as_string(){
	if(!is_consistent()){
		try {
			double value = force_error();
		}
		catch (std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}
	else if(numerator%denominator == 0){
		int whole_number = numerator / denominator;
		return "<" + std::to_string(whole_number) + ">";
	}
	else {
		this->normalize();
		return "<" + std::to_string(numerator) + "/" +
			std::to_string(denominator) + ">";
	}
	std::string empty = "";
	return empty;
}

//getter functions
int rational_t::get_numerator()const{
	return this->numerator;
}
int rational_t::get_denominator()const{
	return this->numerator;
}

//print and scan functions
void rational_t::print(std::ostream& os)const{
	rational_t tmp(*this);
	std::string const output = tmp.as_string();
	os << output;
}

void rational_t::scan(std::istream& ifs){
	int _numerator = 0;
	int _denominator = 1;
	
	if(ifs.good()){
		ifs >> _numerator;
		ifs >> _denominator;
	}
	
	numerator = _numerator;
	denominator = _denominator;
	if(!is_consistent()){
		try {
			double value = force_error();
		}
		catch (std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}
	else if(numerator == 0 && denominator == 1){
		std::cout << "Wrong input. Standard values are <0/1>\n";
	}
}

double rational_t::force_error()const{
	double value;
	if (denominator == 0){
		throw divide_by_zero_error();
	}
	else{
		value = static_cast<double>(numerator) / denominator;
	}

	return value;
}
void rational_t::force_error(int const denom) {
	if (denom == 0) {
		throw divide_by_zero_error();
	}
}

//Operator overloading
rational_t rational_t::operator+(rational_t const & other)const{
	rational_t tmp(*this);
	tmp.add(other);
	return tmp;
}
rational_t rational_t::operator-(rational_t const & other)const {
	rational_t tmp(*this);
	tmp.sub(other);
	return tmp;
}
rational_t rational_t::operator*(rational_t const& other)const {
	rational_t tmp(*this);
	tmp.mul(other);
	return tmp;
}
rational_t rational_t::operator/(rational_t const& other)const {
	rational_t tmp(*this);
	tmp.div(other);
	return tmp;
}

rational_t& rational_t::operator+=(rational_t & other){
	add(other);
	return *this;
}
rational_t& rational_t::operator-=(rational_t & other){
	sub(other);
	return *this;
}
rational_t& rational_t::operator*=(rational_t const& other){
	mul(other);
	return *this;
}
rational_t& rational_t::operator/=(rational_t const& other){
	div(other);
	return *this;
}

rational_t& rational_t::operator=(rational_t other){
	std::swap(numerator, other.numerator);
	std::swap(denominator, other.denominator);
	return *this;
}

//logical operators
bool rational_t::operator==(const rational_t&other) const{
	rational_t tmp1(*this);
	rational_t tmp2(other);
	tmp1.normalize();
	tmp2.normalize();
	return tmp1.numerator == tmp2.numerator && tmp1.denominator == tmp2.denominator;
}
bool rational_t::operator!=(const rational_t& other) const{
	rational_t tmp1(*this);
	rational_t tmp2(other);
	tmp1.normalize();
	tmp2.normalize();
	return tmp1.numerator != tmp2.numerator || tmp1.denominator != tmp2.denominator;
}
bool rational_t::operator<(const rational_t& other)const{
	rational_t const tmp1(*this);
	rational_t const tmp2(other);
	double const value1 = tmp1.force_error();
	double const value2 = tmp2.force_error();
	return value1 < value2;
}
bool rational_t::operator<=(const rational_t& other)const{
	rational_t const tmp1(*this);
	rational_t const tmp2(other);
	double const value1 = tmp1.force_error();
	double const value2 = tmp2.force_error();
	return value1 <= value2;
}
bool rational_t::operator>(const rational_t& other)const{
	rational_t const tmp1(*this);
	rational_t const tmp2(other);
	double const value1 = tmp1.force_error();
	double const value2 = tmp2.force_error();
	return value1 > value2;
}
bool rational_t::operator>=(const rational_t& other)const{
	rational_t const tmp1(*this);
	rational_t const tmp2(other);
	double const value1 = tmp1.force_error();
	double const value2 = tmp2.force_error();
	return value1 >= value2;
}


//Non-Member-Operators
rational_t operator+(int const& lhs, rational_t & rhs){
	rational_t tmp = (lhs);
	tmp.add(rhs);
	return tmp;
}
rational_t operator-(int const& lhs, rational_t& rhs){
	rational_t tmp = (lhs);
	tmp.sub(rhs);
	return tmp;
}
rational_t operator*(int const& lhs, rational_t const& rhs){
	rational_t tmp = (lhs);
	tmp.mul(rhs);
	return tmp;
}
rational_t operator/(int const& lhs, rational_t const& rhs){
	rational_t tmp = (lhs);
	tmp.div(rhs);
	return tmp;
}

std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs){
	rhs.print(lhs);
	return lhs;
}
std::istream& operator>>(std::istream& lhs, rational_t & rhs){
	rhs.scan(lhs);
	return lhs;
}

void rational_t::print_result(rational_t const& other) {
	std::cout << other << "\n";
}