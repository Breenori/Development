//
// Created by arzi on 08.11.22.
//

#ifndef INC_01_RATIONAL_INVALIDRATIONALEXCEPTION_H
#define INC_01_RATIONAL_INVALIDRATIONALEXCEPTION_H

#include "exception"

class InvalidRationalException : public std::exception {
public:
    virtual char const *what() const throw() {
        return "EXCEPTION CLASS: The given rational object is invalid!";
    }
};

#endif //INC_01_RATIONAL_INVALIDRATIONALEXCEPTION_H
