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

void ArithmeticParser::set_variables(string const& variable, int const number){

    if (variable.size() == 0){

        throw variable_exception();

    }

    //map
    variables.insert_or_assign(variable, number);

}

bool ArithmeticParser::is_tb_Expression() const {

    return is_tb_Term();

}

bool ArithmeticParser::is_tb_Term() const {

    return is_tb_Factor();

}

bool ArithmeticParser::is_tb_Factor() const {

    return is_tb_AddOp() || is_tb_Unsigned() || is_tb_PExpression() || is_tb_Variable();

}

bool ArithmeticParser::is_tb_AddOp() const {

    return m_scanner.is('+') || m_scanner.is('-');

}

bool ArithmeticParser::is_tb_MultOp() const {

    return m_scanner.is('*') || m_scanner.is('/');

}

bool ArithmeticParser::is_tb_PExpression() const {

    return m_scanner.is('(');

}

//Digit
bool ArithmeticParser::is_tb_Unsigned() const {

    return m_scanner.is_number();

}

bool ArithmeticParser::is_tb_Variable() const{

    return m_scanner.is_identifier();

}

//calculate
double ArithmeticParser::parse_Expression() {

    //Exp = Term {AddOp Term}

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

    //Term = Faktor {AddOp Term}

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

    if (!is_tb_Factor()){

        throw ParserException{ "Error parsing 'Factor'." };

    }

    double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };
    double value{ 0.0 };

    if (is_tb_Unsigned()) {

        value = m_scanner.get_number();
        m_scanner.next_symbol();

    }

    else if (is_tb_Variable()) {

        string name{m_scanner.get_identifier()};

        if (variables.contains(name)) {

            value = variables.find(name)->second;
            m_scanner.next_symbol();

        }

        else{

            throw ParserException("Variable does not exist!");

        }

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

    if (!is_tb_AddOp()) {

        throw ParserException("Error parsing 'AddOp'.");

    }

    double sign{ 0.0 };

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

    if (!is_tb_PExpression()){

        throw ParserException{ "Error parsing 'PExpression'." };

    }

    m_scanner.next_symbol('(');
    double const value{ parse_Expression() };
    m_scanner.next_symbol(')');

    return value;

}