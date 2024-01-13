#include "scanner.h"
#include "arithmetic_parser_.h"
#include "division_by_zero.h"

bool ArithmeticParser::is_tb_Expression() const {
	return is_tb_Term();
}
bool ArithmeticParser::is_tb_Term() const {
	return is_tb_Factor();
}
bool ArithmeticParser::is_tb_Factor() const {
	return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression();
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

double ArithmeticParser::parse_Expression() {
	//Expression=Term{AddOp Term}

	if (!is_tb_Expression()) {
		throw ParserException("Error parsing 'Expression'.");
	}
	double value{ parse_Term() };
	//until no addOp there
	while (is_tb_AddOp()) {
		double const sign{ parse_AddOp() };
		m_scanner.next_symbol();
		value += sign * parse_Term(); //sign of the number
		
	}


	return value;
}
double ArithmeticParser::parse_Term() {
	//Term=Factor {MultOp Factor}
	if (!is_tb_Term()) {
		throw ParserException("Error parsing 'Term'.");
	}
	double value{ parse_Factor() };
	m_scanner.next_symbol();
	//std::cout << m_scanner.current_symbol();
	while (is_tb_MultOp()) {
		if (m_scanner.is('*')) {
			m_scanner.next_symbol('*');
			value *= parse_Factor();
			
		}
		else if (m_scanner.is('/')) {
			m_scanner.next_symbol('/');
			double factor_value{ parse_Factor() };
			if (factor_value == 0) {
				throw DivideByZeroError();
			}
			else {
				value /= factor_value;
			}
		}
		m_scanner.next_symbol();
	}
	return value;
}

double ArithmeticParser::parse_Factor() {
	double value{ 0 };
	if (!is_tb_Factor()) {
		throw ParserException("Error parsing 'Faktor'.");
	}
	
		double  sign{ 1 };
		if (is_tb_AddOp()) {
			sign= parse_AddOp();
			m_scanner.next_symbol();
		}
		

		if (is_tb_Unsigned()) {
			//std::cout << "number:" << m_scanner.current_symbol();
			value += sign * m_scanner.get_number();
		}
		if(is_tb_PExpression()) {
			value += sign * parse_PExpression();
		}
		return value;
	
}

double ArithmeticParser::parse_AddOp() {
	if (!is_tb_AddOp()) {
		throw ParserException("Error parsing 'AddOp'.");
	}
	if (m_scanner.is('+')) {
		return 1;
	}
	else {
		return -1;
	}
	
}
double ArithmeticParser::parse_PExpression() {
	if (!is_tb_PExpression()) {
		throw ParserException("Error parsing 'PExpression'.");
	}
	m_scanner.next_symbol();
	double value{ parse_Expression() };
	//m_scanner.next_symbol();
	if (!m_scanner.is(')')) {
		throw ParserException("Error parsing 'PExpression'.");
	}
	return value;
}
double ArithmeticParser::parse(std::istream& in) {
	m_scanner.set_istream(in);
	 /*= parse_range()*/;
	 return parse_();
}

double ArithmeticParser::parse_() {
	double value{ parse_Expression()};
	return value;
}