#include "huffman_tree.h"

//Huffman Tree
HuffmanTree::HuffmanTree() : root(nullptr) {}
HuffmanTree::HuffmanTree(HTNode* r) : root(r) {}
HuffmanTree::~HuffmanTree() {
	if (root != nullptr)
		delete root;
}
double HuffmanTree::get_value() const {
	//value of the tree is the value of the root
	double sum(0.0);
	if (root != nullptr)
		sum = root->calc_value();
	return sum;
}
//getter for the root
HTNode* const HuffmanTree::get_root() const {
	return root;
}
//setter for the root
void HuffmanTree::set_root(HTNode* r) {
	root = r;
}
//print tree, starting with the root
ostream& HuffmanTree::print(ostream& out) {
	if (!out.good())
		return out;
	return print_rec(out, root, 0);
}
//print tree recursive
ostream& HuffmanTree::print_rec(ostream& out, HTNode* current, size_t const indent) {
	//only print the node if it is no nullptr
	if (current != nullptr) {
		out << "\n";
		for (int i(0); i < indent; ++i) {
			cout << " \t";
		}
		//print sign and value of current node
		out << "\"" << current->get_sign() << "\" " << current->get_value();
		//call print_rec for its children with a greater indent
		print_rec(out, current->get_left(), indent + 1);
		print_rec(out, current->get_right(), indent + 1);
	}
	return out;
}


//Huffman Tree Node
HTNode::HTNode() {
	//set to default values
	value = 0;
	sign = '-';
	left = nullptr;
	right = nullptr;
}
HTNode::~HTNode() {
	if (left != nullptr)
		delete left;
	if (right != nullptr)
		delete right;
}
HTNode::HTNode(char sign, double& value) : sign(sign), value(value) {
	//set left and right to default values if only sign and value are provided
	left = nullptr;
	right = nullptr;
}
HTNode::HTNode(HTNode* left, HTNode* right) : left(left), right(right) {
	//set sign to default value and calcuate value if only the children are provided
	sign = '-';
	value = calc_value();
}
//getter
HTNode* const HTNode::get_left() const {
	return left;
}
HTNode* const HTNode::get_right() const {
	return right;
}
char const HTNode::get_sign() const {
	return sign;
}
double const HTNode::get_value() const {
	return value;
}
//setter
void HTNode::set_right(HTNode* right) {
	this->right = right;
}
void HTNode::set_left(HTNode* left) {
	this->left = left;
}

double HTNode::calc_value() const {
	//calculating the value of a node from its children
	double sum(0.0);
	if (left != nullptr)
		sum += left->calc_value();
	if (right != nullptr)
		sum += right->calc_value();
	// if both chidlren are nullptr, the node is a leave -> take its value
	if (right == nullptr && left == nullptr)
		sum = value;
	return sum;
}