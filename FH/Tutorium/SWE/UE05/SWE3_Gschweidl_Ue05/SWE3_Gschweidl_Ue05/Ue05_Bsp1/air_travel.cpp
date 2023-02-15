#include "air_travel.h"

AirTravel::AirTravel() {
	//nothing here
}

AirTravel::~AirTravel() {
	//nothing here
}

void AirTravel::addFlight(Flight flight) {
	this->flights.push_back(flight);
}

std::vector<Flight>& AirTravel::getFlights() {
	return this->flights;
}

void AirTravel::addDestination(std::string destination) {
	this->destination.push_back(destination);
}

void AirTravel::addPassenger(person::Person* passenger) {
	this->passengers.push_back(passenger);
}

//std::vector<person::Person*>& AirTravel::getPassengers() {
//	return this->passengers;
//}

std::ostream& operator<<(std::ostream& lhs, AirTravel const& rhs) {
	rhs.printshortItinerary(lhs);
	return lhs;
}

void AirTravel::printFlight(std::ostream& os) const {
	os << "< ";
	for (size_t i{ 0 }; i < this->flights.size(); ++i) {
		if (i == 0) {
			os << this->flights[i].departure << " --> " << this->flights[i].destination;
		}
		else {
			if (i != this->flights.size() - 1) {
				os << " --> ";
			}
			os << this->flights[i].destination;
		}
	}
	os << " >";
}

void AirTravel::printshortItinerary(std::ostream& os) const {
	os << "Flight outbound: ";
	size_t cnt{ 0 };
	for (size_t i{ 0 }; i < this->flights.size(); ++i) {
		os << this->flights[i].departure << " --> ";
		if (this->destination.size() > 1 && cnt < this->destination.size()) {
			if (this->destination[cnt] == this->flights[0].departure) {
				os << this->flights[i].destination << "\n";
				os << "Flight inbound: ";
			}
			else if (this->destination[cnt] == this->flights[i].destination) {
				os << this->flights[i].destination << "\n";
				++cnt;
				if (cnt > this->destination.size() - 1) {
					// if flights are back to home airport
					os << "Flight inbound: ";
				}
				else {
					// destinations before inbound flight
					os << "Travel section " << cnt + 1 << ": ";
				}

			}
		}
		else if (this->destination.size() == 1 && this->destination[0] == this->flights[i].destination) {
			if (i < this->flights.size()-1) {
				os << this->flights[i].destination << "\n";
				os << "Flight inbound: ";
			}
		}

	}

	os << this->flights[flights.size() - 1].destination << "\n";
	
}

void AirTravel::printItinerary(std::ostream& os) const {
	os << "Travel Information for:\n";
	printPassengers(passengers);
	os << "-----------------------------------------------------\n";
	os << "\nComplete Itinerary:\n";
	os << "----------\n";
	for (size_t i{ 0 }; i < flights.size(); ++i) {
		this->flights[i].printItinerary();
		os << "-----------------------------------\n";
	}
}

void AirTravel::printPassengers(std::vector<person::Person*> const persons) const {
	for (size_t i{ 0 }; i < persons.size(); ++i) {
		persons[i]->PrintPersonFile();
	}
}