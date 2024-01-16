#include "flight.h"
#include "person.h"
#include "flight_travel.h"

#include <iostream>

using std::cout;

// Tests class person
void print_person(person& person, std::ostream& os = std::cout) {
	os << "Person:\nName: " << person.get_first_name() << " " << person.get_last_name() << "\nGender: "
		<< person.get_gender() << "\nAge: " << person.get_age() << "\nAddress: " << person.get_address()
		<< "\nCredit card number: " << person.get_credit_card_nr() << "\n";
}

void test_default_constructor_person() {
	person person;
	print_person(person);
}

void test_assign_constructor_person() {
	person person("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	print_person(person);
}

void test_get_first_name() {
	person person("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	cout <<"Firstname: " <<  person.get_first_name() << "\n";
}

void test_get_last_name() {
	person person("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	cout << "Lastname: " << person.get_last_name() << "\n";
}

void test_get_gender() {
	person person("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	cout << "Gender: " << person.get_gender() << "\n";
}

void test_get_age() {
	person person("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	cout << "Age: " << person.get_age() << "\n";
}

void test_get_address() {
	person person("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	cout << "Address: " << person.get_address() << "\n";
}

void test_get_credit_card_nr() {
	person person("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	cout << "Credit card number: " << person.get_credit_card_nr() << "\n";
}




// Tests class flight

void print_flight(flight& flight, std::ostream& os = std::cout) {
	os << "Flight:\nFlight number: " << flight.get_flight_nr() << "\nAirline: " << flight.get_airline()
		<< "\nFrom-To: " << flight.get_departure_location() << " - " << flight.get_arrival_location()
		<< "\nTime: " << flight.get_departure_time() << " - " << flight.get_arrival_time()
		<< "\nFlight duration (in h): " << flight.get_flight_duration()<<"\n";
}

void test_default_constructor_flight() {
	flight flight;
	print_flight(flight);
}

void test_assign_constructor_flight() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	print_flight(flight);
}

void test_get_airline() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	cout << "Airline: " << flight.get_airline()<< "\n";
}

void test_get_departure_location() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	cout << "Departure Location: " << flight.get_departure_location() << "\n";
}

void test_get_arrival_location() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	cout << "Arrival Location: " << flight.get_arrival_location() << "\n";
}

void test_get_departure_time() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	cout << "Departure Time: " << flight.get_departure_time() << "\n";
}

void test_get_arrival_time() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	cout << "Arrival Time: " << flight.get_arrival_time() << "\n";
}

void test_get_flight_duration() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	cout << "Flight Duration: " << flight.get_flight_duration() << "\n";
}

void test_add_person() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	person p1("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	person p2("Lisa", "Mueller", "weiblich", 24, "24 Schmidtstrass", 970);
	person p3("Julia", "Schmidt", "weiblich", 30, "13 Muehlstrasse", 7499);
	flight.add_person(&p1);
	flight.add_person(&p2);
	flight.add_person(&p3); 
	cout << &flight;
}

void test_get_persons() {
	flight flight(123, "Eurowings", "Wien", "Paris", "Mon Aug 09:30 2017", "Mon Aug 11:30 2017", 2);
	person p1("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	person p2("Lisa", "Mueller", "weiblich", 24, "24 Schmidtstrass", 970);
	person p3("Julia", "Schmidt", "weiblich", 30, "13 Muehlstrasse", 7499);
	flight.add_person(&p1);
	flight.add_person(&p2);
	flight.add_person(&p3);
	vector<person*> persons_;
	persons_=flight.get_persons();
	cout << "Passengers:\n";
	for (size_t i = 0; i < persons_.size(); i++)
	{
		person* p = persons_[i];
		cout << p->get_first_name() << " " << p->get_last_name() << std::endl;
	}

}


// Testing class flight travel

void test_default_constructor_flight_travel() {
	flight_travel ft;
	cout << ft;
}

void test_assign_constructor_flight_travel() {
	person p("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	person p2("Lisa", "Mueller", "weiblich", 24, "24 Schmidtstrass", 970);
	person p3("Julia", "Schmidt", "weiblich", 30, "13 Muehlstrasse", 7499);
	flight fd1(123, "Eurowings", "Wien", "Frankfurt", "Mon Aug 09:30 2017", "Mon Aug 10:30 2017", 2);
	fd1.add_person(&p);
	fd1.add_person(&p2);
	flight fr(456, "Austrian Airlines", "Paris", "Linz", "Sun Aug 05:00 2017", "Sun Aug 09:30 2017", 2.5);
	fr.add_person(&p);
	fr.add_person(&p2);
	fr.add_person(&p3);
	flight_travel ft(&fd1, &fr);
	cout << ft;
}


void test_get_departure_flight() {
	person p("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	person p2("Lisa", "Mueller", "weiblich", 24, "24 Schmidtstrass", 970);
	person p3("Julia", "Schmidt", "weiblich", 30, "13 Muehlstrasse", 7499);
	flight fd1(123, "Eurowings", "Wien", "Frankfurt", "Mon Aug 09:30 2017", "Mon Aug 10:30 2017", 2);
	fd1.add_person(&p);
	fd1.add_person(&p2);
	flight fr(456, "Austrian Airlines", "Paris", "Linz", "Sun Aug 05:00 2017", "Sun Aug 09:30 2017", 2.5);
	fr.add_person(&p);
	fr.add_person(&p2);
	fr.add_person(&p3);
	flight_travel ft(&fd1, &fr);
	vector<flight*> departure_flights;
	departure_flights=ft.get_departure_flights();
	cout << "Departure flight:\n";
	for (size_t i = 0; i < departure_flights.size(); i++)
	{
		cout << departure_flights[i];
	}

}


void test_get_return_flight() {
	person p("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	person p2("Lisa", "Mueller", "weiblich", 24, "24 Schmidtstrass", 970);
	person p3("Julia", "Schmidt", "weiblich", 30, "13 Muehlstrasse", 7499);
	flight fd1(123, "Eurowings", "Wien", "Frankfurt", "Mon Aug 09:30 2017", "Mon Aug 10:30 2017", 2);
	fd1.add_person(&p);
	fd1.add_person(&p2);
	flight fr(456, "Austrian Airlines", "Paris", "Linz", "Sun Aug 05:00 2017", "Sun Aug 09:30 2017", 2.5);
	fr.add_person(&p);
	fr.add_person(&p2);
	fr.add_person(&p3);
	flight_travel ft(&fd1, &fr);
	vector<flight*> return_flight;
	return_flight = ft.get_return_flights();
	cout << "Return flight:\n";
	for (size_t i = 0; i < return_flight.size(); i++)
	{
		cout << return_flight[i];
	}

}


void test_op() {
	person p("Max", "Mustermann", "maennlich", 20, "1 Musterstrasse", 123);
	person p2("Lisa", "Mueller", "weiblich", 24, "24 Schmidtstrass", 970);
	person p3("Julia", "Schmidt", "weiblich", 30, "13 Muehlstrasse", 7499);
	flight fd1(123, "Eurowings", "Wien", "Frankfurt", "Mon Aug 09:30 2017", "Mon Aug 10:30 2017", 2);
	fd1.add_person(&p);
	fd1.add_person(&p2);
	flight fr(456, "Austrian Airlines", "Paris", "Linz", "Sun Aug 05:00 2017", "Sun Aug 09:30 2017", 2.5);
	fr.add_person(&p);
	fr.add_person(&p2);
	fr.add_person(&p3);
	flight_travel ft(&fd1, &fr);
	cout << ft;
}



int main() {
	/*
	cout << "Testing class person...\n";
	cout << "Default constructor\n";
	test_default_constructor_person();
	cout << "Assign constructor\n";
	test_assign_constructor_person();
	test_get_first_name();
	test_get_last_name();
	test_get_gender();
	test_get_age();
	test_get_address();
	test_get_credit_card_nr();
	cout << "Test add person:\n";
	test_add_person();
	cout << "Test get persons:\n";
	test_get_persons();

	
	cout << "Testing class flight...\n";
	cout << "Default constructor\n";
	test_default_constructor_flight();
	cout << "Assign constructor\n";
	test_assign_constructor_flight();
	test_get_airline();
	test_get_departure_location();
	test_get_arrival_location();
	test_get_departure_time();
	test_get_arrival_time();
	test_get_flight_duration();
	*/

	cout << "Testing class flight travel...\n";
	test_default_constructor_flight_travel();
	test_assign_constructor_flight_travel();
	test_get_departure_flight();
	test_get_return_flight();
	test_op();
	
	return 0;
}