#include "AirTravel.h"

using std::endl;

Person::Person() {
	first_name = "Max";
	last_name = "Mustermann";
	gender = 'm';
	age = 0;
	address = "-";
	creditcard_number = 0;
}

Person::~Person() {

}

void Person::new_person(std::string const& _first_name, std::string const& _last_name, char const& _gender, int const& _age, std::string const& _address, int const _creditcard_number) {
	first_name = _first_name;
	last_name = _last_name;
	gender = _gender;
	age = _age;
	address = _address;
	creditcard_number = _creditcard_number;
}


std::string Person::get_first_name() const {
	return first_name;
}

std::string Person::get_last_name() const {
	return last_name;
}

char Person::get_gender() const {
	return gender;
}

int Person::get_age() const {
	return age;
}

std::string Person::get_address() const {
	return address;
}

int Person::get_creditcard_number() const {
	return creditcard_number;
}

void Person::print_person(std::ostream& out) const {
	if (get_creditcard_number() == 0) {
		out << "No person found for this flight" << endl;
	}
	else {
		out << "First name: " << get_first_name() << endl;
		out << "Last name: " << get_last_name() << endl;
		out << "Gender: " << get_gender() << endl;
		out << "Age: " << get_age() << endl;
		out << "Adress: " << get_address() << endl;
		out << "Creditcard number: " << get_creditcard_number() << endl;
		out << endl;
	}

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



Flight::Flight() {
	flight_number = "0";
	flight_company = "Hagenberger Airlines";
	location = "-";
	time_of_departure = "-";
	arrival_time = "-";
	flight_durance = 0;
}

Flight::~Flight() {

}

std::string Flight::get_flight_number() const {
	return flight_number;
}

std::string Flight::get_flight_company() const {
	return flight_company;
}

std::string Flight::get_location() const {
	return location;
}

std::string Flight::get_time_of_departure() const {
	return time_of_departure;
}

std::string Flight::get_arrival_time() const {
	return arrival_time;
}

int Flight::get_flight_duration() const {
	return flight_durance;
}

void Flight::get_person_list_info(std::ostream& out) const {
	size_t travel_counter = 0;
	for (int i{ 0 }; i < person_list.size(); i++) {
		out << person_list[i].get_first_name() << " " << person_list[i].get_last_name() << endl;
		++travel_counter;
	}
	out << "Overall amount of travellers for this flight: " << travel_counter << endl;
	out << endl << endl << endl;
}

void Flight::new_flight(std::string const& _flight_number, std::string const& _flight_company, std::string const& _location, std::string const& _time_of_departure, std::string const& _arrival_time, int const& _flight_durance, std::vector<Person>& _person_list) {
	flight_number = _flight_number;
	flight_company = _flight_company;
	location = _location;
	time_of_departure = _time_of_departure;
	arrival_time = _arrival_time;
	flight_durance = _flight_durance;
	person_list = _person_list;
}

std::vector<Person> Flight::add_person(Person const& person) {
	person_list.push_back(person);
	return person_list;
}

void Flight::print_flight(std::ostream& out) const {
	if (get_flight_number() == "0") {
		out << "No flight existing" << endl;
	}
	else {
		out << "Flight number: " << get_flight_number() << endl;
		out << "Flight company: " << get_flight_company() << endl;
		out << "Location: " << get_location() << endl;
		out << "Departure time: " << get_time_of_departure() << endl;
		out << "Arriving time: " << get_arrival_time() << endl;
		out << "Flight duration: " << get_flight_duration() << " minutes" << endl;
		out << "Travel list including first name, last_name and overall amount of travellers for this flight: " << endl;
		get_person_list_info();

	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



AirTravel::AirTravel() {
	outward_flight = {};
	return_flight = {};
}

AirTravel::~AirTravel() {

}

void AirTravel::add_outward_flight(Flight const& flight) {
	outward_flight.push_back(flight);
}

void AirTravel::add_return_flight(Flight const& flight) {
	return_flight.push_back(flight);
}

void AirTravel::print_air_travel(std::ostream& out) const {
	if (outward_flight.size() == 0) {
		out << "Not outward flights existing" << endl;
	}

	if (return_flight.size() == 0) {
		out << "Not return flights existing" << endl;
	}

	out << "Outward flights: " << endl;
	for (int i{ 0 }; i < outward_flight.size(); i++) {
		outward_flight[i].print_flight(out);
	}

	out << endl << endl << endl;

	out << "Return flights: " << endl;
	for (int i{ 0 }; i < return_flight.size(); i++) {
		return_flight[i].print_flight(out);
	}
}

std::ostream& operator<<(std::ostream& lhs, AirTravel const& rhs) {
	rhs.AirTravel::print_air_travel(lhs);
	return lhs;
}



