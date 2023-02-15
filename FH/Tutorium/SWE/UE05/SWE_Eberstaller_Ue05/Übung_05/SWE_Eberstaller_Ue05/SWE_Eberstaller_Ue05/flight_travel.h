#ifndef flight_travel_h
#define flight_travel_h

#include <string>
#include "person.h"
#include "flight.h"
#include <iostream>

using std::string;
using std::vector;

class flight_travel {
private:
	
	vector<flight*> departure_flights; 
	vector<flight*> return_flights;

public:
	flight_travel(); // default constructor
	flight_travel(flight* departure_flight, flight* return_flight); //assign constructor
	~flight_travel(); // destructor 	
	vector<flight*>& get_departure_flights(); // list of departure flights
	vector<flight*>& get_return_flights();
	static void print_flights(std::ostream& os, vector<flight*>& flights);
	// static to be able to call operator << 
};

std::ostream& operator<<(std::ostream& os, flight_travel& ft);


#endif
