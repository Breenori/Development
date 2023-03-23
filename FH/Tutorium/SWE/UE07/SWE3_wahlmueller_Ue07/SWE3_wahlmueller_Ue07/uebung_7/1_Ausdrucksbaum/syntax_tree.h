#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "st_note.h"
#include "expr_exceptions.h"

#include <iomanip>
#include <vector>

#include <sstream>

using std::vector;
using std::string;

using std::setw;
using std::pow;

using std::reverse;
using std::stringstream;

using std::copy;
using std::ostream_iterator;

using std::cout;

namespace xpr {

	template<typename T>
	class SyntaxTree: public StNode<T>{
	private:
		StNode<T>* root;
		using formvec = vector<vector<string>>;

		//depth for 2d print
		int get_depth() const {

			int depth{ 1 };
			get_depth_rec(root, 1, depth);

			return depth;

		}

		void get_depth_rec(StNode<T> const* const node, int depth, int& max_depth) const {

			if (node != nullptr) {

				get_depth_rec(node->get_left(), depth + 1, max_depth);
				get_depth_rec(node->get_right(), depth + 1, max_depth);

				if (depth > max_depth) {

					max_depth = depth;

				}

			}

		}

		void print_2d_rec(StNode<T> const* const p_root, int const depth, ostream& out) const {

			if (p_root) {

				print_2d_rec(p_root->get_right(), depth + 1, out);      // R

				out << setw(depth * 5);
				p_root->print(out);										//W
				out << "\n";

				print_2d_rec(p_root->get_left(), depth + 1, out);      // L

			}

		}

		vector<string> print_2d_upright_form(formvec& vec) const {

			size_t cell{ 0 };

			for (const auto& row_disp : vec) {

				for (const auto& str : row_disp) {

					if (!str.empty() && str.length() > cell) {

						cell = str.length();

					}

				}

			}

			// make sure the cell_width is an odd number
			if (cell % 2 == 0) ++cell;

			// allows leaf nodes to be connected when they are
			// all with size of a single character
			if (cell < 3) cell = 3;

			vector<string> formatted_rows;
			size_t row_count = vec.size();

			size_t row_elem_count = pow(2, row_count - 1);
			size_t left_pad = 0;

			// ("formatted_rows" will need to be reversed when done) 
			for (size_t r = 0; r < row_count; ++r) {

				const auto& cd_row = vec[row_count - r - 1]; // r reverse-indexes the row
				// "space" will be the number of rows of slashes needed to get
				// from this row to the next.  It is also used to determine other
				// text offsets.

				size_t space = (size_t(1) << r) * (cell + 1) / 2 - 1;
				// "row" holds the line of text currently being assembled
				string row;
				// iterate over each element in this row

				for (size_t c = 0; c < row_elem_count; ++c) {

					// add padding, more when this is not the leftmost element
					row += string(c ? left_pad * 2 + 1 : left_pad, ' ');

					if (!cd_row[c].empty()) {

						// This position corresponds to an existing Node
						const string& valstr = cd_row[c];
						// Try to pad the left and right sides of the value string
						// with the same number of spaces.  If padding requires an
						// odd number of spaces, right-sided children get the longer
						// padding on the right side, while left-sided children
						// get it on the left side.
						size_t long_padding = cell - valstr.length();
						size_t short_padding = long_padding / 2;

						long_padding -= short_padding;
						row += string(c % 2 ? short_padding : long_padding, ' ');
						row += valstr;
						row += string(c % 2 ? long_padding : short_padding, ' ');

					}

					else {

						// This position is empty
						row += string(cell, ' ');

					}

				}

				// A row of spaced-apart value strings is ready, add it to the result vector
				formatted_rows.push_back(row);

				// The root has been added, so this loop is finsished
				if (row_elem_count == 1) break;

				// Add rows of forward- and back- slash characters, spaced apart
				// to "connect" two rows' Node value strings.
				// The "space" variable counts the number of rows needed here.
				size_t left_space = space + 1;
				size_t right_space = space - 1;

				for (size_t sr = 0; sr < space; ++sr) {

					string row;

					for (size_t c = 0; c < row_elem_count; ++c) {

						if (c % 2 == 0) {

							row += string(c ? left_space * 2 + 1 : left_space, ' ');
							row += (!cd_row[c].empty()) ? '/' : ' ';
							row += string(right_space + 1, ' ');

						}

						else {

							row += string(right_space, ' ');
							row += (!cd_row[c].empty()) ? '\\' : ' ';

						}

					}

					formatted_rows.push_back(row);
					++left_space;
					--right_space;

				}

				left_pad += space + 1;
				row_elem_count /= 2;

			}

			// Reverse the result, placing the root node at the beginning (top)
			reverse(formatted_rows.begin(), formatted_rows.end());

			return formatted_rows;

		}

		void print_2d_upright_rec(StNode<T> const* const node, formvec& vec, size_t depth, size_t const max_depth) const {

			if (depth != max_depth) {

				if (node != nullptr) {

					//root
					stringstream st;
					node->print(st);
					vec[depth].push_back(st.str());

					//left & right
					print_2d_upright_rec(node->get_left(), vec, depth + 1, max_depth);
					print_2d_upright_rec(node->get_right(), vec, depth + 1, max_depth);

				}

				else {

					vec[depth].push_back("");

					print_2d_upright_rec(nullptr, vec, depth + 1, max_depth);
					print_2d_upright_rec(nullptr, vec, depth + 1, max_depth);

				}

			}

		}

	public:
		SyntaxTree(StNode<T>* root):root(root){}

		~SyntaxTree() {

			if (root != nullptr) {

				delete root;

			}

		}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override {

			if (root == nullptr) {

				throw EvaluationException();

			}

			return root->evaluate(name_list);

		}

		friend ostream& operator<<(ostream& lhs, SyntaxTree<T> const* rhs) {

			rhs->print(lhs);
			return lhs;

		}
		
		//prints tree three times in different order
		virtual void print(ostream& os) const override {

			if (root == nullptr) {

				throw EvaluationException();

			}

			else{

				os << "Print tree in pre-order noation: ";
				root->print_pre_order(os);

				os << "Print tree in in-order noation: ";
				root->print_in_order(os);

				os << "Print tree in post-order noation: ";
				root->print_post_order(os);

			}

		}

		ostream& print_2d(ostream& out) const {//RML

			print_2d_rec(root, 0, out);

			return out;

		}

		ostream& print_2d_upright(ostream& out) const {//W top left of Land right of R

			formvec vec;
			vec.resize(get_depth());

			print_2d_upright_rec(root, vec, 0, get_depth());

			vector<string> out_vec;
			out_vec = print_2d_upright_form(vec);

			copy(out_vec.cbegin(), out_vec.cend(), ostream_iterator<string>(cout, "\n"));

			return out;

		}

	};

};


#endif