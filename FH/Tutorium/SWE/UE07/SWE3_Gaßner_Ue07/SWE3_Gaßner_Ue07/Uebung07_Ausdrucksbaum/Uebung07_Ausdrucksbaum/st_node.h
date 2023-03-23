#ifndef st_node_h
#define st_node_h

#include "expr_excepiton.h"
#include "name_list.h"
#include "syntax_tree.h"
#include <iostream>
#include <cmath>

// alle klassen in dieser h-datei

namespace xpr {

	// forward declaration
	template<typename T>
	class SyntaxTree;

	template<typename T>
	class StNode {
	public:
		StNode() : left(nullptr), right(nullptr) {}
		virtual ~StNode() { // dynamisch, sodass kinder auch darauf zugreifen können
			if (left != nullptr) {
				delete left;
			}
			if (right != nullptr) {
				delete right;
			}
		}

		StNode<T>* const get_left() const {
			return this->left;
		}
		StNode<T>* const get_right() const {
			return this->right;
		}
		void set_left(StNode<T>* right) {
			this->right = right;
		}
		void set_right(StNode<T>* left) { this->left = left; }

		void print_preorder(std::ostream& os) {
			print(os);
			if (left != nullptr) {
				left->print_preorder(os);
			}
			if (right != nullptr) {
				right->print_preorder(os);
			}
		}

		void print_inorder(std::ostream& os) {

			if (left != nullptr) {
				left->print_preorder(os);
			}
			print(os);
			if (right != nullptr) {
				right->print_preorder(os);
			}
		}

		void print_postorder(std::ostream& os) {
			if (left != nullptr) {
				left->print_preorder(os);
			}
			if (right != nullptr) {
				right->print_preorder(os);
			}
			print(os);

		}

		


		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const = 0;
		virtual void print(std::ostream& os) const = 0;

	protected:
		StNode<T>* left{ nullptr };
		StNode<T>* right{ nullptr };

	};

	template <typename T>
	class StNodeValue : public StNode<T> {

	public:
		StNodeValue(T const& value) : value(value) {}
		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list)const override {
			return value;
		}

		virtual void print(std::ostream& os) const override {
			os << value << " ";
		}


	private:
		T value;
	};

	template <typename T>
	class StNodeOperator : public StNode<T> {

	public:
		enum Operator { ADD = 0, SUB, MUL, DIV, EXP }; // liste mit möglichen operatoren
		const std::string Operator_Str[5] = { "+", "-", "*", "/", "^" }; // Array
		StNodeOperator(Operator op) : op(op) {}
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
				return l->evaluate(name_list) / r->evaluate(name_list);
			}
			else if (op == EXP) {
				return std::pow(l->evaluate(name_list), r->evaluate(name_list));
			}
			else {
				throw EvaluationException();
			}

		}
		virtual void print(std::ostream& os) const override {
			os << Operator_Str[op] << " ";
		}


	private:
		Operator op;
	};

	template<typename T>
	class StNodeIdent : public StNode<T> {
	public:
		StNodeIdent(std::string const& identifier) : identifier(identifier) {

		}

		// return {}; lässt kompilieren obwohl Auswertung fehlt
		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {
			SyntaxTree<T>* tree{ name_list->lookup_var(identifier) };
			if (tree != nullptr) {
				return tree->evaluate(name_list);
			}
			throw new VariableNotFoundException("Variable" + identifier + "was not defined.");
		}

		virtual void print(std::ostream& os) const override {
			os << identifier << " ";
		}


	private:
		std::string identifier;
	};



}



#endif // !st_node_h
