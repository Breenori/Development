#ifndef arithmetic_parser_h
#define arithmetic_parser_h

#include <iostream>
#include <string>
#include <exception>
#include "scanner.h"

class ParserException final : public std::runtime_error {
public:
    explicit ParserException(std::string const& message) : std::runtime_error{ message } { }
};
class ArithmeticParser {
public:
    double parse(std::istream& in);
    double parse(std::string const& filename);

private:

    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Signed() const;
    bool is_tb_Op()const;
    bool is_tb_AddOp() const;
    bool is_tb_MultOp() const;
    bool is_tb_Unsigned() const;

    double parse_Expression();
    double parse_Term();
    char parse_Op();
    double  parse_AddOp();
    double parse_PExpression();

    pfc::scanner m_scanner;
};

#endif /* arithmetic_parser_h */
