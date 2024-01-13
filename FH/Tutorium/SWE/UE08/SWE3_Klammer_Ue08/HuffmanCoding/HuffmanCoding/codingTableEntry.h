#ifndef CODING_TABLE_ENTRY_H
#define CODING_TABLE_ENTRY_H

#include <string>
#include <iostream>

class codingTableEntry {
public:
    codingTableEntry(char character, std::string code, codingTableEntry* next = nullptr) : chr{ character }, code{ code }, next{ next } {}
    std::string getCode() {
        
        return code;
    }
    char getCharacter() {
        
        return chr;
    }
    codingTableEntry* getNext() {
        
        return next;
    }

    friend std::ostream& operator<<(std::ostream& stream, codingTableEntry& lhs) {

        stream << "{CodingTableEntry Char: " << lhs.chr << ", Code: " << lhs.code << "}\n";
        return stream;
    }

private:
    char chr;
    std::string code;
    codingTableEntry* next;
    
};

#endif // !CODING_TABLE_ENTRY_H