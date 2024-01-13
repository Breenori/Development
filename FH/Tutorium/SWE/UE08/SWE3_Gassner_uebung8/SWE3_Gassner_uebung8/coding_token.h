//
//  coding_token.h
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#ifndef coding_token_h
#define coding_token_h

#include "frequency_table.h"
#include "coding_table.h"
#include "huffman_list.h"

#include <string>
#include <map>

class coding_token {
public:
    coding_token(std::string const* text);
    void clear();
    std::string * encode(std::string const* text);
    std::string * decode(std::string const* encoded_text);
    
    coding_table * get_coding_table();
    frequency_table* get_frequency_table();
    void set_frequency_table(std::string const* text);
    // std::string* get_encoded_text();
private:
    frequency_table * freq_table;
    huffman_list * h_list;
    coding_table * c_table;
    
};


#endif /* coding_token_h */
