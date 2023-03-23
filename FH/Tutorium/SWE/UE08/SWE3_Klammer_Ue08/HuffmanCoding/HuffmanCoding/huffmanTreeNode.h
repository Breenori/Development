#ifndef HUFFMAN_TREE_NODE_H
#define HUFFMAN_TREE_NODE_H

#define EMPTY_TREE_NODE '-'
#include <iostream>
#include <iomanip>
#include <cassert>

class huffmanTreeNode {
public:
    huffmanTreeNode(int val, char chr = EMPTY_TREE_NODE, huffmanTreeNode * l = nullptr, huffmanTreeNode* r = nullptr) 
        : value{ val }, character{ chr }, left{ l }, right{r} {}

    void setLeft(huffmanTreeNode* l) {
        
        assert(l != nullptr);
        
        left = l;
    }
    void setRight(huffmanTreeNode* r) {
        
        assert(r != nullptr);
        right = r;
    }
    
    int getValue() {
        
        return value;
    }
    char getCharacter() {
        
        return character;
    }
    huffmanTreeNode* getLeft() {
        
        return left;
    }
    huffmanTreeNode* getRight() {
        
        return right;
    }
    
    bool isEmpty() {
        
        return character == EMPTY_TREE_NODE;
    }
    void printTreeNode() {
        
        printTreeInteral(this, 0);
    }
    friend std::ostream& operator<< (std::ostream& lhs, huffmanTreeNode & rhs) {

        lhs << "{HuffmanTreeNode  Character:" << rhs.getCharacter() << ", Value: " << rhs.getValue() << "}\n";
        return lhs;
    }

private:
    int value;
    char character;
    huffmanTreeNode* left;
    huffmanTreeNode* right;
    void printTreeInteral(huffmanTreeNode* node, int level, bool lft = false) {
        
        if (node != nullptr) {
            
            printTreeInteral(node->getRight(), level + 1, false);
            for (int i = 0; i < level; i++) {
                
                std::cout << std::setw(5) << " ";
            }

            std::cout << (level == 0 ? "*--" : lft ? "\\--" : "/--") << (*node);
            printTreeInteral(node->getLeft(), level + 1, true);
        }
    }
    
};

#endif // !HUFFMAN_TREE_NODE_H