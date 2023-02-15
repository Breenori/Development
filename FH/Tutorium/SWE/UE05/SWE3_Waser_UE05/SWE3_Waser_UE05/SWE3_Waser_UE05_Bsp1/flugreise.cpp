#include "flugreise.h"

ostream& operator<<(ostream& out, Flugreise const& f) {
	cout << "Hinflug: "<<f.start<<" -> ";
	for (auto it = f.hin.begin(); it != f.hin.end(); ++it) {
		cout << (*it).get_ort();
		if (it != --f.hin.end()) {
			cout << " -> ";
		}
	}
	cout << "\nRueckflug: ";
	for (auto it = f.rueck.begin(); it != f.rueck.end(); ++it) {
		cout << (*it).get_ort() << " -> ";
	}
	cout << f.start;
	return out;
}

Flugreise::Flugreise() {}

Flugreise::Flugreise(string const& _start) : start(_start) {}

void Flugreise::add_hinflug(Flug& f) {
	bool found(false);
	//check flugnummer, can't add same flug
	for (auto it = hin.begin(); it != hin.end() && !found; ++it) {
		if ((*it).get_flugnummer() == f.get_flugnummer()) {
			found = true;
		}
	}
	//add flug
	if (!found)
		hin.push_back(f);
}
void Flugreise::add_ruckflug(Flug& f) {
	bool found(false);
	//check flugnummer, can't add same flug
	for (auto it = rueck.begin(); it != rueck.end() && !found; ++it) {
		if ((*it).get_flugnummer() == f.get_flugnummer()) {
			found = true;
		}
	}
	//add flug
	if (!found)
		rueck.push_back(f);
}