//
//  coding_token.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#include "coding_token.h"

coding_token::coding_token(std::string const* text) {
    set_frequency_table(text);
    h_list = new huffman_list(*freq_table);
    h_list->build_tree()->print(std::cout);
    c_table = new coding_table(h_list->get_p_head()->p_tree);
}

void coding_token::clear() {
    freq_table->clear();
    h_list->clear();
    c_table->clear();
}

std::string * coding_token::encode(std::string const* text) {
    std::string* encoded_text = new std::string("");
    for (char c : (*text)) {
        *encoded_text += *c_table->get_code_for_char(c);
    }
    return encoded_text;
}


std::string * coding_token::decode(std::string const* encoded_text) {
    std::string* decoded_text = new std::string("");
    std::string buffer = "";
    for (char c : (*encoded_text)) {
        buffer += c;
        char decoded_char = c_table->get_char_for_code(buffer);
        
        if (decoded_char != '\0') {
            *decoded_text += decoded_char;
            buffer = "";
        }
    }
    return decoded_text;
}

coding_table* coding_token::get_coding_table() {
    return c_table;
}

frequency_table* coding_token::get_frequency_table() {
    return freq_table;
}

void coding_token::set_frequency_table(std::string const* text) {
    freq_table = new frequency_table(text);
}
