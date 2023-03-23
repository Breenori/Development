#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "st_node.h"
#include "expr_exceptions.h"

namespace xpr {

	template<typename T>
	class SyntaxTree {
	public:
		SyntaxTree(StNode<T>* root) : root(root) { }
		~SyntaxTree() {
			if (root != nullptr) {
				delete root;
			}
		}
		// pointer to namelist which contains pointer on syntaxtree which contains pointers of type T
		T evaluate(NameList<SyntaxTree<T>*>* name_list) {
			if (root == nullptr) {
				throw EvaluationException();
			}
			return root->evaluate(name_list);
		}

		friend std::ostream& operator<<(std::ostream& lhs, SyntaxTree<T> const* rhs) {
			rhs->print(lhs);
			return lhs;
		}

		std::ostream& print_horizontally(std::ostream& os = std::cout) const {
			if (root == nullptr) {
				throw EvaluationException();
			}
			else {
				os << "\nPrint tree in 2D (horizontally): \n";
				root->print_horizontally(os);
			}
		}

		std::ostream& print_vertically(std::ostream& os = std::cout) const {
			if (root == nullptr) {
				throw EvaluationException();
			}
			else {
				os << "\nPrint tree in 2D (vertically): \n";
				root->print_vertically(os);
			}
		}

	private:
		StNode<T>* root;

		void print(std::ostream& os) const {
			if (root == nullptr) {
				throw EvaluationException();
			}
			else {
				os << "Print tree in pre-order notation: ";
				root->print_pre_order(os);
				os << "\nPrint tree in in-order notation: ";
				root->print_in_order(os);
				os << "\nPrint tree in post-order notation: ";
				root->print_post_order(os);
			}
		}
	};

}

#endif