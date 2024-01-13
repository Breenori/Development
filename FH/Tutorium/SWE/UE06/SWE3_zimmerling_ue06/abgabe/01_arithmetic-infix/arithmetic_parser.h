#ifndef arithmetic_parser_h
#define arithmetic_parser_h

#include <iostream>
#include <string>
#include <exception>
#include "pfc_scanner.h"

class ParserException final : public std::runtime_error {
public:
    explicit ParserException (std::string const & message) : std::runtime_error {message} { }
};

class ArithmeticParserInfix {
public:
    double parse (std::istream & in);
    double parse (std::string const & filename);
    
private:
    
    bool is_tb_Expression() const; // tb ... terminal-beginning
    bool is_tb_Term() const;
    bool is_tb_Factor() const;
    bool is_tb_Unsigned() const;
    bool is_tb_PExpression() const;
    bool is_tb_AddOp() const;
    bool is_tb_MultOp() const;
    // bool_is_digit == m_scanner.is_number()

    double parse_Expression();
    double parse_Term();
    double parse_Factor();
    double parse_AddOp();
    double parse_PExpression();

    pfc::scanner m_scanner;
};

#endif /* arithmetic_parser_h */
