#include <iostream>
#include "flight.h"
#include"person.h"
#include"flight_trip.h"
int main() {
    flight f("AA938475","Air Blah", "Linz", "Frankfurt", "7:00 02.02.2022", "8:30 02.02.2022",1.5);
    flight f2("AF9238475","Air Germany","Frankfurt","Denver","9:00 02.02.2022","15:00 02.02.2022",6);
    flight f3("ZR98475","Spirit","Denver","Las Vegas","17:00 02.02.2022","20:00 02.02.2022",3);

    flight f4("UH3478475","Spirit","Las Vegas","San Francisco","7:00 17.02.2022","10:00 17.02.2022",3);
    flight f5("OD98479895","Air Canada","San Francisco","München","10:00 17.02.2022","20:00 17.02.2022",10);
    flight f6("EB998345","Air Canada","München","Linz","21:00 17.02.2022","23:00 17.02.2022",2);


    person a("Anja","Schwab","Musterstrasse 4, 4240 Freistadt",20,"AT983247595443","female");
    f.add_passenger(&a);

    vector<flight *> flight_itinerary {&f,&f2,&f3,&f4,&f5,&f6};
    std::cout<<f;
    std::cout<<"\n";

    flight_trip trip(flight_itinerary);
    std::cout<<trip;
    trip.print_passenger_list(std::cout);
    return 0;
}
