#ifndef FREQUENCY_TABLE_ENTRY_H
#define FREQUENCY_TABLE_ENTRY_H

#include <iostream>

class frequencyTableEntry {
public:
    frequencyTableEntry(char code) : code{ code }, frequency{ 1 }, next { nullptr }, prev{ nullptr } {}
    virtual ~frequencyTableEntry() = default;
    void setNext(frequencyTableEntry* n) {
        
        next = n;
    }
    void setPrev(frequencyTableEntry* p) {
        
        prev = p;
    }
    
    frequencyTableEntry* getNext() {
        
        return next;
    }
    frequencyTableEntry* getPrev() {
        
        return prev;
    }
    int getFrequency() {
        
        return frequency;
    }
    char getCode() {
        
        return code;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, frequencyTableEntry& rhs) {

        stream << "{" << "Code: " << rhs.code << ", " << "Frequency: " << rhs.frequency << "}";
        return stream;
    }
    frequencyTableEntry& operator++() {
        
        frequency++;
        return *this;
    }
     int operator <=> (frequencyTableEntry &rhs) {
        
        return frequency - rhs.frequency;
    }

private:
    char code;
    int frequency;
    frequencyTableEntry* next;
    frequencyTableEntry* prev;

};

#endif // !FREQUENCY_TABLE_ENTRY_H