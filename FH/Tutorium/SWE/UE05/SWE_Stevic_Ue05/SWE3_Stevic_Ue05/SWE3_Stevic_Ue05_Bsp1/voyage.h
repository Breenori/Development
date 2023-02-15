#ifndef voyage_h
#define voyage_h

#include "flight.h"
#include "person.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;

string print_time(time_type const& time)
{
	string to_print = "";
	if (time.hour < 10) to_print += "0";
	to_print += std::to_string(time.hour) + ":";
	if (time.minute < 10) to_print += "0";
	to_print += std::to_string(time.minute);
	return to_print;
}

string print_date(date_type const& date)
{
	string to_print = "";
	to_print += std::to_string(date.year) + "-";
	if (date.month < 10) to_print += "0";
	to_print += std::to_string(date.month) + "-";
	if (date.day < 10) to_print += "0";
	to_print += std::to_string(date.day) + "\t";
	to_print += print_time(date.time);

	return to_print;
}

class voyage
{
private:
	string voyage_departure_city;
	date_type voyage_departure_time;
	string voyage_arrival_city;
	date_type voyage_arrival_time;
	vector<flight> flights;
	size_t number_flights;
	vector<person> passengers;
	size_t number_passengers;

	friend inline ostream& operator<<(ostream& lhs, voyage const& rhs)
		//operator overloading for outputstream
	{
		lhs << "Departure city:\t" << rhs.voyage_departure_city << "\n";
		lhs << "Departure time:\t" << print_date(rhs.voyage_departure_time) << "\n\n";
		lhs << "Arrival city:\t" << rhs.voyage_arrival_city << "\n";
		lhs << "Arrival time:\t" << print_date(rhs.voyage_arrival_time) << "\n\n";

		lhs << "Stations of voyage:\t";

		for (size_t i{ 0 }; i < rhs.flights.size(); ++i)
		{
			if (i == 0) lhs << rhs.flights[i].get_departure_city();
			lhs << " -> " << rhs.flights[i].get_arrival_city();
		}
		lhs << "\n--------------------------------------------------\n";
		lhs << "Flights in total: " << rhs.number_flights << "\n\n";
		lhs << "List of flights: \n";

		for (size_t i{ 0 }; i < rhs.flights.size(); ++i)
		{
			lhs << rhs.flights[i].get_departure_city() << " -> " << rhs.flights[i].get_arrival_city() << "\n";
			lhs << "\t" << "Departure time:\t" << print_date(rhs.flights[i].get_departure_time()) << "\n";
			lhs << "\t" << "Arrival time:\t" << print_date(rhs.flights[i].get_arrival_time()) << "\n";
		}
		lhs << "--------------------------------------------------\n";
		lhs << "Passengers in total: " << rhs.number_passengers << "\n\n";
		lhs << "List of voyage passengers: \n";

		for (size_t i{ 0 }; i < rhs.passengers.size(); ++i)
		{
			lhs << rhs.passengers[i].get_first_name() << " " << rhs.passengers[i].get_last_name() << "\n";
		}
		lhs << "--------------------------------------------------\n";
		return lhs;
	}

public:

	voyage(string const& _departure_city, string const& _arrival_city,
		vector<flight> const& _flights, vector<person> const& _passengers)
	{
		this->voyage_departure_city = _departure_city;
		this->voyage_arrival_city = _arrival_city;
		this->flights = _flights;
		this->number_flights = this->flights.size();
		this->passengers = _passengers;
		this->number_passengers = this->passengers.size();
		
		this->voyage_departure_time = flights[0].get_departure_time();					//departure time of first flight
		this->voyage_arrival_time = flights[flights.size() - 1].get_arrival_time();		//arrival time of last flight
	}

	voyage(string const& _departure_city, string const& _arrival_city)
	{
		this->voyage_departure_city = _departure_city;
		this->voyage_arrival_city = _arrival_city;
		this->voyage_departure_time.day = 0;
		this->voyage_departure_time.month = 0;
		this->voyage_departure_time.year = 0;
		this->voyage_departure_time.time.hour = 0;
		this->voyage_departure_time.time.minute = 0;
		this->number_flights = 0;
		this->number_passengers = 0;
		this->flights.clear();
		this->passengers.clear();
	}

	void add_flight(flight const& next_flight)
	{
		if (flights.empty())
		{
			this->voyage_departure_time = next_flight.get_departure_time();
		}

		this->flights.push_back(next_flight);
		this->voyage_arrival_time = next_flight.get_arrival_time();
		++this->number_flights;
	}

	void add_passenger(person const& new_person)
	{
		this->passengers.push_back(new_person);
		++this->number_passengers;
	}
};

#endif