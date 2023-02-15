#ifndef flight_h
#define flight_h

#include <string>

using std::string;

struct time_type
{
	int hour; //between 00 and 23
	int minute; //between 00 and 59
};

struct date_type
	//easier to use than existing date_types
{
	int year; // >= 2022
	int month; //between 0 and 12
	int day; //between 0 and 31

	time_type time;
};

class flight
{
private:
	int flight_number;
	string airline;
	string departure_city;
	date_type departure_time;
	string arrival_city;
	date_type arrival_time;
	time_type flight_duration;

public:

	flight(int const _flight_number, string const& _airline, string const& _departure_city,
		date_type const& _departure_time, string const& _arrival_city, date_type const& _arrival_time,
		time_type const& _flight_duration)
	{
		this->flight_number = _flight_number;
		this->airline = _airline;
		this->departure_city = _departure_city;
		this->departure_time = _departure_time;
		this->arrival_city = _arrival_city;
		this->arrival_time = _arrival_time;
		this->flight_duration = _flight_duration;
	}

	int get_flight_number() const
	{
		return this->flight_number;
	}

	string get_departure_city() const
	{
		return this->departure_city;
	}

	date_type get_departure_time() const
	{
		return this->departure_time;
	}

	string get_arrival_city() const
	{
		return this->arrival_city;
	}

	date_type get_arrival_time() const
	{
		return this->arrival_time;
	}

	time_type get_flight_duration() const
	{
		return this->flight_duration;
	}

};
#endif