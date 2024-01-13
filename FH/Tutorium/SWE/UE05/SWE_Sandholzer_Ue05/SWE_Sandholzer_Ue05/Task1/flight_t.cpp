#include "flight_t.h"

flight_t::flight_t(int const flight_number, std::string const& airline_name, 
	std::string const& departure_airport, std::string const& destination_airport, 
	std::string const& departure_time, std::string const& arrival_time, double const travel_time)
{
	// init flight
	this->flight_number = flight_number;
	this->airline_name = airline_name;
	this->departure_airport = departure_airport;
	this->destinaion_airport = destination_airport;
	this->departure_time = departure_time;
	this->arrival_time = arrival_time;
	this->travel_time = travel_time;
}

std::string const& flight_t::get_des_airport() const
{
	// gets destination airport
	return this->destinaion_airport;
}

std::string const& flight_t::get_dep_airport() const
{
	// gets departure airport
	return this->departure_airport;
}

std::ostream& operator<<(std::ostream& out, flight_t const& flight)
{
	// print flight data and return out stream
	return out << "#" << flight.flight_number << " " << flight.departure_airport << " -> "
		<< flight.destinaion_airport << " " << flight.departure_time << " - " << flight.arrival_time
		<< " (" << flight.travel_time << "h) by " << flight.airline_name;
}
