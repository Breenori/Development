//
//  huffman_tree.h
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#ifndef huffman_tree_h
#define huffman_tree_h

#include <string>
#include "frequency_table.h"

class coding_token;
class coding_table;

class huffmanTreeException : public std::exception {
public: huffmanTreeException(std::string const& s);
    
    std::string& what();
    
private:
    std::string message = "Frequency Table Exception: ";
    
};

class huffman_tree {
public:
    struct huffman_tree_node {
        frequency_table_entry* entry = nullptr;
        huffman_tree_node* p_left = nullptr;
        huffman_tree_node* p_right = nullptr;
        
    };
    
    static bool is_leaf(huffman_tree_node * p_node);
    static huffman_tree_node* create_node(frequency_table_entry* e, huffman_tree_node* p_l, huffman_tree_node* p_r);
    
    huffman_tree();
    huffman_tree(huffman_tree_node* p_root);
    
    std::ostream & print(std::ostream & out) const;
    
    std::ostream & print_node(std::ostream& out, int const prefix, huffman_tree_node * p_node) const;
    huffman_tree_node* get_p_root();
    void set_p_root(huffman_tree_node* p_node);
    
private:
    huffman_tree_node* p_root;
    
};

#endif /* huffman_tree_h */
