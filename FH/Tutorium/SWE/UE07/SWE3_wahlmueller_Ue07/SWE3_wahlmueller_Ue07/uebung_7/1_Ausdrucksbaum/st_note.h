#ifndef ST_NOTE_H
#define ST_NOTE_H

#include <iostream>
#include <cmath>

#include <string>
#include "expr_exceptions.h"

#include "name_list.h"
#include "syntax_tree.h"

using std::ostream;
using std::string;

using std::pow;

namespace xpr {

	//forword declaration
	template<typename T>
	class SyntaxTree;

	//abstracte class
	template<typename T>
	class StNode{
	public:
		StNode() : left{ nullptr }, right{ nullptr } {}

		virtual ~StNode() {

			if (left != nullptr) {

				delete left;

			}

			if (right != nullptr) {

				delete right;

			}

		}

		StNode<T>* const get_left() const {

			return left;

		}

		StNode<T>* const get_right() const {

			return right;

		}

		void set_left(StNode<T>* left) {

			this->left = left;

		}

		void set_right(StNode<T>* right) {

			this->right = right;

		}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const = 0;
		virtual void print(ostream& os) const = 0;

		void print_pre_order(ostream& os) {//wlr - Präfix

			//w
			print(os);

			//l
			if (left != nullptr) {

				left->print_pre_order(os);

			}

			//r
			if (right != nullptr) {

				right->print_pre_order(os);

			}

		}

		void print_in_order(ostream& os) {//lwr - Infix

			//l
			if (left != nullptr) {

				left->print_in_order(os);

			}

			//w
			print(os);

			//r
			if (right != nullptr) {

				right->print_in_order(os);

			}

		}

		void print_post_order(ostream& os) {//lrw - Postfix

			//l
			if (left != nullptr) {

				left->print_post_order(os);

			}

			//r
			if (right != nullptr) {

				right->print_post_order(os);

			}

			//w
			print(os);

		}

	//so child class can access it too
	//also children secured if the class changes
	protected:
		StNode<T>* left{ nullptr };
		StNode<T>* right{ nullptr };

	};

	template <typename T>
	class StNodeValue: public StNode<T> {
	public:
		StNodeValue(T const& value): value(value){}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {

			return value;

		}

		virtual void print(ostream& os) const override {

			os << value << " ";

		}

	private:
		T value;

	};

	template <typename T>
	class StNodeOp: public StNode<T>{
	public:
		enum Operator{ADD = 0, SUB, MUL, DIV, EXP};
		const string Operator_str[5] = { "+", "-", "*", "/", "^" };

		StNodeOp(Operator op):op(op){}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {

			StNode<T>* l = this->left;
			StNode<T>* r = this->right;

			if (op == ADD) {

				return l->evaluate(name_list) + r->evaluate(name_list);

			}

			else if (op == SUB) {

				return l->evaluate(name_list) - r->evaluate(name_list);

			}

			else if (op == MUL) {

				return l->evaluate(name_list) * r->evaluate(name_list);

			}

			else if (op == DIV) {

				//check if div by zero
				T const temp = r->evaluate(name_list);
				if (temp == 0) {

					throw div_by_zero_error();

				}

				return l->evaluate(name_list) / temp;

			}

			else if (op == EXP) {

				return pow(l->evaluate(name_list), r->evaluate(name_list));

			}

			else {

				throw EvaluationException();

			}

		}

		virtual void print(ostream& os) const override {

			os << Operator_str[op] << " ";

		}

	private:
		Operator op;

	};

	template<typename T>
	class StNodeIdent: public StNode<T>{
	public:
		StNodeIdent(string const& identifier) :identifier(identifier) {};
		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list)const override {

			SyntaxTree<T>* tree{ name_list->lookup_var(identifier) };

			if (tree != nullptr) {

				return tree->evaluate(name_list);

			}

			else{

				throw new VariableNotFoundException("Variablen " + identifier + " was not definde.");

			}

		}

		virtual void print(ostream& os) const override{

			os << identifier << " ";

		}

	private:
		string identifier;

	};

};


#endif