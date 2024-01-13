#if ! defined FLUG_TEST_H
#define FLUG_TEST_H

#include "flugreisen.h"

void full_test() {

	flight test1(1224, "austrian airlines", "linz", "stockholm", date_t(2022, 12, 27, 13, 12), date_t(2022, 12, 27, 14, 22), 70);
	flight test2(1231, "austrian airlines", "stockholm", "wien", date_t(2022, 12, 28, 8, 02), date_t(2022, 12, 28, 8, 59), 57);
	flight test3(1724, "austrian airlines", "wien", "linz", date_t(2022, 12, 28, 10, 24), date_t(2022, 12, 28, 10, 40), 16);

	person lisa("Lisa", "Test", gender_t(female), 20, "4040 Linz", "248714986");
	person lena("Lena", "Try", gender_t(female), 22, "4040 Linz", "273462283");
	person luis("Luis", "Testing", gender_t(male), 23, "4040 Linz", "764143819");

	std::vector<flight> flights{ test1, test2, test3 };
	std::vector<person> people{ lisa, lena, luis };

	air_travel air(flights, people);


	std::cout << air;

}

void empty_air_travel() {
	std::vector<flight> flights{};
	std::vector<person> people{};

	air_travel air(flights, people);


	std::cout << air;
}




#endif
