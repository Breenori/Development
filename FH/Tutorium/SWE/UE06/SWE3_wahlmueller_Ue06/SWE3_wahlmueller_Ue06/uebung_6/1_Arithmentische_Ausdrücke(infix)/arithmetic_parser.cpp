#include "arithmetic_parser.h"

//parse grammar
double ArithmeticParser::parse(istream& in) {

    m_scanner.set_istream(in, true);
    double const value{ parse_Expression() };
    m_scanner.set_istream();

    return value;

}

double ArithmeticParser::parse(string const& filename) {

    ifstream in;

    in.open(filename, ifstream::in);

    if (!in.good()){

        throw ParserException("stream not good!");

    }

    return parse(in);

}

//grammar rules
//= Term { AddOp Term }
bool ArithmeticParser::is_tb_Expression() const {

    return is_tb_Term();

}

//= Factor { MultOp Factor }
bool ArithmeticParser::is_tb_Term() const {

    return is_tb_Factor();

}

//= [ AddOp ] ( Unsigned | PExpression )
bool ArithmeticParser::is_tb_Factor() const {

    return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression();

}

//= ”+“ | ”−“
bool ArithmeticParser::is_tb_AddOp() const {

    return m_scanner.is('+') || m_scanner.is('-');

}

//= ”·“ | ”/“
bool ArithmeticParser::is_tb_MultOp() const {

    return m_scanner.is('*') || m_scanner.is('/');

}

// ”(“ Expression ”)“
bool ArithmeticParser::is_tb_PExpression() const {

    return m_scanner.is('(');

}

// (Digit) = ”0“ | ”1“ | ”2“ | ”3“ | ”4“ | ”5“ | ”6“ | ”7“ | ”8“ | ”9“
bool ArithmeticParser::is_tb_Unsigned() const {

    return m_scanner.is_number();

}

//parse functions
double ArithmeticParser::parse_Expression() {

    //= Term { AddOp Term }

    if (!is_tb_Expression()) {

        throw ParserException("Error parsing 'Expression'.");

    }

    double value{ parse_Term() };

    while (is_tb_AddOp()) {

        double const sign{ parse_AddOp() };
        value += sign * parse_Term();

    }

    return value;

}

double ArithmeticParser::parse_Term() {

    //= Factor { MultOp Factor }

    if (!is_tb_Term()) {

        throw ParserException("Error parsing 'Term'.");

    }

    double value{ parse_Factor() };

    while (is_tb_MultOp()) {

        if (m_scanner.is('*')) {

            m_scanner.next_symbol('*');
            value *= parse_Factor();

        }

        else if (m_scanner.is('/')) {

            m_scanner.next_symbol('/');
            double check_factor{ parse_Factor() };

            if (check_factor == 0) {
                throw div_by_zero_error();
            }

            value /= check_factor;

        }

        else {

            throw ParserException("Error parsing 'Term'.");

        }

    }

    return value;

}

double ArithmeticParser::parse_Factor() {

    //= [ AddOp ] ( Unsigned | PExpression )

    if (!is_tb_Factor()){

        throw ParserException{ "Error parsing 'Factor'." };

    }

    double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };
    double value;

    if (is_tb_Unsigned()) {

        value = m_scanner.get_number();
        m_scanner.next_symbol();

    }

    else if (is_tb_PExpression()) {

        value = parse_PExpression();

    }

    else{

        throw ParserException{ "Error parsing 'Factor'." };

    }

    return sign * value;

}

double ArithmeticParser::parse_AddOp() {

    //= ”+“ | ”−“

    if (!is_tb_AddOp()) {

        throw ParserException("Error parsing 'AddOp'.");

    }

    double sign;

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

    return sign;

}

double ArithmeticParser::parse_PExpression() {

    // ”(“ Expression ”)“

    if (!is_tb_PExpression()){

        throw ParserException{ "Error parsing 'PExpression'." };

    }

    m_scanner.next_symbol('(');
    double const value{ parse_Expression() };
    m_scanner.next_symbol(')');

    return value;

}