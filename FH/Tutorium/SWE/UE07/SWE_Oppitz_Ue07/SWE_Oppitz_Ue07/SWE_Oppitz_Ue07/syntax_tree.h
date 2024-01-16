#ifndef syntax_tree_h
#define syntax_tree_h

#include "st_node.h"
#include "expr_exceptions.h"

namespace xpr {
	template <typename T>
	class SyntaxTree {
	public:
		SyntaxTree(StNode<T>* root) : root(root) {}
		~SyntaxTree() {
			if (root) delete root;
		}

		T evaluate(NameList<SyntaxTree<T>*>* name_list ) {
			if (root == nullptr) {
				throw EvaluationException();
			}
			return root->evaluate(name_list);
		}

		//print_tree() {
		//	//todo

		//}

		//T evaluate() {
		//	if (root == nullptr) {
		//		throw EvaluationException();
		//	}
		//	return root->evaluate();
		//}

		friend std::ostream& operator<<(std::ostream& out, SyntaxTree<T> const* rhs) {
			rhs->print(out);
			return out;
		}
	private:
		StNode<T>* root;

		void print(std::ostream& out) const {
			if (!root) {
				throw EvaluationException();
			}
			else {
				out << "Print tree in pre-order notation: ";
				root->print_pre_order(out);
				out << "\nPrint tree in in-order notation: ";
				root->print_in_order(out);
				out << "\nPrint tree in post-order notation: ";
				root->print_post_order(out);
			}
		}
	};
}

#endif // !syntax_tree_h
