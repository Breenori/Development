#ifndef ST_NODE
#define ST_NODE

#include "expr_exceptions.h"
#include "name_list.h"
#include "syntax_tree.h"
#include <iostream>
#include <cmath>

namespace xpr {

	// forward declaration
	template<typename T>
	class SyntaxTree;

	template<typename T>
	class StNode {
	public:
		StNode() : left(nullptr), right(nullptr) { }
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

		void print_pre_order(std::ostream& os) {
			print(os);
			if (left != nullptr) {
				left->print_pre_order(os);
			}
			if (right != nullptr) {
				right->print_pre_order(os);
			}
		}

		void print_in_order(std::ostream& os) {
			if (left != nullptr) {
				left->print_in_order(os);
			}
			print(os);
			if (right != nullptr) {
				right->print_in_order(os);
			}
		}

		void print_post_order(std::ostream& os) {
			if (left != nullptr) {
				left->print_post_order(os);
			}
			if (right != nullptr) {
				right->print_post_order(os);
			}
			print(os);
		}

		std::ostream& print_horizontally(std::ostream& os) {
			// calling up helper function with shift = 10 (10 spaces)
			print_horizontally_rec(os, this, 10);
			os << "\n";
			return os;
		}

		std::ostream& print_horizontally_rec(std::ostream& os, StNode* const current, int shift) {
			if (current != nullptr) {
				// adding up to shift
				shift += 10;
				// going through the right side first as these are the values printed first (first row)
				print_horizontally_rec(os, current->right, shift);
				// printing out shift
				for (int i = 10; i < shift; i++)
				{
					os << " ";
				}
				current->print(os);
				// going down one line
				os << "\n";
				print_horizontally_rec(os, current->left, shift);
			}
			return os;
		}

		std::ostream& print_vertically(std::ostream& os) {
			// getting height (number of levels/stages) of tree
			int height = get_height(this);
			int count = height;
			// going through all the levels
			for (int i = 0; i <= height; i++)
			{
				// putting some space at the beginning
				for (int i = 0; i < count; i++)
				{
					os << " ";
				}
				// printing out level by level
				print_vertically_rec(os, this, i);
				os << "\n";
				// decrease space inbetween for next call
				count--;
			}
			os << "\n";
			return os;
		}

		int get_height(StNode* const current) const {
			if (current != nullptr) {
				int height_left = get_height(current->left);
				int height_right = get_height(current->right);

				// returning bigger height
				if (height_left > height_right) {
					return (height_left + 1);
				}
				else {
					return (height_right + 1);
				}
			}
			else {
				return 0;
			}
		}

		std::ostream& print_vertically_rec(std::ostream& os, StNode* const current, int level) const {
			// printing out one single level
			if (current != nullptr) {
				if (level == 1) {
					current->print(os);
				}
				else if (level > 1) {
					print_vertically_rec(os, current->left, level - 1);
					print_vertically_rec(os, current->right, level - 1);
				}
			}
			return os;
		}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const = 0;
		virtual void print(std::ostream& os) const = 0;

	protected:
		StNode<T>* left{ nullptr };
		StNode<T>* right{ nullptr };
	};


	template<typename T>
	class StNodeValue : public StNode<T> {
	public:
		StNodeValue(T const& value) : value(value) { }

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {
			return value;
		}
		virtual void print(std::ostream& os) const override {
			os << value << " ";
		}

	private:
		T value;
	};


	template<typename T>
	class StNodeOperator : public StNode<T> {
	public:
		enum Operator {ADD = 0, SUB, MUL, DIV, EXP};
		const std::string Operator_Str[5] = { "+", "-", "*", "/", "^" };

		StNodeOperator(Operator op) : op(op) { }

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
		StNodeIdent(std::string const& identifier) : identifier(identifier) {}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {
			SyntaxTree<T>* tree{ name_list->lookup_var(identifier) };
			if (tree != nullptr) {
				return tree->evaluate(name_list);
			}
			throw new VariableNotFoundException("Variable " + identifier + " was not defined.");
		}
		virtual void print(std::ostream& os) const override {
			os << identifier << " ";
		}

	private:
		std::string identifier;
	};

}

#endif