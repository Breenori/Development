//
//  coding_table.h
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#ifndef coding_table_h
#define coding_table_h

#include <unordered_map>
#include "huffman_tree.h"

#include "bit_code.h"
#include <string>

// Exception for coding table
class codingTableException : public std::exception {
public: codingTableException(std::string const& s) {
        message += s;
    }
    
    std::string& what() {
        return message;
    }
    
private:
    std::string message = "Coding Table Exception: ";
    
};

// Entry for coding table
class coding_table_entry {
public:
    coding_table_entry(char const c, bit_code const& code_);
    
    char get_key();
    std::string* get_code();
    std::ostream & print(std::ostream & out = std::cout, bool const eol = true) const;
private:
    char key;
    bit_code code;
};

// coding table
class coding_table {
public:
    coding_table();
    coding_table(huffman_tree * p_huffman_tree);
    std::string* get_code_for_char(char const  c) const;
    char get_char_for_code(std::string const& code) const;
    std::ostream & print(std::ostream & out = std::cout);
    void clear();

private:
    std::vector<coding_table_entry*> entries;
    
    void traverse_tree(huffman_tree::huffman_tree_node* p_node, std::string& code);
    void sort();
};

#endif /* coding_table_h */
