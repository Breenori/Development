#if!defined FLIGHT_H
#define FLIGHT_H
#include "Person.h"

class Flight {
public:
	Flight();  //default-constructor
	~Flight(); //deconstructor

	std::string get_flight_number() const;
	std::string get_flight_company() const;
	std::string get_location() const;
	std::string get_time_of_departure() const;
	std::string get_arrival_time() const;
	int get_flight_duration() const;
	void get_person_list_info(std::ostream& out = std::cout) const;

	void new_flight(std::string const& _flight_number, std::string const& _flight_company, std::string const& _location,
		std::string const& _time_of_departure, std::string const& _arrival_time, int const& _flight_durance, std::vector<Person>& _person_list);
	std::vector<Person> add_person(Person const& person);
	void print_flight(std::ostream& out = std::cout) const;


private:
	std::string flight_number;
	std::string flight_company;
	std::string location;
	std::string time_of_departure;
	std::string arrival_time;
	int flight_durance; //in minutes
	std::vector<Person> person_list;
};

#endif