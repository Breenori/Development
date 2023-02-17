#pragma once
#ifndef prefix_parser_h
#define prefix_parser_h

#include <iostream>
#include <string>
#include <exception>
#include <fstream>

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

    bool is_tb_Term() const;
    bool is_tb_Operation() const;
    bool is_tb_Number() const;

    double parse_Term();
    double parse_Number();
    int parse_Operation();

    pfc::scanner m_scanner;
};

#endif
