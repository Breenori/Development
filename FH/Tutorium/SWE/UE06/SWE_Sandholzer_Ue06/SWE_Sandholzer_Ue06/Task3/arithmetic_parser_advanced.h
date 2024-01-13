#ifndef ARITHMETIC_PARSER_ADVANCED_H
#define ARITHMETIC_PARSER_ADVANCED_H

#include "../Header Files/arithmetic_parser_base.h"
#include <map>

class arithmetic_parser_advanced : public arithmetic_parser_base
{
public:
    arithmetic_parser_advanced() = default;
    arithmetic_parser_advanced(arithmetic_parser_advanced const& src) = delete;
    ~arithmetic_parser_advanced() = default;

    void set_variables(std::map<std::string, int> const& variables);

protected:
    std::map<std::string, int> const* m_variables{ nullptr };

    virtual bool is_tb_Identifier() const;
    virtual bool is_tb_Unsigned() const override;
    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Factor() const;
    bool is_tb_PExpression() const;

    double parse_Unsigned();
    double parse_Expression();
    double parse_Term();
    double parse_Factor();
    double parse_PExpression();
    double parse_AddOp();
};

#endif // !ARITHMETIC_PARSER_ADVANCED_H
