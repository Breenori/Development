#include "flight.h"


flight::flight(): flight_nr(-1), flight_duration(-1), departure_time ("00:00"), departure_location("invalid start"), arrival_location ("invalid end"), arrival_time("00:00") { // Default constructor
      
}

flight::flight(int const flight_nr, string const airline, string const arrival_location, //assign constructor
    string departure_location, string  const departure_time, string  arrival_time, double flight_duration) : flight_nr(flight_nr), airline(airline), 
    arrival_location(arrival_location), departure_location(departure_location), departure_time(departure_time), arrival_time(arrival_time), flight_duration(flight_duration) {    
}

flight::~flight() {
    // destructor
}

int flight::get_flight_nr() {
    return flight_nr;
}

string flight::get_airline() {
    return airline;
}

string flight::get_departure_location() {
    return departure_location;
}

string flight::get_arrival_location() {
    return arrival_location;
}

string  flight::get_departure_time() {
    return departure_time;
}

string  flight::get_arrival_time() {
    return arrival_time;
}

double flight::get_flight_duration() {
    return flight_duration;
}

void flight::add_person(person* p) {
    this->persons.push_back(p);
}

vector<person*>& flight::get_persons() {
    return this->persons;

}


std::ostream& operator<<(std::ostream& os, flight* f) {

    os << f->get_airline() << " Nr: " << f->get_flight_nr() << " From " << f->get_arrival_location() << " To " << f->get_departure_location() << " Duration: " << f->get_flight_duration() << "h" << std::endl;
    os << "--- Passenger List ---" << std::endl;
    for (size_t i = 0; i < f->get_persons().size(); i++)
    {
        person* p = f->get_persons().at(i);
        os << p->get_first_name() << " " << p->get_last_name() << std::endl;
    }
    return os;
}