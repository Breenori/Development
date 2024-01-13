#ifndef PARSER_H
#define PARSER_H

#include "expr_exceptions.h"
#include <iostream>

#include <fstream>
#include "pfc_scanner.h"

#include "name_list.h"
#include "syntax_tree.h"

using std::istream;
using std::ifstream;

namespace xpr {

    //interface for parser
    class Parser {
    public:
        Parser() {};

        virtual void parse(istream& in) = 0;
        virtual void parse(string const& filename) = 0;
        virtual void print_vars(ostream& out) = 0;

        virtual ~Parser() {};

    };

    class ParseSyntaxTree:public Parser {
    public:
        ParseSyntaxTree();

        void parse(istream& in) override;
        void parse(string const& filename) override;
        void print_vars(ostream& out) override;

        ~ParseSyntaxTree();

    private:
        //predicates
        bool is_tb_Expression() const;
        bool is_tb_Term() const;

        bool is_tb_Factor() const;
        bool is_tb_AddOp() const;

        bool is_tb_MultOp() const;
        bool is_tb_PExpression() const;

        bool is_tb_U_Factor() const;
        bool is_tb_Monom() const;

        bool is_tb_WMonom() const;
        bool is_tb_Exponent() const;

        bool is_tb_Assignment() const;
        bool is_tb_Print() const;

        //parse functions
        StNode<double>* parse_Expression();
        StNode<double>* parse_Term();

        StNode<double>* parse_Factor();
        StNode<double>* parse_U_Factor();

        StNode<double>* parse_AddOp();
        StNode<double>* parse_MultOp();

        StNode<double>* parse_PExpression();
        StNode<double>* parse_Monom();

        StNode<double>* parse_WMonom();
        StNode<double>* parse_Exponent();

        void parse_Assignment();
        void parse_Print();

        NameList<SyntaxTree<double>*>* m_list;
        pfc::scanner m_scanner;
    };

};

#endif