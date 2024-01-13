#ifndef air_travel_h
#define air_travel_h

#include "flight.h"
#include "person.h"
#include <vector>
#include <iostream>
#include <string>

class AirTravel {
private:
	std::vector<Flight> flights;
	std::vector<std::string> destination;
	std::vector<person::Person*> passengers;

	friend std::ostream& operator<<(std::ostream& lhs, AirTravel const& rhs);


public:
	AirTravel();
	~AirTravel();
	void addFlight(Flight flight);
	std::vector<Flight>& getFlights();
	void addDestination(std::string destination);
	void addPassenger(person::Person* passenger);
	//std::vector<person::Person*>& getPassengers();

	void printFlight(std::ostream& os) const;
	void printshortItinerary(std::ostream& os) const;
	void printItinerary(std::ostream& os) const;
	void printPassengers(std::vector<person::Person*> const persons) const;
};

std::ostream& operator<<(std::ostream& lhs, AirTravel const& rhs);

#endif // !air_travel_h
