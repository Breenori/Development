#ifndef arithmetic_parser_h
#define arithmetic_parser_h

/*
* ----- Includes. -----
*/
#include <iostream>
#include <string>
#include <exception>
#include <map>
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

    void set_variable(std::string const& var, double const& val);
    
private:    
    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Factor() const;
    bool is_tb_AddOp() const;
    bool is_tb_MultOp() const;
    bool is_tb_PExpression() const;
    bool is_tb_Unsigned() const;
    bool is_tb_Variable() const;
    
    double parse_Expression();
    double parse_Term();
    double parse_Factor();
    double parse_AddOp();
    double parse_PExpression();
    double parse_Variable();

    pfc::scanner m_scanner;
    std::map<std::string, double> variable_map; 
};

#endif /* arithmetic_parser_h */
