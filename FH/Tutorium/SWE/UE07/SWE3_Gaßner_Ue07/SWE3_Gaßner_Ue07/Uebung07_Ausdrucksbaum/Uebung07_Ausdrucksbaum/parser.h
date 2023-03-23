#ifndef parser_h
#define parser_h

#include "expr_excepiton.h"
#include "syntax_tree.h"
#include "pfc_scanner.h"
#include <exception>


namespace xpr {

    class ParserException final : public std::runtime_error {
    public:
        explicit ParserException(std::string const& message) : std::runtime_error{ message } {}
    };

	template <typename T>
	class Parser {
	public:
		Parser() {}
		virtual ~Parser() {}
		virtual void parse(std::istream in) = 0;
        virtual void parse(std::string const& filename) = 0;
		virtual void print_name_list() = 0;

	};


    template<typename T>
    class ParseSyntaxTree : public Parser<T> {
    public:
        ParseSyntaxTree(){
			NameListMap<SyntaxTree<T>*> namesMap;
			this->names = &namesMap;
			m_scanner.register_keyword("print");
			m_scanner.register_keyword("set");
        }

        virtual ~ParseSyntaxTree() {}

        void parse(std::istream& in) override {
			m_scanner.set_istream(in, true);
			parse_Program();
			m_scanner.set_istream();
		}

       void parse(std::string const& filename) override {
			//Create input string stream from the given file name
			std::istringstream in(filename);
			if (in.fail()) {
				throw std::runtime_error("Failed to open file: " + filename);
			}
			return parse(in);
		}

		void print_name_list() override {
			if (names) {
				names->print();
			}
		}
    
    private:
		bool is_tb_Program() const {
			return is_tb_Assignment() || is_tb_Output();
		}
		bool is_tb_Output() const {
			return m_scanner.is_keyword("print");
		}
		bool is_tb_Assignment() const {
			return m_scanner.is_keyword("set");
		}
		bool is_tb_Expression() const {
			return is_tb_Term();
		}
		bool is_tb_Term() const {
			return is_tb_Factor();
		}
		bool is_tb_Factor() const {
			return is_tb_UFactor() || is_tb_AddOp();
		}
		bool is_tb_UFactor() const {
			return is_tb_Monom || is_tb_PExpression();
		}
		bool is_tb_Monom() const {
			return m_scanner.is_number() || m_scanner.is_identifier();
		}
		bool is_tb_PExpression() const {
			return m_scanner.is('(');
		}
		bool is_tb_Exponent() const {
			return m_scanner.is('^');
		}
		bool is_tb_AddOp() const {
			return m_scanner.is('+') || m_scanner.is('-');
		}
		bool is_tb_MultOp() const {
			return m_scanner.is('*') || m_scanner.is('/');
		}
		bool is_tb_Identifier() const {
			return m_scanner.is_identifier();
		}

		void parse_Program() {
			// Program = { Output | Assignment }.
			if (!is_tb_Program()) {
				throw ParserException("Error parsing 'Program'.");
			}

			while (is_tb_Program()) {
				if (m_scanner.is_keyword("set")) {
					parse_Assignment();
				}
				else if (m_scanner.is_keyword("print")) {
					parse_Output();
				}
				else {
					throw ParserException("Error parsing 'Program'.");
				}
			}
		}

		void parse_Output() {
			// Output = "print" "(" Expression ")" ";".
			if (!is_tb_Output()) {
				throw ParserException("Error parsing 'Output'.");
			}

			m_scanner.next_symbol(); // skip "print"
			m_scanner.next_symbol(); // skip "("

			StNode<T>* expression = parse_Expression();
			std::cout << expression->evaluate(names) << "\n";

			m_scanner.next_symbol(); // skip ")"
			m_scanner.next_symbol(); // skip ";"
		}

		void parse_Assignment() {
			// Assignment = "set" "(" Identifier "," Expression ")" ";".
			if (m_scanner.next_symbol() != is_tb_Assignment()) {
				throw ParserException("Error parsing 'Assignment'.");
			}
			if (m_scanner.next_symbol() != is_tb_PExpression()) {
				throw ParserException("Error parsing '('.");
			}
			if (m_scanner.next_symbol() != is_tb_Identifier()) {
				throw ParserException("Error parsing 'Identifier'.");
			}
			std::string ident{ m_scanner.get_identifier() };
			if (m_scanner.next_symbol() != m_scanner.is(',')) {
				throw ParserException("Error parsing ','.");
			}

			StNode<T>* val = parse_Expression();
			SyntaxTree<T>* tree = new SyntaxTree<T>(val);
			names->register_var(ident, tree);

			if (m_scanner.next_symbol() != m_scanner.is(')')) {
				throw ParserException("Error parsing ')'.");
			}
			if (m_scanner.next_symbol() != m_scanner.is(';')) {
				throw ParserException("Error parsing ';'.");
			}
		}

		StNode<T>* parse_Expression() {
			// Expression = Term { AddOp Term }.
			if (!is_tb_Expression()) {
				throw ParserException("Error parsing 'Expression'");
			}

			StNode<T>* left_node = parse_Term();

			while (is_tb_AddOp()) {
				StNode<T>* middle_node = parse_AddOp();
				StNode<T>* right_node = parse_Term();
				middle_node->set_left(left_node);
				middle_node->set_right(right_node);
				left_node = middle_node;
			}
			return left_node;
		}

		StNode<T>* parse_AddOp() {
			// "+" | "-".
			if (!is_tb_AddOp()) {
				throw ParserException("Error parsing 'AddOp'.");
			}

			StNode<T>* middle_node = nullptr;

			if (m_scanner.is('+')) {
				middle_node = new StNodeOperator<T>(StNodeOperator<T>::ADD);
				m_scanner.next_symbol();
			}
			else if (m_scanner.is('-')) {
				middle_node = new StNodeOperator<T>(StNodeOperator<T>::SUB);
				m_scanner.next_symbol();
			}
			return middle_node;
		}

		StNode<T>* parse_Term() {
			// Term = Factor { MultOp Factor }.
			StNode<T>* node = parse_Factor();

			while (is_tb_MultOp()) {
				char op = m_scanner.current_symbol();
				if (op == '*') {
					m_scanner.next_symbol('*');
					node = new StNodeOperator<T>(StNodeOperator<T>::MUL, node, parse_Factor());
				}
				else if (op == '/') {
					m_scanner.next_symbol('/');
					StNode<T>* divisor = parse_Factor();
					if (divisor->evaluate(names) == 0.0) {
						throw DivisionByZeroException("Error division by zero.");
					}
					node = new StNodeOperator<T>(StNodeOperator<T>::DIV, node, divisor);
				}
			}
			return node;
		}
		
		StNode<T>* parse_Factor() {
			// Factor = [ AddOp ] UFaktor.
			if (!is_tb_Factor()) {
				throw ParserException("Error parsing 'Factor'.");
			}

			StNode<T>* middle_node{ nullptr };
			StNode<T>* left_node{ nullptr };

			// check for Sign
			if (m_scanner.is('-')) {
				m_scanner.next_symbol('-');
				middle_node = parse_AddOp();
			}

			left_node = parse_UFactor();

			if (middle_node != nullptr) {
				middle_node->set_right(left_node);
			}
			return middle_node == nullptr ? left_node : middle_node;
		}

		StNode<T>* parse_UFactor() {
			if (!is_tb_UFactor()) {
				throw ParserException("Error parsing 'UFactor'.");
			}
			return is_tb_Monom() ? parse_Monom() : parse_PExpression();
		}

		StNode<T>* parse_PExpression() {
			// PExpression = "(" Expression ")".
			if (!is_tb_PExpression()) {
				throw ParserException("Error parsing 'PExression'.");
			}

			StNode<T>* middle_node{ nullptr };

			if (m_scanner.is('(')) {
				m_scanner.next_symbol();
				middle_node = parse_Expression();
				if (m_scanner.is(')')) {
					m_scanner.next_symbol();
				}
				else {
					throw ParserException("Error: missing closing parenthesis.");
				}
			}
			else {
				throw ParserException("Error: missing opening parenthesis.");
			}
			return middle_node;
		}

		StNode<T>* parse_Monom() {
			// Monom = WMonom [Exponent]
			if (!is_tb_Monom()) {
				throw ParserException("Error parsing 'Monom'.");
			}

			StNode<T>* middle_node = nullptr;

			if (m_scanner.is_number()) {
				middle_node = new StNodeValue<T>{ m_scanner.get_number() };
			}
			else if (m_scanner.is_identifier()) {
				middle_node = new StNodeIdent<T>{ m_scanner.get_identifier() };
			}

			m_scanner.next_symbol();

			// check for Exponent
			if (m_scanner.is('^')) {
				m_scanner.next_symbol();
				StNode<T>* left_node = parse_Factor();
				middle_node = new StNodeOperator<T>{ StNodeOperator<T>::EXP, middle_node, left_node };
			}

			return middle_node;
		}

		StNode<T>* parse_Exponent() {
			// Exponent = "^" [ AddOp ] Real.
			if (!is_tb_Exponent()) {
				throw ParserException("Error parsing 'Exponent'.");
			}

			StNode<T>* left_node{ nullptr };
			StNode<T>* middle_node{ nullptr };

			// check for exponent symbol
			if (m_scanner.is('^')) {
				middle_node = new StNodeOperator<T>(StNodeOperator<T>::EXP);
			}

			// check for sign
			if (is_tb_AddOp()) {
				left_node = parse_AddOp();
			}
			else {
				left_node = new StNodeValue<T>(m_scanner.get_number());
			}

			// If an exponent symbol was found, set the left child node
			if (middle_node) {
				middle_node->set_left(left_node);
				return middle_node;
			}
			else {
				return left_node;
			}
		}

		pfc::scanner m_scanner;
		NameListMap<SyntaxTree<T>*>* names{ nullptr };
    };



}







#endif