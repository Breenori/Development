//
// Created by Anja Schwab on 25.12.22.
//

#ifndef FLUGREISEN_PERSON_H
#define FLUGREISEN_PERSON_H
#include <string>
using std::string;

class person {
public:
    person(string const & first, string const & last,string const & ad, int age_, string const & credit,string const & gd = "unkown"):first_name(first),last_name(last),gender(gd),address(ad),age(age_),credit_card(credit){}
    string const & get_first_name();
    string const & get_last_name();
    string const & get_address();
    string const & get_gender();
    int const & get_age();
    string const & get_credit_card();

private:
    string first_name;
    string last_name;
    string gender = "unknown";
    string address;
    int age;
    string credit_card;


};


#endif //FLUGREISEN_PERSON_H
