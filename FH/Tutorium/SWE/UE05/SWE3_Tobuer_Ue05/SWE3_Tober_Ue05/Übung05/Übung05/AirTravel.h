#if!defined AIRTRAVEL_H
#define AIRTRAVEL_H
#include "Fligtht.h"

class AirTravel {
public:
	AirTravel();  //default-constructor
	~AirTravel(); //deconstructor

	void add_outward_flight(Flight const& flight);
	void add_return_flight(Flight const& flight);
	void print_air_travel(std::ostream& out = std::cout) const;

private:
	std::vector<Flight> outward_flight;
	std::vector<Flight> return_flight;
};

std::ostream& operator<<(std::ostream& lhs, AirTravel const& rhs);

#endif