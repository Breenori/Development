#include "Flugreise.h"
#include <stdio.h>

//Standartkonstruktor ohne Argumente macht nichts außer das Objekt zu Instanzieren
adress_t::adress_t()
{
}
//Konstruktor um Adresse mitsamt deren Daten Anzulegen
adress_t::adress_t(string const& street, size_t const street_number, int postal_code, string const& city, string const& country)
{
	this->street = street;
	this->street_number = street_number;
	this->postal_code = postal_code;
	this->city = city;
	this->country = country;
}

//Formatierung der Adresse und Erstellung eines Strings
string adress_t::to_string() const
{
	string s = "Adresse:\n" + this->street + " " + std::to_string(this->street_number) + "\n" +
		std::to_string(this->postal_code) + " " + this->city + "\n" + this->country + "\n";
	return s;
}

//Standartkonstruktor ohne Argumente macht nichts außer das Objekt zu Instanzieren
Person::Person()
{
}

//Konstruktor um Person mitsamt deren Daten Anzulegen
Person::Person(string const& first_name, string const& last_name, gender_t const gender, adress_t const& adress, size_t const age, string const& credit_card_number)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->gender = gender;
	this->adress = adress;
	this->age = age;
	this->credit_card_number = credit_card_number;
}

//Formatierung der Person und Erstellung eines Strings
string Person::to_string() const
{
	auto gender = gender_map.find(this->gender);
	string s = "Name: " + this->first_name + " " + this->last_name + "\n" +
		"Geschlecht: " + gender->second + ", Alter: " + std::to_string(this->age) + "\n" +
		"Kreditkartennummer: " + this->credit_card_number + "\n" + this->adress.to_string() + "\n";
	return s;
}

//Standartkonstruktor ohne Argumente macht nichts außer das Objekt zu Instanzieren
Flug::Flug()
{
}

//Konstruktor um Flug mitsamt dessen Daten Anzulegen
Flug::Flug(int const flight_number, string const& src, string const& dest, time_t const& departure_time, time_t const& arrival_time, string const& airline)
{
	this->flight_number = flight_number;
	this->src = src;
	this->dest = dest;
	this->departure_time = departure_time;
	this->arrival_time = arrival_time;
	this->airline = airline;

	//Flugzeit automatisch berechnen
	this->flight_duration = arrival_time - departure_time;
}

//Formatierung des Flugs und Erstellung eines Strings
string Flug::to_string() const
{
	string s = "";
	struct tm* tmp = gmtime(&this->flight_duration);			//Erstellung eines Structs um den Minuten und Stundenwert einfach abzulesen

	s += "Flugnummer: " + std::to_string(this->flight_number) + "\n" +
		"Von: " + this->src + ", Abflugszeit: " + ctime(&this->departure_time) +
		"Nach: " + this->dest + ", Ankunftszeit: " + ctime(&this->arrival_time) +
		"Dauer: " + std::to_string(tmp->tm_hour) + "h " + std::to_string(tmp->tm_min) +"m\n";

	return s;
}

//Operator überladung
std::ostream& operator<<(std::ostream& os, const Flugreise& trip)
{
	os << trip.to_string() << "\n";
	return os;
}

//Erstellt für alle Personen und Flüge Strings mit den Daten und fügt sie zusammen
string Flugreise::to_string() const
{
	string s = "";
	for (auto &passenger : this->passengers) {
		s += passenger.to_string();
	}

	for (auto& flight : this->outward_flights) {
		s += flight.to_string();
	}
	return s;
}

//Fügt einen Flug hinzu, je nach typ kommt er in den entsprechenden Vector
void Flugreise::add_flight(Flug const& flight, flight_t flight_type)
{
	if (flight_type == flight_t::outwards) {
		this->outward_flights.push_back(flight);
	}
	else {
		this->return_flights.push_back(flight);
	}
}


//Fügt einen Passagier zur Reise hinzu
void Flugreise::add_passenger(Person const& passenger)
{
	this->passengers.push_back(passenger);
}
