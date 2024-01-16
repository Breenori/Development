#pragma once
#pragma warning(disable : 4996)	//notwendig da dem compiler die ctime Funktion sonnst nicht schmeckt, anscheinend veraltet aber sollte keine Probleme machen
#include <string>
#include <vector>
#include <time.h>
#include <iostream>
#include <map>


using std::string;
using std::vector;


//Eigener Datentyp zum speichern der Adresse
struct adress_t {
	string street;
	size_t street_number;
	int postal_code;
	string city;
	string country;

	adress_t();
	adress_t(string const& street, size_t const street_number, int postal_code, string const& city, 
		string const& country);
	string to_string() const;
};

//Gender Optionen
enum gender_t {
	male,
	female,
	not_binary,
	not_given
};

//Person Klasse
class Person {
private:
	std::map<int, string> gender_map{ {0, "Männlich"} , {1, "Weiblich"}, {2, "Nicht Binär"}, {3, "Keine Angabe"} };
	string first_name;
	string last_name;
	gender_t gender;
	adress_t adress;
	size_t age = 0;
	string credit_card_number;

public:
	Person();
	Person(string const& first_name, string const& last_name, gender_t const gender, adress_t const& adress, 
		size_t const age, string const& credit_card_number);
	string to_string() const;
};

//Flug Klasse
class Flug {
	int flight_number;
	string src;								//Abflughafen
	string dest;							//Zielflughafen

	//Zeiten werden mit time_t's und nicht in Strings gespeichert um eine automatische Berechnung der Dauer zu ermöglichen
	time_t departure_time;
	time_t arrival_time;
	time_t flight_duration;
	string airline;
public:
	Flug();
	Flug(int const flight_number, string const& src, string const& dest, time_t const& departure_time, 
		time_t const& arrival_time, string const& airline);
	string to_string() const;
};

//Flug Typ
enum flight_t {
	outwards,
	returning
};

//Flugreise Klasse
class Flugreise {
private:
	vector<Person> passengers;
	vector<Flug> outward_flights;
	vector<Flug> return_flights;

public:
	//Reise in String verwandeln
	string to_string() const;

	//Operator überladen
	friend std::ostream& operator<<(std::ostream& os, const Flugreise& trip);

	//Flug hinzufügen
	void add_flight(Flug const& flight, flight_t flight_type);

	//Passagier hinzufügen
	void add_passenger(Person const& passenger);
};