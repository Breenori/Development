#ifndef flight_h
#define flight_h

#include <string>
#include <iostream>

	struct takeoff_time {
		int to_hour;
		int to_minute;
	};

	struct arrival_time {
		int a_hour;
		int a_minute;
	};

	struct flight_duration {
		int hours;
		int minutes;
	};

class Flight {

public:
	std::string flight_no;
	std::string airline;
	std::string departure;
	std::string destination;
	takeoff_time departure_time;
	arrival_time arrival_time;
	flight_duration duration;

	void printItinerary() const;
	void printDeparture() const;

};

#endif // !flight_h
