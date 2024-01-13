#ifndef FLIGHT_T_H
#define FLIGHT_T_H

#include <string>
#include <iostream>
#include <time.h>

class flight_t
{
	int flight_number;
	std::string airline_name;
	std::string departure_airport;
	std::string destinaion_airport;
	std::string departure_time;
	std::string arrival_time;
	double travel_time;

	friend std::ostream& operator<< (std::ostream& out, flight_t const& flight);

public:
	flight_t(int const flight_number, std::string const& airline_name, std::string const& departure_airport,
		std::string const& destination_airport, std::string const& departure_time,
		std::string const& arrival_time, double const travel_time);
	flight_t() = delete;
	flight_t(flight_t const& src) = delete;
	~flight_t() = default;

	std::string const& get_des_airport() const;
	std::string const& get_dep_airport() const;
};

std::ostream& operator<< (std::ostream& out, flight_t const& flight);

#endif // !FLIGHT_T_H
