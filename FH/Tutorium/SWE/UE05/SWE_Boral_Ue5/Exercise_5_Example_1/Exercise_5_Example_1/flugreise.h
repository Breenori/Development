#ifndef flugreise_h
#define flugreise_h

#include <iostream>
#include <string>
#include <vector>

class Flight {
public:
	int flightnumber = 0;
	std::string airline;
	std::string destination;
	std::string departure;
	std::string approach;
	//in minutes 
	int duration =0;
	void setFlightnumber(int flnum);
	void setInformation(std::string airl, std::string dst, std::string dp, std::string ap, int dur);
};

class PlaneTripInfo {	
public:
	//has all stops 
	std::vector<std::string> stops;
	Flight flightInfo;
	void setPlaneTripInfo(std::vector<std::string> st, Flight fl);
};

class PlaneTrip {
private:
	PlaneTripInfo departureFlight;
	PlaneTripInfo returnFlight;
	friend std::ostream& operator<<(std::ostream& out, PlaneTrip const& pl) {
		//if flightnumber =0 --> flight does not exist
		if (pl.departureFlight.flightInfo.flightnumber != 0) {
			out << "Hinflug:\nZiel: " << pl.departureFlight.flightInfo.destination <<"\n";
			for (int i = 0; i < pl.departureFlight.stops.size(); ++i) {
				out << pl.departureFlight.stops[i];
				if (i < pl.returnFlight.stops.size() - 1) {
					out << " --> ";
				}
			}
			out << "\n";
			out << "Fluggesellschaft: " << pl.departureFlight.flightInfo.airline << std::endl;
			out << "Abflugszeit: " << pl.departureFlight.flightInfo.departure << std::endl;
			out << "Anflugszeit: " << pl.departureFlight.flightInfo.approach << std::endl;
			out << "Flugdauer: " << pl.departureFlight.flightInfo.duration << std::endl;
			out << "Flugnummer: " << pl.departureFlight.flightInfo.flightnumber << std::endl;


			if (pl.returnFlight.flightInfo.flightnumber != 0) {
				out << "Rückflug:\n";
				out << "Ziel: " << pl.returnFlight.flightInfo.destination <<"\n";
				for (int i = 0; i < pl.returnFlight.stops.size(); ++i) {
					out << pl.returnFlight.stops[i];
					if (i < pl.returnFlight.stops.size() - 1) {
						out << " --> ";
					}
				}
				out << "\n";
				out << "Fluggesellschaft: " << pl.returnFlight.flightInfo.airline << std::endl;
				out << "Abflugszeit: " << pl.returnFlight.flightInfo.departure << std::endl;
				out << "Anflugszeit: " << pl.returnFlight.flightInfo.approach << std::endl;
				out << "Flugdauer: " << pl.returnFlight.flightInfo.duration << std::endl;
				out << "Flugnummer: " << pl.returnFlight.flightInfo.flightnumber << std::endl;
			}
			else {
				out << "Achtung: Rückflug noch nicht gebucht!";
			}
		}
		else {
			out << "Achtung: Kein Flug wurde gebucht!";
		}
		return out;
	}
public:
	PlaneTrip();
	PlaneTrip(PlaneTripInfo dstInf, PlaneTripInfo rtnInf);
};

class Person {
private:
	std::string firstname;
	std::string lastname;
	int age = 0;
	std::string address;
	int kreditkartnumber = 0;
	std::string gender;
	PlaneTrip flight;

public:
	Person();
	Person(PlaneTrip f, std::string fname, std::string lname, std::string adrs, int knum, std::string gen = "Not given", int a=0);
	Person(PlaneTrip f, std::string fname, std::string lname, std::string adrs, int knum, int a);
	Person(PlaneTrip f, std::string gen, int a, std::string adrs, int knum);
	void print(std::ostream& out);
};

std::ostream& operator<<(std::ostream& out, PlaneTrip const& pl);
#endif // !flugreise_h

