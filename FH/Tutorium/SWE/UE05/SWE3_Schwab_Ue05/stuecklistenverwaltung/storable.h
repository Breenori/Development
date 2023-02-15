//
// Created by Anja Schwab on 25.12.22.
//

#ifndef STUECKLISTENVERWALTUNG_STORABLE_H
#define STUECKLISTENVERWALTUNG_STORABLE_H
#include <string>

using std::string;

class storable{
public:
    //virtual void store_hierachy(string filename)=0;
    //virtual void store_shopping_list(string filename);//set format
    virtual void store(string const & filename) = 0;
    virtual void load(string const & filename) = 0;//can only load in hierachy format - otherwise the structure of the parts cannot be reconstructed
};

#endif //STUECKLISTENVERWALTUNG_STORABLE_H
