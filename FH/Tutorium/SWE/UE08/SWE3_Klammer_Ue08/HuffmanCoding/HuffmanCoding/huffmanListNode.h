#ifndef HUFFMAN_LIST_NODE_H
#define HUFFMAN_LIST_NODE_H

#include <cassert>
#include <iostream>
#include "huffmanTreeNode.h"

class huffmanListNode {
public:
    huffmanListNode(huffmanTreeNode* tree) {
        
        head = tree;
        next = nullptr;
    }
    void setNext(huffmanListNode* n) {
        
        next = n;
    }
    void setTree(huffmanTreeNode* t) {
        
        assert(t != nullptr);
        head = t;
    }
    
    huffmanListNode* getNext() {
        
        return next;
    }
    huffmanTreeNode* getTree() {
        
        return head;
    }
    int getTreeValue() {
        
        return head == nullptr ? 0 : head->getValue();
    }
    
    void printNode() {
        
        std::cout << "{HuffmanListNode} \n";
        head->printTreeNode();
        std::cout << "\n";
    }

private:
    huffmanTreeNode* head;
    huffmanListNode* next;
    
};

#endif // !HUFFMAN_LIST_NODE_H