//
//  text_coder.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#include "text_coder.h"

text_coder::text_coder() {
    
}

text_coder::text_coder(std::string const& filename) {
    text = new std::string;
    read(filename);
    
    if (*text == "") {
        throw CoderException(filename + " is empty file..");
    }
    token = new coding_token(text);
    encode();
    decode();
    
    if (*text == *decoded_text) {
        good = true;
    } else {
        good = false;
        throw CoderException("decoded text is different than normal text.");
    }
}

text_coder::~text_coder() {
    delete text;
    text = nullptr;
    
    // token->clear();
    delete token;
    token = nullptr;
}

void text_coder::read(std::string const& filename) {
    std::ifstream in(filename);
    if (in.good()) {
        read(in);
        in.close();
    } else {
        throw CoderException("unable to open file! (" + filename + ")");
    }
    
}

std::istream& text_coder::read(std::istream& in) {
    std::string tmp = "";
    if (!in.good()) {
        throw CoderException("stream is not good.");
        return in;
    }
    
    while (std::getline(in, tmp)) {
        (*text) += tmp;
    }
    original_lenght = text->size()*8;
    
    return in;
}

void text_coder::encode() {
    encoded_text = token->encode(text);
    encoded_lenght = encoded_text->size();
    calculate_compression_rate();
}

void text_coder::decode() {
    decoded_text = token->decode(encoded_text);
}

double text_coder::get_compression_rate() const {
    return compression_rate;
}

size_t text_coder::get_original_lenght() const {
    return original_lenght;
}

size_t text_coder::get_encoded_lenght() const {
    return encoded_lenght;
}

std::string& text_coder::get_text() const {
    return *text;
}

std::string& text_coder::get_encoded_text() const {
    return *encoded_text;
}

std::string& text_coder::get_decoded_text() const {
    return *decoded_text;
}


void text_coder::calculate_compression_rate() {
    encoded_lenght = encoded_text->size();
    compression_rate = (1 - (double)encoded_lenght / original_lenght) * 100;
}


void text_coder::print_statistics() const {
    // print original text length
    std::cout << std::setw(25) << std::left << "Is Good?: " << std::boolalpha << good << std::endl;
    std::cout << std::setw(25) << std::left << "Original text length: " << original_lenght << " bits" << std::endl;
    // print encoded text length
    std::cout << std::setw(25) << std::left << "Encoded text length: " << encoded_lenght << " bits" << std::endl;
    
    // print compression rate
    std::cout << std::setw(25) << std::left << "Compression rate: " << compression_rate << " %" << std::endl;
    
    // print relative frequencies table
    token->get_frequency_table()->print();
    token->get_coding_table()->print();
}
