#ifndef PARSER_H
#define PARSER_H

#include "pfc_scanner.h"
#include "exceptions.h"
#include "syntax_tree.h"
#include <fstream>
#include <iostream>

namespace xpr {

	class Parser final{
	public:

		void parse(std::istream& _in_);
		void parse(std::string const& _filename_);
		std::ostream& print_namelist(std::ostream& _out_) const;

	private:
		pfc::scanner						m_scanner;
		NameListMap<SyntaxTree<double>*>	name_list;

		void try_parsing(std::istream& _in_);

		bool is_tb_Program()		const;
		bool is_tb_Print()			const;
		bool is_tb_Set()			const;

		bool is_tb_Expression()		const;
		bool is_tb_Term()			const;
		bool is_tb_Factor()			const;
		bool is_tb_UFactor()		const;
		bool is_tb_Monom()			const;
		bool is_tb_PExpression()	const;
		bool is_tb_WMonom()			const;
		bool is_tb_Exponent()		const;
		bool is_tb_MultOp()			const;
		bool is_tb_AddOp()			const;
		bool is_tb_Identifier()		const;
		bool is_tb_Real()			const;

		void parse_Program();
		void parse_Print();
		void parse_Set();

		StNode<double>* parse_Expression();
		StNode<double>* parse_Term();
		StNode<double>* parse_Factor();
		StNode<double>* parse_UFactor();
		StNode<double>* parse_Monom();
		StNode<double>* parse_PExpression();
		StNode<double>* parse_WMonom();
		StNode<double>* parse_Exponent();

	};

} // !namespace xpr

#endif // !PARSER_H