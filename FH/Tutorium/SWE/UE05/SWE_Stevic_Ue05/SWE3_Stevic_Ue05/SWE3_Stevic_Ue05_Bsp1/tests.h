#ifndef tests_h
#define tests_h

#include "voyage.h"

void test1()
{
	adress_type a1;
	a1.street_name = "Sesamstraße";
	a1.street_number = "22";
	a1.post_code = "4020";
	a1.city_name = "Linz";
	a1.country = "Austria";
	person p1("Albert", "Einstein", male, 45, a1, "158478462540132");

	adress_type a2;
	a2.street_name = "Sesamstraße";
	a2.street_number = "22";
	a2.post_code = "4020";
	a2.city_name = "Linz";
	a2.country = "Austria";
	person p2("Albertina", "Einstein", female, 41, a2, "0235847956210548");

	date_type dt1;
	dt1.day = 26;
	dt1.month = 12;
	dt1.year = 2022;
	dt1.time.hour = 13;
	dt1.time.minute = 45;

	date_type at1;
	at1.day = 26;
	at1.month = 12;
	at1.year = 2022;
	at1.time.hour = 14;
	at1.time.minute = 40;

	time_type ft1;
	ft1.hour = 0;
	ft1.minute = 55;

	flight f1(12345, "AirAustria", "Linz", dt1, "Frankfurt", at1, ft1);

	date_type dt2;
	dt2.day = 26;
	dt2.month = 12;
	dt2.year = 2022;
	dt2.time.hour = 17;
	dt2.time.minute = 15;

	date_type at2;
	at2.day = 26;
	at2.month = 12;
	at2.year = 2022;
	at2.time.hour = 19;
	at2.time.minute = 35;

	time_type ft2;
	ft2.hour = 2;
	ft2.minute = 20;

	flight f2(12345, "MaltaAirline", "Frankfurt", dt2, "Luqa", at2, ft2);

	voyage v1("Linz", "Luqa");
	v1.add_flight(f1);
	v1.add_flight(f2);
	v1.add_passenger(p1);
	v1.add_passenger(p2);

	std::cout << v1;
}

void test2()
{
	adress_type a1;
	a1.street_name = "Musterstraße";
	a1.street_number = "34";
	a1.post_code = "4020";
	a1.city_name = "Linz";
	a1.country = "Austria";
	person p1("Richard", "Mayer", male, 44, a1, "7382756499374637");

	adress_type a2;
	a2.street_name = "Masterstraße";
	a2.street_number = "1";
	a2.post_code = "4060";
	a2.city_name = "Leonding";
	a2.country = "Austria";
	person p2("Maria", "Holzinger", female, 33, a2, "098765432123456");

	adress_type a3;
	a3.street_name = "Ministerstraße";
	a3.street_number = "123";
	a3.post_code = "4020";
	a3.city_name = "Linz";
	a3.country = "Austria";
	person p3("Jonas", "Johnson", male, 26, a3, "6789456789073245");

	adress_type a4;
	a4.street_name = "Mausstraße";
	a4.street_number = "244";
	a4.post_code = "4060";
	a4.city_name = "Leonding";
	a4.country = "Austria";
	person p4("Rosalinde", "Gartner", female, 51, a4, "1234567890098765");

	date_type dt1;
	dt1.day = 27;
	dt1.month = 12;
	dt1.year = 2022;
	dt1.time.hour = 10;
	dt1.time.minute = 45;

	date_type at1;
	at1.day = 27;
	at1.month = 12;
	at1.year = 2022;
	at1.time.hour = 11;
	at1.time.minute = 40;

	time_type ft1;
	ft1.hour = 0;
	ft1.minute = 55;

	flight f1(54321, "AirAustria", "Linz", dt1, "Frankfurt", at1, ft1);

	date_type dt2;
	dt2.day = 27;
	dt2.month = 12;
	dt2.year = 2022;
	dt2.time.hour = 12;
	dt2.time.minute = 30;

	date_type at2;
	at2.day = 27;
	at2.month = 12;
	at2.year = 2022;
	at2.time.hour = 23;
	at2.time.minute = 10;

	time_type ft2;
	ft2.hour = 10;
	ft2.minute = 40;

	flight f2(54321, "AirGermany", "Frankfurt", dt2, "Denver", at2, ft2);

	date_type dt3;
	dt3.day = 28;
	dt3.month = 12;
	dt3.year = 2022;
	dt3.time.hour = 2;
	dt3.time.minute = 15;

	date_type at3;
	at3.day = 28;
	at3.month = 12;
	at3.year = 2022;
	at3.time.hour = 4;
	at3.time.minute = 15;

	time_type ft3;
	ft3.hour = 2;
	ft3.minute = 0;

	flight f3(54321, "AirAmerica", "Denver", dt3, "Las Vegas", at3, ft3);

	voyage v1("Linz", "Las Vegas");
	v1.add_flight(f1);
	v1.add_flight(f2);
	v1.add_flight(f3);
	v1.add_passenger(p1);
	v1.add_passenger(p2);
	v1.add_passenger(p3);
	v1.add_passenger(p4);

	std::cout << v1;
}

void test3()
{
	adress_type a1;
	a1.street_name = "Musterstraße";
	a1.street_number = "34";
	a1.post_code = "4020";
	a1.city_name = "Linz";
	a1.country = "Austria";
	person p1("Lisa", "Haslinger", female, 20, a1, "7382756499374637");

	adress_type a2;
	a2.street_name = "Masterstraße";
	a2.street_number = "1";
	a2.post_code = "4060";
	a2.city_name = "Leonding";
	a2.country = "Austria";
	person p2("Lorentz", "Bauer", male, 31, a2, "098765432123456");

	adress_type a3;
	a3.street_name = "Ministerstraße";
	a3.street_number = "123";
	a3.post_code = "4020";
	a3.city_name = "Linz";
	a3.country = "Austria";
	person p3("Jakob", "Sauer", male, 31, a3, "6789456789073245");

	adress_type a4;
	a4.street_name = "Mausstraße";
	a4.street_number = "244";
	a4.post_code = "4060";
	a4.city_name = "Leonding";
	a4.country = "Austria";
	person p4("Bettina", "Baecker", female, 49, a4, "1234567890098765");

	date_type dt1;
	dt1.day = 26;
	dt1.month = 12;
	dt1.year = 2022;
	dt1.time.hour = 3;
	dt1.time.minute = 00;

	date_type at1;
	at1.day = 26;
	at1.month = 12;
	at1.year = 2022;
	at1.time.hour = 4;
	at1.time.minute = 40;

	time_type ft1;
	ft1.hour = 1;
	ft1.minute = 40;

	flight f1(54321, "AirAmerica", "Las Vegas", dt1, "San Francisco", at1, ft1);

	date_type dt2;
	dt2.day = 26;
	dt2.month = 12;
	dt2.year = 2022;
	dt2.time.hour = 6;
	dt2.time.minute = 30;

	date_type at2;
	at2.day = 26;
	at2.month = 12;
	at2.year = 2022;
	at2.time.hour = 17;
	at2.time.minute = 40;

	time_type ft2;
	ft2.hour = 11;
	ft2.minute = 10;

	flight f2(54321, "AirGermany", "San Francisco", dt2, "Muenchen", at2, ft2);

	date_type dt3;
	dt3.day = 26;
	dt3.month = 12;
	dt3.year = 2022;
	dt3.time.hour = 20;
	dt3.time.minute = 15;

	date_type at3;
	at3.day = 26;
	at3.month = 12;
	at3.year = 2022;
	at3.time.hour = 23;
	at3.time.minute = 20;

	time_type ft3;
	ft3.hour = 3;
	ft3.minute = 5;

	flight f3(54321, "AirAustria", "Muenchen", dt3, "Linz", at3, ft3);

	voyage v1("Las Vegas", "Linz");
	v1.add_flight(f1);
	v1.add_flight(f2);
	v1.add_flight(f3);
	v1.add_passenger(p1);
	v1.add_passenger(p2);
	v1.add_passenger(p3);
	v1.add_passenger(p4);

	std::cout << v1;
}

void test4()
{
	adress_type a1;
	a1.street_name = "Musterstraße";
	a1.street_number = "34";
	a1.post_code = "4020";
	a1.city_name = "Linz";
	a1.country = "Austria";
	person p1("Larissa", "Hauser", female, 20, a1, "7382756499374637");

	adress_type a2;
	a2.street_name = "Masterstraße";
	a2.street_number = "1";
	a2.post_code = "4060";
	a2.city_name = "Leonding";
	a2.country = "Austria";
	person p2("Lorenzo", "Mueller", male, 31, a2, "098765432123456");

	adress_type a3;
	a3.street_name = "Ministerstraße";
	a3.street_number = "123";
	a3.post_code = "4020";
	a3.city_name = "Linz";
	a3.country = "Austria";
	person p3("Janine", "Suess", female, 31, a3, "6789456789073245");

	adress_type a4;
	a4.street_name = "Mausstraße";
	a4.street_number = "244";
	a4.post_code = "4060";
	a4.city_name = "Leonding";
	a4.country = "Austria";
	person p4("Marina", "Koch", female, 49, a4, "1234567890098765");

	date_type dt1;
	dt1.day = 28;
	dt1.month = 12;
	dt1.year = 2022;
	dt1.time.hour = 14;
	dt1.time.minute = 40;

	date_type at1;
	at1.day = 28;
	at1.month = 12;
	at1.year = 2022;
	at1.time.hour = 16;
	at1.time.minute = 45;

	time_type ft1;
	ft1.hour = 2;
	ft1.minute = 5;

	flight f1(54321, "AirSerbia", "Belgrad", dt1, "Frankfurt", at1, ft1);

	voyage v1("Belgrad", "Frankfurt");
	v1.add_flight(f1);
	v1.add_passenger(p1);
	v1.add_passenger(p2);
	v1.add_passenger(p3);
	v1.add_passenger(p4);

	std::cout << v1;
}

void test5()
{
	voyage v1("Muenchen", "Linz");
	std::cout << v1;
}

#endif