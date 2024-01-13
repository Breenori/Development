#pragma once
#include "pfc_scanner.h"
#include "syntax_tree.h"

namespace xpr
{

	// ABSTRACT PARSER -----------------------------------------------------------------------------------------------


	class parser
	{
	public:
		virtual ~parser(){};

	protected:
		virtual void clear() = 0;

		virtual void parse(std::istream& in) = 0;

		virtual void parse(std::string const& str) = 0;

	};




	// PARSER -----------------------------------------------------------------------------------------------

	class parse_syntax_tree : public parser
	{
	public:

		//CONSTRUCTOR (REGISTER)
		parse_syntax_tree();
		~parse_syntax_tree();

		void clear() override;
		void reset_syntax_tree();

		// parse input
		void parse(std::istream& in) override;

		// parse string
		void parse(std::string const& str) override;

		void print_in_order_by_name(std::string const& name, std::ostream& os = std::cout) const;
		void print_pre_order_by_name(std::string const& name, std::ostream& os = std::cout) const;
		void print_post_order_by_name(std::string const& name, std::ostream& os = std::cout) const;
		void print_2d_by_name(std::string const& name, std::ostream& os = std::cout) const;
		void print_2d_upright_by_name(std::string const& name, std::ostream& os = std::cout) const;
		void print_namelist(std::ostream& os = std::cout) const;

	private:

		// TB CHECKER
		bool is_tb_programm() const;
		bool is_tb_output() const;
		bool is_tb_assignment() const;
		bool is_tb_expression() const;
		bool is_tb_term() const;
		bool is_tb_factor() const;
		bool is_tb_u_factor() const;
		bool is_tb_monom() const;
		bool is_tb_p_expression() const;
		bool is_tb_wmonom() const;
		bool is_tb_exponent() const;
		bool is_tb_add_op() const;
		bool is_tb_mult_op() const;

		// PARSE FCTNS
		void parse_programm();
		void parse_output();
		void parse_assignment();
		xpr::st_node<double>* parse_expression();
		xpr::st_node<double>* parse_term();
		xpr::st_node<double>* parse_factor();
		xpr::st_node<double>* parse_u_factor();
		xpr::st_node<double>* parse_monom();
		xpr::st_node<double>* parse_p_expression();
		xpr::st_node<double>* parse_wmonom();
		xpr::st_node<double>* parse_exponent();
		xpr::st_node_operator<double>* parse_add_op();
		xpr::st_node_operator<double>* parse_mult_op();

		// current tree
		syntax_tree<double>* m_tree = nullptr;

		// name_list
		name_list<syntax_tree<double>*>* m_nl = nullptr;

		// scanner
		pfc::scanner m_scanner;
	};

}

