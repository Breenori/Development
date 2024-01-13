#ifndef TEXTCODER_H
#define TEXTCODER_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include "bitStream.h"
#include "frequencyTable.h"
#include "huffmanListNode.h"
#include "codingTable.h"

class textCoder {
public:
    textCoder(bitStream& s) {
        
        content = s.getContent();
        codedContent = "";
        head = nullptr;
    }
    void decodeFile() {
        
        int i = 0;
        char c = content[i];
        while (c != '\0') {
            
            if (c != '\n') {
                
                table.updateEntry(c);
            }
            i++;
            c = content[i];
        }

        std::cout << "File-Content: " << content << "\n";

        table.printTable();
        buildHuffmanList();
        decryptContent();
        encryptContent();
        printStatistics();
    }
    std::string getDecodedContent() {
        
        return codedContent;
    }
    std::string getFileContent() {
        
        return content;
    }
    
    void printHuffmanList() {
        
        huffmanListNode * n = head;
        while (n != nullptr) {
            
            n->printNode();
            n = n->getNext();
        }
    }

private:
    std::string fileName;
    std::string content;
    std::string codedContent;
    frequencyTable table;
    huffmanListNode* head;
    codingTable codingTable;

    void buildHuffmanList() {
        
        if (!table.isEmpty()) {
            frequencyTableEntry * e = table.getHead();

            while (e != nullptr) {
                
                if (head == nullptr) {
                    
                    head = new huffmanListNode(new huffmanTreeNode{ e->getFrequency(), e->getCode() });
                }
                else {
                    
                    huffmanListNode * n = head;
                    while (n->getNext() != nullptr) {
                        
                        n = n->getNext();
                    }
                    
                    n->setNext(new huffmanListNode(new huffmanTreeNode{ e->getFrequency(), e->getCode() }));
                }
                
                e = e->getNext();
            }
            
            generateHuffmanCodingTree();
        }
    }
    void generateHuffmanCodingTree() {
        
        huffmanListNode * p1 = head;
        if (p1 == nullptr) {
            
            return;
        }
        
        while(p1->getNext() != nullptr) {
            
            huffmanListNode* p2 = p1->getNext();
            this->head = p2;
            
            p2->setTree(new huffmanTreeNode{ p1->getTreeValue() + p2->getTreeValue(), EMPTY_TREE_NODE,  p1->getTree(), p2->getTree()});
            delete p1;
            
            reorderHead();
            p1 = head;
        }

        printHuffmanList();

        codingTable.generateCodingTableFrom(head->getTree());
        codingTable.printCodingTable();
    }
    void reorderHead() {
        
        huffmanListNode * h = head;
        huffmanListNode* prev = nullptr;
        while (h->getNext() != nullptr && h->getTreeValue() > h->getNext()->getTreeValue()) {
            
            if (prev == nullptr) {
                
                head = h->getNext();
                h->setNext(head->getNext());
                head->setNext(h);
                prev = head;
            }
            else {

                prev->setNext(h->getNext());
                h->setNext(prev->getNext()->getNext());
                prev->getNext()->setNext(h);
                prev = prev->getNext();
            }
        }
    }
    void decryptContent() {
        
        int i = 0;
        char c = content[i];
        while (c != '\0') {
            
            if (c != '\n') {
                
                codedContent += codingTable.getCodeFor(content[i]);
            }
            
            i++;
            c = content[i];
        }

        std::cout << "\nCoded-Content: \n" << codedContent << "\n";
    }
    void encryptContent() {
        
        std::string encryptedString = "";
        std::string code = "";
        for (int i = 0; i < codedContent.length(); i++) {
            
            code += codedContent[i];
            if (codingTable.getCharFor(code) != EMPTY_TREE_NODE) {
                
                encryptedString += codingTable.getCharFor(code);
                code = "";
            }
        }

        std::cout << "\nEncrypted-Content: \n" << encryptedString << "\n";
    }
    void printStatistics() {
        
        std::cout << "########### STATISTICS ###############" << "\n";
        std::cout << "Old Length: " << content.length() << ", New Length: " << codedContent.length() << "\n";
        std::cout << "Old Size: " << content.length() * 8 << "(bits) , New Size: " << codedContent.length() << "(bits)\n";

        if (content.length() > 0) {
            
            std::cout << "Compression-Rate: " << 100 - round(((double) codedContent.length() / (content.length() * 8) * 100)) << "%\n";
        }

        std::cout << "#######################################" << "\n";
    }
    
};

#endif // !TEXTCODER_H