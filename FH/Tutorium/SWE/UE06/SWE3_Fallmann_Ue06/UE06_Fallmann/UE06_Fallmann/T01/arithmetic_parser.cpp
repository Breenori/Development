#include "arithmetic_parser.h"
#include <fstream>

double ArithmeticParser::parse(std::istream& in) {
	this->m_scanner = pfc::scanner(in);
	return this->parse_Expression();
}

double ArithmeticParser::parse(std::string const& filename)
{
	std::ifstream ifs(filename);
	double result = parse(ifs);
	ifs.close();
	return result;
}
// check for terminal beginnings ----------------------
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
	return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression();
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
//--------------------------------------------------------

double ArithmeticParser::parse_Expression()
{
	//Expression = Term {AddOp Term}

	if (!is_tb_Expression()) {
		throw ParserException("Error parsing 'Expression'");
	}
	else
	{
		//get first value
		double value = parse_Term();
		//add all values as long as there is an addition operator
		while (is_tb_AddOp())
		{
			//get sign
			double const sign = parse_AddOp();
			value += sign * parse_Term();
		}
		return value;
	}
}

double ArithmeticParser::parse_Term()
{
	//Term = Factor 
	if (!is_tb_Term()) {
		throw ParserException("Error parsing 'Term'");
	}
	else {
		//parse factor
		double value = parse_Factor();
		while (is_tb_MultOp())
		{
			//differ between * and /
			if (m_scanner.is('*')) {
				m_scanner.next_symbol('*');
				value *= parse_Factor();
			}

			else if (m_scanner.is('/')) {
				m_scanner.next_symbol('/');
				double r = parse_Factor();
				if (r == 0) {
					throw ParserException("Divison by zero exception");
				}
				value /= r;
			}
			else {
				throw ParserException("Error parsing 'Term'");
			}
		}
		return value;
	}
}

double ArithmeticParser::parse_Factor()
{
	double sign = 1;
	double result = 0;
	if (is_tb_Factor()) {
		if (is_tb_AddOp()) {
			//get sign
			sign = parse_AddOp();
		}
		//get PExpression
		if (is_tb_PExpression()) {
			result = parse_PExpression();
		}
		else if (is_tb_Unsigned()) {
			result = m_scanner.get_number();
			m_scanner.next_symbol();
		}
		else {
			throw ParserException("Error parsing 'factor'");
		}
		return sign * result;
	}
	else
		throw ParserException("Error parsing 'factor'");
}

double ArithmeticParser::parse_AddOp()
{
	if (is_tb_AddOp()) {
		double result = m_scanner.is('+') ? 1 : -1;
		m_scanner.next_symbol();
		return result;
	}
	else
		throw ParserException("Error parsing 'AddOp");
}

double ArithmeticParser::parse_PExpression()
{
	if (!is_tb_PExpression()) {
		throw ParserException("Error parsing 'PE'");
	}
	else {
		m_scanner.next_symbol('(');
		double result = parse_Expression();
		m_scanner.next_symbol(')');
		return result;
	}
}
