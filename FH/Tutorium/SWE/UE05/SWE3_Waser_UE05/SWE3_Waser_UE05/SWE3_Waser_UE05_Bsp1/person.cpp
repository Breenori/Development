#include "person.h"

Person::Person(): alter(0), geschlecht(true){}
Person::Person(string _vorname, string _nachname, bool _geschlecht, int _alter, string _adresse, string _kreditkarten_nummer) 
	:vorname(_vorname), nachname(_nachname), geschlecht(_geschlecht), alter(_alter), adresse(_adresse), kreditkarten_nummer(_kreditkarten_nummer) {}

//setter
string& Person::get_vorname() {
	return vorname;
}
string& Person::get_nachname() {
	return nachname;
}
bool& Person::get_geschlecht() {
	return geschlecht;
}
int& Person::get_alter() {
	return alter;
}
string& Person::get_adresse() {
	return adresse;
}
string& Person::get_kreditkarten_nummer() {
	return kreditkarten_nummer;
}
//getter
string const& Person::get_vorname() const {
	return vorname;
}
string const& Person::get_nachname() const {
	return nachname;
}
int const  Person::get_alter() const {
	return alter;
}
bool const& Person::get_geschlecht() const {
	return geschlecht;
}
string const& Person::get_adresse() const {
	return adresse;
}
string const& Person::get_kreditkarten_nummer() const {
	return kreditkarten_nummer;
}