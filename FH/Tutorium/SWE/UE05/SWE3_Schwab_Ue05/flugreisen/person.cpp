//
// Created by Anja Schwab on 25.12.22.
//

#include "person.h"

string const &person::get_last_name() {
    return last_name;
}

string const &person::get_first_name() {
    return first_name;
}

string const &person::get_address() {
    return address;
}

string const &person::get_gender() {
    return gender;
}

int const &person::get_age() {
    return age;
}

string const &person::get_credit_card() {
    return credit_card;
}
