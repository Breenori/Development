#ifndef ARITHMETIC_PARSER_INFIX_H
#define ARITHMETIC_PARSER_INFIX_H

#include "../Header Files/arithmetic_parser_base.h"

class arithmetic_parser_infix : public arithmetic_parser_base
{
public:
    arithmetic_parser_infix() = default;
    arithmetic_parser_infix(arithmetic_parser_infix const& src) = delete;
    ~arithmetic_parser_infix() = default;

protected:
    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Factor() const;
    bool is_tb_PExpression() const;

    virtual double parse_Expression() override;
    double parse_Term();
    double parse_Factor();
    double parse_PExpression();
    double parse_Unsigned();
    double parse_AddOp();
};

#endif // !arithmetic_parser_advanced_H
