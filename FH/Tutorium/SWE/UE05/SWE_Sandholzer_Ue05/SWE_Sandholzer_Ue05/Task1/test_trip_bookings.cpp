#include "test_trip_bookings.h"

#include "person_t.h"

using std::cout;

void test1()
{
	cout << "start test 1\n";

	int flight_num(13683);		// arbitrary flight number

	flight_t f1(flight_num++, "Air Hagenberg", "Vienna", "London", "10.01.2023 12:00:00", 
		"10.01.2023 13:45:00", 1.75);
	cout << "\ncreating a flight: " << f1;

	flight_t f2(flight_num, "Air Hagenberg", "Innsbruck", "London", "10.01.2023 12:00:00", 
		"10.01.2023 13:45:00", 1.75);
	cout << "\ncreating another flight with THE SAME flight number: " << f1;

	flight_t f3(flight_num++, "Air Hagenberg", "Vienna", "London", "100.01.2023 12:70:00", 
		"not even close a to date", -7.53);
	cout << "\nflight with invalid date and travel time: " << f3;

	flight_t f4(flight_num++, "", "Vienna", "Hell", "10.01.2023 12:00:00", 
		"10.01.2023 13:45:00", 7/3.0);
	cout << "\ncreating a flight without airline: " << f4;

	flight_t f5(flight_num++, "Air Hagenberg", "", "somewhere far beyond", "10.01.2023 12:00:00", 
		"10.01.2023 13:45:00", 10);
	cout << "\ncreating a flight without departure airport: " << f5;

	cout << "\n\nend test 1\n\n";
}

void test2()
{
	cout << "start test 2\n";

	trip_t t1("stay at home");
	cout << "Trip without flights: " << t1;

	flight_t f1(13, "Air Hagenberg", "Vienna", "London", "10.01.2023 12:00:00", 
		"10.01.2023 13:45:00", 1.75);
	flight_t f2(96, "London Air", "London", "Reykjavik", "10.01.2023 15:00:00", 
		"10.01.2023 19:45:00", 3.75);
	trip_t t2("one way ticket!");
	t2.add_outbound_flight(&f1);
	t2.add_outbound_flight(&f2);
	cout << "\nOnly outbound flights: " << t2;

	flight_t f3(98, "London Air", "Reykjavik", "London", "20.01.2023 15:00:00", 
		"20.01.2023 19:45:00", 3.75);
	flight_t f4(15, "Air Hagenberg", "Oslo", "Vienna", "15.01.2023 12:00:00", 
		"15.01.2023 13:45:00", 2);
	t2.add_return_flight(&f3);
	t2.add_return_flight(&f4);
	cout << "\nAdding the following flights to return flights:\n" << f3 << std::endl << f4
		<< "\ntrip looks as follows: " << t2;

	t2.add_return_flight(&f3);
	t2.add_return_flight(&f4);

	cout << "\nAdded the same flights again, check result: " << t2;

	cout << "\nend test 2\n\n";
}

void test3()
{
	cout << "start test 3\n\n";

	address_t a1(6721, "Thueringerberg", "Faschinastrasse", 555);
	address_t a2(-6721, "", "Innerberg", 666);
	address_t a3(6712, "Thueringen", "Walgaustrasse", -777);
	address_t a4(6722, "St. Gerold", "Faschinastrasse", 888);
	address_t a5(6733, "Fontanella", "", 999);

	cout << a1 << "\n" << a2 << "\n" << a3 << "\n" << a4 << "\n" << a5;
	
	cout << "\n\nend test 3\n\n";
}

void test4()
{
	cout << "start test 4\n\n";

	address_t a1(6733, "Fontanella", "Faschinastrasse", 0);
	address_t a2(6731, "Sonntag", "Buchboden", 666);
	address_t a3(6712, "Thueringen", "Walgaustrasse", 777);
	address_t a4(6722, "St. Gerold", "Faschinastrasse", 888);

	person_t p1("Friedrich", "Walter", gender_t::male, 76, "004-152-614-141-163", &a3);
	person_t p2("", "Gruber", gender_t::female, 12, "???", &a1);
	person_t p3("Max", "", gender_t::unknown, -10, "666-666-666-666-666", nullptr);
	person_t p4("Reinelde", "Burtscher", gender_t::female, 97, "no credit card no :(", &a2);
	person_t p5("Engelbert", "Sparr", gender_t::male, 80, "3", &a4);

	cout << p1 << "\n" << p2 << "\n" << p3 << "\n" << p4 << "\n" << p5;

	cout << "\n\nend test 4\n\n";
}

void test5()
{
	cout << "start test 5\n";

	address_t a1(6733, "Fontanella", "Faschinastrasse", 555);
	person_t p1("Ferdinand", "Maier", gender_t::male, 69, "234-014-140-414-144", &a1);

	cout << "\nperson without bookings: " << p1;

	// will be ignored (not added to bookings)
	p1.add_booking(nullptr);
	p1.add_booking(nullptr);

	trip_t t1;
	// will be ignored
	t1.add_outbound_flight(nullptr);
	t1.add_outbound_flight(nullptr);
	t1.add_return_flight(nullptr);
	p1.add_booking(&t1);

	cout << "\nperson with one booking without flights\n" << p1;

	flight_t f1(13, "Air Hagenberg", "Vienna", "London", "10.01.2023 12:00:00",
		"10.01.2023 13:45:00", 1.75);
	flight_t f2(96, "London Air", "London", "Reykjavik", "10.01.2023 15:00:00", 
		"10.01.2023 19:45:00", 3.75);
	flight_t f3(98, "London Air", "Reykjavik", "London", "20.01.2023 15:00:00", 
		"20.01.2023 19:45:00", 3.75);
	flight_t f4(15, "Air Hagenberg", "London", "Vienna", "20.01.2023 12:00:00", 
		"20.01.2023 13:45:00", 2);

	t1.add_outbound_flight(&f1);
	t1.add_outbound_flight(&f2);
	t1.add_return_flight(&f3);
	t1.add_return_flight(&f4);

	cout << "flights have beed added to the trip\n" << p1;

	person_t p2("Rosmarie", "Maier", gender_t::female, 72, "234-014-140-414-144", &a1);
	p2.add_booking(&t1);

	cout << "his wife is joining the trip to Iceland (in January...)\n" << p2;

	// initialize with new to test dangling pointers
	flight_t* f5 = new flight_t(65, "Malle Airlines", "Muenchen", "Palma de Mallorca", 
		"02.02.2023 08:50:00", "02.02.2023 10:50:00", 2);
	flight_t* f6 = new flight_t(67, "Malle Airlines", "Palma de Mallorca", "Frankfurt", 
		"10.02.2023 15:35:00", "10.02.2023 17:05:00", 1.5);
	flight_t* f7 = new flight_t(68, "My personal Airline", "Frankfurt", "Muenchen", 
		"10.02.2023 18:00:00", "10.02.2023 19:00:00", 1);

	trip_t t2("\"Inlandsfluege\"");
	t2.add_outbound_flight(f5);
	t2.add_return_flight(f6);
	t2.add_return_flight(f7);
	p1.add_booking(&t2);

	cout << "Added a new trip:\n" << p1;

	delete f5;
	f5 = nullptr;

	cout << "Print again:\n" << p1;

	delete f6;
	f6 = nullptr;
	delete f7;
	f7 = nullptr;

	cout << "\nend test 5\n\n";
}