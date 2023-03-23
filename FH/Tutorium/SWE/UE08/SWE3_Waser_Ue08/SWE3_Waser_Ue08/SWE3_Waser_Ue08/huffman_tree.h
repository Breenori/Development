#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include<iostream>

using std::ostream;
using std::cout;

class HTNode {
private:
	char sign;
	double value;
	HTNode* left;
	HTNode* right;
public:
	HTNode();
	~HTNode();
	HTNode(char sign, double& value);
	HTNode(HTNode* left, HTNode* right);
	//getter
	HTNode* const get_left() const;
	HTNode* const get_right() const;
	char const get_sign() const;
	double const get_value() const;
	//setter
	void set_right(HTNode* right);
	void set_left(HTNode* left);

	double calc_value() const;
};


class HuffmanTree {
private:
	HTNode* root;
	ostream& print_rec(ostream& out, HTNode* current, size_t const indent);
public:
	HuffmanTree();
	HuffmanTree(HTNode* r);
	~HuffmanTree();
	double get_value() const;
	HTNode* const get_root() const;
	void set_root(HTNode* r);
	ostream& print(ostream& out = cout);

};


#endif // !HUFFMAN_TREE_H
