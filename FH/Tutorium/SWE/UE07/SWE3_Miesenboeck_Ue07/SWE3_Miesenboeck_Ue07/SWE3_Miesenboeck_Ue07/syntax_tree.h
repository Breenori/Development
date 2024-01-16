#pragma once

#include "st_node.h"
#include "expr_exceptions.h"
#include <iomanip>
#include <vector>

using std::setw;
using std::endl;
using std::vector;

namespace globals
{
	int constexpr DEPTH_START(0);
	int constexpr SETW_ENHANCER_2D(6);
	int constexpr  SETW_ENHANCER_2D_UPRIGHT(4);

}

namespace xpr
{
	

	template<typename T>
	class syntax_tree
	{
	public:

		// CONSTRUCTOR

		syntax_tree(st_node<T>* root) :root(root)
		{

		}

		// DESTRUCTOR

		~syntax_tree()
		{
			if (root != nullptr)
			{
				delete root;
			}
		}


		// evaluate syntax tree and return result
		T evaluate(name_list<syntax_tree<T>*>* name_list)
		{
			// throw excp if root is nullptr
			if (root == nullptr)
			{
				throw EvaluationException();
			}
			return root->evaluate(name_list);
		}

		// overload yy operator for output
		friend std::ostream& operator<<(std::ostream& lhs, syntax_tree<T> const* rhs)
		{
			rhs->print(lhs);
			return lhs;
		}

		// print in pre order notation
		void print_pre_order(std::ostream& os = std::cout) const
		{
			if (root == nullptr)
			{
				throw EvaluationException();
			}
			else
			{
				os << "pre-order: ";
				root->print_pre_order(os);
			}
		}

		// print in post order notation
		void print_post_order(std::ostream& os = std::cout) const
		{
			if (root == nullptr)
			{
				throw EvaluationException();
			}
			else
			{
				os << "post-order: ";
				root->print_post_order(os);
			}
		}

		// print in 2d view
		std::ostream& print_2d(std::ostream& out = std::cout) {

			if (root == nullptr) {
				throw EvaluationException();
			}

			// call recursive fctn
			else {
				print_2d_recursive(out, root, globals::DEPTH_START);
			}

			return out;
		}


		// print in 2d upright view
		std::ostream& print_2d_upright(std::ostream& out = std::cout) {

			if (root == nullptr) {
				throw EvaluationException();


			}

			else{

				vector < vector<st_node<T>*>> matrix(create_matrix()); //generate matrix containing all nodes and possible nodes

				int max_depth(this->depth());

				vector<int> offset_vec; //saves offset for every layer (reversed!)
				int offset_value(globals::SETW_ENHANCER_2D_UPRIGHT); //start value higher for better optic

				for (int i(0); i < max_depth; ++i) { //generate offset table for rows
					offset_vec.push_back(offset_value);
					offset_value = offset_value * 2;
				}

				for (int i(0); i < matrix.size(); ++i) { //every row

					for (int j(0); j < matrix[i].size(); ++j) { //every column

						if (matrix[i][j] != nullptr) { //node exists, output payload
							if (j == 0) { //first node of row - only half offset
								out << setw((offset_vec[max_depth - (i + 1)]) / 2);
								matrix[i][j]->print(out); //output payload with correct offset for row
							}
							else { //offset between nodes
								out << setw(offset_vec[max_depth - (i + 1)]);
								matrix[i][j]->print(out); //output payload with correct offset for row
							}
						}
						else {
							if (j == 0) { //first node of row - only half offset
								out << setw((offset_vec[max_depth - (i + 1)]) / 2) << ""; //output payload with correct offset for row
							}
							else { //offset between nodes
								out << setw(offset_vec[max_depth - (i + 1)]) << ""; //output payload with correct offset for row
							}
						}
					}

					std::cout << endl; //new line

				}
			}

			return out;

		}


	private:
		st_node<T>* root;

		// private print fctn for operator overloading
		void print(std::ostream& os) const
		{
			if (root == nullptr)
			{
				throw EvaluationException();
			}
			else
			{
				root->print_in_order(os);
			}
		}

		// needed for print 2d upright
		vector<vector<st_node<T>*>> create_matrix() {

			vector<vector<st_node<T>*>> matrix(this->depth()); //create empty matrix with correct depth
			create_matrix_recursive(this->root, matrix, globals::DEPTH_START, this->depth()); // call recursive fctn
			return matrix;

		}

		void create_matrix_recursive(st_node<T>* current_node, vector<vector<st_node<T>*>>& matrix, int const depth, int const max_depth) {

			if (depth < max_depth) { //needed for end of recursive function

				matrix[depth].push_back(current_node); //also stores nullptrs!!!
				if (current_node != nullptr) { //node exists

					create_matrix_recursive(current_node->get_left(), matrix, depth + 1, max_depth);
					create_matrix_recursive(current_node->get_right(), matrix, depth + 1, max_depth);

				}
				else { //needed so that everywhere there could be a node is in matrix
					create_matrix_recursive(nullptr, matrix, depth + 1, max_depth);
					create_matrix_recursive(nullptr, matrix, depth + 1, max_depth);
				}
			}

		}

		// needed for print 2d upright
		size_t depth() {
			int depth_max(globals::DEPTH_START);
			depth_recursive(this->root, globals::DEPTH_START, depth_max);
			return depth_max + 1; //+1 because of p_head
		}

		void depth_recursive(st_node<T>* current_node, int const depth, int& depth_max) {

			if (current_node != nullptr) {
				depth_recursive(current_node->get_left(), depth + 1, depth_max); //left node

				if (depth > depth_max) {
					depth_max = depth; //depth check
				}

				depth_recursive(current_node->get_right(), depth + 1, depth_max); //right node

			}

		}

		// recursive fctn for print 2d
		std::ostream& print_2d_recursive(std::ostream& out, st_node<T>* current_node, int const depth) {

			if (current_node != nullptr) {

				print_2d_recursive(out, current_node->get_right(), depth + 1); //print right nodes at top

				out << setw(depth * globals::SETW_ENHANCER_2D);
				current_node->print(out);
				out << endl; //print payload

				print_2d_recursive(out, current_node->get_left(), depth + 1); //print left nodes at bottom

			}

			return out;
		}

	};
}