#include "flight_travel.h"

flight_travel::flight_travel() {

}

flight_travel::flight_travel(flight* departure_flight, flight* return_flight){
    this->departure_flights.push_back(departure_flight);
    this->return_flights.push_back(return_flight);    
}

flight_travel::~flight_travel() {
    // destructor
}

vector<flight*>& flight_travel::get_departure_flights() {
    return departure_flights;
}

vector<flight*>& flight_travel::get_return_flights() {
    return return_flights;

}

std::ostream& operator<<(std::ostream& os, flight_travel& ft) {
    if (ft.get_departure_flights().size() == 0) { // If there is no flight
        os << "Flight has no departure flight -- Invalid flight !!!!" << std::endl;
        return os;
    }
    else {
        os << "--- Departure Flight ---" << std::endl;;
        flight_travel::print_flights(os, ft.get_departure_flights());
        os << std::endl;
    }

    if (ft.get_return_flights().size() == 0) {
        os << "No Return flight" << std::endl;
    }
    else {
        os << "--- Return Flight ---" << std::endl;;
        flight_travel::print_flights(os, ft.get_departure_flights());
        os << std::endl;        
    }
    
    return os;
}

void flight_travel::print_flights(std::ostream& os, vector<flight*>& flights)
{
   
    for (size_t i = 0; i < flights.size();  i++) // print flight overview
    {
        flight* f = flights.at(i);
        if (i == 0)            
            os << f->get_departure_location() << "->" << f->get_arrival_location();
        else
            os <<  "->" << f->get_arrival_location();
    }

    os << std::endl;

    for (size_t i = 0; i < flights.size(); i++) { // print flight details
        os << flights.at(i);
    }
}