#ifndef arithmetic_variable_parser_h
#define arithmetic_variable_parser_h

#include <iostream>
#include <string>
#include <exception>
#include <map>
#include "pfc_scanner.h"

class ParserException final : public std::runtime_error {
public:
    explicit ParserException(std::string const& message) : std::runtime_error{ message } { }
};

class ArithmeticVariableParser {
public:
    double parse(std::istream& in);
    double parse(std::string const& filename);

    void createVarible(std::string const& name, double const value);
    void updateVarible(std::string const& name, double const value);
    void deleteVarible(std::string const& name);

private:

    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Factor() const;
    bool is_tb_AddOp() const;
    bool is_tb_MultOp() const;
    bool is_tb_PExpression() const;
    bool is_tb_Unsigned() const;
    bool is_tb_Var() const;

    double parse_Expression();
    double parse_Term();
    double parse_Factor();
    double parse_AddOp();
    double parse_PExpression();
    double parse_Variable();

    pfc::scanner m_scanner;
    std::map<std::string, double> varList;

};

#endif /* arithmetic_parser_h */
