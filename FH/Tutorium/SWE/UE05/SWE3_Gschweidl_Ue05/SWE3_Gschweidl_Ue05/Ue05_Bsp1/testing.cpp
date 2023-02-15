#include "testing.h"

void testPerson() {
	std::cout << "Testing class person and printing customer file: \n";
	person::Person clark;
	clark.setPerson("Clark", "Kent", 1992, 12, 10, 30, 4548390212, person::male, "Favoritenstrasse", 34, 1100, "Vienna");
	clark.PrintPersonFile();
	std::cout << "\n\n";

	std::cout << "---------------------------------\n";

	person::Person p2;
	p2.setPerson("Lois", "Lane", 1993, 02, 10, 29, 34891923823, person::female, "Favoritenstrasse", 34, 1100, "Vienna");
	p2.PrintPersonFile();
	std::cout << "\n\n";
}

void testCustomers() {
	std::cout << "Testing class customers and printing customer files for vienna customers: \n";
	person::Person p1;
	p1.setPerson("Clark", "Kent", 1992, 12, 10, 30, 4548390212, person::male, "Favoritenstrasse", 34, 1100, "Vienna");

	person::Person p2;
	p2.setPerson("Lois", "Lane", 1993, 02, 10, 29, 34891923823, person::female, "Favoritenstrasse", 34, 1100, "Vienna");

	Customers vienna_customers;
	vienna_customers.AddPerson(&p1);
	vienna_customers.AddPerson(&p2);

	Customers::PrintPersons(vienna_customers.getCustomers());
}

void testFlight() {
	Flight lnz_fra;
	lnz_fra.airline = "Lufthansa";
	lnz_fra.departure = "Linz";
	lnz_fra.destination = "Frankfurt";
	lnz_fra.flight_no = "LH 6933";
	lnz_fra.departure_time.to_hour = 14;
	lnz_fra.departure_time.to_minute = 25;
	lnz_fra.arrival_time.a_hour = 15;
	lnz_fra.arrival_time.a_minute = 30;
	lnz_fra.duration.hours = 1;
	lnz_fra.duration.minutes = 05;
	
	std::cout << "\n";
	std::cout << "Testing class flight and print itinerary: \n";
	//lnz_fra.printDeparture();
	//std::cout << "\n";
	lnz_fra.printItinerary();
}

void testAirTravel() {
	Flight lnz_fra;
	lnz_fra.airline = "Lufthansa";
	lnz_fra.departure = "Linz";
	lnz_fra.destination = "Frankfurt";

	Flight fra_den;
	fra_den.airline = "Lufthansa";
	fra_den.departure = "Frankfurt";
	fra_den.destination = "Denver";

	Flight den_las;
	den_las.airline = "Southwest";
	den_las.departure = "Denver";
	den_las.destination = "Las Vegas";

	Flight las_sfo;
	las_sfo.airline = "United";
	las_sfo.departure = "Las Vegas";
	las_sfo.destination = "San Francisco";

	Flight sfo_muc;
	sfo_muc.airline = "Lufthansa";
	sfo_muc.departure = "San Francisco";
	sfo_muc.destination = "Munich";

	Flight muc_lnz;
	muc_lnz.airline = "Lufthansa";
	muc_lnz.departure = "Munich";
	muc_lnz.destination = "Linz";

	Flight fra_lnz;
	fra_lnz.airline = "Lufthansa";
	fra_lnz.departure = "Frankfurt";
	fra_lnz.destination = "Linz";

	AirTravel rnd_USA;
	rnd_USA.addFlight(lnz_fra);
	rnd_USA.addFlight(fra_den);
	rnd_USA.addFlight(den_las);
	rnd_USA.addFlight(las_sfo);
	rnd_USA.addFlight(sfo_muc);
	rnd_USA.addFlight(muc_lnz);
	//rnd_USA.addFlight(fra_lnz);
	rnd_USA.addDestination("Las Vegas");

	std::cout << "Testing AirTravel Journey - 1: Roundtrip USA with one Destination stops:\n";
	std::cout << rnd_USA << "\n";

	std::cout << "Testing AirTravel Journey - 2: Roundtrip USA with two Destination stops:\n";
	rnd_USA.addDestination("San Francisco");
	std::cout << rnd_USA << "\n";

	std::cout << "Testing AirTravel Journey - 3: Simple Trip with no return:\n";
	AirTravel uk;
	Flight vie_lon;
	vie_lon.airline = "Austrian Airlines";
	vie_lon.departure = "Vienna";
	vie_lon.destination = "London";
	uk.addFlight(vie_lon);
	uk.addDestination("London");
	std::cout << uk << "\n";

	std::cout << "Testing AirTravel Journey - 4: Simple Round Trip with no layovers:\n";
	Flight lon_vie;
	lon_vie.airline = "Austrian Airliens";
	lon_vie.departure = "London";
	lon_vie.destination = "Vienna";
	uk.addFlight(lon_vie);
	std::cout << uk;	

}

void testUseCase() {
	Customers hollywood_office;
	person::Person p1;
	p1.setPerson("Natascha", "Romanoff", 1990, 05, 12, 32, 1234568291, person::female, "Universal City Plaza", 100, 91608, "Universal City");
	hollywood_office.AddPerson(&p1);
	person::Person p2;
	p2.setPerson("Clint", "Barton", 1989, 05, 20, 33, 1239987876, person::male, "Universal City Plaza", 100, 91608, "Universal City");
	hollywood_office.AddPerson(&p2);
	person::Person p3;
	p3.setPerson("Tony", "Stark", 1980, 10, 10, 42, 1981276374, person::male, "Malibu Drive", 10, 90263, "Malibu");
	hollywood_office.AddPerson(&p3);
	person::Person p4;
	p4.setPerson("Lucy", "Chen", 1992, 10, 01, 30, 191282168, person::female, "Wilshire Blvd", 8850, 90211, "Beverly Hills");
	hollywood_office.AddPerson(&p4);
	person::Person p5;
	p5.setPerson("Timothy", "Bradford", 1988, 10, 01, 34, 191282168, person::male, "Wilshire Blvd", 8850, 90211, "Beverly Hills");
	hollywood_office.AddPerson(&p5);
	
	AirTravel US_West;
	Flight lax_las;
	lax_las.airline = "United";
	lax_las.departure = "Los Angeles";
	lax_las.destination = "Las Vegas";
	lax_las.departure_time.to_hour = 10;
	lax_las.departure_time.to_minute = 20;
	lax_las.arrival_time.a_hour = 11;
	lax_las.arrival_time.a_minute = 40;
	lax_las.duration.hours = 1;
	lax_las.duration.minutes = 20;
	lax_las.flight_no = "UA 2381";
	US_West.addDestination("Las Vegas");
	US_West.addFlight(lax_las);
	US_West.addPassenger(&p4);
	US_West.addPassenger(&p5);

	AirTravel europe;
	Flight vie_zrh;
	vie_zrh.airline = "Austrian Airlines";
	vie_zrh.departure = "Vienna";
	vie_zrh.destination = "Zurich";
	vie_zrh.departure_time.to_hour = 10;
	vie_zrh.departure_time.to_minute = 20;
	vie_zrh.arrival_time.a_hour = 11;
	vie_zrh.arrival_time.a_minute = 40;
	vie_zrh.duration.hours = 1;
	vie_zrh.duration.minutes = 20;
	vie_zrh.flight_no = "OS 3478";
	europe.addDestination("London");
	europe.addFlight(vie_zrh);
	europe.addPassenger(&p1);
	europe.addPassenger(&p2);
	Flight zrh_lcy;
	zrh_lcy.airline = "Swiss";
	zrh_lcy.departure = "Zurich";
	zrh_lcy.destination = "London City Airport";
	zrh_lcy.departure_time.to_hour = 12;
	zrh_lcy.departure_time.to_minute = 20;
	zrh_lcy.arrival_time.a_hour = 14;
	zrh_lcy.arrival_time.a_minute = 40;
	zrh_lcy.duration.hours = 2;
	zrh_lcy.duration.minutes = 20;
	zrh_lcy.flight_no = "CH 3342";
	europe.addFlight(zrh_lcy);

	std::cout << "Print Complete Itinerary incl. Passenger Details for europe-flight:\n";
	europe.printItinerary(std::cout);

	std::cout << "\nPrint Complete Itinerary incl. Passenger Details for US-West-flight:\n";
	US_West.printItinerary(std::cout);
	
	std::cout << "Print Short Itinerary with Operator<<:\n";
	std::cout << europe << "\n";
	std::cout << US_West << "\n";

	std::cout << "\------------------------------------------------------\n";
	std::cout << "Print all Customers on File for Hollywood Division:\n";
	hollywood_office.PrintPersons(hollywood_office.getCustomers());

}