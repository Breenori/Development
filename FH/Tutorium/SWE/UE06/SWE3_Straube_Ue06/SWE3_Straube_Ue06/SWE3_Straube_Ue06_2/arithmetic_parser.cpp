/*
* ----- Includes. -----
*/
#include "arithmetic_parser.h"
#include <fstream>
#include <string>

/*
* ----- Functions. -----
*/

/*
* Parse Expression for istream.
* 
* return double
*/
double ArithmeticParser::parse(std::istream& in) {
	m_scanner.set_istream(in, true); 
	double const value{ parse_Expression() };
	m_scanner.set_istream();

	return value;
}

/*
* Create istringstream and delegate to parse.
*
* return double
*/
double ArithmeticParser::parse(std::string const& filename) {
	std::istringstream in{ filename };
	
	return parse(in);
}

/*
* If is Expression.
* Expression == ( Term | Number ).
*
* return bool
*/
bool ArithmeticParser::is_tb_Expression() const {
	return is_tb_Term() || is_tb_Unsigned();
}

/*
* If is Term.
* Term = Operator
*
* return bool
*/
bool ArithmeticParser::is_tb_Term() const {
	return is_tb_Operator();
}

/*
* If is Operator.
* Operator = ( "+" | "-" | ":" | "*" )
*
* return bool
*/
bool ArithmeticParser::is_tb_Operator() const {
	return m_scanner.is('+') || m_scanner.is('-') || m_scanner.is('*') || m_scanner.is('/');
}

/*
* If is Unsigned.
* Unsigned == full number.
*
* return bool
*/
bool ArithmeticParser::is_tb_Unsigned() const {
	return m_scanner.is_number();
}

/*
* Parse Expression.
* Expression = ( Term | Number )
*
* return double
*/
double ArithmeticParser::parse_Expression(){
	// If korrect symbol from scanner.
	if (!is_tb_Expression()) { 
		throw ParserException("Error parsing 'Expression'.");
	}

	double value{ 0.0 };

	// ( Term | Number )
	if (is_tb_Term()) {
		value = parse_Term();
	}
	else {
		value = m_scanner.get_number();
		m_scanner.next_symbol();
	}

	return value;
}

/*
* Parse Term.
* Term = Operator Expression Expression
*
* return double
*/
double ArithmeticParser::parse_Term(){
	// If korrect symbol from scanner.
	if (!is_tb_Term()) {
		throw ParserException("Error parsing 'Term'.");
	}

	return parse_Operator();
}

/*
* Parse Operator.
* Operator = ( "+" | "-" | ":" | "*" )
*
* return double
*/
double ArithmeticParser::parse_Operator() {
	// If korrect symbol from scanner.
	if (!is_tb_Operator()) {
		throw ParserException("Error parsing 'Term'.");
	}

	double value{ 0.0 };

	// Operator Expression Expression
	if (m_scanner.is('*')) {
		m_scanner.next_symbol('*');
		value = parse_Expression() * parse_Expression();
	}
	else if (m_scanner.is('/')) {
		m_scanner.next_symbol('/');
		value = parse_Expression();
		double rightval{ parse_Expression() };

		if (rightval == 0) {
			throw ParserException("Error division by zero.");
		}

		value /= rightval;
	}
	else if (m_scanner.is('+')) {
		m_scanner.next_symbol('+');
		value = parse_Expression() + parse_Expression();
	}
	else if (m_scanner.is('-')) {
		m_scanner.next_symbol('-');
		value = parse_Expression() - parse_Expression();
	}

	return value;
}