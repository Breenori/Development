#pragma once
#ifndef EXPRESSION_TREE_SYNTAX_TREE_H
#define EXPRESSION_TREE_SYNTAX_TREE_H

#include"st_node.h"
#include"expr_exceptions.h"
#include "namelist.h"
#include <iomanip>
#include <queue>

using std::queue;
using std::setw;

namespace xpr{

    template<typename T>
    class SyntaxTree{
    public:
        SyntaxTree(StNode<T>* root):root(root){}

        ~SyntaxTree(){
            if (root != nullptr){
                delete root;
            }
        }

        T evaluate( NameList<SyntaxTree<T>*>* nameList){
            if (root == nullptr){
                throw EvaluationException();
            }
            return root->evaluate(nameList);
        }

        friend std::ostream & operator <<(std::ostream & lhs, SyntaxTree<T> const * rhs){
            rhs->print_side_ways(lhs);
            return lhs;
        }

    private:
        StNode<T>* root;
        std::ostream& print_side_ways(std::ostream & os)const{
            if(root==nullptr){
                throw EvaluationException();
            }
            else{
                return print_side_ways_recursive(root, os);
            }

        }
        std::ostream & print_side_ways_recursive(StNode<T>* p_head,  std::ostream& out, size_t level = 0)const{
            if (p_head != nullptr){
                print_side_ways_recursive(p_head->get_right(), out, level+1);
                out<<"\n"<<setw(5*level)<<" ";
                p_head->print(out);
                print_side_ways_recursive(p_head->get_left(), out, level+1);
            }
            return out;
        }
    };



}

#endif //EXPRESSION_TREE_SYNTAX_TREE_H
