//
// Created by arzi on 09.01.23.
//


/**
 *
Expression = Term { AddOp Term } .
Term = Factor { MultOp Factor } .
Factor = [ AddOp ] ( Unsigned | PExpression ) .
Unsigned = Digit { Digit } .
PExpression = ”(“ Expression ”)“ .
AddOp = ”+“ | ”−“ .
MultOp = ”·“ | ”/“ .
Digit = ”0“ | ”1“ | ”2“ | ”3“ | ”4“ | ”5“ | ”6“ | ”7“ | ”8“ | ”9“ .
 */


#include "arithmetic_parser.h"
#include "fstream"

double ArithmeticParserInfix::parse(std::istream &in) {
    m_scanner.set_istream (in, true);
    auto const value {parse_Expression ()};
    m_scanner.set_istream ();

    return value;
}

double ArithmeticParserInfix::parse(std::string const& filename) {
    std::istringstream in {filename};
    return parse (in);
}

// ----------------------------------------------------------------------------

bool ArithmeticParserInfix::is_tb_Expression() const {
    return is_tb_Term();
}

bool ArithmeticParserInfix::is_tb_Term() const {
    return is_tb_Factor();
}

bool ArithmeticParserInfix::is_tb_Factor() const {
    return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression();
}

bool ArithmeticParserInfix::is_tb_AddOp() const {
    return m_scanner.is('+') || m_scanner.is('-');
}

bool ArithmeticParserInfix::is_tb_MultOp() const {
    return m_scanner.is('*') || m_scanner.is('/');

}

bool ArithmeticParserInfix::is_tb_PExpression() const {
    return m_scanner.is('(');
}

bool ArithmeticParserInfix::is_tb_Unsigned() const {
    return m_scanner.is_number();
}

// ----------------------------------------------------------------------------

double ArithmeticParserInfix::parse_Expression() {
    // Expression = Term { AddOp Term }
    if (!is_tb_Expression()) {
        throw ParserException("Error parsing 'expression'.");
    }

    double value { parse_Term() };

    while (is_tb_AddOp()) {
        double const sign { parse_AddOp() };
        value += sign * parse_Term();
    }

    return value;
}

double ArithmeticParserInfix::parse_Term() {
    // Term = Factor { MultOp Factor }
    if (!is_tb_Term()) {
        throw ParserException("Error parsing 'expression'.");
    }

    double value { parse_Factor() };

    while (is_tb_MultOp()) {
        if (m_scanner.is('*')) {
            m_scanner.next_symbol('*');
            value *= parse_Factor();
        } else if (m_scanner.is('/')) {
            m_scanner.next_symbol('/');
            double div = parse_Factor();
            if (div == 0) {
                std::cout << "Division by zero" << std::endl;
                throw ParserException("Division by zero");
            }
//            value /= parse_Factor();
            value /= div;
        } else {
            throw ParserException("Error parsing 'Term'.");
        }
    }

    return value;
}

double ArithmeticParserInfix::parse_Factor() {
    if (!is_tb_Factor ())
        throw ParserException {"Error parsing 'Factor'."};

    auto const sign {is_tb_AddOp () ? parse_AddOp () : 1.0};
    double value {0.0};

    if (m_scanner.is_number()) {
        value = m_scanner.get_number ();
        m_scanner.next_symbol ();

    } else if (is_tb_PExpression ()) {
        value = parse_PExpression ();
    }
    else
        throw ParserException {"Error parsing 'Factor'."};

    return sign * value;
}

double ArithmeticParserInfix::parse_AddOp() {
    if (!is_tb_AddOp ())
        throw ParserException {"Error parsing 'AddOp'."};

    double sign {0.0};

    if (m_scanner.is ('+')) {
        sign =  1;
        m_scanner.next_symbol ();
    }
    else if (m_scanner.is ('-')) {
        sign = -1;
        m_scanner.next_symbol ();
    }
    else
        throw ParserException {"Error parsing 'AddOp'."};

    return sign;
}

double ArithmeticParserInfix::parse_PExpression() {
    if (!is_tb_PExpression ())
        throw ParserException {"Error parsing 'PExpression'."};

    m_scanner.next_symbol ('(');
    auto const value {parse_Expression ()};
    m_scanner.next_symbol (')');

    return value;
}
