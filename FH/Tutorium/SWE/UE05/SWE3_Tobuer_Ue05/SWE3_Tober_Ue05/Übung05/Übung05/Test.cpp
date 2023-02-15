#include "Test.h"
using std::vector;

void test_person() {
	Person a;
	Person b;
	Person c;

	a.new_person("Maria", "Mustermann", 'f', 21, "4240 Freistadt, Taubenstraße 69", 1234);
	b.new_person("Fabian", "Tober", 'm', 22, "4240 Freistadt, Taubenstraße 6", 1111);
	c.new_person("Lukas", "Hartmann", 'f', 14, "4240 Freistadt, Grosslingen 2", 5555);

	a.print_person();
	b.print_person();
	c.print_person();
}

void test_person_2() {
	Person d;
	d.print_person();
}

void test_flight() {
	Flight flight_1;
	vector<Person> travel_list;
	Person a;
	Person b;
	Person c;

	a.new_person("Maria", "Mustermann", 'f', 21, "4240 Freistadt, Taubenstraße 69", 1234);
	b.new_person("Fabian", "Tober", 'm', 22, "4240 Freistadt, Taubenstraße 6", 1111);
	c.new_person("Lukas", "Hartmann", 'f', 14, "4240 Freistadt, Grosslingen 2", 5555);

	travel_list.push_back(a);
	travel_list.push_back(b);
	travel_list.push_back(c);

	flight_1.new_flight("AB123", "Hagenberg Airlines", "Hagenberg", "14:00", "16:00", 120, travel_list);
	flight_1.print_flight();
}

void test_flight_2() {
	Flight ab124;
	ab124.print_flight();
}

void test_air_travel() {
	AirTravel air_travel_1;
	Flight flight_1;
	Flight flight_2;
	Flight flight_3;
	Person a;
	Person b;
	Person c;
	Person d;
	Person e;
	Person f;
	vector<Person> outward_list;
	vector<Person> return_list;

	a.new_person("Maria", "Mustermann", 'f', 21, "4240 Freistadt, Taubenstraße 69", 1234);
	b.new_person("Fabian", "Tober", 'm', 22, "4240 Freistadt, Taubenstraße 6", 1111);
	c.new_person("Lukas", "Hartmann", 'f', 14, "4240 Freistadt, Grosslingen 2", 5555);

	outward_list.push_back(a);
	outward_list.push_back(b);
	outward_list.push_back(c);

	flight_1.new_flight("AB123", "Hagenberg Airlines", "Hagenberg", "14:00", "16:00", 120, outward_list);

	d.new_person("Klara", "Kauffrau", 'f', 11, "4240 Freistadt, Taubenstraße 1", 2222);
	e.new_person("Hans", "Wurst", 'm', 42, "4240 Freistadt, Klostergasse 2", 3333);
	f.new_person("Moritz", "Strolch", 'd', 69, "4240 Freistadt, Grosslingen 222", 4444);

	return_list.push_back(d);
	return_list.push_back(e);
	return_list.push_back(f);

	flight_2.new_flight("AX451", "Hagenberg Airlines", "Toronto", "14:00", "16:00", 120, return_list);

	return_list.clear();
	return_list.push_back(a);
	return_list.push_back(c);
	return_list.push_back(f);
	return_list.push_back(a);

	flight_3.new_flight("XZ986", "Hagenberg Airlines", "Salzburg", "01:00", "04:00", 240, return_list);

	air_travel_1.add_outward_flight(flight_1);
	air_travel_1.add_return_flight(flight_2);
	air_travel_1.add_return_flight(flight_3);

	std::cout << air_travel_1 << std::endl;
}

void test_air_travel_2() {
	AirTravel air_travel_2;
	std::cout << air_travel_2;
}
