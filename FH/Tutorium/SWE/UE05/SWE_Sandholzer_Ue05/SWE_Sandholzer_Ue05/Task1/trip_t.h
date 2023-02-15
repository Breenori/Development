#ifndef TRIP_T_H
#define TRIP_T_H

#include "flight_t.h"
#include <vector>

class trip_t
{
	using flights_t = std::vector<flight_t const*>;

	std::string trip_name;
	flights_t outbound_flights;
	flights_t return_flights;

	friend std::ostream& operator<< (std::ostream& out, trip_t const& trip);

public:
	trip_t();
	trip_t(std::string const& trip_name);
	trip_t(trip_t const& src) = delete;
	~trip_t() = default;

	void add_return_flight(flight_t const* const flight);
	void add_outbound_flight(flight_t const* const flight);

private:
	static std::ostream& print_flights(std::ostream& out, flights_t const& flights);
	static std::string const& default_trip_name();
};

std::ostream& operator<< (std::ostream& out, trip_t const& trip);

#endif // !TRIP_T_H
