#include "travel_agency.h"

using travel_agency::flight;
using travel_agency::flight_travel;
using travel_agency::person;

person::person() {

}

person::person(string const first_name, string const last_name, string const gender,
	int const age, string const address, int const credit_card_nr) {



    this->first_name = first_name;
    this->last_name = last_name;
    this->gender = gender;
    this->age = age;
    this->address = address;
    this->credit_card_nr = credit_card_nr;
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













