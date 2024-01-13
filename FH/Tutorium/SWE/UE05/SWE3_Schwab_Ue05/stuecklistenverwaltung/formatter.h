//
// Created by Anja Schwab on 25.12.22.
//

#ifndef STUECKLISTENVERWALTUNG_FORMATTER_H
#define STUECKLISTENVERWALTUNG_FORMATTER_H
#include"part.h"
#include"map"
#include<iostream>
#include<map>
#include<string>
#include<vector>
using std::string;
using std::cout;
using std::vector;

namespace formatters{
    class formatter {
    public:
        virtual void print_parts(parts_list::part * p, std::ostream & out)=0;
    };

    class hierachy_formatter: public formatter{
    public:
        void print_parts(parts_list::part * p, std::ostream & out) override;
        void print_parts_rec(parts_list::part * p, std::ostream&out, int level);

    private:
    };
    class set_formatter: public formatter{
    public:
        void print_parts(parts_list::part * p, std::ostream & out) override;
    private:
        static std::map<string,int> count_parts(vector<parts_list::part *> const & parts);
        static void count_parts_rec(vector<parts_list::part *> const & parts, std::map<string,int> & map);

    };
}



#endif //STUECKLISTENVERWALTUNG_FORMATTER_H
