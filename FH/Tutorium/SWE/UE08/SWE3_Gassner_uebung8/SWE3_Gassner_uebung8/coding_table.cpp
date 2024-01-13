//
//  coding_table.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#include "coding_table.h"

std::ostream & coding_table_entry::print(std::ostream & out, bool const eol) const {
    out << "|" <<std::setw(8) << std::left << key << "|" <<std::right <<std::setw(9) << *(code.get_code()) << "|";
    if (eol) {
        out << std::endl;
    }
    return out;
}

std::string* coding_table::get_code_for_char(char const  c) const {
    for (coding_table_entry* e : entries) {
        if (e->get_key() == c) {
            return (e->get_code());
        }
    }
    throw codingTableException(std::string(1, c) +  " not found in coding table.");
}

char coding_table::get_char_for_code(std::string const& code) const {
    for (coding_table_entry* e : entries) {
        if (*(e->get_code()) == code) {
            return (e->get_key());
        }
    }
    return '\0';
}

void coding_table::clear() {
    for (coding_table_entry* e : entries) {
        delete e;
        e = nullptr;
    }
    entries.clear();
}

coding_table::coding_table() {
    entries = {};
}

coding_table::coding_table(huffman_tree * p_huffman_tree) {
    if (p_huffman_tree != nullptr) {
        // traversing the tree to create coding table entries
        std::string code;
        traverse_tree(p_huffman_tree->get_p_root(), code);
        sort();
    }
    
}

coding_table_entry::coding_table_entry(char const c, bit_code const& code_) : key(c), code(code_) {
    
}

char coding_table_entry::get_key() {
    return key;
}

std::string* coding_table_entry::get_code() {
    return code.get_code();
}

void coding_table::traverse_tree(huffman_tree::huffman_tree_node* p_node, std::string& code) {
    if (p_node == nullptr) {
        return;
    }

    // if node is a leaf, create a new coding table entry for it
    if (huffman_tree::is_leaf(p_node)) {
        entries.push_back(new coding_table_entry(p_node->entry->get_c(), code));
    }
    else {
        // traverse left subtree, adding '0' to code
        code.push_back('0');
        traverse_tree(p_node->p_left, code);
        code.pop_back();

        // traverse right subtree, adding '1' to code
        code.push_back('1');
        traverse_tree(p_node->p_right, code);
        code.pop_back();
    }
}

std::ostream & coding_table::print(std::ostream & out) {
    out << "--------------------" << std::endl;
    out << std::setw(20) << "  Coding Table   " << std::endl;
    out << "--------------------" <<  std::endl;
    for (coding_table_entry * entry : entries) {
        entry->print();
    }
    
    out << "--------------------" << std::endl;
    return out;
}

void coding_table::sort() {
    for (int i = 0; i < entries.size()-1; ++i) {
        if (entries[i]->get_key() > entries[i+1]->get_key()) {
            std::swap(entries[i], entries[i+1]);
            sort();
            break;
        }
    }
}
