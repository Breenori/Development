//
//  main.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#include <iostream>
#include "test_text_coder.h"
#include "bit_stream.h"

int main(int argc, const char * argv[]) {
    // Testcase 1
    test_frequency_table();
    
    // Testcase 2
    test_decoder("LoremIpsum.txt");
    
    // Testcase 3 Text
    test_decoder("test3.txt");
    
    // Testcase 4 Protein
    test_decoder("test4.txt");
    
    // Testcase 5: DNA
    test_decoder("test5.txt");
    
    // Testcase 6: Empty
    test_decoder("empty.txt");
    
    // Testcase 7: non-exist
    test_decoder("not_there.txt");
    
    // Testcase 8: .cpp
    test_decoder("bit_code.cpp");
}
