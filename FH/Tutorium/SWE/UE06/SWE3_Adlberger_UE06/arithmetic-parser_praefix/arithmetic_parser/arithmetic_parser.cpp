#include "scanner.h"
#include "arithmetic_parser_.h"
#include "division_by_zero.h"

bool ArithmeticParser::is_tb_Expression() const {
	return is_tb_Term() ||is_tb_AddOp()||is_tb_MultOp();
}
bool ArithmeticParser::is_tb_Term() const {
	return m_scanner.is('-')|| is_tb_Unsigned();
}
bool ArithmeticParser::is_tb_Signed() const {
	return m_scanner.is('-') || is_tb_Unsigned();
}
bool ArithmeticParser::is_tb_AddOp() const {
	return m_scanner.is('+') || m_scanner.is('-');
}
bool ArithmeticParser::is_tb_MultOp() const {
	return m_scanner.is('*') || m_scanner.is('/');
}
bool ArithmeticParser::is_tb_Op() const {
	return is_tb_AddOp() || is_tb_MultOp();
}
bool ArithmeticParser::is_tb_Unsigned() const {
	return m_scanner.is_number();
}
double ArithmeticParser::parse_Expression() {
	//Expression={OPOp Term} Term

	if (!is_tb_Expression()) {
		throw ParserException("Error parsing 'Expression'.");
	}

	double value{  };
	//until no Op there
	char  sign{ ' '};
	//helping variable
	char  sign_h{ ' ' }; 

	while (is_tb_Op()) {
		if (sign!=' ') {
			sign_h = parse_Op();
			m_scanner.next_symbol();
			if (sign=='*') {
				value*= parse_Term();
			}
			else if (sign == '/') {
				value /= parse_Term();
			}
			else if (sign == '+') {
				value += parse_Term();
			}
			else if (sign == '-') {
				value -= parse_Term();
			}
			sign = sign_h;
			m_scanner.next_symbol();
		}
		else {
			sign = parse_Op();
			m_scanner.next_symbol();
			value = parse_Term();
			m_scanner.next_symbol();
			
		}
		
	}
	//check sign 
	if (sign == '*') {
		value *= parse_Term();
	}
	else if (sign == '/') {
		value /= parse_Term();
	}
	else if (sign == '+') {
		value += parse_Term();
	}
	else if (sign == '-') {
		value -= parse_Term();
	}

	return value;
}
double ArithmeticParser::parse_Term() {
	//Term=Signed|Op Term Term
	if (!is_tb_Term()) {
		throw ParserException("Error parsing 'Term'.");
	}
	double value{ 0 };
	double  sign = { 1 };
	if (m_scanner.is('-')) {
		sign = parse_Op();
		m_scanner.next_symbol();

		value=sign * m_scanner.get_integer() ;
	}
	else {
		 value= m_scanner.get_integer() ;
	}
	return value;
		
}

char ArithmeticParser::parse_Op() {
	double value{ 0 };
	if (!is_tb_Op()) {
		throw ParserException("Error parsing 'Faktor'.");
	}
	
		char  sign{' '};
	
			if (m_scanner.is('*')) sign = '*';
			if (m_scanner.is('/')) sign = '/';
			if (m_scanner.is('+')) sign = '+';
			if (m_scanner.is('-')) sign = '-';
			
		return sign;
}

double ArithmeticParser::parse_AddOp() {
	if (m_scanner.is('-') ){
		throw ParserException("Error parsing '-'.");
	}
	
		return -1;
	
}
double ArithmeticParser::parse(std::istream& in) {
	m_scanner.set_istream(in);
	 /*= parse_range()*/;
	 return parse("result.txt");
}

double ArithmeticParser::parse(std::string const& filename) {
	double value{ parse_Expression()};
	return value;
}