//
//  test_text_coder.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#include "test_text_coder.h"


void test_decoder(std::string const& filename) {
    std::cout << std::endl << std::endl;
    std::cout << "Testing All:" << std::endl;
    try {
        text_coder my_coder(filename);
        std::cout << std::setw(25) << std::left <<"Text we got: " << my_coder.get_text() << std::endl;
        std::cout << std::setw(25) << std::left  << "Encoded Text: " << my_coder.get_encoded_text() << std::endl;
        std::cout << std::setw(25) << std::left  << "Decoded Text: " << my_coder.get_decoded_text() << std::endl;
        my_coder.print_statistics();
    } catch (CoderException & e) {
        std::cout << e.what() << std::endl;
    }
}

void test_frequency_table() {
    std::cout << "Testing Frequency Table:" << std::endl;
    try {
        std::string* s = new std::string;
        *s = "Hallo, Hallo, Hallo";
        std::cout << "Generating table.." << std::endl;
        frequency_table f_t(s);
        
        std::cout << "Printing table.." << std::endl;
        f_t.print();
        
        std::cout << "Test size of table.." << std::endl;
        if (f_t.get_size() != 6) {
            throw frequencyTableException(" error in get_size()!");
        } else {
            std::cout << "get_size: 6" << std::endl;
        }

        std::cout << "Test get frequency ..." << std::endl;
        std::cout << "get_frequency: " << f_t.get_frequency('H') << " should be 0.157895" << std::endl;
        
        if (f_t.get_frequency('H') == double(0.157895)) {
            throw frequencyTableException("error in get_frequency()!");
        }
        
        f_t.get_frequency('G');
        
        delete s;
        s = nullptr;
    } catch (frequencyTableException & e) {
        std::cout << e.what() << std::endl;
    }
}
