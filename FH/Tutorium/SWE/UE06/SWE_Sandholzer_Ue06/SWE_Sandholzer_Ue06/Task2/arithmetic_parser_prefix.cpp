#include "arithmetic_parser_prefix.h"
#include <fstream>

bool arithmetic_parser_prefix::is_tb_Sub_Expression() const
{
    // sub expression must begin with an operator
    return this->is_tb_MultOp() || this->is_tb_AddOp();
}

double arithmetic_parser_prefix::parse_Expression()
{
    // Expression = Unsigned | Sub-Expression
    if (this->is_tb_Unsigned())
    {
        return this->parse_Unsigned();
    }
    else if (this->is_tb_Sub_Expression())
    {
        return this->parse_Sub_Expression();
    }
    else
    {
        throw parser_exception("Error parse expression");
    }
}

double arithmetic_parser_prefix::parse_Sub_Expression()
{
    // Sub-Expression = (AddOp | MultOp) (Unsigned | Sub-Expression) (Unsigned | Sub-Expression)
    if (this->is_tb_Sub_Expression() == false)
    {
        throw parser_exception("Error parse sub-expression");
    }

    // remember operator
    auto op(this->m_scanner.current_symbol());
    this->m_scanner.next_symbol();

    double left(1);

    // get lhs (unsigned or expression)
    if (this->is_tb_Unsigned())
    {
        left = this->parse_Unsigned();
    }
    else if (this->is_tb_Sub_Expression())
    {
        left = this->parse_Sub_Expression();
    }
    else
    {
        throw parser_exception("Error parse sub-expression left");
    }

    double right(1);

    // get rhs (unsigned or expression)
    if (this->is_tb_Unsigned())
    {
        right = this->parse_Unsigned();
    }
    else if (this->is_tb_Sub_Expression())
    {
        right = this->parse_Sub_Expression();
    }
    else
    {
        throw parser_exception("Error parse sub-expression right");
    }

    // perform operation
    if (op.is('*'))
    {
        return left * right;
    }
    else if (op.is('/'))
    {
        // avoid division by zero
        if (right == 0)
        {
            throw divide_by_zero_exception();
        }

        return left / right;
    }
    else if (op.is('+'))
    {
        return left + right;
    }
    else if (op.is('-'))
    {
        return left - right;
    }
    else
    {
        throw parser_exception("Error pasre sub-expression: invalid operation");
    }
}

double arithmetic_parser_prefix::parse_Unsigned()
{
    // Unsigned = Number
    if (this->is_tb_Unsigned() == false)
    {
        throw parser_exception("Error parse unsigned");
    }

    // return number and go to next symbol
    double retval(this->m_scanner.get_number());
    this->m_scanner.next_symbol();
    return retval;
}
