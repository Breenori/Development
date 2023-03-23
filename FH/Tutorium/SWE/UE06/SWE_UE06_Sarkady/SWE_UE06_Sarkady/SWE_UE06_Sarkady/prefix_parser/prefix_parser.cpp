#include "prefix_parser.h"
#include <fstream>

using std::istream;
using std::ifstream;
using std::string;
using std::istringstream;

double PrefixParser::parse(istream& in) {
	m_scanner.set_istream(in);
	double const result = parse_Expression();
	m_scanner.set_istream();
	return result;
}

double PrefixParser::parse(string const& filename) {
	std::istringstream in(filename);
	return parse(in);
}

bool PrefixParser::is_tb_Expression() const {
	return is_tb_Unsigned() || is_tb_BinaryOp();
}

bool PrefixParser::is_tb_BinaryOp() const {
	return is_tb_AddOp() || is_tb_MultOp();
}

bool PrefixParser::is_tb_Term() const {
	return is_tb_Expression();
}

bool PrefixParser::is_tb_AddOp() const {
	return m_scanner.is('+') || m_scanner.is('-');
}

bool PrefixParser::is_tb_MultOp() const {
	return m_scanner.is('*') || m_scanner.is('/');
}

bool PrefixParser::is_tb_Unsigned() const {
	return m_scanner.is_number();
}

double PrefixParser::parse_Expression() {
	double x{ 0.0 };
	double y{ 0.0 };
	double op{ 0.0 };
	double result{ 0.0 };
	// Expression = Unsigned | (BinaryOp Term Term) .

	if (!is_tb_Expression()) {
		throw ParserException("Error parsing `Expression`");
	}

	if (!is_tb_BinaryOp()) { // if the current symbol is not a BinaryOperation, it must be a number, because we do not need to look out for Parenthises! ()
		result = m_scanner.get_number();
		m_scanner.next_symbol();
	}
	else if (is_tb_AddOp()) {
		// can be AddOp Unsigned Unsigned
		// or AddOp BinaryOp .....
		// or AddOp Unsigned .....
		op = parse_AddOp();
		x = parse_Expression();
		y = parse_Expression();

		result = x + op * y;
	}
	else if (is_tb_MultOp()) {
		string v{ "" }; 
		if (m_scanner.is('/')) { // we need to remember this symbol so that we know which operation it is
			//v = m_scanner.current_symbol().get_identifier();
			v = "/";
		} 
		m_scanner.next_symbol();
		double i{ parse_Expression() };
		double j{ parse_Expression() };

		if (v == "/") {
			if (j == 0) {
				throw ParserException("Error trying to divide by zero!");
			}

			j = 1 / j;
			result = i * j;
		}
		else {
			result = i * j;
		}
	}
	return result;
}

double PrefixParser::parse_AddOp() {
	// AddOp = "+" | "-"
	if (!is_tb_AddOp()) {
		throw ParserException("Error parsing `AddOp`");
	}

	double sign{ 1.0 };
	if (m_scanner.is('+')) {
		sign = 1;
		m_scanner.next_symbol('+');
	}
	else if (m_scanner.is('-')) {
		sign = -1;
		m_scanner.next_symbol('-');
	}
	else {
		throw ParserException("Error parsing `AddOp`");
	}

	return sign;
}
