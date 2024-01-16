//
//  text_coder.h
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#ifndef text_coder_h
#define text_coder_h

#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <map>

#include "coding_token.h"


class text_coder {
public:
    text_coder();
    text_coder(std::string const& filename);
    ~text_coder();
    
    void print_statistics() const;
    void encode();
    void decode();
    
    double get_compression_rate() const;
    size_t get_original_lenght() const;
    size_t get_encoded_lenght() const;
    std::string& get_text() const;
    std::string& get_encoded_text() const;
    std::string& get_decoded_text() const;
    
private:
    std::istream& read(std::istream& in);
    void read(std::string const& filename);
    void calculate_compression_rate();
    
    // Attributes
    std::string* text;
    std::string* encoded_text;
    std::string* decoded_text;
    coding_token* token;
    double compression_rate;
    size_t original_lenght;
    size_t encoded_lenght;
    bool good = false;
    

    
    
};

class CoderException : public std::exception {
public:
    CoderException(std::string const& message) {
        this->message += message;
    }
    
    std::string& what() {
        return message;
    }
private:
    std::string message = "Coder Exception: ";
};


#endif /* text_coder_h */
