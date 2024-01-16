#include "arithmetic_parser.h"
#include <fstream>

double ArithmeticParser::parse(std::istream& in, std::map<std::string, double>& vars){
	m_scanner.set_istream(in, true); 
	this->vars = vars;
	double const value{ parse_Expression() };
	m_scanner.set_istream();
	return value;
}
double ArithmeticParser::parse(std::string const& str, std::map<std::string, double>& vars){
	// string to stream
	std::istringstream in{ str };
	return parse(in, vars);
}

bool ArithmeticParser::is_tb_Expression() const {
	return is_tb_Term();
}
bool ArithmeticParser::is_tb_Term() const {
	return is_tb_Factor();
}
bool ArithmeticParser::is_tb_Factor() const {
	return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression() || is_tb_Var();
}
bool ArithmeticParser::is_tb_AddOp() const {
	return m_scanner.is('+') || m_scanner.is('-');
}
bool ArithmeticParser::is_tb_MultOp() const {
	return m_scanner.is('*') || m_scanner.is('/');
}
bool ArithmeticParser::is_tb_PExpression() const {
	return m_scanner.is('(');
}
bool ArithmeticParser::is_tb_Unsigned() const {
	return m_scanner.is_number();
}
bool ArithmeticParser::is_tb_Var() const {
	return m_scanner.is_identifier();
}

double ArithmeticParser::parse_Expression() {
	// Expression = Term {AddOp Term}
	if (!is_tb_Expression()) {
		throw ParserException("Error parsing 'Expression': didn't start with a Term.");
	}
	double value{ parse_Term() };
	while (is_tb_AddOp()) {
		double const sign(parse_AddOp());
		value += sign * parse_Term();
	}
	return value;
}


double ArithmeticParser::parse_Term() {
	// Term = Factor { MultOp Factor }
	if (!is_tb_Term()) {
		throw ParserException("Error parsing 'Term': didn't start with a Factor.");
	}

	double value{ parse_Factor() }; 
	// parse multiple MultOps
	while (is_tb_MultOp()) {
		if (m_scanner.is('*')) {
			// scanner to next symbol
			m_scanner.next_symbol('*');
			value *= parse_Factor();
		}
		else if (m_scanner.is('/')) {
			m_scanner.next_symbol('/');
			double temp{ parse_Factor() };
			if (temp == 0.0) {
				throw DivideByZeroException();
			}
			value /= temp;
		}
		else {
			throw ParserException("Error parsing 'Term': invalid operation");
		}
	}
	return value;
}
double ArithmeticParser::parse_Factor() {
	// Factor = [AddOp] (Unsigned|PExpression)
	if (!is_tb_Factor()) {
		throw ParserException("Error parsing 'Factor': invalid start.");
	}
	double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };
	double value = 0.0;
	if (is_tb_Unsigned()) {
		value = m_scanner.get_number();
		m_scanner.next_symbol();
	}
	else if (is_tb_PExpression()) {
		value = parse_PExpression();
	}
	else if (is_tb_Var()) {
		value = parse_Var();
		m_scanner.next_symbol();
	}
	else {
		throw ParserException("Error parsing 'Factor'.");
	}
	return sign * value;
}

double ArithmeticParser::parse_AddOp() {
	// "+" | "-"
	if (!is_tb_AddOp()) {
		throw ParserException("Error parsing 'AddOp': invalid operation.");
	}
	double sign = 0.0;
	if (m_scanner.is('+')) {
		sign = 1.0;
		m_scanner.next_symbol();
	}
	else if (m_scanner.is('-')) {
		sign = -1.0;
		m_scanner.next_symbol();
	}
	else {
		throw ParserException("Error parsing 'AddOp': invalid operation.");
	}
	return sign;
}
double ArithmeticParser::parse_PExpression() {
	// "(" Expression ")"
	if (!is_tb_PExpression()) {
		throw ParserException("Error parsing 'PExpression': didn't start with left paranthesis.");
	}
	// PExpression must have parenthesis around it
	m_scanner.next_symbol('(');
	double value{ parse_Expression() };
	m_scanner.next_symbol(')');

	return value;
}
double ArithmeticParser::parse_Var() {
	if (!is_tb_Var()) {
		throw ParserException("Error parsing 'Variable'.");
	}
	std::string name{ m_scanner.get_identifier() };
	// search for name in keys
	auto it = vars.find(name);
	if (it == vars.end()) {
		throw ParserException("Error parsing 'Variable': Variable not found.");
	}
	else {
		// return value
		return it->second;
	}
}