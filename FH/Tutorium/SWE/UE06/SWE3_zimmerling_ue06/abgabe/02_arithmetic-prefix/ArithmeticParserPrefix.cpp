//
// Created by arzi on 20.01.23.
//

#include <stack>
#include <iostream>
#include "ArithmeticParserPrefix.h"


double ArithmeticParserPrefix::parse(std::istream &in) {
    scanner.set_istream(in, true);
    auto const value = parseExpression();
    scanner.set_istream();
    return value;
}

double ArithmeticParserPrefix::parse(const std::string &filename) {
    std::istringstream in {filename};
    return parse(in);
}

// ----------------------------------------------------------------------------

bool ArithmeticParserPrefix::isTbExpression() const {
    return isTbOperator() || isTbOperand();
}

bool ArithmeticParserPrefix::isTbOperator() const {
    return scanner.is('+') | scanner.is('-') | scanner.is('*') | scanner.is('/');

}

bool ArithmeticParserPrefix::isTbOperand() const {
    return scanner.is_number() || isTbExpression();
}

bool ArithmeticParserPrefix::isTbUnsigned() const {
    return scanner.is_number();
}

// ----------------------------------------------------------------------------


double ArithmeticParserPrefix::parseExpression() {
    if (!isTbExpression()) {
        throw ParserException("Error parsing 'expression'.");
    }

    if (isTbOperator()) {
        std::string op = parseOperator();
        scanner.next_symbol();
        double operand1 = parseOperand();
        scanner.next_symbol();
        double operand2 = parseOperand();
        return calc(op, operand1, operand2);
    } else {
        return parseOperand();
    }
}

std::string ArithmeticParserPrefix::parseOperator() {
    if (!isTbOperator()) {
        throw ParserException("Error parsing 'operator'.");
    }
    std::string op;
    if (scanner.is('+')) {
        op = "+";
    } else if (scanner.is('/')) {
        op = "/";
    } else if (scanner.is('-')) {
        op = "-";
    } else if (scanner.is('*')) {
        op = "*";
    } else {
        throw ParserException("Error parsing 'operator'.");
    }
    return op;
}

double ArithmeticParserPrefix::parseOperand() {
    if (!isTbOperand()) {
        throw ParserException("Error parsing 'operand'.");
    }
    if (isTbUnsigned()) {
        return parseUnsigned();
    } else {
        return parseExpression();
    }
}

double ArithmeticParserPrefix::parseUnsigned() {
    if (!isTbUnsigned()) {
        throw ParserException("Error parsing 'unsigned'.");
    }
    double value = scanner.get_number();
    return value;
}

double ArithmeticParserPrefix::calc(std::string &op, double operand1, double operand2) {
    double result;
    if (op == "+") {
        result = operand1 + operand2;
    } else if (op == "-") {
        result = operand1 - operand2;
    } else if (op == "*") {
        result = operand1 * operand2;
    } else if (op == "/") {
        if (operand2 == 0) {
            throw ParserException("Division by zero not allowed.");
        }
        result = operand1 / operand2;
    } else {
        throw ParserException("Error parsing 'expression'.");
    }
    return result;
}
