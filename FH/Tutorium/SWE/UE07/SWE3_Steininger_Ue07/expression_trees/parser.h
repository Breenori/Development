#ifndef EXPRESSION_TREE_PARSER_H
#define EXPRESSION_TREE_PARSER_H

#include "pfc_scanner.h"
#include <iostream>
#include "syntax_tree.h"
#include <exception>
#include <string>


using std::string;
using std::cout;

namespace xpr{

    struct parser_error : public std::exception{
    public:
        parser_error(std::string _message):message(_message){}
        const char * what() const noexcept override{
            return message.c_str();
        }
    private:
        std::string message;
    };


    class parser{
    public:
        virtual ~parser()=default;
        virtual void parse(std::ostream& out=cout)=0;
    protected:
        //move constructor into protected scope so that derived classes
        //can make use of it --> same base level implementation
        parser(std::istream& in){
            this->m_scanner.register_keyword("set");
            this->m_scanner.register_keyword("print");
            this->m_scanner.set_istream(in);
        }
        pfc::scanner m_scanner;

        //define the is_tb_ function here because this part of logic stays the same
        //for every (future) implementation of the parser
        //region Terminal Beginnings

        bool is_tb_program(){
            return is_tb_output() || is_tb_assignment();
        }
        bool is_tb_output(){
            return this->m_scanner.is_keyword("print");
        }
        bool is_tb_assignment(){
            return this->m_scanner.is_keyword("set");
        }
        bool is_tb_expression(){
            return is_tb_term();
        }
        bool is_tb_term(){
            return is_tb_factor();
        }
        bool is_tb_factor(){
            return is_tb_add_opp() || is_tb_u_factor();
        }
        bool is_tb_add_opp(){
            return this->m_scanner.is('+')|| this->m_scanner.is('-');
        }
        bool is_tb_mult_opp(){
            return this->m_scanner.is('*')|| this->m_scanner.is('/');
        }
        bool is_tb_u_factor(){
            return is_tb_monom() || is_tb_p_expression();
        }
        bool is_tb_p_expression(){
            return this->m_scanner.is('(');
        }
        bool is_tb_monom(){
            return is_tb_w_monom();
        }
        bool is_tb_w_monom(){
            return is_tb_identifier() || is_tb_real();
        }
        bool is_tb_identifier(){
            return this->m_scanner.is_identifier();
        }
        bool is_tb_real(){
            return this->m_scanner.is_number();
        }
        bool is_tb_exponent(){
            return this->m_scanner.is('^');
        }
        //endregion
    };

    class parse_syntax_tree : parser{
    public:
        //make use of base constructor
        parse_syntax_tree(std::istream& in): parser(in){
            nl = new NameListMap<SyntaxTree<double>*>();
        }
        //kick off the destructor chaining
        virtual ~parse_syntax_tree() override{
            delete nl;
        };
        void parse(std::ostream& out=cout)override{
            parse_program(out);
        }
        void print_name_list(std::ostream& out=cout){
            nl->print(out);
        }
    protected:
        NameList<SyntaxTree<double>*>*nl;
        void parse_program(std::ostream& out){
            //for every line / until end of file is reached parse program
            while(!this->m_scanner.is_eof()) {
                if (parser::is_tb_program()) {
                    if (parser::is_tb_assignment()) {
                        //check if beginning of assigment is correct
                        this->m_scanner.next_symbol("set");
                        this->m_scanner.next_symbol('(');

                        //get identifier
                        StdNodeIdent<double> *identifier = parse_identifier();

                        //check if seprated by ','
                        this->m_scanner.next_symbol(',');

                        //parse the expression as a tree and store it in the namelist
                        //so it can be used later
                        StNode<double> *expr = parse_expression();
                        SyntaxTree<double> *st = new SyntaxTree<double>(expr);
                        nl->register_var(identifier->get_identifier(), st);

                        //check if end of assignment is correct
                        this->m_scanner.next_symbol(')');
                        this->m_scanner.next_symbol(';');


                    } else {
                        //check if beginning of assigment is correct
                        this->m_scanner.next_symbol("print");
                        this->m_scanner.next_symbol('(');

                        StNode<double> *expr = parse_expression();
                        SyntaxTree<double> *st = new SyntaxTree<double>(expr);
                        //check if end of assignment is correct
                        this->m_scanner.next_symbol(')');
                        this->m_scanner.next_symbol(';');

                        //print the result of the expression
                        out << st->evaluate(nl)<<"\n";
                    }
                } else {
                    throw new parser_error("Error parsing 'program'");
                }
            }
        }
        StNode<double>* parse_expression(){
            if (is_tb_expression()){
                StNode<double>* left = parse_term();
                //expression consists of term addop term
                if (is_tb_add_opp()){
                    StNodeOperator<double>* root = parse_add_op();//operation is the root of the subtree
                    StNode<double>* right = parse_term();
                    root->set_left(left);//element that is read first is the left child
                    root->set_right(right); //second element is right child
                    return root;
                }
                //expression consists only of one term
                else{
                    return left;
                }
            }
            else{
                throw new parser_error("Error parsing 'expression'");
            }
        }
        StNode<double>* parse_term(){
            if (is_tb_term()){
                StNode<double>* left = parse_factor();
                //term consists of factor multop factor
                if (is_tb_mult_opp()){
                    StNodeOperator<double>* root = parse_mult_op();
                    StNode<double>* right = parse_factor();
                    root->set_left(left);
                    root->set_right(right);
                    return root;
                }
                //term consists only of one factor
                else{
                    return left;
                }
            }
            else {
                throw new parser_error("Error parsing 'term'");
            }
        }
        StNode<double>* parse_factor(){
            if (is_tb_factor()){
                if (is_tb_add_opp()){
                    //if addop is leading subtract from or add to 0 to achieve the desired value
                    StNode<double>* left = new StNodeValue<double>(0);
                    StNode<double>* root = parse_add_op();
                    StNode<double>* right = parse_u_factor();

                    root->set_left(left);
                    root->set_right(right);
                    return root;
                }
                else {
                    return parse_u_factor();
                }
            }
            else {
                throw new parser_error("Error parsing 'factor'");
            }
        }
        StNode<double>* parse_u_factor(){
            if (is_tb_u_factor()){
                return is_tb_monom() ?  parse_monom() :  parse_p_expression();
            }
            else {
                throw new parser_error("Error parsing 'u factor'");
            }
        }
        StNode<double>* parse_monom(){
            if (is_tb_monom()){
                StNode<double>* left = parse_w_monom();
                if (is_tb_exponent()){
                    //if exponent exists use the w_monom as the left child,
                    // the operation '^' as the root and the value as the right child
                    StNode<double>* root = parse_exponent();
                    root->set_left(left);
                    return root;
                }
                return left;
            }
            else{
                throw new parser_error("Error parsing 'monom'");
            }
        }
        StNode<double>* parse_w_monom(){
            if (is_tb_w_monom()){
                return is_tb_real() ? parse_real() : parse_identifier();
            }
            else {
                throw parser_error("Error parsing 'w monom");
            }
        }
        StNode<double>* parse_p_expression(){
            if (is_tb_p_expression()){
                this->m_scanner.next_symbol('(');
                StNode<double>* expr = parse_expression();
                this->m_scanner.next_symbol(')');
                return expr;
            }
            else {
                throw new parser_error("Error parsing 'p expression");
            }
        }
        StNode<double>* parse_real(bool is_neg = false){
            if (is_tb_real()){
                //if passed is_neg is true multiply the number by -1
                //because a number has to follow -> no need for 0 - expression (like factor)
                StNode<double>* real =  new StNodeValue<double>(!is_neg ? this->m_scanner.get_number() : this->m_scanner.get_number()*-1 );
                this->m_scanner.next_symbol();
                return real;
            }
            else {
                throw new parser_error("Error parsing 'real'");
            }
        }
        StNode<double>* parse_exponent(){
            if (is_tb_exponent()){
                //use the exponent sign as root
                StNode<double>* root = new StNodeOperator<double>(StNodeOperator<double>::EXP);
                this->m_scanner.next_symbol();
                bool is_neg = false;
                if (is_tb_add_opp()){
                    is_neg = this->m_scanner.is('-');
                    this->m_scanner.next_symbol();
                }
                //use the number as the right child
                //the left child of root is set in parse_monom
                StNode<double>* right = !is_neg ? parse_real(): parse_real(true);

                root->set_right(right);
                return root;
            }
            else {
                throw new parser_error("Error parsing 'exponent'");
            }
        }

        StdNodeIdent<double>* parse_identifier(){
            if (is_tb_identifier()){
                //create ident node (and don't return plain string) so
                // variables are checked when evaluating
                StdNodeIdent<double>* id = new StdNodeIdent<double>(this->m_scanner.get_identifier());
                this->m_scanner.next_symbol();
                return id;
            }
            else {
                throw new parser_error("Error parsing 'identifier'");
            }
        }
        StNodeOperator<double>* parse_add_op(){
            if (is_tb_add_opp()){
                //return correct operation node depending on the scanner
                StNodeOperator<double>* op;
                if (this->m_scanner.is('+')){
                    op = new StNodeOperator<double>(StNodeOperator<double>::ADD);
                }
                else {
                    op = new StNodeOperator<double>(StNodeOperator<double>::SUB);
                }
                this->m_scanner.next_symbol();
                return op;
            }
            else{
                throw new parser_error("Error parsing 'add op'");
            }
        }
        StNodeOperator<double>* parse_mult_op(){
            if (is_tb_mult_opp()){
                //return correct operation node depending on the scanner
                StNodeOperator<double>* op;
                if (this->m_scanner.is('*')){
                    op = new StNodeOperator<double>(StNodeOperator<double>::MUL);
                }
                else {
                    op = new StNodeOperator<double>(StNodeOperator<double>::DIV);
                }
                this->m_scanner.next_symbol();
                return op;
            }
            else{
                throw new parser_error("Error parsing 'mult op'");
            }
        }
    };
}

#endif //EXPRESSION_TREE_PARSER_H
