#include <fstream>

#include "arithmetic_variable_parser.h"

double ArithmeticVariableParser::parse(std::istream& in) {
	this->m_scanner = pfc::scanner(in);
	return this->parse_Expression();
}

double ArithmeticVariableParser::parse(std::string const& filename)
{
	std::ifstream ifs(filename);
	double result = parse(ifs);
	ifs.close();
	return result;
}

void ArithmeticVariableParser::createVarible(std::string const& name, double const value)
{
	this->varList[name] = value;
}

void ArithmeticVariableParser::updateVarible(std::string const& name, double const value)
{
	this->varList[name] = value;
}

void ArithmeticVariableParser::deleteVarible(std::string const& name)
{
	this->varList.erase(name);
}

bool ArithmeticVariableParser::is_tb_Expression() const
{
	return is_tb_Term();
}

bool ArithmeticVariableParser::is_tb_Term() const
{
	return is_tb_Factor();
}

bool ArithmeticVariableParser::is_tb_Factor() const
{
	return is_tb_AddOp() || is_tb_Var() || is_tb_Unsigned() || is_tb_PExpression();
}

bool ArithmeticVariableParser::is_tb_AddOp() const
{
	return m_scanner.is('+') || m_scanner.is('-');
}

bool ArithmeticVariableParser::is_tb_MultOp() const
{
	return m_scanner.is('*') || m_scanner.is('/');
}

bool ArithmeticVariableParser::is_tb_PExpression() const
{
	return m_scanner.is('(');
}

bool ArithmeticVariableParser::is_tb_Unsigned() const
{
	return m_scanner.is_number();
}

bool ArithmeticVariableParser::is_tb_Var() const
{
	return this->m_scanner.is_identifier();
}

double ArithmeticVariableParser::parse_Expression()
{
	//Expression = Term {AddOp Term}

	if (!is_tb_Expression()) {
		throw ParserException("Error parsing 'Expression'");
	}
	else
	{
		double value = parse_Term();
		while (is_tb_AddOp())
		{
			double const sign = parse_AddOp();
			value += sign * parse_Term();
		}
		return value;
	}
}

double ArithmeticVariableParser::parse_Term()
{
	//Term = Factor 
	if (!is_tb_Term()) {
		throw ParserException("Error parsing 'Term'");
	}
	else {
		double value = parse_Factor();
		while (is_tb_MultOp())
		{
			if (m_scanner.is('*')) {
				m_scanner.next_symbol('*');
				value *= parse_Factor();
			}

			else if (m_scanner.is('/')) {
				m_scanner.next_symbol('/');
				value /= parse_Factor();
			}
			else {
				throw ParserException("Error parsing 'Term'");
			}
		}
		return value;
	}
}

double ArithmeticVariableParser::parse_Factor()
{
	double sign = 1;
	double result = 0;
	if (is_tb_Factor()) {
		if (is_tb_AddOp()) {
			sign = parse_AddOp();
			m_scanner.next_symbol();
		}
		if (is_tb_PExpression()) {
			result = parse_PExpression();
		}
		//add var parser
		else if (is_tb_Var()) {
			result = this->parse_Variable();
		}
		else if (is_tb_Unsigned()) {
			result = m_scanner.get_number();
			m_scanner.next_symbol();
		}
		return sign * result;
	}
	else
		throw ParserException("Error parsing 'factor'");
}

double ArithmeticVariableParser::parse_AddOp()
{
	if (is_tb_AddOp()) {
		double result = m_scanner.is('+') ? 1 : -1;
		m_scanner.next_symbol();
		return result;
	}
	else
		throw ParserException("Error parsing 'AddOp");
}

double ArithmeticVariableParser::parse_PExpression()
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

double ArithmeticVariableParser::parse_Variable()
{
	if (this->is_tb_Var()) {
		std::string varName = this->m_scanner.get_identifier();
		//get value of var
		if (this->varList.count(varName)) {
			this->m_scanner.next_symbol();
			return this->varList[varName];
		}
		else
		{
			throw ParserException("Error Variable not found");
		}
	}
	else
	{
		throw ParserException("Error while parsing variable");
	}
}
