#include "flugreise.h"

PlaneTrip::PlaneTrip() {
	//only default values for flightnumber --> if 0 then flight does not exist
	departureFlight.flightInfo.flightnumber = 0;
	returnFlight.flightInfo.flightnumber = 0;
}

PlaneTrip::PlaneTrip(PlaneTripInfo dstInf, PlaneTripInfo rtnInf) {
	departureFlight = dstInf;
	returnFlight = rtnInf;
}

void PlaneTripInfo::setPlaneTripInfo(std::vector<std::string> st, Flight fl) {
	stops = st;
	flightInfo.setInformation(fl.airline, fl.destination, fl.departure, fl.approach, fl.duration);
	flightInfo.setFlightnumber(fl.flightnumber);
}

void Flight::setFlightnumber(int flnum) {
	flightnumber = flnum;
}

void Flight::setInformation(std::string airl, std::string dst, std::string dp, std::string ap, int dur) {
	airline = airl;
	destination = dst;
	departure = dp;
	approach = ap;
	duration = dur;
}

//default values for string not given, for int 0
Person::Person() {
	firstname = "Not given";
	lastname = "Not given";
	age = 0;
	address = "Not given";
	kreditkartnumber = 0;
	gender = "Not given";
}

Person::Person(PlaneTrip f,std::string fname, std::string lname, std::string adrs, int knum, std::string gen, int a) {
	firstname = fname;
	lastname = lname;
	age = a;
	address = adrs;
	kreditkartnumber = knum;
	gender = gen;
	flight = f;
}

Person::Person(PlaneTrip f, std::string fname, std::string lname, std::string adrs, int knum, int a ) {
	flight = f;
	lastname = lname;
	firstname = fname;
	address = adrs;
	kreditkartnumber = knum;
	age = a;
	gender = "Not given";
}

Person::Person(PlaneTrip f, std::string gen, int a, std::string adrs, int knum) {
	flight = f;
	firstname = "Not";
	lastname = " Given";
	gender = gen;
	address = adrs;
	age = a;
	kreditkartnumber = knum;
}

void Person::print(std::ostream& out) {
	out << "Passagier: " << firstname << " " << lastname << "<";
	if (age == 0) {
		out << "Not given, ";
	}
	else {
		out << age << ", ";
	}
	out << gender << ">";
	out << "\n";
	out << "Kreditkartennummer: " << kreditkartnumber;
	out << "\n";
	out << "Adresse: " << address;
	out << "\n";
	out << flight;
}

