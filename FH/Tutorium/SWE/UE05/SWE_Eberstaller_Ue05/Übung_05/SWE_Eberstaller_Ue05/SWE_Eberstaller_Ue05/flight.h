#ifndef flight_h
#define flight_h

#include <string>
#include <vector>
#include <iostream>
#include "person.h"

using std::string;
using std::vector;

class flight {
private:
	int flight_nr;
	string airline;
	string departure_location;
	string arrival_location;
	string departure_time;
	string arrival_time;
	double flight_duration;
	vector<person*> persons;
public:
	flight(); // default constructor
	flight(int const flight_nr, string const airline, string const arrival_location, // assign constructor
		string departure_location, string  const departure_time, string  arrival_time, double flight_duration);
	~flight(); // destrucutor 
	int get_flight_nr();
	string get_airline();
	string get_departure_location();
	string get_arrival_location();
	string get_departure_time();
	string get_arrival_time();
	double get_flight_duration();
	void add_person(person* p);
	vector<person*>& get_persons();
};

std::ostream& operator<<(std::ostream& os, flight* f);


#endif