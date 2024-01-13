//
// Created by Anja Schwab on 25.12.22.
//

#ifndef FLUGREISEN_FLIGHT_H
#define FLUGREISEN_FLIGHT_H
#include <vector>
#include"person.h"
#include <string>
#include<iostream>

using std::cout;
using std::string;
using std::vector;

class flight {
public:
    void add_passenger(person * person);
    flight(string number, string airline, string dep_airport, string arr_airport, string dep_time, string arr_time, double duration);
    friend inline std::ostream & operator<<(std::ostream & lhs,flight const & rhs) {
        lhs<<rhs.number<<"\t"<<rhs.airline<<"\t"<<"Duration: "<<rhs.duration<<"\n";
        lhs<<"Departure: "<<rhs.dep_airport<<" "<<rhs.dep_time<<"\n";
        lhs<<"Arrival: "<<rhs.arr_airport<<" "<<rhs.arr_time<<"\n";
        return lhs;
    }
    vector<person *> get_passengers()const;

private:

    vector<person *> passengers;
    string number;
    string airline;
    string dep_airport;
    string arr_airport;
    string dep_time;
    string arr_time;
    double duration;// in hours

};


#endif //FLUGREISEN_FLIGHT_H
