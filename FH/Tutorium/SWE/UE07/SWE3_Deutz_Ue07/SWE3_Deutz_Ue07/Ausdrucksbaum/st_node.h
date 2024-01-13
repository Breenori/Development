#ifndef ST_NODE_H
#define ST_NODE_H

#include "name_list.h"

namespace xpr {

	// forward declaration for SyntaxTreeS
	template<typename T> class SyntaxTree;

	template<typename T> class StNode {
	public:
		StNode() : left(nullptr), right(nullptr) { }

		virtual ~StNode() {
			clear_node();
		}

		void set_left(StNode<T>* _left_) {
			left = _left_;
		}

		void set_right(StNode<T>* _right_) {
			right = _right_;
		}

		virtual T evaluate(NameList<SyntaxTree<T>*>* _name_list_)	const = 0;
		virtual std::ostream& print(std::ostream& _out_)			const = 0;

	protected:
		StNode<T>* left;
		StNode<T>* right;

	private:
		void clear_node() {
			if (left != nullptr) {
				delete left; left = nullptr;
			}
			if (right != nullptr) {
				delete right; right = nullptr;
			}
		}

	};

	template<typename T> class StNodeValue : public StNode<T> {
	public:
		StNodeValue(T const& _value_) : value(_value_) { }

		T evaluate(NameList<SyntaxTree<T>*>* _name_list_) const override {
			return value;
		}

		std::ostream& print(std::ostream& _out_) const override {
			print_value(_out_); return _out_;
		}

	private:
		T value;

		std::ostream& print_value(std::ostream& _out_) const {
			_out_ << value << " "; return _out_;
		}

	};

	template<typename T> class StNodeOperator : public StNode<T> {
	public:
		enum Operator { ADD = 0 , SUB , MUL , DIV , EXP };
		const std::string operator_str[5] = { "+" , "-" , "*" , "/" , "^" };

		StNodeOperator(Operator _op_) : op(_op_) { }

		T evaluate(NameList<SyntaxTree<T>*>* _name_list_) const override {
			T value = evaluate_op(_name_list_); return value;
		}

		std::ostream& print(std::ostream& _out_) const override {
			print_op(_out_); return _out_;
		}

	private:
		Operator op;

		T evaluate_op(NameList<SyntaxTree<T>*>* _name_list_) const {

			StNode<T>* l = this->left;
			StNode<T>* r = this->right;

			switch (op) {
			case ADD:
				return l->evaluate(_name_list_) + r->evaluate(_name_list_);
			case SUB:
				return l->evaluate(_name_list_) - r->evaluate(_name_list_);
			case MUL:
				return l->evaluate(_name_list_) * r->evaluate(_name_list_);
			case DIV:
				{T r_value = r->evaluate(_name_list_);

				if (r_value == 0.0)
					throw DivisionByZero();

				return l->evaluate(_name_list_) / r_value; }
			case EXP:
				return std::pow(l->evaluate(_name_list_), r->evaluate(_name_list_));
			default:
				throw EvaluationException("Error evaluating operator node!\n"); return 0.0;
			}

		}

		std::ostream& print_op(std::ostream& _out_) const {
			if (this->left != nullptr)
				this->left->print(_out_);
			_out_ << operator_str[op] << " ";
			if (this->right != nullptr)
				this->right->print(_out_);

			return _out_;
		}

	};

	template<typename T> class StNodeIdent : public StNode<T> {
	public:
		StNodeIdent(std::string const& _identifier_) : identifier(_identifier_){ }

		T evaluate(NameList<SyntaxTree<T>*>* _name_list_) const override {
			T value = evaluate_ident(_name_list_); return value;
		}

		std::ostream& print(std::ostream& _out_) const {
			print_ident(_out_); return _out_;
		}

	private:
		std::string identifier;

		T evaluate_ident(NameList<SyntaxTree<T>*>* _name_list_) const {
			SyntaxTree<T>* tree = _name_list_->lookup_var(identifier);

			if (tree != nullptr)
				return tree->evaluate(_name_list_);

			return 0.0;
		}

		std::ostream& print_ident(std::ostream& _out_) const{
			_out_ << identifier << " "; return _out_;
		}

	};

}

#endif // !ST_NODE_H