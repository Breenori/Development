#ifndef HUFFMAN_LIST_H
#define HUFFMAN_LIST_H

#include "huffman_tree.h"

class HLNode {
private:
	HuffmanTree* value{ nullptr };
	HLNode* next{ nullptr };
public:
	HLNode();
	~HLNode();
	HLNode(HuffmanTree* value);
	HLNode(HuffmanTree* value, HLNode* next);
	//getter
	HLNode* const get_next() const;
	HuffmanTree* const get_node() const;
	double const get_node_value() const;
	//setter
	void set_next(HLNode* next);
	void set_node(HuffmanTree* value);
};

class HuffmanList {
private:
	HLNode* root{ nullptr };
	int size = 0;
public:
	HuffmanList() {}
	HuffmanList(HLNode* r);
	~HuffmanList();
	int const get_size() const;
	void add(HLNode* node);
	HLNode* pop_front();
	void print_tree() const;
};


#endif // !HUFFMAN_LIST_H
