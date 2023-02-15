#if ! defined FLUGREISEN_H
#define FLUGREISEN_H

#include <iostream>
#include <string>
#include <vector>

// gender_t is used in person
enum gender_t {
	female,
	male,
	diverse
};

class person {
private:
	std::string first_name;
	std::string last_name;
	gender_t gender;
	int age;
	std::string address;
	std::string credit_card;

	friend inline std::ostream& operator<<(std::ostream& lhs, person const& rhs) {

		// formatting the gender to one letter
		std::string gender_string;

		switch (rhs.gender) {
		case female:
			gender_string = "f";
			break;
		case male:
			gender_string = "m";
			break;
		case diverse:
			gender_string = "d";
			break;
		}

		lhs << rhs.first_name << " " << rhs.last_name << "(gender: " << gender_string << ", age: " << rhs.age << ", address: "
			<< rhs.address << ", credit card number: " << rhs.credit_card << ")";

		return lhs;
	}

public:
	person(std::string const& fn, std::string const& ln, gender_t const& g, int const a, std::string const& ad, std::string const& cr) {
		first_name = fn;
		last_name = ln;
		gender = g;
		age = a;
		address = ad;
		credit_card = cr;
	}
};



class date_t {
public:
	int year;
	int month;
	int day;
	int hour;
	int min;

	// default constructor is required for flight class
	date_t() : year(0), month(0), day(0), hour(0), min(0) {

	}

	date_t(int y, int m, int d, int h, int mi) : year(y), month(m), day(d), hour(h), min(mi) {

	}
};

std::ostream& operator<<(std::ostream& lhs, date_t const& rhs) {
	lhs << rhs.day << "." << rhs.month << "." << rhs.year << "(" << rhs.hour << ":" << rhs.min << ")";
	return lhs;
}


class flight {
private:
	int flight_number;
	std::string company;
	std::string departure;
	std::string destination;
	date_t departure_time;
	date_t arrival_time;
	int flight_time;

	friend inline std::ostream& operator<<(std::ostream& lhs, flight const& rhs) {
		// formatting output for flight
		lhs << rhs.departure << "->" << rhs.destination << "(number: " << rhs.flight_number << ", company: " << rhs.company
			<< ", departure time: " << rhs.departure_time << ", arrival time: " << rhs.arrival_time << ", duration: "
			<< rhs.flight_time << " min)";
		return lhs;
	}

public:
	flight(int const num, std::string const& co, std::string const& dep, std::string const& des, date_t const& dep_t, date_t const& arr_t, int const f_t) {
		flight_number = num;
		company = co;
		departure = dep;
		destination = des;
		departure_time = dep_t;
		arrival_time = arr_t;
		flight_time = f_t;
	}
};


class air_travel {
private:
	std::vector<flight> flights;
	std::vector<person> passengers;

	friend inline std::ostream& operator<<(std::ostream& lhs, air_travel const& rhs) {
		// formatting output for air travel
		lhs << "All passengers of this journey: \n";
		for (size_t i{ 0 }; i < rhs.passengers.size(); ++i) {
			lhs << rhs.passengers[i] << "\n";
		}
		lhs << "\n";
		lhs << "All flights of this journey: \n";
		for (size_t i{ 0 }; i < rhs.flights.size(); ++i) {
			lhs << rhs.flights[i] << "\n";
		}
		lhs << "\n";
		return lhs;
	}
public:
	air_travel(std::vector<flight> const& fl, std::vector<person> const& p) {
		flights = fl;
		passengers = p;
	}
};



#endif