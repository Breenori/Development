#include "rational_t.h"
//constructors
//default
//rational_t::rational_t() = default;
rational_t::rational_t(int _numerator, int _denominator) :numerator{ _numerator }, denominator{ _denominator } {this->normalize(); if (denominator == 0)throw DivideByZeroError(); }
//cpy
rational_t::rational_t(rational_t const& other) {
	this->numerator = other.numerator;
	this->denominator = other.denominator;
}
//get
int rational_t::get_numerator()const { return this->numerator; }
int rational_t::get_denominator()const { return this->denominator; }
//set
void rational_t::set_numerator(int _numerator) { numerator = _numerator; }
void rational_t::set_denominator(int _denominator) {denominator = _denominator; }
//return str
std::string rational_t::as_string() const
{
	return ("<" + std::to_string(numerator) + "/" + std::to_string(denominator) + ">");
}
//helper
bool rational_t::is_negative()const {
	return numerator / denominator < 0 ? true : false;
}
bool rational_t::is_positive()const {
	return numerator / denominator > 0 ? true : false;
}
bool rational_t::is_zero()const {
	return numerator / denominator == 0 ? true : false;
}
bool rational_t::is_consistent()const {
	return this->denominator != 0 ? true : false;
}
int rational_t::gcd(int _numerator, int _denominator) {
	if (_denominator == 0)
		return _numerator;
	return gcd(_denominator, _numerator % _denominator);
}
void rational_t::normalize() {
	//neg denom
	if (denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
	if (denominator == 0)
	{
		denominator = 1;
	}
	//gcd
	int tmp = gcd(numerator, denominator);
	//canonical form
	numerator /= tmp;
	denominator /= tmp;
}
//operators
void rational_t::add(rational_t const& other)
{
	this->numerator += other.numerator;
	this->denominator += other.denominator;
	this->normalize();
}
void rational_t::sub(rational_t const& other)
{
	this->numerator -= other.numerator;
	this->denominator -= other.denominator;
	this->normalize();
}
void rational_t::mul(rational_t const& other)
{
	int t_numerator = this->numerator;
	int t_denominator = this->denominator;
	this->numerator = (t_numerator * other.numerator) - (t_denominator * other.denominator);
	this->denominator = (t_denominator * other.numerator) + (t_numerator * other.denominator);
	this->normalize();
}
void rational_t::div(rational_t const& other)
{
	int t_numerator = this->numerator;
	int t_denominator = this->denominator;
	//denominator
	int denom = (other.numerator * other.numerator) + (other.denominator * other.denominator);
	//ensure denom != 0
	if (denom == 0)
	{
		throw DivideByZeroError();
	}
	this->numerator = (t_numerator * other.numerator + t_denominator * other.denominator) / denom;
	this->denominator = ((t_denominator * other.numerator) - (t_numerator * other.denominator)) / denom;
	this->normalize();
}
//overloading
rational_t rational_t::operator+(rational_t const& c1)
{
	rational_t result(*this);
	result.add(c1);
	return result;
}
rational_t rational_t::operator-(rational_t const& c1)
{
	rational_t result(*this);
	result.sub(c1);
	return result;
}
rational_t rational_t::operator*(rational_t const& c1)
{
	rational_t result(*this);
	result.mul(c1);
	return result;
}
rational_t rational_t::operator/(rational_t const& c1)
{
	rational_t result(*this);
	result.div(c1);
	return result;
}
//compound assignment operators
rational_t& rational_t::operator+=(rational_t const& c1)
{
	add(c1);
	return *this;
}
rational_t& rational_t::operator-=(rational_t const& c1)
{
	sub(c1);
	return *this;
}
rational_t& rational_t::operator*=(rational_t const& c1)
{
	mul(c1);
	return *this;
}
rational_t& rational_t::operator/=(rational_t const& c1)
{
	div(c1);
	return *this;
}
//compare operators
bool rational_t::operator==(rational_t const& c1)const {
	return (this->numerator == c1.numerator && this->denominator == c1.denominator) ? true : false;
}
bool rational_t::operator!=(rational_t const& c1)const {
	return !(*this == c1);
}
bool rational_t::operator<(rational_t const& c1)const {
	return (this->numerator / this->denominator < c1.numerator / c1.denominator);
}
bool rational_t::operator<=(rational_t const& c1)const {
	return *this > c1 ? false : true;
}
bool rational_t::operator>(rational_t const& c1)const {
	return (this->numerator / this->denominator > c1.numerator / c1.denominator);
}
bool rational_t::operator>=(rational_t const& c1)const {
	return *this < c1 ? false : true;
}
//Copy-assignement
//Copy-assignment Idiom
//rational_t& rational_t::operator=(rational_t const& other)
//{
//	if (this == &other) {
//		return *this;
//	}
//	this->numerator = other.numerator;
//	this->denominator = other.denominator;
//	return *this;
//}
//Copy-swap Idiom
rational_t& rational_t::operator=(rational_t other)
{
	std::swap(this->numerator, other.numerator);
	std::swap(this->denominator, other.denominator);
	return *this;
}
//print
void rational_t::print(std::ostream & out) const
{
	if (is_consistent()&&out.good())
	{
		out << "<" << numerator << "/" << denominator << ">\n";
	}
	else
	{
		throw DivideByZeroError();
	}
}
void rational_t::print_result(std::ostream & out, rational_t & c1) {
	c1.normalize();
	out << c1.as_string() << "\n";
}
//scan
void rational_t::scan(std::istream & in)const {
	if(in.good())
	{
		in >> numerator >> denominator;
	}
}
//non-member
//lhs compatibility
rational_t operator+(int const& lhs, rational_t const& rhs) {
	rational_t tmp{ rhs };
	tmp.add(lhs);
	return tmp;
}
rational_t operator-(int const& lhs, rational_t const& rhs) {
	rational_t tmp{ rhs };
	tmp.sub(lhs);
	return tmp;
}
rational_t operator*(int const& lhs, rational_t const& rhs) {
	rational_t tmp{ rhs };
	tmp.mul(lhs);
	return tmp;
}
rational_t operator/(int const& lhs, rational_t const& rhs) {
	rational_t tmp{ rhs };
	tmp.div(lhs);
	return tmp;
}
//rhs compatibility
rational_t operator+(rational_t const& lhs, int const& rhs) {
	rational_t tmp{ lhs };
	tmp.add(rhs);
	return tmp;
}
rational_t operator-(rational_t const& lhs, int const& rhs) {
	rational_t tmp{ lhs };
	tmp.sub(rhs);
	return tmp;
}
rational_t operator*(rational_t const& lhs, int const& rhs) {
	rational_t tmp{ lhs };
	tmp.mul(rhs);
	return tmp;
}
rational_t operator/(rational_t const& lhs, int const& rhs) {
	rational_t tmp{ lhs };
	tmp.div(rhs);
	return tmp;
}
//fstream
std::ostream& operator<<(std::ostream & lhs, rational_t const& rhs) {
	rhs.print(lhs);
	return lhs;
}
std::istream& operator>>(std::istream & lhs, rational_t const& rhs) {
	rhs.scan(lhs);
	return lhs;
}