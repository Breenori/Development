#include "trip_t.h"

// creates trip with default name
trip_t::trip_t() : trip_t(default_trip_name())
{}	

trip_t::trip_t(std::string const& trip_name)
{
	// init trip
	this->trip_name = trip_name;
	this->outbound_flights.clear();
	this->return_flights.clear();
}

std::ostream& trip_t::print_flights(std::ostream& out, flights_t const& flights)
{
	// prints the route of the flights or "no flights" if there are no
	if (flights.size() > 0)
	{
		out << flights[0]->get_dep_airport();
		for (size_t i{ 0 }; i < flights.size(); ++i)
		{
			out << " -> " << flights[i]->get_des_airport();
		}
	}
	else
	{
		out << "no flights";
	}

	return out;
}

std::string const& trip_t::default_trip_name()
{
	// default name
	static const std::string def_trip{ "unnamed trip" };
	return def_trip;
}

void trip_t::add_outbound_flight(flight_t const* const flight)
{
	// add flight if existing
	if (flight != nullptr)
	{
		this->outbound_flights.push_back(flight);
	}
}

void trip_t::add_return_flight(flight_t const* const flight)
{
	// add flight if existing
	if (flight != nullptr)
	{
		this->return_flights.push_back(flight);
	}
}

std::ostream& operator<<(std::ostream& out, trip_t const& trip)
{
	// prints the trip infos, first the name
	out << trip.trip_name << ":\noutbound flights: ";

	// then all outbound flights
	trip.print_flights(out, trip.outbound_flights) << "\nreturning flights: ";

	// and finally the return flights
	return trip.print_flights(out, trip.return_flights) << std::endl;
}
