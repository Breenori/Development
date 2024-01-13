#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "pfc_scanner.h"
#include "syntax_tree.h"
#include "exception.h"

namespace xpr {
	class Parser {
	public:
		Parser() {}
		virtual ~Parser() {}
		virtual void parse(std::string const& str) = 0;
		virtual void  parse(std::istream& in) = 0;
	};

	class ParseSyntaxTree : public Parser {
	public:
		ParseSyntaxTree() {
			variables = new NameListMap<SyntaxTree<double>*>;
		}
		virtual ~ParseSyntaxTree() {
			delete variables;
		}

		virtual void parse(std::string const& str) override {
			std::istringstream in{ str };
			return parse(in);
		}

		virtual void parse(std::istream& in) {
			//register keywords
			m_scanner.register_keyword("print");
			m_scanner.register_keyword("set");
			m_scanner.set_istream(in, true);
			parse_Program();
			m_scanner.set_istream();

		}

	private:
		//private data components:
		NameListMap<SyntaxTree<double>*>* variables;
		pfc::scanner m_scanner;
		NameList<SyntaxTree<double>*>* nl;
		//-------------------------------------

		bool is_tb_Program() const {
			return is_tb_Output() || is_tb_Assignment();
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
			return is_tb_AddOp() || is_tb_UFactor();
		}

		bool is_tb_UFactor() const {
			return is_tb_Monom() || is_tb_PExpression();
		}

		bool is_tb_Monom() const {
			return is_tb_WMonom();
		}

		bool is_tb_PExpression() const {

			return m_scanner.is('(');
		}

		bool is_tb_WMonom() const {
			return m_scanner.is_identifier() || m_scanner.is_number();
		}

		bool is_tb_Exponent() const {
			return m_scanner.is('^');
		}

		bool is_tb_MultOp() const {
			return m_scanner.is('*') || m_scanner.is('/');
		}

		bool is_tb_AddOp() const {
			return m_scanner.is('+') || m_scanner.is('-');
		}

		StNode<double>* parse_Program() {

			if (!is_tb_Program()) {
				throw parser_exception{ "Error parsing 'Program'." };
			}

			StNode<double>* value{};

			if (is_tb_Output()) {
				SyntaxTree<double>* st = new SyntaxTree<double>(parse_Output());
				std::cout << st->evaluate(variables);
			}
			else if (is_tb_Assignment()) {
				//todo
			}
			else {
				throw parser_exception("Error parsing 'Program'.");
			}

			return value;
		}


		StNode<double>* parse_Output() {
			if (!is_tb_Output()) {
				throw parser_exception{ "Error parsing 'Output'." };
			}
			m_scanner.next_symbol();
			StNode<double>* value{};
			if (is_tb_PExpression()) {
				value = parse_PExpression();
			}
			else {
				throw parser_exception{ "Error parsing 'Output'." };
			}
			return value;
		}

		StNode<double>* parse_PExpression() {
			if (!is_tb_PExpression())
				throw parser_exception{ "Error parsing 'PExpression'." };

			m_scanner.next_symbol('(');
			StNode<double>* const node{ parse_Expression() };
			m_scanner.next_symbol(')');

			return node;
		}

		StNode<double>* parse_Expression() {
			if (!is_tb_Expression()) {
				throw parser_exception{ "Error parsing 'Expression'." };
			}

			StNode<double>* left_node = parse_Term();
			StNodeOperator<double>* root{ nullptr };

			while (is_tb_AddOp()) {
				if (m_scanner.is('+')) {
					root = new StNodeOperator<double>(StNodeOperator<double>::ADD);

				}
				else if (m_scanner.is('-')) {
					root = new StNodeOperator<double>(StNodeOperator<double>::SUB);
				}
				else {
					throw parser_exception{ "Error parsing 'Expression'." };
				}

				root->set_left(left_node);
				root->set_right(parse_Term());

			}

			if (root == nullptr) {
				return left_node;
			}

			return root;
		}





		StNode<double>* parse_Term() {
			if (!is_tb_Term()) {
				throw parser_exception{ "Error parsing 'Term'." };
			}

			StNode<double>* left_node = parse_Factor();
			StNodeOperator<double>* root{ nullptr };

			while (is_tb_MultOp()) {
				if (m_scanner.is('*')) {
					m_scanner.next_symbol();
					root = new StNodeOperator<double>(StNodeOperator<double>::MUL);
				}

				else if (m_scanner.is('/')) {
					m_scanner.next_symbol();
					root = new StNodeOperator<double>(StNodeOperator<double>::DIV);
					/*			if (left_node->get_value() == 0.0) {
									throw DivByZeroException();
								}*/
				}
				else {
					throw parser_exception{ "Error parsing 'Term'." };
				}
				root->set_left(left_node);
				root->set_right(parse_Factor());
			}

			if (root == nullptr) {
				return left_node;
			}

			return root;
		}


		//Monom or PEexpresion
		StNode<double>* parse_Factor() {
			if (!is_tb_Factor())
				throw parser_exception{ "Error parsing 'Factor'." };

			//auto const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };
			StNode<double>* node{ nullptr };

			if (is_tb_Monom()) {
				node = parse_Monom();
				//m_scanner.next_symbol();

			}
			else if (is_tb_PExpression()) {
				node = parse_PExpression();
			}
			else {
				throw parser_exception{ "Error parsing 'Factor'." };
			}

			return node;
		}

		//WMonom [Exponent]
		StNode<double>* parse_Monom(){
			if (!is_tb_Monom()) {
				throw parser_exception{ "Error parsing 'Monom'." };
			}

			StNode<double>* left_node = parse_WMonom();
			StNodeOperator<double>* root{ nullptr };

			m_scanner.next_symbol();
			if (is_tb_Exponent()) {
				root = new StNodeOperator<double>(StNodeOperator<double>::EXP);

				root->set_left(left_node);
				root->set_right(parse_PExpression());

			}
			else {
				return left_node;
			}

			return root;
		}


		StNode<double>* parse_WMonom() {
			if (!is_tb_Monom()) {
				throw parser_exception{ "Error parsing 'WMonom'." };
			}

			StNode<double>* node{  };

			if (m_scanner.is_number()) {
				node = new StNodeValue<double>(m_scanner.get_number());
			}
			//else if (m_scanner.is_identifier()) {
			//	node = new StNodeIdent<double>(m_scanner.get_identifier());
			//}
			else {
				throw parser_exception{ "Error parsing 'WMonom'." };
			}
			return node;
		}


	};
}

#endif // !PARSE_SYNTAX_TREE_H

