#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <iostream>
#include "frequencyTableEntry.h"

class frequencyTable {
public:
    frequencyTable() = default;
    frequencyTableEntry* get(char code) {
        
        frequencyTableEntry * e = head;
        while (e != nullptr && e->getCode() != code) {
            
            e = e->getNext();
        }

        return e;
    }
    frequencyTableEntry* getHead() {
        
        return head;
    }
    int getSum() {
        
        return sum;
    }
    
    void updateEntry(char code) {
        
        frequencyTableEntry* e = get(code);
        sum++;
        
        if (e == nullptr) {
            
            frequencyTableEntry* old = head;
            head = new frequencyTableEntry{ code };
            head->setNext(old);

            if (old != nullptr) {
                
                old->setPrev(head);
            }

            if (tail == nullptr) {
                
                tail = head;
            }
        }
        else {
            
            ++(*e);
            while (e->getNext() != nullptr && e->getNext()->getFrequency() < e->getFrequency()) {
                
                frequencyTableEntry * tmp = e->getNext();
                e->setNext(tmp->getNext());
                tmp->setNext(e);

                tmp->setPrev(e->getPrev());
                e->setPrev(tmp);

                if (e->getNext() == nullptr) {
                    
                    tail = e;
                }

                if (tmp->getPrev() == nullptr) {
                    
                    head = tmp;
                }
                else {
                    
                    tmp->getPrev()->setNext(tmp);
                }
            }
        }
    }
    void printTable() {
        
        frequencyTableEntry* e = head;
        while (e != nullptr) {
            
            std::cout << *e << "\n";
            e = e->getNext();
        }
    }
    bool isEmpty() {
        
        return head == nullptr;
    }

private:
    frequencyTableEntry* head;
    frequencyTableEntry* tail;
    int sum;
    
};

#endif // !FREQUENCY_TABLE_H