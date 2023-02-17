#include "var_parser.h"
#include <fstream>

using std::istream;
using std::ifstream;
using std::string;
using std::istringstream;
using std::unordered_map;

double VariableParser::parse(istream& in, unordered_map<string, int> const& variables) {
	m_scanner.set_istream(in);
	this->var_map = variables;
	double const result = parse_Expression();

	m_scanner.set_istream();
	this->var_map.clear();
	return result;
}

double VariableParser::parse(string const& filename, unordered_map<string, int> const& variables) {
	istringstream in(filename);
	return parse(in, variables);
}

bool VariableParser::is_tb_Expression() const {
	return is_tb_Term();
}

bool VariableParser::is_tb_Term() const {
	return is_tb_Factor();
}

bool VariableParser::is_tb_Factor() const {
	return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression() || is_tb_Variable();
}

bool VariableParser::is_tb_Variable() const {
	return !is_tb_AddOp() && !is_tb_MultOp() && !is_tb_Unsigned() && !is_tb_PExpression();
}

bool VariableParser::is_tb_AddOp() const {
	return m_scanner.is('+') || m_scanner.is('-');
}

bool VariableParser::is_tb_MultOp() const {
	return m_scanner.is('*') || m_scanner.is('/');
}

bool VariableParser::is_tb_PExpression() const {
	return m_scanner.is('(');
}

bool VariableParser::is_tb_Unsigned() const {
	return m_scanner.is_number();
}

double VariableParser::parse_Expression() {
	// Expression = Term { AddOp Term } .
	if (!is_tb_Expression()) {
		throw ParserException("Error parsing `Expression`");
	}

	// parse Term
	double value{ parse_Term() };

	while (is_tb_AddOp()) {
		double const sign{ parse_AddOp() };
		value += sign * parse_Term();
	}

	return value;
}

double VariableParser::parse_Term() {
	// Term = Factor { MultOp Factor }
	if (!is_tb_Factor()) {
		throw ParserException("Error parsing `Term`");
	}

	// Factor
	double value{ parse_Factor() };

	while (is_tb_MultOp()) {
		if (m_scanner.is('*')) {
			m_scanner.next_symbol('*');
			value *= parse_Factor();
		}
		else if (m_scanner.is('/')) {

			m_scanner.next_symbol('/');
			int i = m_scanner.get_number(); // if this number is zero, then we do not need to go any further
			// division by zero is bad!!!
			if (i == 0) {
				throw ParserException("Error trying to divide by zero!");
			}
			value /= parse_Factor();
		}
		else {
			throw ParserException("Error parsing `Term`");
		}
	}

	return value;
}

double VariableParser::parse_Factor() {
	double result{ 0.0 }; // this is where we will store the current values
	double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };

	// Factor = [ AddOp ] ( Unsigned | PExpression )
	if (!is_tb_Factor()) {
		throw ParserException("Error parsing `Factor`");
	}

	if (is_tb_Unsigned()) { // if we just have a number, we will get the value and store it in result
		result = m_scanner.get_number();
		m_scanner.next_symbol(); // do not forget to go to the next symbol, so that we are not stuck in a loop 
	}
	else if (is_tb_Variable()) {
		string v = get<string>(m_scanner.current_symbol().m_attr);
		// with the functions in the pfc_scanner-file, I can get the current_symbol, and from that symbol get the m_attr, which is
		// the value associated with that symbol. neat!
		// the best way to do this is by storing the attribute in a string, the get_attribute()-Function unfortunately only returns a symbol-type

		if (var_map.find(v) != var_map.end()) {
			result = var_map[v];
			m_scanner.next_symbol();
		}
		else {
			throw ParserException("Error parsing `Variable`");
		}
	}
	else if (is_tb_PExpression()) {
		result = parse_PExpression();
	}
	else {
		throw ParserException("Error parsing `Factor`");
	}

	return sign * result;
}

double VariableParser::parse_AddOp() {
	// AddOp = "+" | "-"
	if (!is_tb_AddOp()) {
		throw ParserException("Error parsing `AddOp`.");
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

double VariableParser::parse_PExpression() {
	// PExpression = "(" Expression ")"
	if (!is_tb_PExpression()) {
		throw ParserException("Error parsing `PExpression`");
	}

	m_scanner.next_symbol('(');
	double const value{ parse_Expression() };
	m_scanner.next_symbol(')');

	return value;
}

