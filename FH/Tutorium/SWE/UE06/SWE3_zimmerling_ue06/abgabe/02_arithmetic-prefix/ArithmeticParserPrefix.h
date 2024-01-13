//
// Created by arzi on 20.01.23.
//

#ifndef INC_02_ARITHMETIC_PREFIX_ARITHMETICPARSERPREFIX_H
#define INC_02_ARITHMETIC_PREFIX_ARITHMETICPARSERPREFIX_H

#include <exception>
#include <string>
#include <iostream>
#include "pfc_scanner.h"

/**
Grammar:
Expression = Operator Operand Operand | Operand .
Operator = "+" | "-" | "*" | "/" .
Operand = Unsigned | Expression .
Unsigned = Digit { Digit } .
Digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" .

 */
class ParserException final : public std::runtime_error {
public:
    explicit ParserException (std::string const & message) : std::runtime_error {message} { }
};

class ArithmeticParserPrefix {
public:
    double parse(std::istream& in);
    double parse(std::string const& filename);

private:
    bool isTbExpression() const;
    bool isTbOperator() const;
    bool isTbOperand() const;
    bool isTbUnsigned() const;

    double parseExpression();
    std::string parseOperator();
    double parseOperand();
    double parseUnsigned();

    static double calc(std::string& op, double operand1, double operand2);

    pfc::scanner scanner;
};


#endif //INC_02_ARITHMETIC_PREFIX_ARITHMETICPARSERPREFIX_H
