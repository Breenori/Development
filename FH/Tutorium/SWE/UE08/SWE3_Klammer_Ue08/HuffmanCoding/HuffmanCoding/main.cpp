#include <iostream>
#include <string>

#include "textcoder.h"
#include "bitStream.h"

void testCoder(std::string file) {
    
    std::cout << "####### Test for file " << file << "########## \n";
    textCoder coder{ *(new bitStringStream{ file }) };
    coder.decodeFile();
    std::cout << "####### Test for file " << file << "########## \n\n";
}

int main() {
    
    testCoder("Example.txt");
    testCoder("EmptyFile.txt");
    testCoder("shortText.txt");
    testCoder("longText.txt");
}