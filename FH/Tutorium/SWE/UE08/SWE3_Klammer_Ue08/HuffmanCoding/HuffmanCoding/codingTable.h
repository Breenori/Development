#ifndef CODING_TABLE_H
#define CODING_TABLE_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include "codingTableEntry.h"
#include "huffmanTreeNode.h"

class codingTable {
public:
    codingTable() : head{ nullptr } {}
    codingTableEntry* getHead() {
        
        return head;
    }
    std::string getCodeFor(char character) {
        
        codingTableEntry* n = head;
        while (n != nullptr && n->getCharacter() != character) {
            
            n = n->getNext();
        }
        assert(n != nullptr);
        return n->getCode();
    }
    char getCharFor(std::string code) {
        
        codingTableEntry* n = head;
        while (n != nullptr && n->getCode() != code) {
            
            n = n->getNext();
        }

        if (n == nullptr) {
            
            return EMPTY_TREE_NODE;
        }
        else {
            
            return n->getCharacter();
        }
    }
    
    void generateCodingTableFrom(huffmanTreeNode* tree) {
        
        assert(tree != nullptr);
        generateCodingTableInternal(tree, "");
    }
    
    void printCodingTable() {
        
        codingTableEntry * n = head;
        while (n != nullptr) {
            
            std::cout << *n;
            n = n->getNext();
        }
    }
    
private:
    codingTableEntry * head;
    void generateCodingTableInternal(huffmanTreeNode* tree, std::string prefix) {
        
        if (tree != nullptr) {
            
            generateCodingTableInternal(tree->getLeft(), prefix + "0");
            generateCodingTableInternal(tree->getRight(), prefix + "1");
		
            if (tree->getCharacter() != EMPTY_TREE_NODE) {
                
                head = new codingTableEntry{tree->getCharacter(),prefix, head};
            }
        }
    }

};

#endif // !CODING_TABLE_H