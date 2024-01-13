//
// Created by Anja Schwab on 25.12.22.
//

#include "flight_trip.h"






void flight_trip::add_passenger(person *person) {
    for (int i = 0; i < flights.size(); ++i) {
        flights[i]->add_passenger(person);
    }
}



void flight_trip::print(std::ostream & out) const {

    out<<"Details of this trip:\n";
    for (int i = 0; i < flights.size(); ++i) {
        out <<*flights[i];
    }
    out<<"\n";

}

void flight_trip::add_flights(vector<flight *> const & flights) {
    this->flights = flights;
}

void flight_trip::print_passenger_list(std::ostream & out) {
    out<<"Print all passengers:\n";
    for (int i = 0; i < flights.size(); ++i) {
        vector<person * > passengers =flights[i]->get_passengers() ;
        for (int j = 0; j < passengers.size(); ++j) {
            out <<passengers[j]->get_first_name()<<" "<<passengers[j]->get_last_name()<<"\n";
        }
    }
}


