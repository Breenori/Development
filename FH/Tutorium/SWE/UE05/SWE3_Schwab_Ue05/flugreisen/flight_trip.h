//
// Created by Anja Schwab on 25.12.22.
//

#ifndef FLUGREISEN_FLIGHT_TRIP_H
#define FLUGREISEN_FLIGHT_TRIP_H
#include<vector>
#include"flight.h"
#include"person.h"
#include<iostream>

using std::cout;
using std::vector;

class flight_trip {
public:
    flight_trip():flights(){}
    flight_trip(vector<flight *> flights):flights(flights){}
    void add_flights(vector<flight *> const & flights);
    void add_passenger(person * person);
    friend inline std::ostream & operator<<(std::ostream & lhs,flight_trip const & rhs ){
        rhs.print(lhs);
        return lhs;
    }
    void print_passenger_list(std::ostream & out);
private:
    void print(std::ostream & out) const;
    vector<flight*> flights;




};


#endif //FLUGREISEN_FLIGHT_TRIP_H
