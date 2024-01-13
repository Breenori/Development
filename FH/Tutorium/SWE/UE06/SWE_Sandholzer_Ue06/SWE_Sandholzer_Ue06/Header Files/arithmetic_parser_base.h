#ifndef ARITHMETIC_PARSER_BASE_H
#define ARITHMETIC_PARSER_BASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "pfc_scanner.h"

/* custom exceptions */

class parser_exception final : public std::runtime_error {
public:
    explicit parser_exception(std::string const & message) : std::runtime_error {message} { }
};

class divide_by_zero_exception : public std::exception
{
public:
    virtual char const* what() const throw()
    {
        return "Divide by 0 Error!";
    }
};

/* parser base class */

class arithmetic_parser_base {
public:
    /// <summary>
    /// parse expression from a given istream
    /// </summary>
    /// <returns>expression result</returns>
    virtual double parse (std::istream & in)
    {
        this->m_scanner.set_istream(in);

        double result(this->parse_Expression());

        if (this->m_scanner.is_eof() == false)
        {
            throw parser_exception("Error finished parsing Expression (with result = " 
                + std::to_string(result) + ") before eof");
        }

        return result;
    }

    /// <summary>
    /// parse expression from a given file
    /// </summary>
    /// <returns>expression result</returns>
    virtual double parse(std::string const& filename)
    {
        std::ifstream ifs(filename);

        double result(this->parse(ifs));

        ifs.close();

        return result;
    }

    /// <summary>
    /// prints the content from a given istream onto an output stream
    /// </summary>
    static std::ostream& print_file_content(std::istream& in, std::ostream& out = std::cout)
    {
        std::string tmp("");

        while (in.good())
        {
            in >> tmp;
            out << tmp << " ";
        }

        return out;
    }

    /// <summary>
    /// prints the content from a file onto an output stream
    /// </summary>
    static std::ostream& print_file_content(std::string const& file_name, std::ostream& out = std::cout)
    {
        std::ifstream ifs(file_name);
        
        print_file_content(ifs, out);

        ifs.close();
        return out;
    }

protected:
    arithmetic_parser_base() = default;
    arithmetic_parser_base(arithmetic_parser_base const& src) = delete;
    virtual ~arithmetic_parser_base() = default;

    /// <summary>
    /// checks if the current symbol is a + or a -
    /// </summary>
    virtual bool is_tb_AddOp() const
    {
        return this->m_scanner.is('+') || this->m_scanner.is('-');
    }

    /// <summary>
    /// checks if the current symbol is a * or a /
    /// </summary>
    virtual bool is_tb_MultOp() const
    {
        return this->m_scanner.is('*') || this->m_scanner.is('/');
    }

    /// <summary>
    /// checks if the current symbol is a number
    /// </summary>
    virtual bool is_tb_Unsigned() const
    {
        return this->m_scanner.is_number();
    }
    
    /// <summary>
    /// is called to parse an expression, every arithmetic parser needs to implement it
    /// </summary>
    virtual double parse_Expression() = 0;

    /// <summary>
    /// our scanner :)
    /// </summary>
    pfc::scanner m_scanner;
};

#endif /* ARITHMETIC_PARSER_BASE_H */
