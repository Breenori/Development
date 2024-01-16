#ifndef syntax_tree_h
#define syntax_tree_h

#include "st_node.h"
#include "expr_excepiton.h"
#include <vector>
#include <iomanip>

namespace xpr {

	template<typename T>
	class SyntaxTree {

	public:
		SyntaxTree(StNode<T>* root) : root(root) {}
		~SyntaxTree() {
			if (root != nullptr) {
				delete root;
			}
		}

		T evaluate(NameList<SyntaxTree<T>*>* name_list) {
			if (root == nullptr) {
				throw EvaluationException();
			}
			return root->evaluate(name_list);
		}

		friend std::ostream& operator << (std::ostream& lhs, SyntaxTree<T> const* rhs) {
			rhs->print(lhs);
			return lhs;
		}

		void print_2d_upright(std::ostream& os) const {
			if (root == nullptr) {
				throw EvaluationException();
			}
			
			size_t height = get_height();

			for (int i = 1; i <= height; ++i) {
				print_2d_upright_rec(os, root, i, height);
				os << '\n';
			}
		}

		void print_2d(std::ostream& os) const {
			if (root == nullptr) {
				throw EvaluationException();
			}
			else {
				size_t depth = 0;
				print_2d_rec(os, root, depth);
			}
		}


	private:
		StNode<T>* root;
		void print(std::ostream& out) const {
			if (root == nullptr) {
				throw EvaluationException();
			}
			else {
				out << "Print tree in pre-order notation: ";
				root->print_preorder(out);
				out << "\n";
				out << "Print tree in in-order notation: ";
				root->print_inorder(out);
				out << "\n";
				out << "Print tree in post-order notation: ";
				root->print_postorder(out);
				out << "\n";
			}
		}

		void print_2d_rec(std::ostream& os, StNode<T>* current_node, size_t depth) const {
			if (current_node) {
				print_2d_rec(os, current_node->get_right(), depth + 1); // R
				os << std::setw(depth * 6); current_node->print(os); // M
				os << "\n";
				print_2d_rec(os, current_node->get_left(), depth + 1); // L
			}
		}

		void print_2d_upright_rec(std::ostream& os, StNode<T>* current_node, int level, size_t height) const {
			std::vector<StNode<T>*> nodes;
			nodes.push_back(current_node);
			int current_level = 1;

			while (!nodes.empty()) {
				std::vector<StNode<T>*> next_level_nodes;

				for (const auto& node : nodes) {
					if (node) {
						if (current_level == level) {
							os << std::setw(height * 3);
							node->print(os); os << "   ";
						}
						else {
							next_level_nodes.push_back(node->get_left());
							next_level_nodes.push_back(node->get_right());
						}
					}
				}
				nodes = next_level_nodes;
				++current_level;
			}
		}

		size_t get_height() const {
			return get_height_rec(root);
		}

		size_t get_height_rec(StNode<T>* current_node) const {
			if (!current_node) {
				return 0;
			}
			size_t left_tree_height = get_height_rec(current_node->get_left());
			size_t right_tree_height = get_height_rec(current_node->get_right());
			return std::max(left_tree_height, right_tree_height) + 1;
		}
	};


}


#endif // !syntax_tree_h
