#ifndef PERSON_H
#define PERSON_H

#include<string>


using std::string;

class Person
{
private:
	string vorname;
	string nachname;
	bool geschlecht;
	int alter;
	string adresse;
	string kreditkarten_nummer;
public:
	Person();
	Person(string _vorname, string _nachname, bool _geschlecht, int _alter, string _adresse, string _kreditkarten_nummer);

	//setter
	string& get_vorname();
	string& get_nachname();
	bool& get_geschlecht();
	int& get_alter();
	string& get_adresse();
	string& get_kreditkarten_nummer();
	//getter
	string const& get_vorname() const;
	string const& get_nachname() const;
	int const  get_alter() const;
	bool const& get_geschlecht() const;
	string const& get_adresse() const;
	string const& get_kreditkarten_nummer() const;
};

#endif // !PERSON_H

