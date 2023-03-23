#ifndef st_node_h
#define st_node_h

#include "expr_exceptions.h"
#include "name_list.h"
#include "syntax_tree.h"
#include <iostream>
#include <cmath>

namespace xpr {
	//forward declaration 
	template <typename T>
	class SyntaxTree;

	template <typename T>
	class StNode {
	public:
		StNode() :left(nullptr), right(nullptr) {

		}
		virtual ~StNode() {
			if (left != nullptr) {
				delete left;
			}
			if (right) {
				delete right;
			}
		}

		//T const get_value() const {
		//	return this->value;
		//}

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
		virtual void print(std::ostream& os) const = 0;
		virtual void print_pre_order(std::ostream& out) const {
			print(out);
			if (left) left->print_pre_order(out);
			if (right) right->print_pre_order(out);
		}
		virtual void print_in_order(std::ostream& out) const {
			if (left) left->print_in_order(out);
			print(out);
			if (right) right->print_in_order(out);
		}
		virtual void print_post_order(std::ostream& out) const {
			if (left) left->print_post_order(out);
			if (right) right->print_post_order(out);
			print(out);
		}

	protected:
		StNode<T>* left{ nullptr };
		StNode<T>* right{ nullptr };
	};

	template <typename T>
	class StNodeValue :public StNode<T> {
	public:
		StNodeValue(T const& value) : value(value) {}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {
			return value;
		}

		virtual void print(std::ostream& os) const override {
			os << value << " ";
		}
	private:
		T value;
	};

	template <typename T>
	class StNodeOperator :public StNode<T> {
	public:
		enum Operator { ADD = 0, SUB, MUL, DIV, EXP };
		const std::string Operator_Str[5] = { "+", "-", "*", "/", "^" };

		StNodeOperator(Operator const& op) : op(op) {}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {
			StNode<T>* l = this->left;
			StNode<T>* r = this->right;

			switch (op)
			{
			case ADD:
				return l->evaluate(name_list) + r->evaluate(name_list);
			case SUB:
				return l->evaluate(name_list) - r->evaluate(name_list);
			case MUL:
				return l->evaluate(name_list) * r->evaluate(name_list);
			case DIV:
				return l->evaluate(name_list) / r->evaluate(name_list);
			case EXP:
				return std::pow(l->evaluate(name_list), r->evaluate(name_list));
			default:
				throw EvaluationException(); // can't happen
			}
		}

		virtual void print(std::ostream& os) const override {
			os << Operator_Str[op] << " ";
		}
	private:
		Operator op;
	};

	template<typename T>
		class StNodeIndent {
		public:
			StNodeIndent(std::string const& indentifier): identifier(indentifier){}

			virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {
				SyntaxTree<T>* tree{ name_list->lookup_var(identifier) };
				if (tree != nullptr) {
					return tree->evaluate(name_list);
				}
				throw new VariableNotFoundException("Variable " + identifier + " was not defined.");

			}

			virtual void print(std::ostream& os) const override{
				os << identifier << " ";
			}

		private:
			std::string identifier;

	};







}

#endif // st_node_h
