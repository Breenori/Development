#include "flight.h"

void Flight::printItinerary() const {
	std::cout << "Airline: " << this->airline <<"\n";
	std::cout << "Flightnumber: " << this->flight_no << "\n";
	std::cout << "------------------------\n";
	std::cout << this->departure << " --> " << this->destination << "\n";
	std::cout << "Take Off: " << this->departure_time.to_hour << ":" << this->departure_time.to_minute << "\n";
	std::cout << "Arrival time: " << this->arrival_time.a_hour << ":" << this->arrival_time.a_minute << "\n";
	std::cout << "Flight duration: " << this->duration.hours << "hrs " << this->duration.minutes << "min\n";
}

void Flight::printDeparture() const {
	std::cout << this->departure;
}