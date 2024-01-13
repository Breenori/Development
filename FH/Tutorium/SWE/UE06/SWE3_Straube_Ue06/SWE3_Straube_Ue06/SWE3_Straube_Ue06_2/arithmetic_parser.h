#ifndef arithmetic_parser_h
#define arithmetic_parser_h

/*
* ----- Includes. -----
*/
#include <iostream>
#include <string>
#include <exception>
#include "pfc_scanner.h"

/*
* Class ParserException.
*/
class ParserException final : public std::runtime_error {
public:
    explicit ParserException (std::string const & message) : std::runtime_error {message} { }
};

/*
* Class ArithmeticParser.
*/
class ArithmeticParser {
public:
    double parse (std::istream & in);
    double parse (std::string const & filename);
    
private:    
    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Operator() const;
    bool is_tb_Unsigned() const;
    
    double parse_Expression();
    double parse_Term();
    double parse_Operator();

    pfc::scanner m_scanner;
};

#endif /* arithmetic_parser_h */
