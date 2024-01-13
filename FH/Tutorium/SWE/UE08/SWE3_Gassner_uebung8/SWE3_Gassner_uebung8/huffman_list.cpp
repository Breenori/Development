//
//  huffman_list.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#include "huffman_list.h"

huffmanListException::huffmanListException(std::string const& s) {
    message += s;
}

std::string& huffmanListException::what() {
    return message;
}

huffman_list::huffman_list() {
    p_head = nullptr;
}

huffman_list::huffman_list(frequency_table & table) {
    p_head = new huffman_list_node;
    huffman_list_node* p_current = p_head;
    std::vector<frequency_table_entry*> f = (*table.get_table());
    
    for (int i = 0; i < f.size(); ++i) {
        huffman_tree::huffman_tree_node* p_node = new huffman_tree::huffman_tree_node;
        p_node->entry = f[i];
        p_current->p_tree = new huffman_tree(p_node);
        if (i < f.size()-1) {
            p_current->p_next = new huffman_list_node;
            p_current = p_current->p_next;
        } else {
            p_current->p_next = nullptr;
        }
    }
}

void huffman_list::add(huffman_list_node* p_node) {
    huffman_list_node* p_current = p_head;
    
    while (p_current->p_next != nullptr) {
        p_current = p_current->p_next;
    }
    p_current->p_next = p_node;
}

huffman_list::huffman_list_node* huffman_list::get_p_head() {
    return p_head;
}

void huffman_list::clear() {
    huffman_list_node* current = p_head;
    while (current != nullptr) {
        huffman_list_node* next = current->p_next;
        delete current;
        current = next;
    }
    current = nullptr;
}

std::ostream& huffman_list::print(std::ostream & out) {
    huffman_list_node* current = p_head;
    while (current != nullptr) {
        out << "Tree:";
        current->p_tree->print(out);
        current = current->p_next;
        if (current != nullptr) {
            out << "Next ";
        }
    }
    out << std::endl;
    
    return out;
}

huffman_tree* huffman_list::build_tree() {
    while (p_head->p_next != nullptr) {
        build_tree_rec();
    }
    
    return p_head->p_tree;
}

void huffman_list::sort() {
    if (p_head == nullptr || p_head->p_next == nullptr) {
        return;
    }
    huffman_list_node* n_p_head = nullptr;
    huffman_list_node* p_curr = p_head;
    huffman_list_node* p_next = p_head->p_next;
    huffman_list_node* p_prev = p_head;
    
    while (p_curr != nullptr && p_next != nullptr) {
        
        if (p_curr->p_tree->get_p_root()->entry->get_frequency() > p_next->p_tree->get_p_root()->entry->get_frequency()) {
            if (p_curr == p_head) {
                p_head = swap(p_curr, p_next);
                p_prev = p_curr;
                p_curr = p_next;
                p_next = p_curr->p_next;
            } else {
                p_prev->p_next = swap(p_curr, p_next);
                p_curr = p_next;
                p_next = p_curr->p_next;
            }

        } else {
            p_prev = p_curr;
            p_curr = p_curr->p_next;
            p_next = p_curr->p_next;
        }
    }
}

huffman_list::huffman_list_node* huffman_list::swap(huffman_list_node* p1, huffman_list_node* p2) {
    huffman_list_node* tmp = p2->p_next;
    p2->p_next = p1;
    p1->p_next = tmp;
    return p2;
}

size_t huffman_list::get_size() {
    int i = 0;
    huffman_list_node* tmp = p_head;
    while (tmp != nullptr) {
        ++i;
        tmp = tmp->p_next;
    }
    return i;
}


void huffman_list::build_tree_rec() {
    sort();
    if (p_head->p_next == nullptr) {
        return;
    }
    
    huffman_tree* smaller = nullptr;
    huffman_tree* bigger = nullptr;
    
    if (p_head->p_tree->get_p_root()->entry < p_head->p_next->p_tree->get_p_root()->entry) {
        smaller = p_head->p_tree;
        bigger = p_head->p_next->p_tree;
    } else {
        bigger = p_head->p_tree;
        smaller = p_head->p_next->p_tree;
    }
    
    frequency_table_entry* new_entry = new frequency_table_entry(smaller->get_p_root()->entry->get_c()+bigger->get_p_root()->entry->get_c(), smaller->get_p_root()->entry->get_frequency()+bigger->get_p_root()->entry->get_frequency());
    
    huffman_tree::huffman_tree_node * p_new_tree_node = huffman_tree::create_node(new_entry, smaller->get_p_root(), bigger->get_p_root());
    
    huffman_list_node* new_p_head = p_head->p_next;
    delete p_head;
    p_head = new_p_head;
    p_head->p_tree = new huffman_tree(p_new_tree_node);
    
}
