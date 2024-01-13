#ifndef prefix_parser_h
#define prefix_parser_h

#include <iostream>
#include <string>
#include <exception>
#include "pfc_scanner.h"

class ParserException final : public std::runtime_error {
public:
    explicit ParserException(std::string const& message) : std::runtime_error{ message } { }
};

class PrefixParser {
public:
    double parse(std::istream& in);
    double parse(std::string const& filename);

private:

    bool is_tb_Expression() const;
    bool is_tb_BinaryOp() const;
    bool is_tb_Term() const;
    bool is_tb_AddOp() const;
    bool is_tb_MultOp() const;
    bool is_tb_Unsigned() const;

    double parse_Expression(); // becuase this function is recursive, we only need the one :)!
    double parse_AddOp(); // (and the parse AddOp)


    pfc::scanner m_scanner;
};

#endif 
