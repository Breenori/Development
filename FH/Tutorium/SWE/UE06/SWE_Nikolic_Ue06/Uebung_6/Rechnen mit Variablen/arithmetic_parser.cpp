#include "arithmetic_parser.h"
#include <fstream>
#include <ostream>


double ArithmeticParser::parse(std::istream& in, std::map<std::string, double> const& variables) {
	m_scanner.set_istream(in, true);
	identifiers = variables;
	double value{ parse_Expression() };
	m_scanner.set_istream();
	return value;
}

double ArithmeticParser::parse(std::string const& filename, std::map<std::string, double> const& variables)
{
	std::ifstream in(filename);
	return parse(in, variables);
}

bool ArithmeticParser::is_tb_Expression() const
{
	return is_tb_Term();
}

bool ArithmeticParser::is_tb_Term() const
{
	return is_tb_Factor();
}

bool ArithmeticParser::is_tb_Factor() const
{
	// additional tb_Identifier
	return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression() || is_tb_Identifier();
}

bool ArithmeticParser::is_tb_AddOp() const
{
	return m_scanner.is('+') || m_scanner.is('-');
}

bool ArithmeticParser::is_tb_MultOp() const
{
	return m_scanner.is('*') || m_scanner.is('/');

}

bool ArithmeticParser::is_tb_PExpression() const
{
	return m_scanner.is('(');
}

bool ArithmeticParser::is_tb_Unsigned() const
{
	return m_scanner.is_number();
}

bool ArithmeticParser::is_tb_Identifier() const
{
	// check if symbol is identifier and if identifier is in map
	return m_scanner.is_identifier() && identifiers.count(m_scanner.get_identifier());
}


double ArithmeticParser::parse_Expression()
{
	// Expression = Term {AddOp Term}
	if (!is_tb_Expression()) throw ParserException("Error parsing Expression");
	double value{ parse_Term() };

	while (is_tb_AddOp())
	{
		double const sign{ parse_AddOp() };
		value += sign * parse_Term();
	}

	return value;
}

double ArithmeticParser::parse_Term()
{
	// Term = Factor {MultOp Factor}
	if (!is_tb_Term()) throw ParserException("Error parsing 'Expression'.");
	double value{ parse_Factor() };
	while (is_tb_MultOp())
	{
		if (m_scanner.is('*')) {
			m_scanner.next_symbol('*'); // jump to next symbol
			value *= parse_Factor();
		}
		else if (m_scanner.is('/')) {
			m_scanner.next_symbol('/'); // jump to next symbol
			double next_factor = parse_Factor();
			if (next_factor == 0) throw ParserException("Division by Zero!");
			value /= next_factor;
		}
		else {
			throw ParserException("Error parsing 'Term'.");
		}
	}
	return value;
}

double ArithmeticParser::parse_Factor()
{
	if (!is_tb_Factor())
		throw ParserException{ "Error parsing 'Factor'." };

	double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 }; // optional AddOp
	double       value{ 0.0 };

	if (m_scanner.is_number()) {
		value = m_scanner.get_number();
		m_scanner.next_symbol();
	}
	else if (is_tb_PExpression())
		value = parse_PExpression();
	else if (is_tb_Identifier()) {
		value = identifiers[m_scanner.get_identifier()];
		m_scanner.next_symbol();
	}
	else
		throw ParserException{ "Error parsing 'Factor'." };

	return sign * value;
}

double ArithmeticParser::parse_AddOp()
{
	if (!is_tb_AddOp())
		throw ParserException{ "Error parsing 'AddOp'." };

	double sign{ 0.0 };

	if (m_scanner.is('+')) { sign = 1; m_scanner.next_symbol(); }
	else if (m_scanner.is('-')) { sign = -1; m_scanner.next_symbol(); }

	else
		throw ParserException{ "Error parsing 'AddOp'." };

	return sign;
}

double ArithmeticParser::parse_PExpression()
{
	if (!is_tb_PExpression())
		throw ParserException{ "Error parsing 'PExpression'." };

	m_scanner.next_symbol('(');
	double const value{ parse_Expression() };
	m_scanner.next_symbol(')');

	return value;
}
