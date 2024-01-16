//
//  huffman_tree.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#include "huffman_tree.h"

huffmanTreeException::huffmanTreeException(std::string const& s) {
    message += s;
}

std::string& huffmanTreeException::what() {
    return message;
}

huffman_tree::huffman_tree() {
    p_root = nullptr;
}

huffman_tree::huffman_tree(huffman_tree_node* p_root) {
    this->p_root = p_root;
}

bool huffman_tree::is_leaf(huffman_tree_node * p_node) {
    return (p_node->entry != nullptr && p_node->p_left == nullptr && p_node->p_right == nullptr);
}

std::ostream& huffman_tree::print(std::ostream& out) const {
    print_node(out, 0, p_root);
    return out;
}

std::ostream& huffman_tree::print_node(std::ostream& out, int const prefix, huffman_tree_node * p_node) const {
    if (p_node == nullptr) {
         return out;
     }

     print_node(out, prefix + 1, p_node->p_right);

     for (int i = 0; i < prefix; i++) {
         out << "           ";
     }

     if (p_node == p_root) {
         out << "[" << p_node->entry->get_c() << " : " << p_node->entry->get_frequency() << "]" << std::endl;
     } else {
         if (is_leaf(p_node)) {
             out << "(L)-[" << p_node->entry->get_c() << " : " << p_node->entry->get_frequency() << "]" << std::endl;
         } else {
             out << "+-[" << p_node->entry->get_c() << " : " << p_node->entry->get_frequency() << "]" << std::endl;
         }
     }

     print_node(out, prefix + 1, p_node->p_left);

     return out;
}

huffman_tree::huffman_tree_node* huffman_tree::get_p_root() {
    return p_root;
}

void huffman_tree::set_p_root(huffman_tree_node* p_node) {
    p_root = p_node;
}

huffman_tree::huffman_tree_node* huffman_tree::create_node(frequency_table_entry* e, huffman_tree_node* p_l, huffman_tree_node* p_r) {
    huffman_tree_node* new_node = new huffman_tree_node;
    new_node->entry = e;
    new_node->p_right = p_r;
    new_node->p_left = p_l;
    
    return new_node;
}
