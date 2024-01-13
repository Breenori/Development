//
// Created by Hakim Bajim on 10.11.22.
//

#ifndef SWE_BAJIM_UE03_DIV_BY_ZERO_H
#define SWE_BAJIM_UE03_DIV_BY_ZERO_H


#include <iostream>
#include <exception>

class div_by_zero : public std::exception{
public:
    const char* what() {
        return "Division by zero error";
    }

};


#endif //SWE_BAJIM_UE03_DIV_BY_ZERO_H
