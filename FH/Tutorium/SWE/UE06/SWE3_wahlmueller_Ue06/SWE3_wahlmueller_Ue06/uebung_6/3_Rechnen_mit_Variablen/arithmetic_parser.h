#ifndef arithmetic_parser_h
#define arithmetic_parser_h

#include <iostream>
#include <string>

#include <exception>
#include "pfc_scanner.h"

#include <map>

using std::istream;
using std::string;

using std::runtime_error;
using std::exception;

using std::map;

//exceptions
class ParserException final : public runtime_error {
public:
    explicit ParserException(string const& message) : runtime_error{ message } { }
};

class div_by_zero_error :public exception {
public:
    virtual char const* what() const throw() {

        return "Error div by zero!";

    }
};

class variable_exception :public exception {
public:
    virtual char const* what() const throw() {

        return "Error variables!";

    }
};


class ArithmeticParser {
public:
    double parse(istream& in);
    double parse(string const& filename);
    void set_variables(string const& variable, int const number); //to definde variables

private:
    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Factor() const;
    bool is_tb_AddOp() const;
    bool is_tb_MultOp() const;
    bool is_tb_PExpression() const;
    bool is_tb_Unsigned() const;
    bool is_tb_Variable() const; //check if variable

    double parse_Expression();
    double parse_Term();
    double parse_Factor();
    double parse_AddOp();
    double parse_PExpression();

    pfc::scanner m_scanner;
    map<string, int> variables; //for storing variables

};

#endif