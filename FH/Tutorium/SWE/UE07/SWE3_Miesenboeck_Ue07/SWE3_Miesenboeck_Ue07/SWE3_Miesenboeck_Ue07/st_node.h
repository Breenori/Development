#pragma once

#include "expr_exceptions.h"
#include "name_list.h"
#include<iostream>
#include <cmath>



namespace xpr
{

	//forward declaration
	template<typename T>
	class syntax_tree;

	template<typename T>
	class st_node
	{
	public:

		// CONSTRUCTOR
		st_node() :left(nullptr), right(nullptr)
		{

		}

		// DESTRUCTOR
		virtual ~st_node()
		{
			// delete left node
			if (left != nullptr)
			{
				delete left;
			}

			// delete right node
			if (right != nullptr)
			{
				delete right;
			}
		}

		st_node<T>* const get_left() const
		{
			return left;
		}

		st_node<T>* const get_right() const
		{
			return right;
		}

		void set_left(st_node<T>* left)
		{
			this->left = left;
		}

		void set_right(st_node<T>* right)
		{
			this->right = right;
		}

		// recursive fctn to print in pre-order notation
		void print_pre_order(std::ostream& os) const
		{
			// print before calling fctn recursively for left and right node
			print(os);
			os << " ";
			if (left != nullptr)
			{
				left->print_pre_order(os);
			}
			if (right != nullptr)
			{
				right->print_pre_order(os);
			}
		}

		// recursive fctn to print in in-order notation
		void print_in_order(std::ostream& os) const
		{
			if (left != nullptr)
			{
				left->print_in_order(os);
			}
			// print before calling fctn recursively for right node
			print(os);
			os << " ";
			if (right != nullptr)
			{
				right->print_in_order(os);
			}
		}

		// recursive fctn to print in post-order notation
		void print_post_order(std::ostream& os) const
		{
			if (left != nullptr)
			{
				left->print_post_order(os);
			}
			if (right != nullptr)
			{
				right->print_post_order(os);
			}
			// print after calling fctn recursively for right and left node
			print(os);
			os << " ";
		}

		// pure virtual fctns
		virtual T evaluate(name_list<syntax_tree<T>*>* name_list) const = 0;
		virtual void print(std::ostream& os) const = 0;

	protected:
		// left node
		st_node<T>* left{ nullptr };

		// right node
		st_node<T>* right{ nullptr };

	};


	// value node --> holds value
	template<typename T>
	class st_node_value :public st_node<T>
	{
	public:

		// CONSTRUCTOR
		st_node_value(T const& value_) :value(value_)
		{

		}

		// evaluate --> return value of node
		virtual T evaluate(name_list<syntax_tree<T>*>* name_list) const override
		{
			return value;
		}

		// print --> print value to stream
		virtual void print(std::ostream& os) const override
		{
			os << value;
		}

	private:
		// node-value
		T value;
	};


	// operator node --> holds operator
	template<typename T>
	class st_node_operator :public st_node<T>
	{
	public:

		// enum with possible operatos
		enum Operator { ADD = 0, SUB, MUL, DIV, EXP };

		// operator-string
		const std::string Operator_Str[5] = { "+","-","*","/","^" };

		// CONSTRUCTOR
		st_node_operator(Operator op_) :op(op_)
		{

		}

		// evaluate --> call evaluate for left and right node and perform operation on results
		virtual T evaluate(name_list<syntax_tree<T>*>* name_list) const override
		{
			st_node<T>* l = this->left;
			st_node<T>* r = this->right;

			if (op == ADD)
			{
				return l->evaluate(name_list) + r->evaluate(name_list);
			}
			else if (op == SUB)
			{
				return l->evaluate(name_list) - r->evaluate(name_list);
			}
			else if (op == MUL)
			{
				return l->evaluate(name_list) * r->evaluate(name_list);
			}
			else if (op == DIV)
			{
				// if right node evaluates to 0 --> throw excp
				if(r->evaluate(name_list) == 0)
				{
					throw DivByZeroException("ERROR: Division by Zero.");
				}
				return l->evaluate(name_list) / r->evaluate(name_list);
			}
			else if (op == EXP)
			{
				return pow(l->evaluate(name_list), r->evaluate(name_list));
			}
			// other operator --> throw excp
			else {
				throw EvaluationException();
			}
		}

		virtual void print(std::ostream& os) const override
		{
			// print corresponding operator
			os << Operator_Str[op];
		}

	private:
		// node-operator
		Operator op;

	};


	// identity node --> holds identity
	template<typename T>
	class st_node_ident : public st_node<T>
	{

	public:

		// CONSTRUCTOR
		st_node_ident(std::string const& identifier_) :identifier(identifier_) {}

		// evaluate --> lookup identifier in name_list, evaluate and return value
		virtual T evaluate(name_list<syntax_tree<T>*>* name_list) const override
		{
			// lookup identifier in name_list
			syntax_tree<T>* tree{ name_list->lookup_var(identifier) };
			if (tree != nullptr)
			{
				// evaluate tree
				return tree->evaluate(name_list);
			}
			// variable is not defined --> throw excp
			throw VariableNotFoundException("ERROR: Variable " + identifier + " was not defined.");
		}

		virtual void print(std::ostream& os) const override
		{
			// print identifier
			os << identifier;
		}


	private:
		// node-identifier
		std::string identifier;

	};

}