//
// Created by Anja Schwab on 25.12.22.
//

#include "flight.h"

void flight::add_passenger(person *person) {
    passengers.push_back(person);

}


flight::flight(string number, string airline, string dep_airport, string arr_airport, string dep_time, string arr_time,
               double duration)
        :number(number),airline(airline), dep_airport(dep_airport), arr_airport(arr_airport), dep_time(dep_time), arr_time(arr_time), duration(duration) {

}

vector<person *> flight::get_passengers() const {
    return passengers;
}



