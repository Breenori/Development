#ifndef programm_parser_h
#define program_parser_h

#include <iostream>
#include <string>
#include <exception>
#include <stack>

#include "pfc_scanner.h"
#include "st_node.h"
#include "name_list.h"

using namespace xpr;

class ParserException final : public std::runtime_error {
public:
    explicit ParserException(std::string const& message) : std::runtime_error{ message } { }
};

class DivByZeroException final : public std::runtime_error {
public:
    explicit DivByZeroException(std::string const& message) : std::runtime_error{ message } { }
};

class Parser {
public:
	virtual double parse(std::istream& in) = 0;
	virtual double parse(std::string& str) = 0;
};

class ProgrammParser : Parser{
public:
	std::string set_word = "set";
	std::string print_word = "print";

	double parse(std::istream& in) override {

		// registering keywords:
		this->m_scanner.register_keyword(set_word);
		this->m_scanner.register_keyword(print_word);

		m_scanner.set_istream(in);

		return parse_Programm();
	}
	double parse(std::string& str) override {
		std::istringstream in{ str };
		return parse(in);
	}

private:
	
	// parse-methods

	double parse_Programm() {
		// Programm = {Ausgabe|Zuweisung}
		if (!is_tb_Programm()) {
			throw ParserException("Error parsing 'Programm'.");
		}

		double value;

		while (is_tb_Programm()) {
			if (is_tb_Ausgabe()) {
				value = parse_Ausgabe();
			}
			else if (is_tb_Zuweisung()) {
				value = parse_Zuweisung();
			}
			else {
				throw ParserException("Error parsing 'Programm'.");
			}
		}
	}

	double parse_Ausgabe() {
		// Ausgabe = "print" "(" Ausdruck ")" ";"
		if (!is_tb_Ausgabe()) {
			throw ParserException("Error parsing 'Ausgabe'.");
		}

		m_scanner.next_symbol();
		m_scanner.next_symbol("(");

		// creating stack that will contain all elements of expression in right order
		std::stack<StNode<double>*> ausdruck_stack;
		std::stack<StNode<double>*> op_stack;
		StNode<double>* value = parse_Ausdruck(ausdruck_stack, op_stack);

		m_scanner.next_symbol(")");
		m_scanner.next_symbol(";");
	}

	double parse_Zuweisung() {
		// Zuweisung = "set" "(" Identifier "," Ausdruck ")" ";"
		if (!is_tb_Zuweisung()) {
			throw ParserException("Error parsing 'Zuweisung'.");
		}

		m_scanner.next_symbol();
		m_scanner.next_symbol('(');
		std::string ident = m_scanner.get_identifier(); m_scanner.next_symbol();
		m_scanner.next_symbol(',');

		// creating stack that will contain all elements of expression in right order
		std::stack<StNode<double>*> ausdruck_stack;
		std::stack<StNode<double>*> op_stack;
		StNode<double>* value = parse_Ausdruck(ausdruck_stack, op_stack);
		
		// TODO: evaluating stack and adding ident and parsed expression to stack

		m_scanner.next_symbol(")");
		m_scanner.next_symbol(";");
	}

	StNode<double>* parse_Ausdruck(std::stack<StNode<double>*>& expr_stack, std::stack<StNode<double>*>& op_stack) {
		return NULL;
		// TODO
	}

	// tb-methods

	bool is_tb_Programm() const {
		return is_tb_Ausgabe() || is_tb_Zuweisung();
	}

	bool is_tb_Ausgabe() const {
		return m_scanner.is_keyword(print_word);
	}

	bool is_tb_Zuweisung() const {
		return m_scanner.is_keyword(set_word);
	}

	bool is_tb_Ausdruck() const {
		return is_tb_Term();
	}

	bool is_tb_Term() const {
		return is_tb_Faktor();
	}

	bool is_tb_Faktor() const {
		return is_tb_AddOp() || is_tb_UFaktor();
	}

	bool is_tb_AddOp() const {
		return m_scanner.is('+') || m_scanner.is('-');
	}

	bool is_tb_UFaktor() const {
		return is_tb_Monom() || is_tb_KAusdruck();
	}

	bool is_tb_Monom() const {
		return is_tb_WMonom();
	}

	bool is_tb_WMonom() const {
		return m_scanner.is_identifier() || m_scanner.is_real();
	}

	bool is_tb_KAusdruck() const {
		return m_scanner.is('(');
	}

	bool is_tb_Exponent() const {
		return m_scanner.is('^');
	}

	bool is_tb_MultOp() const {
		return m_scanner.is('*') || m_scanner.is('/');
	}

    pfc::scanner m_scanner;
};

#endif