#include "prefix_parser.h"

double PrefixParser::parse(std::istream& in)
{
    this->m_scanner = pfc::scanner(in);
    return this->parse_Term();
}

double PrefixParser::parse(std::string const& filename)
{
    //init
    std::ifstream ifs(filename);
    double res = this->parse(ifs);
    ifs.close();
    return res;
}

//check for terminal beginnings
bool PrefixParser::is_tb_Term() const
{
    return this->is_tb_Operation() || this->is_tb_Number();
}

bool PrefixParser::is_tb_Operation() const
{
    return this->m_scanner.is('*')|| this->m_scanner.is('/') || this->m_scanner.is('+') || this->m_scanner.is('-');
}



bool PrefixParser::is_tb_Number() const
{
    return this->m_scanner.is_number();
}
//-----------------------

double PrefixParser::parse_Term()
{
    //check if it is a term
    if (this->is_tb_Term()) {
        //differ between number and another term
        if (this->is_tb_Number()) {
            return this->parse_Number();
        }
        else if (this->is_tb_Operation()) {
            int op = this->parse_Operation();
            this->m_scanner.next_symbol();
            double t1 = this->parse_Term();
            double t2 = this->parse_Term();

            //differ between the operations
            switch (op)
            {
            case 0:
                return t1 * t2;
                break;

            case 1:
                //throw div by zero if second term evaluates to zero 
                if (t2 == 0) {
                    throw ParserException("Division By Zero");
                }
                return t1 / t2;
                break;

            case 2:
                return t1 + t2;
                break;

            case 3:
                return t1 - t2;
                break;
            }
        }

    }
    else {
        throw ParserException("Error parsing Term");
    }
}



double PrefixParser::parse_Number()
{
    if (this->is_tb_Number()) {
        double nr = this->m_scanner.get_number();
        this->m_scanner.next_symbol();
        return nr;
    }
    else
    {
        throw ParserException("Error while parsing number");
    }
}

int PrefixParser::parse_Operation()
{
    //check which operation is beeing used
    if (is_tb_Operation()) {
        if (this->m_scanner.is('*')) {
            return 0;
        }
        else if (this->m_scanner.is('/')) {
            return 1;
        }
        else if(this->m_scanner.is('+'))
        {
            return 2;
        }
        else {
            return 3;
        }
    }
    else {
        throw ParserException("Error while parsing Operation");
    }
}
