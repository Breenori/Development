#pragma once
#include "pfc_scanner.h"
#include <fstream>
#include <iostream>
#include <map>
class ParserException final : public std::runtime_error {
public:
    explicit ParserException(std::string const& message) : std::runtime_error{ message } { }
};

class DivideByZeroException final : public std::runtime_error {
public:
    explicit DivideByZeroException() : std::runtime_error{ "Divide By Zero Error." }{}
};

class Prefix_Parser {
public:
    double parse(std::istream& in);
    double parse(std::string const& filename);

private:
    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Operation() const;
    bool is_tb_Unsigned() const;

    double parse_Expression();
    double parse_Term();

    pfc::scanner m_scanner;
};