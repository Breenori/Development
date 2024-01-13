//
//  bit_code.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 16.02.23.
//

#include "bit_code.h"

bit_code::bit_code() {
    code = new std::string();
}

bit_code::bit_code(std::string const& code_) {
    code = new std::string(code_);
}

bool bit_code::get_bit(unsigned const int i) const {
    if (i >= code->length()) {
        return false;
    }
    return code->at(i) == '1';
}

std::string* bit_code::get_code() const {
    return code;
}

void bit_code::append_bit(bool const bit) {
    if (bit) {
        *code += "1";
    } else {
        *code += "0";
    }
}

size_t bit_code::get_length() const {
    return code->size();
}

