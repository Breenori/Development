#include "huffman_list.h"


//Huffman List
HuffmanList::HuffmanList(HLNode* r) : root(r) {}
HuffmanList::~HuffmanList() {
	if (root != nullptr)
		delete root;
}
//getter
int const HuffmanList::get_size() const {
	return size;
}

void HuffmanList::print_tree() const {
	//since at the end the finished tree is in the root of the list
	//only print the tree in the root node
	if (root != nullptr) {
		root->get_node()->print();
	}
}

//adds the node sorted
void HuffmanList::add(HLNode* node) {
	//add as root if there isn't one already
	if (root == nullptr)
		root = node;
	//check if the nodes value is less then the current root's
	//and possibly add before it
	else if (root->get_node_value() > node->get_node_value()) {
		node->set_next(root);
		root = node;
	}
	else {
		//save previous node and current node
		HLNode* prev = root;
		HLNode* current = root->get_next();

		//find last node that is less than node
		while (current != nullptr && current->get_node_value() < node->get_node_value()) {
			prev = current;
			current = current->get_next();
		}
		//add the new node between the last one that was smaller(prev) and it's next(current)
		node->set_next(current);
		prev->set_next(node);
	}
	//count size of nodes in list
	size++;
}

HLNode* HuffmanList::pop_front() {
	//remove root and set the next one as root
	HLNode* current = root;
	if (root != nullptr) {
		root = root->get_next();
		current->set_next(nullptr);
		//count size of nodes in the list
		--size;
	}
	return current;
}


//Huffman List Node
HLNode::HLNode() {}
HLNode::~HLNode() {
	if (value != nullptr)
		delete value;
}
HLNode::HLNode(HuffmanTree* value) : value(value) {}
HLNode::HLNode(HuffmanTree* value, HLNode* next) : value(value), next(next) {}
//getter
HLNode* const HLNode::get_next() const {
	return next;
}
HuffmanTree* const HLNode::get_node() const {
	return value;
}
double const HLNode::get_node_value() const {
	return value->get_value();
}
//setter
void HLNode::set_next(HLNode* next) {
	this->next = next;
}
void HLNode::set_node(HuffmanTree* value) {
	this->value = value;
}