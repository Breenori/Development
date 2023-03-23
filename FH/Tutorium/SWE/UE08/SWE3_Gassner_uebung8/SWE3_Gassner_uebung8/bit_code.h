//
//  bit_code.h
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#ifndef bit_code_h
#define bit_code_h

#include <string>

class bit_code {
public:
    bit_code();
    bit_code(std::string const& code_);
    
    bool get_bit(unsigned const int i) const;
    std::string* get_code() const;
    void append_bit(bool const bit);
    size_t get_length() const;
    
private:
    std::string* code;
};

#endif /* bit_code_h */
