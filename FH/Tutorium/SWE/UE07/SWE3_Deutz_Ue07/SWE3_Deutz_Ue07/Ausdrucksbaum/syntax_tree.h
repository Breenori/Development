#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "st_node.h"
#include "name_list.h"

namespace xpr {

	template<typename T> class SyntaxTree {
	public:
		SyntaxTree() : root(nullptr) { }
		SyntaxTree(StNode<T>* _root_) : root(_root_) { }

		~SyntaxTree() {
			clear_tree();
		}

		T evaluate(NameList<SyntaxTree<T>*>* _name_list_) {
			T result = evaluate_tree(_name_list_); return result;
		}

		void set_root(StNode<T>* _node_) {
			if (root != nullptr)
				delete root;

			root = _node_;
		}

		std::ostream& print(std::ostream& _out_) const {
			print_tree(_out_); return _out_;
		}

		friend std::ostream& operator<<(std::ostream& _left_, SyntaxTree<T> const* _right_) {
			_right_->print(_left_); return _left_; 
		}

	private:
		StNode<T>* root = nullptr;

		void clear_tree() {
			if (root != nullptr) {
				delete root;
				root = nullptr;
			}
		}

		T evaluate_tree(NameList<SyntaxTree<T>*>* _name_list_) {
			if (root == nullptr)
				throw EvaluationException("Error evaluating tree!\n");

			return root->evaluate(_name_list_);
		}

		std::ostream& print_tree(std::ostream& _out_) const {
			if (root == nullptr)
				throw EvaluationException("Error printing tree!\n");

			root->print(_out_); return _out_;
		}

	};

}

#endif // !SYNTAX_TREE_H