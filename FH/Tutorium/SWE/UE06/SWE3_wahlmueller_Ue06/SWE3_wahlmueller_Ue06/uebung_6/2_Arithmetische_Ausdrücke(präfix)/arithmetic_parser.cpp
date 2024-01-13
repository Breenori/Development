#include "arithmetic_parser.h"
#include <fstream>

double ArithmeticParser::parse(istream& in) {

    m_scanner.set_istream(in, true);
    double const value{ parse_Expression() };
    m_scanner.set_istream();

    return value;

}

double ArithmeticParser::parse(string const& filename) {

    std::ifstream in;

    in.open(filename, std::ifstream::in);

    if (!in.good()){

        throw ParserException("stream not good!");

    }

    return parse(in);

}

bool ArithmeticParser::is_tb_Expression() const {

    return is_tb_Term() || is_tb_Unsigned();

}

//Term = Operation Term|Digit Term|Digit
bool ArithmeticParser::is_tb_Term() const {

    return is_tb_Op();

}

bool ArithmeticParser::is_tb_Op() const{

    return is_tb_AddOp() || is_tb_MultOp();

}

bool ArithmeticParser::is_tb_AddOp() const {

    return m_scanner.is('+') || m_scanner.is('-');

}

bool ArithmeticParser::is_tb_MultOp() const {

    return m_scanner.is('*') || m_scanner.is('/');

}

//Digit
bool ArithmeticParser::is_tb_Unsigned() const {

    return m_scanner.is_number();

}

//calculate
double ArithmeticParser::parse_Expression() {

    //Expression = Term|Digit

    if (!is_tb_Expression()) {

        throw ParserException("Error parsing 'Expression'.");

    }

    double value;

    if (is_tb_Unsigned()) {

        value = m_scanner.get_number();
        m_scanner.next_symbol();

    }

    else{

        value = parse_Term();

    }

    return value;

}

double ArithmeticParser::parse_Term() {

    //Term = Operation " " Term|Digit " " Term|Digit

    if (!is_tb_Term()) {

        throw ParserException("Error parsing 'Term'.");

    }

    double value;

    if (is_tb_MultOp()) {

        value = parse_MultOp();

    }

    else if (is_tb_AddOp()) {

        value = parse_AddOp();

    }

    else {

        throw ParserException("Error parsing 'Term'.");

    }

    return value;

}

double ArithmeticParser::parse_MultOp() {

    if (!is_tb_MultOp()) {

        throw ParserException("Error parsing 'MultOp'.");

    }

    double value;

    if (m_scanner.is('*')) {

        m_scanner.next_symbol();

        if (is_tb_Op()) {

            value = parse_Term();

        }

        else {

            value = m_scanner.get_number();
            m_scanner.next_symbol();

        }

        if (is_tb_Op()) {

            value *= parse_Term();

        }

        else {

            value *= m_scanner.get_number();
            m_scanner.next_symbol();

        }

    }

    else if (m_scanner.is('/')) {

        m_scanner.next_symbol();

        double temp;

        if (is_tb_Op()) {

            value = parse_Term();

        }

        else {

            value = m_scanner.get_number();
            m_scanner.next_symbol();

        }

        if (is_tb_Op()) {

            temp = parse_Term();

            if (temp == 0) {

                throw div_by_zero_error();

            }

            else{

                value /= temp;

            }

        }

        else {

            temp = m_scanner.get_number();

            if (temp == 0) {

                throw div_by_zero_error();

            }

            else {

                value /= temp;
                m_scanner.next_symbol();

            }

        }

    }

    else {

        throw ParserException("Error parsing 'MultOp'.");

    }

    return value;

}

double ArithmeticParser::parse_AddOp() {

    if (!is_tb_AddOp()) {

        throw ParserException("Error parsing 'AddOp'.");

    }

    double sign;
    double value;

    if (m_scanner.is('+')) {

        sign = 1;
        m_scanner.next_symbol();

    }

    else if (m_scanner.is('-')) {

        sign = -1;
        m_scanner.next_symbol();

    }

    else {

        throw ParserException("Error parsing 'AddOp'.");

    }

    if (is_tb_Op()) {

        value = parse_Term();

    }

    else {

        value = m_scanner.get_number();
        m_scanner.next_symbol();

    }

    if (is_tb_Op()) {

        value += sign*parse_Term();

    }

    else {

        value += sign * m_scanner.get_number();
        m_scanner.next_symbol();

    }

    return value;

}