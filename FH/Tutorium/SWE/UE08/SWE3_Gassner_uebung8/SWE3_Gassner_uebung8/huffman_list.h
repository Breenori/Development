//
//  huffman_list.h
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#ifndef huffman_list_h
#define huffman_list_h
#include "huffman_tree.h"
//#include "frequency_table.h"

#include <exception>

class huffmanListException : public std::exception {
public: huffmanListException(std::string const& s);
    
    std::string& what();
    
private:
    std::string message = "Frequency Table Exception: ";
    
};

class huffman_list {
public:
    struct huffman_list_node {
        huffman_tree* p_tree;
        huffman_list_node* p_next;
    };
    
    huffman_list();
    huffman_list(frequency_table & table);
    void add(huffman_list_node* p_node);
    huffman_tree* build_tree();
    std::ostream& print(std::ostream & out = std::cout);
    void clear();
    huffman_list_node* get_p_head();
    
    void sort();
    huffman_list_node* swap(huffman_list_node* p1, huffman_list_node* p2);
    size_t get_size();
    
private:
    huffman_list_node* p_head;
    void build_tree_rec();
    void swap_nodes();
        
};

#endif /* huffman_list_h */
