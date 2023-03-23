#include "arithmetic_parser.h"
#include <fstream>
#include <ostream>


double ArithmeticParser::parse(std::istream& in) {
	m_scanner.set_istream(in, true);
	double value{ parse_Expression() };
	m_scanner.set_istream();
	return value;
}

double ArithmeticParser::parse(std::string const& filename)
{
	std::ifstream in(filename);
	return parse(in);
}

bool ArithmeticParser::is_tb_Expression() const {
	return is_tb_Op() || m_scanner.is_number();
}

bool ArithmeticParser::is_tb_Op() const
{
	return m_scanner.is('+') || m_scanner.is('-') || m_scanner.is('*') || m_scanner.is('/');
}

double ArithmeticParser::parse_Expression()
{
	if (!is_tb_Expression()) throw ParserException("Error parsing Expression");

	double value = 0.0;

	// Expression is either number or Operator Expression Expression
	if (m_scanner.is_number()) {
		value = m_scanner.get_number();
		m_scanner.next_symbol();
	}
	else {
		// differentiate Operators, parse first Expression and second Expression recursive
		if (m_scanner.is('+')) {
			m_scanner.next_symbol();
			value = parse_Expression() + parse_Expression();
		}
		else if (m_scanner.is('-')) {
			m_scanner.next_symbol();
			value = parse_Expression() - parse_Expression();
		}
		else if (m_scanner.is('*')) {
			m_scanner.next_symbol();
			value = parse_Expression() * parse_Expression();
		}
		else if (m_scanner.is('/')) {
			m_scanner.next_symbol();
			double first_expr = parse_Expression();
			double second_expr = parse_Expression();
			// check Division by Zero
			if (second_expr == 0) throw ParserException("Division by Zero!");
			value = first_expr / second_expr;
		}
	}
	return value;
}


