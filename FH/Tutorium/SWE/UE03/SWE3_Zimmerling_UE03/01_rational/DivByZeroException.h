//
// Created by arzi on 08.11.22.
//

#include "exception"

#ifndef INC_01_RATIONAL_DIVBYZEROEXCEPTION_H
#define INC_01_RATIONAL_DIVBYZEROEXCEPTION_H

class DivByZeroException : public std::exception {
public:
    virtual char const *what() const throw() {
        return "EXCEPTION CLASS: Division by zero!";
    }
};

#endif //INC_01_RATIONAL_DIVBYZEROEXCEPTION_H
