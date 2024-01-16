#include "Flugreise.h"

//Test von Grundfunktionalitäten
void test1() {
	//Erstellen der Adressen
	adress_t adress("Gute Strasse", 1, 4580, "Vienna", "Austria");

	//Person anlegen
	Person person1("Hans", "Huber", gender_t::male, adress, 45, "ATG12998289472929");

	//Flug anlegen
	Flug flug1(1234, "Vienna", "Munich", 1234567, 1236468, "Lufthansa");

	//Adresse ausgeben
	std::cout << adress.to_string();

	//Person ausgeben
	std::cout << "\n\nperson:\n";
	std::cout << person1.to_string();

	//Flug ausgeben
	std::cout << "\n\nflug:\n";
	std::cout << flug1.to_string();
}


//Eine Familienreise mit Pärchen und Sohn
void test2() {
	Flugreise reise1;

	//Erstellen der Adressen
	adress_t adress1("Gute Strasse", 1, 4580, "Vienna", "Austria");
	adress_t adress2("Neue Strasse", 3, 6969, "Hagenberg", "Austria");

	//Personen anlegen
	Person person1("Hans", "Huber", gender_t::male, adress1, 45, "ATG12998289472929");
	Person person2("Frederike", "Huber", gender_t::female, adress1, 42, "ATG143636456456");
	Person person3("Max", "Huber", gender_t::male, adress2, 24, "ATG143636456456");

	//Flüge anlegen
	Flug flug1(1234, "Vienna", "Munich", 1234567, 1236468, "Lufthansa");
	Flug flug2(1246, "Munich", "Amsterdam", 1246468, 1256468, "Lufthansa");


	//Die Personen zur Reise Hinzufügen
	reise1.add_passenger(person1);
	reise1.add_passenger(person2);
	reise1.add_passenger(person3);

	//Die Flüge zur Reise hinzufügen
	reise1.add_flight(flug1, flight_t::outwards);
	reise1.add_flight(flug2, flight_t::outwards);

	//Die gesamte Reise ausgeben
	std::cout << reise1;
}



