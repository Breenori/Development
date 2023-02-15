#include "person.h"


person::person() { // default constructor
    this->age = -1; // all integers get default value -1 
    this->credit_card_nr = -1;
}

person::person(string const first_name, string const last_name, string const gender, // assign constructor
    int const age, string const address, int const credit_card_nr):first_name(first_name), last_name(last_name), gender(gender), age(age), 
    address(address), credit_card_nr(credit_card_nr) {
}

person::~person() {
    // destructor
}

string person::get_first_name() {
    return first_name;
}

string person::get_last_name() {
    return last_name;
}

string person::get_gender() {
    return gender;
}

int person::get_age() {
    return age;
}

string person::get_address() {
    return address;
}

int person::get_credit_card_nr() {
    return credit_card_nr;
}

