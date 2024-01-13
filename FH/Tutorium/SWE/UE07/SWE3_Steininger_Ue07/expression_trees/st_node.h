#ifndef EXPRESSION_TREE_ST_NODE_H
#define EXPRESSION_TREE_ST_NODE_H

#include "expr_exceptions.h"
#include "namelist.h"
#include "syntax_tree.h"
#include <iostream>
#include <cmath>
#include <string>

namespace xpr{
    struct division_by_zero : public std::exception{
        const char * what() const noexcept override{
            return "Division by Zero!";
        }
    };
    //Forward Declaration for resolving the circular dependency
    template<typename T>
    class SyntaxTree;

    class VariableNotFoundException : public std::exception{
    public:
        VariableNotFoundException(std::string _message):message(_message){}
        virtual const char * what() const noexcept override{
            return message.c_str();
        }
    private:
        std::string message;
    };


    template<typename T>
    class StNode{
    public:
        StNode() : p_left(nullptr), p_right(nullptr){}

        virtual ~StNode(){
            if(p_left!= nullptr){
                delete p_left;
                p_left = nullptr;
            }
            if(p_right != nullptr){
                delete p_right;
                p_right = nullptr;
            }
        }

        StNode<T>* const get_left() const{
            return p_left;
        }
        StNode<T>* const get_right() const{
            return p_right;
        }

        void set_left(StNode<T>* left) {
            p_left = left;
        }
        void set_right(StNode<T>* right) {
             p_right = right;
        }

        void print_pre_order(std::ostream & os){
            print(os);
            if(p_left != nullptr){
                this->get_left()->print(os);
            }
            if(p_right!= nullptr){
                this->get_right()->print(os);
            }
        }

        void print_in_order(std::ostream & os){
            if(p_left != nullptr){
                this->get_left()->print(os);
            }
            print(os);
            if(p_right!= nullptr){
                this->get_right()->print(os);
            }
        }

        void print_post_order(std::ostream & os){
            if(p_left != nullptr){
                this->get_left()->print(os);
            }
            if(p_right!= nullptr){
                this->get_right()->print(os);
            }
            print(os);
        }



        virtual T evaluate(NameList<SyntaxTree<T>*>* nameList) const = 0;
        virtual void print(std::ostream & os) const = 0;

    protected:
        StNode<T>* p_left{nullptr};
        StNode<T>* p_right{nullptr};

    };


    template<typename T>
    class StNodeValue : public StNode<T>{
    public:
        StNodeValue(T const & value) : value(value){}

        virtual T evaluate(NameList<SyntaxTree<T>*>* nameList) const override{
            return value;
        }

        virtual void print (std::ostream & os) const override{
            os << value<<" ";
        }
    private:
        T value;
    };

    template<typename T>
    class StNodeOperator : public StNode<T>{
    public:
        enum Operator{ ADD = 0, SUB, MUL, DIV, EXP};
        const std::string Operator_Str[5] = { "+","-","*","/","^"};
        //map mit operator als key und callables welche 2 parameter verwenden als value
        StNodeOperator(Operator op): op(op){}

        virtual T evaluate(NameList<SyntaxTree<T>*>* nameList) const override{
            StNode<T>* l = this->p_left;
            StNode<T>* r = this->p_right;

            switch (op) {
                case ADD:
                    return l->evaluate(nameList) + r->evaluate(nameList);
                case SUB:
                    return l->evaluate(nameList) - r->evaluate(nameList);
                case MUL:
                    return l->evaluate(nameList) * r->evaluate(nameList);
                case DIV:
                    if (r->evaluate(nameList)==0) throw new division_by_zero();
                    return l->evaluate(nameList) / r->evaluate(nameList);
                case EXP:
                    return std::pow(l->evaluate(nameList), r->evaluate(nameList));
                default:
                    throw EvaluationException();
            }
        }

        virtual void print (std::ostream & os) const override{
            os<< Operator_Str[op]<<" ";
        }


    private:
        Operator op;
    };

    template <typename T>
    class StdNodeIdent : public StNode<T>{
    public:
        StdNodeIdent(std::string const & _identifier): identifier(_identifier){}

        virtual T evaluate(NameList<SyntaxTree<T>*>* nameList)const override{
            SyntaxTree<T>* tree {nameList->lookup_var(identifier)};
            if (tree != nullptr){
                return tree->evaluate(nameList);
            }
            throw new VariableNotFoundException("Variable "+identifier+" was not found!");
        }
        virtual void print(std::ostream& out)const override{
            out << identifier<<" ";
        }
        std::string get_identifier() const{
            return identifier;
        }

    private:
        std::string identifier;
    };




}




#endif //EXPRESSION_TREE_ST_NODE_H
