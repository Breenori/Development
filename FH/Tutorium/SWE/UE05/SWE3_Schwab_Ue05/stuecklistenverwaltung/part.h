//
// Created by Anja Schwab on 25.12.22.
//

#ifndef STUECKLISTENVERWALTUNG_PART_H
#define STUECKLISTENVERWALTUNG_PART_H
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include"storable.h"

using std::string;
using std::vector;

namespace parts_list{
    class part {
    public:
        part(string name_ );
        virtual bool equals(part* other);
        string get_name() const;
        virtual ~part(){}
    protected:
        string name;
    };

    class composite_part: public parts_list::part, storable{
    public:
        composite_part(string name_);
        composite_part(string name_, vector<part *> const & parts_list);
        ~composite_part() override;
        bool equals(part* other) override;
        void add_part(part * p);
        vector<part*> & get_parts();
        void load(string const & filename) override;
        void store(string const & filename) override;
        friend inline bool operator == (composite_part const & lhs, composite_part const & rhs);
    private:
        vector<part *> all_parts;
        void delete_parts();
        void delete_parts_rec(part * p);
        void store_rec(std::ostream & out, part * part, vector<string> & all_lines) ;
        string get_line(string name, vector<part *> p);
    };

}

#endif //STUECKLISTENVERWALTUNG_PART_H
