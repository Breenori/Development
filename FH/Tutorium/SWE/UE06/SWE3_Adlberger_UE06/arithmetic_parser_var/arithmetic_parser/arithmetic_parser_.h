#ifndef arithmetic_parser_h
#define arithmetic_parser_h

#include <iostream>
#include <string>
#include <exception>
#include "scanner.h"
#include <map>

class ParserException final : public std::runtime_error {
public:
    explicit ParserException(std::string const& message) : std::runtime_error{ message } { }
};
class ArithmeticParser {
public:
    double parse(std::istream& in);
    double parse(std::string const& filename);

private:
    std::map<std::string, int> vars;
    void initialize();
    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Factor() const;
    bool is_tb_AddOp() const;
    bool is_tb_MultOp() const;
    bool is_tb_PExpression() const;
    bool is_tb_Unsigned() const;
    bool is_tb_Identifier()const;

    double parse_Expression();
    double parse_Term();
    double parse_Factor();
    double  parse_AddOp();
    double parse_PExpression();
    double get_Identifier_value(std::string x);


    pfc::scanner m_scanner;
};

#endif /* arithmetic_parser_h */
