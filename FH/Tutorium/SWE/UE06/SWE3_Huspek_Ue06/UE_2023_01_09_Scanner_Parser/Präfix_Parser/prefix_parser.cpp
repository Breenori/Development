#include "prefix_parser.h"

double Prefix_Parser::parse(std::istream& in) {
	m_scanner.set_istream(in, true);
	double const value{ parse_Expression() };
	m_scanner.set_istream();
	return value;
}
double Prefix_Parser::parse(std::string const& str) {
	// string to stream
	std::istringstream in{ str };
	return parse(in);
}

bool Prefix_Parser::is_tb_Expression() const {
	return is_tb_Operation();
}
bool Prefix_Parser::is_tb_Term() const {
	return is_tb_Unsigned() || is_tb_Expression();
}
bool Prefix_Parser::is_tb_Operation() const {
	return m_scanner.is('+') || m_scanner.is('-')
		|| m_scanner.is('*') || m_scanner.is('/');
}
bool Prefix_Parser::is_tb_Unsigned() const {
	return m_scanner.is_number();
}

double Prefix_Parser::parse_Expression() {
	// Operation Term Term
	if (!is_tb_Expression()) {
		throw ParserException("Error parsing 'Expression': didn't start with a valid Operation.");
	}
	double value = 0.0;
	if (m_scanner.is('+')) {
		value = parse_Term() + parse_Term();
	}
	else if (m_scanner.is('-')) {
		value = parse_Term() - parse_Term();
	}
	else if (m_scanner.is('*')) {
		value = parse_Term() * parse_Term();
	}
	else if (m_scanner.is('/')) {
		double tmp1 = parse_Term();
		double tmp2 = parse_Term();
		// check if second operand is zero
		if (tmp2 == 0.0) {
			throw DivideByZeroException();
		}
		value = tmp1 / tmp2;
	}
	return value;
}

double Prefix_Parser::parse_Term() {
	// (Unsigned|Expression)
	if (!is_tb_Term()) {
		throw ParserException("Error parsing 'Term': didn't start with a Digit or a Expression.");
	}
	m_scanner.next_symbol();
	double value = 0.0;
	if (is_tb_Unsigned()) {
		value = m_scanner.get_number();
	}
	else if (is_tb_Expression()) {
		value = parse_Expression();
	}
	else {
		throw ParserException("Error parsing 'Term': second part wasn't a Digit or a Expression.");
	}
	return value;
}