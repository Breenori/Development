#include "arithmetic_parser_advanced.h"

void arithmetic_parser_advanced::set_variables(std::map<std::string, int> const& variables)
{
    // initialize variables
    this->m_variables = &variables;
}

bool arithmetic_parser_advanced::is_tb_Identifier() const
{
    // check if the current symbol is an identifier (variable)
	return this->m_scanner.is_identifier();
}

bool arithmetic_parser_advanced::is_tb_Unsigned() const
{
    // checks if the current symbol is a number or an identifier
    return this->m_scanner.is_number() || this->m_scanner.is_identifier();
}

bool arithmetic_parser_advanced::is_tb_Expression() const
{
    // expression must begin with a term
    return this->is_tb_Term();
}

bool arithmetic_parser_advanced::is_tb_Term() const
{
    // term must begin with a factor
    return this->is_tb_Factor();
}

bool arithmetic_parser_advanced::is_tb_Factor() const
{
    // a factor must begin with an an addop(+ or -), a number/identifier or an expression in parenthesis
    return this->is_tb_AddOp() || this->is_tb_Unsigned() || this->is_tb_PExpression();
}

bool arithmetic_parser_advanced::is_tb_PExpression() const
{
    // a p-expression must begin with an opening parenthesis
    return this->m_scanner.is('(');
}

double arithmetic_parser_advanced::parse_Expression()
{
    // Expression = Term { AddOp Term}
    if (!is_tb_Expression())
    {
        throw parser_exception("Error parsing Expression");
    }

    // get value from the first term
    double value{ this->parse_Term() };

    // add/subtract additional values from terms if existing
    while (this->is_tb_AddOp())
    {
        double const sign{ this->parse_AddOp() };   // check sign
        value += sign * this->parse_Term();
    }

    return value;
}

double arithmetic_parser_advanced::parse_Term()
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
            this->m_scanner.next_symbol('*');
            value *= this->parse_Factor();
        }
        else if (this->m_scanner.is('/'))
        {
            this->m_scanner.next_symbol('/');
            double divisor(this->parse_Factor());

            // avoid division by zero
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

double arithmetic_parser_advanced::parse_Factor()
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
        // get number (unsigned or from identifier)
        retval = retval * this->parse_Unsigned();
        return retval;
    }
    else if (this->is_tb_PExpression())
    {
        // get p-expression result
        return retval * this->parse_PExpression();
    }
    else
    {
        throw parser_exception("Error parsing Factor");
    }
}

double arithmetic_parser_advanced::parse_PExpression()
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

double arithmetic_parser_advanced::parse_Unsigned()
{
    if (this->is_tb_Identifier())
    {
        // get variable name
        std::string ident(this->m_scanner.get_identifier());
        this->m_scanner.next_symbol();

        // check if any variables have been defined
        if (this->m_variables == nullptr)
        {
            throw parser_exception("Error parse unsigned: variables expected!");
        }
        else
        {
            // check if variable is defined
            if (this->m_variables->count(ident) > 0)
            {
                // return variable value
                return this->m_variables->at(ident);
            }
            else
            {
                throw parser_exception("Error parse unsigned! Variable not found: " + ident);
            }
        }
    }
    else if (this->is_tb_Unsigned())
    {
        // if current sign is a number OR identifier but identifier is already excluded
        double retval(this->m_scanner.get_number());
        this->m_scanner.next_symbol();
        return retval;      // return unsigned value
    }
    else
    {
        throw parser_exception("Error parse unsigned");
    }
}

double arithmetic_parser_advanced::parse_AddOp()
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
