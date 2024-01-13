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
* Set given variables in map variables.
*
* return void
*/
void ArithmeticParser::set_variable(std::string const& var, double const& val) {
	// Invalid symbols.
	for (size_t i{ 0 }; i < var.size(); ++i) {
		if (var[i] == '\t' || var[i] == '\n' || var[i] == ' ') {
			throw ParserException("Error setting variable '" + var + "'. No spaces allowed.");
		}
	}

	// Empty.
	if (var == "") {
		throw ParserException("Error setting empty variable.");
	}

	variable_map.insert_or_assign(var, val);
}

/*
* If is Expression.
* Expression == Term.
*
* return bool
*/
bool ArithmeticParser::is_tb_Expression() const {
	return is_tb_Term();
}

/*
* If is Term.
* Term == Factor.
*
* return bool
*/
bool ArithmeticParser::is_tb_Term() const {
	return is_tb_Factor();
}

/*
* If is Factor.
* Factor == AddOp, Unsigned, Variable, PExpression.
*
* return bool
*/
bool ArithmeticParser::is_tb_Factor() const {
	return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression() || is_tb_Variable();
}

/*
* If is AddOp.
*
* return bool
*/
bool ArithmeticParser::is_tb_AddOp() const {
	return m_scanner.is('+') || m_scanner.is('-');
}

/*
* If is MultOp.
*
* return double
*/
bool ArithmeticParser::is_tb_MultOp() const {
	return m_scanner.is('*') || m_scanner.is('/');
}

/*
* If is PExpression.
* PExpression == brackets.
*
* return bool
*/
bool ArithmeticParser::is_tb_PExpression() const{
	return m_scanner.is('(');
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
* If is Variable.
* Unsigned == string.
*
* return bool
*/
bool ArithmeticParser::is_tb_Variable() const {
	return m_scanner.is_identifier();
}

/*
* Parse Expression.
* Expression = Term {AddOp Term}
*
* return double
*/
double ArithmeticParser::parse_Expression(){
	// If korrect symbol from scanner.
	if (!is_tb_Expression()) { 
		throw ParserException("Error parsing 'Expression'.");
	}

	// Term
	double value{ parse_Term() };

	// {AddOp Term}
	while (is_tb_AddOp()) {
		double const sign{ parse_AddOp() };
		value += sign * parse_Term(); 
	}

	return value;
}

/*
* Parse Term.
* Term = Factor {MultOp Factor}
*
* return double
*/
double ArithmeticParser::parse_Term(){
	// If korrect symbol from scanner.
	if (!is_tb_Term()) {
		throw ParserException("Error parsing 'Term'.");
	}

	// Factor
	double value{ parse_Factor() };

	// {MultOp Factor}
	while (is_tb_MultOp()) {
		if (m_scanner.is('*')) {
			m_scanner.next_symbol('*');
			value *= parse_Factor();
		}
		else if (m_scanner.is('/')) {
			m_scanner.next_symbol('/');
			double factor{ parse_Factor() };

			if (factor == 0) {
				throw ParserException("Error division by zero.");
			}

			value /= factor;
		}
		else {
			throw ParserException("Error parsing 'Term'.");
		}
	}

	return value;
}

/*
* Parse Factor.
* Factor = [ AddOp ] ( Number | PExpression )
*
* return double
*/
double ArithmeticParser::parse_Factor(){
	// If korrect symbol from scanner.
	if (!is_tb_Factor()) {
		throw ParserException{ "Error parsing 'Factor'." };
	}

	// [ AddOp ] -> 0-1x
	double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };
	double value{ 0.0 };

	// ( Number | Variable | PExpression )
	if (is_tb_Unsigned()) {
		value = m_scanner.get_number(); 
		m_scanner.next_symbol();
	}
	else if (is_tb_Variable()) {
		value = parse_Variable();
		m_scanner.next_symbol();
	}
	else if (is_tb_PExpression()) {
		value = parse_PExpression();
	}
	else {
		throw ParserException{ "Error parsing 'Factor'." };
	}

	return sign * value;
}

/*
* Parse AddOp.
* AddOp = "+" | "-"
*
* return double
*/
double ArithmeticParser::parse_AddOp(){
	// If korrect symbol from scanner.
	if (!is_tb_AddOp()) {
		throw ParserException{ "Error parsing 'AddOp'." };
	}

	double sign{ 0.0 };

	if (m_scanner.is('+')) { 
		sign = 1; m_scanner.next_symbol(); 
	}
	else if (m_scanner.is('-')) { 
		sign = -1; m_scanner.next_symbol(); 
	}
	else {
		throw ParserException{ "Error parsing 'AddOp'." };
	}

	return sign;
}

/*
* Parse PExpression.
* PExpression = "(" Expression ")"
*
* return double
*/
double ArithmeticParser::parse_PExpression(){
	// If korrect symbol from scanner.
	if (!is_tb_PExpression()) {
		throw ParserException{ "Error parsing 'PExpression'." };
	}

	m_scanner.next_symbol('('); 
	double const value{ parse_Expression() }; // Expression
	m_scanner.next_symbol(')');

	return value;
}

/*
* Parse Variable.
* Variable = string
*
* return double
*/
double ArithmeticParser::parse_Variable() {
	std::string scanned_identifier{ m_scanner.get_identifier() };

	if (!variable_map.contains(scanned_identifier)) {
		throw ParserException{ "Error parsing 'Variable': " + scanned_identifier + ". Please add identifier to variables."};
	}

	return variable_map.find(scanned_identifier)->second;
}