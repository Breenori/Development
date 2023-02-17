#include "arithmetic_parser_infix.h"

bool arithmetic_parser_infix::is_tb_Expression() const
{
    // expression must begin with a term
    return this->is_tb_Term();
}

bool arithmetic_parser_infix::is_tb_Term() const
{
    // term must begin with a factor
    return this->is_tb_Factor();
}

bool arithmetic_parser_infix::is_tb_Factor() const
{
    // a factor must begin with an an addop(+ or -), a number or an expression in parenthesis
    return this->is_tb_AddOp() || this->is_tb_Unsigned() || this->is_tb_PExpression();
}

bool arithmetic_parser_infix::is_tb_PExpression() const
{
    // a p-expression must begin with an opening parenthesis
    return this->m_scanner.is('(');
}

double arithmetic_parser_infix::parse_Unsigned()
{
    // returns the current number and go to the next symbol
    double result(this->m_scanner.get_number());
    this->m_scanner.next_symbol();
    return result;
}

double arithmetic_parser_infix::parse_Expression()
{
    // Expression = Term { AddOp Term}
    if (!is_tb_Expression())
    {
        throw parser_exception("Error parsing Expression");
    }

    // get value from the first term
    double value{ this->parse_Term() };

    // add/sub additional values from terms if existing
    while (this->is_tb_AddOp())
    {
        double const sign{ this->parse_AddOp() };       // get sign first
        value += sign * this->parse_Term();
    }

    return value;
}

double arithmetic_parser_infix::parse_Term()
{
    // Term = Factor { MultOp Factor }
    if (!this->is_tb_Term())
    {
        throw parser_exception("Error parsing Term");
    }

    // start by getting value from the first factor
    double value{ this->parse_Factor() };

    // multiply or divide optional additional values to/from the current value
    while (this->is_tb_MultOp())
    {
        if (this->m_scanner.is('*'))
        {
            this->m_scanner.next_symbol('*');       // assert that current symbol is *
            value *= this->parse_Factor();          // multiply the value from the next factor
        }
        else if (this->m_scanner.is('/'))
        {
            this->m_scanner.next_symbol('/');       // assert that current symbol is /
            double divisor(this->parse_Factor());   // divide the value from the next factor

            // ... check if divisor is null first
            if (divisor == 0)
            {
                throw divide_by_zero_exception();
            }
            value /= divisor;
        }
        else
        {
            throw parser_exception("Error parsing Term");
        }
    }

    return value;
}

double arithmetic_parser_infix::parse_Factor()
{
    // Factor = [AddOp] (Unsigned | PExpression)
    if (this->is_tb_Factor() == false)
    {
        throw parser_exception("Error parse factor");
    }

    double retval{ 1 };

    // check if there is a sign in front of the factor
    if (this->is_tb_AddOp())
    {
        retval = this->parse_AddOp();
    }

    if (this->is_tb_Unsigned())
    {
        // get number
        retval = retval * this->parse_Unsigned();
        return retval;
    }
    else if (this->is_tb_PExpression())
    {
        // get result from the p-expression
        return retval * this->parse_PExpression();
    }
    else
    {
        throw parser_exception("Error parsing Factor");
    }
}

double arithmetic_parser_infix::parse_PExpression()
{
    // PExpression = "(" Expression ")"
    if (this->is_tb_PExpression() == false)
    {
        throw parser_exception("Error parsing PExpression");
    }

    // open parenthesis is there - get next symbol
    this->m_scanner.next_symbol('(');

    // get value from the expression inside the p-expression
    double retval(this->parse_Expression());

    // check if p-expression ends with closing parenthesis
    if (this->m_scanner.is(')') == false)
    {
        throw parser_exception("Error parsing PExpression");
    }

    this->m_scanner.next_symbol(')');

    return retval;
}

double arithmetic_parser_infix::parse_AddOp()
{
    // AddOp = "+" | "-"
    if (this->is_tb_AddOp() == false)
    {
        throw parser_exception("Error parsing AddOp");
    }

    // return -1 if the upcoming number is negative, or +1 if positive
    if (this->m_scanner.is('+'))
    {
        this->m_scanner.next_symbol('+');
        return 1;
    }
    else if (this->m_scanner.is('-'))
    {
        this->m_scanner.next_symbol('-');
        return -1;
    }
    else
    {
        throw parser_exception("Error parsing AddOp");
    }
}
