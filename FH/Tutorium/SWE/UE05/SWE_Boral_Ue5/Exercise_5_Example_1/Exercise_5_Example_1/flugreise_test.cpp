#include "flugreise_test.h"


void Testfligth() {
	Flight dp_f;
	dp_f.setInformation("UniFly", "Las Vegas", "14:50", "4:50", 800);
	dp_f.setFlightnumber(4563);
	std::vector<std::string> dp_st{ "Schwechat", "Frankfurt", "Denver", "Las Vegas" };
	PlaneTripInfo dp_info;
	dp_info.setPlaneTripInfo(dp_st, dp_f);
	Flight rt_f;
	rt_f.setFlightnumber(8598);
	rt_f.setInformation("FlyHigh", "Schwechat", "8:10", "21:40", 810);
	std::vector<std::string> rt_st{ "Las Vegas", "San Francisco", "München", "Linz" };
	PlaneTripInfo rt_info;
	rt_info.setPlaneTripInfo(rt_st, rt_f);
	PlaneTrip pt(dp_info, rt_info);
	Person p(pt, "Anna", "Anabel","Straße 10/4/2, 2222 Wien", 458652215, "weiblich", 25);
	p.print(std::cout);
}

void TestNoReturnFlight() {
	Flight dp_f;
	dp_f.setInformation("UniFly", "Las Vegas", "14:50", "4:50", 800);
	dp_f.setFlightnumber(4563);
	std::vector<std::string> dp_st{ "Schwechat", "Frankfurt", "Denver", "Las Vegas" };
	PlaneTripInfo dp_info;
	dp_info.setPlaneTripInfo(dp_st, dp_f);
	Flight rt_f;
	rt_f.setFlightnumber(0);
	PlaneTripInfo rt_info;
	rt_info.setPlaneTripInfo({}, rt_f);
	PlaneTrip pt(dp_info, rt_info);
	Person p(pt, "Anna", "Anabel", "Straße 10/4/2, 2222 Wien", 458652215, "weiblich", 25);
	p.print(std::cout);
}

void TestNoPersonalInfo() {
	Flight dp_f;
	dp_f.setInformation("UniFly", "Las Vegas", "14:50", "4:50", 800);
	dp_f.setFlightnumber(4563);
	std::vector<std::string> dp_st{ "Schwechat", "Frankfurt", "Denver", "Las Vegas" };
	PlaneTripInfo dp_info;
	dp_info.setPlaneTripInfo(dp_st, dp_f);
	Flight rt_f;
	rt_f.setFlightnumber(8598);
	rt_f.setInformation("FlyHigh", "Schwechat", "8:10", "21:40", 810);
	std::vector<std::string> rt_st{ "Las Vegas", "San Francisco", "München", "Schwechat" };
	PlaneTripInfo rt_info;
	rt_info.setPlaneTripInfo(rt_st, rt_f);
	PlaneTrip pt(dp_info, rt_info);
	//Person p(pt);
	//p.print(std::cout);
}


void TestNoStops() {
	Flight dp_f;
	dp_f.setInformation("UniFly", "Las Vegas", "14:50", "4:50", 800);
	dp_f.setFlightnumber(4563);
	PlaneTripInfo dp_info;
	dp_info.setPlaneTripInfo({}, dp_f);
	Flight rt_f;
	rt_f.setFlightnumber(8598);
	rt_f.setInformation("FlyHigh", "Schwechat", "8:10", "21:40", 810);
	PlaneTripInfo rt_info;
	rt_info.setPlaneTripInfo({}, rt_f);
	PlaneTrip pt(dp_info, rt_info);
	Person p(pt, "Anna", "Anabel", "Straße 10/4/2, 2222 Wien", 458652215, "weiblich", 25);
	p.print(std::cout);
}

void TestNoAge() {
	Flight dp_f;
	dp_f.setInformation("UniFly", "Las Vegas", "14:50", "4:50", 800);
	dp_f.setFlightnumber(4563);
	std::vector<std::string> dp_st{ "Schwechat", "Frankfurt", "Denver", "Las Vegas" };
	PlaneTripInfo dp_info;
	dp_info.setPlaneTripInfo(dp_st, dp_f);
	Flight rt_f;
	rt_f.setFlightnumber(8598);
	rt_f.setInformation("FlyHigh", "Schwechat", "8:10", "21:40", 810);
	std::vector<std::string> rt_st{ "Las Vegas", "San Francisco", "München", "Linz" };
	PlaneTripInfo rt_info;
	rt_info.setPlaneTripInfo(rt_st, rt_f);
	PlaneTrip pt(dp_info, rt_info);
	Person p(pt, "Anna", "Bell", "Strasse ,2222 Wien", 45632, "weiblich");
	p.print(std::cout);
}

void TestNoGender() {
	Flight dp_f;
	dp_f.setInformation("UniFly", "Las Vegas", "14:50", "4:50", 800);
	dp_f.setFlightnumber(4563);
	std::vector<std::string> dp_st{ "Schwechat", "Frankfurt", "Denver", "Las Vegas" };
	PlaneTripInfo dp_info;
	dp_info.setPlaneTripInfo(dp_st, dp_f);
	Flight rt_f;
	rt_f.setFlightnumber(8598);
	rt_f.setInformation("FlyHigh", "Schwechat", "8:10", "21:40", 810);
	std::vector<std::string> rt_st{ "Las Vegas", "San Francisco", "München", "Linz" };
	PlaneTripInfo rt_info;
	rt_info.setPlaneTripInfo(rt_st, rt_f);
	PlaneTrip pt(dp_info, rt_info);
	Person p(pt, "Anna", "Bell", "Strasse ,2222 Wien", 45632,25);
	p.print(std::cout);
}

void TestNoName() {
	Flight dp_f;
	dp_f.setInformation("UniFly", "Las Vegas", "14:50", "4:50", 800);
	dp_f.setFlightnumber(4563);
	std::vector<std::string> dp_st{ "Schwechat", "Frankfurt", "Denver", "Las Vegas" };
	PlaneTripInfo dp_info;
	dp_info.setPlaneTripInfo(dp_st, dp_f);
	Flight rt_f;
	rt_f.setFlightnumber(8598);
	rt_f.setInformation("FlyHigh", "Schwechat", "8:10", "21:40", 810);
	std::vector<std::string> rt_st{ "Las Vegas", "San Francisco", "München", "Linz" };
	PlaneTripInfo rt_info;
	rt_info.setPlaneTripInfo(rt_st, rt_f);
	PlaneTrip pt(dp_info, rt_info);
	Person p(pt, "weiblich", 25, "Strasse 10, 2222 Wien", 44586589);
	p.print(std::cout);
}