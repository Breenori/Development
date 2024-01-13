#ifndef arithmetic_parser_h
#define arithmetic_parser_h

#include <iostream>
#include <string>

#include <exception>
#include "pfc_scanner.h"

using std::istream;
using std::string;

using std::runtime_error;
using std::exception;

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


class ArithmeticParser {
public:
    double parse(istream& in);
    double parse(string const& filename);

private:
    //predicates
    bool is_tb_Expression() const; //= Term|Digit
    bool is_tb_Term() const; //= Operation „space“ Term|Digit „space“ Term|Digit
    bool is_tb_Op() const; //= „+“ | „-“ | „:“ | „*“
    bool is_tb_AddOp() const; //= ”+“ | ”−“
    bool is_tb_MultOp() const; //= ”·“ | ”/“
    bool is_tb_Unsigned() const; // - Digit = ”0“ | ”1“ | ”2“ | ”3“ | ”4“ | ”5“ | ”6“ | ”7“ | ”8“ | ”9“

    double parse_Expression();
    double parse_Term();
    double parse_MultOp();
    double parse_AddOp();

    pfc::scanner m_scanner;

};

#endif