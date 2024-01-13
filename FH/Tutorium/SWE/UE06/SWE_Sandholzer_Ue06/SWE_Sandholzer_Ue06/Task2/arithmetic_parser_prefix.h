#ifndef ARITHMETIC_PARSER_PREFIX
#define ARITHMETIC_PARSER_PREFIX

#include "../Header Files/arithmetic_parser_base.h"

class arithmetic_parser_prefix : public arithmetic_parser_base
{
public:
    arithmetic_parser_prefix() = default;
    arithmetic_parser_prefix(arithmetic_parser_prefix const& src) = delete;
    ~arithmetic_parser_prefix() = default;

protected:
    bool is_tb_Sub_Expression() const;

    virtual double parse_Expression() override;
    double parse_Sub_Expression();
    double parse_Unsigned();
};

#endif // !ARITHMETIC_PARSER_PREFIX
