#ifndef FLUG_H
#define FLUG_H

#include "person.h"
#include <vector>

using std::vector;

class Flug
{
private:
	string flugnummer;
	string fluggesellschaft;
	string ort;
	string abflug;
	string ankunft;
	int dauer;
	vector<Person> passagiere;
public:
	Flug();
	Flug(string _flugnummer, string _fluggesellschaft, string _ort, string _abflug, string _ankunft, int dauer);


	void update_dauer();
//can be used as setter but have the same name as the real getter
	string& get_flugnummer();
	string&  get_fluggesellschaft();
	string&  get_ort();
	string&  get_abflug();
	string&  get_ankunft();
	int&  get_dauer();
	vector<Person>& get_passagiere();
	//getter
	string const& get_flugnummer() const;
	string const& get_fluggesellschaft() const;
	string const& get_ort() const;
	string const& get_abflug() const;
	string const& get_ankunft() const;
	int const& get_dauer() const;
	vector<Person> const& get_passagiere() const;

};


#endif // !FLUG_H

