#include "flug.h"

Flug::Flug() {}
Flug::Flug(string _flugnummer, string _fluggesellschaft, string _ort, string _abflug, string _ankunft, int _dauer)
	:flugnummer(_flugnummer), fluggesellschaft(_fluggesellschaft), ort(_ort), abflug(_abflug), ankunft(_ankunft), dauer(_dauer) {
	update_dauer();
}


//can be used as setter but have the same name as the real getter
string& Flug::get_flugnummer() {
	return flugnummer;
}
string& Flug::get_fluggesellschaft() {
	return fluggesellschaft;
}
string& Flug::get_ort() {
	return ort;
}
string& Flug::get_abflug() {
	return abflug;
}
string& Flug::get_ankunft() {
	return ankunft;
}
int& Flug::get_dauer() {
	return dauer;
}
vector<Person>& Flug::get_passagiere() {
	return passagiere;
}
//getter
string const& Flug::get_flugnummer() const {
	return flugnummer;
}
string const& Flug::get_fluggesellschaft() const {
	return fluggesellschaft;
}
string const& Flug::get_ort() const {
	return ort;
}
string const& Flug::get_abflug() const {
	return abflug;
}
string const& Flug::get_ankunft() const {
	return ankunft;
}
int const& Flug::get_dauer() const {
	return dauer;
}
vector<Person> const& Flug::get_passagiere() const {
	return passagiere;
}


void Flug::update_dauer() {
	//TODO
}