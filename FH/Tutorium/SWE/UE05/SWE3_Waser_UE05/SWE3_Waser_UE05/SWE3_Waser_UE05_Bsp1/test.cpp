#include "test.h"
void testFlugreise() {
	cout << "\n\ntest Flugreise:\n";
	Flugreise f("Linz");
	Person p1("Testine", "Testinger", true, 20, "Adresse", "1241234123");
	Person p2("Testian", "Testinger", false, 20, "Adresse", "123812323234");
	Person p3("Test", "Testner", false, 30, "Adresse", "12381222323234");

	Flug fl1("1234A", "Fluggesellschaft A", "Frankfurt", "12:00", "14:00", 120);
	fl1.get_passagiere().push_back(p1);
	fl1.get_passagiere().push_back(p2);
	fl1.get_passagiere().push_back(p3);
	Flug fl2("6234B", "Fluggesellschaft A", "Denver", "12:00", "14:00", 120);
	fl2.get_passagiere().push_back(p1);
	fl2.get_passagiere().push_back(p2);
	fl2.get_passagiere().push_back(p3);
	Flug fl3("3234C", "Fluggesellschaft B", "Las Vegas", "12:00", "14:00", 120);
	fl3.get_passagiere().push_back(p1);
	fl3.get_passagiere().push_back(p2);
	fl3.get_passagiere().push_back(p3);

	Flug fl4("7234D", "Fluggesellschaft C", "Las Vegas", "12:00", "14:00", 120);
	fl4.get_passagiere().push_back(p1);
	fl4.get_passagiere().push_back(p2);
	fl4.get_passagiere().push_back(p3);
	Flug fl5("1334E", "Fluggesellschaft A", "San Francisco", "12:00", "14:00", 120);
	fl5.get_passagiere().push_back(p1);
	fl5.get_passagiere().push_back(p2);
	fl5.get_passagiere().push_back(p3);
	Flug fl6("1234E", "Fluggesellschaft E", "München", "12:00", "14:00", 120);
	fl6.get_passagiere().push_back(p1);
	fl6.get_passagiere().push_back(p2);
	fl6.get_passagiere().push_back(p3);

	f.add_hinflug(fl1);
	f.add_hinflug(fl2);
	f.add_hinflug(fl3);

	f.add_ruckflug(fl4);
	f.add_ruckflug(fl5);
	f.add_ruckflug(fl6);

	cout << f;

	cout << "\ntry add same flug twice: ";
	f.add_hinflug(fl5);
	f.add_hinflug(fl5);
	f.add_ruckflug(fl2);
	f.add_ruckflug(fl2);
	cout << f;


}
void testPerson() {
	cout << "Test Person:\nwith default constructor: ";
	Person p;
	cout << "\nget_vorname:\t" << p.get_vorname();
	cout << "\nget_nachname:\t" << p.get_nachname();
	cout << "\nget_alter:\t" << p.get_alter();
	cout << "\nget_adresse:\t" << p.get_adresse();
	cout << "\nget_geschlecht:\t";
	if (p.get_geschlecht())
		cout << "weiblich";
	else
		cout << "männlich";
	cout << "\nget_kreditkarten_nummer:\t" << p.get_kreditkarten_nummer();

	cout << "\n\nconstructor with values: ";
	Person p2("Testine","Testinger",true,21,"Adresse 23, 1234 Stadt", "12345666677899");

	cout << "\nget_vorname:\t" << p2.get_vorname();
	cout << "\nget_nachname:\t" << p2.get_nachname();
	cout << "\nget_alter:\t" << p2.get_alter();
	cout << "\nget_adresse:\t" << p2.get_adresse();
	cout << "\nget_geschlecht:\t";
	if (p2.get_geschlecht())
		cout << "weiblich";
	else
		cout << "männlich";
	cout << "\nget_kreditkarten_nummer:\t" << p2.get_kreditkarten_nummer();
	cout << "\n\nuse 'setter' and change vorname and alter: ";
	p2.get_vorname() = "Tina";
	p2.get_alter() = 22;
	cout << "\nget_vorname:\t" << p2.get_vorname();
	cout << "\nget_alter:\t" << p2.get_alter();
		
}
void testFlug() {
	cout << "\n\nTest Flug:\n default consturctor:";
	Person p1("Testine", "Testinger", true, 20, "Adresse", "1241234123");
	Person p2("Testian", "Testinger", false, 20, "Adresse", "123812323234");
	Person p3("Test", "Testner", false, 30, "Adresse", "12381222323234");
	Flug f;
	Flug f2("1234A","Fluggesellschaft","Wien", "12:00", "14:00", 120);
	f2.get_passagiere().push_back(p1);
	f2.get_passagiere().push_back(p2);
	f2.get_passagiere().push_back(p3);
	cout << "\nget_flugnummer:\t" << f.get_flugnummer();
	cout << "\nget_fluggesellschaft:\t" << f.get_fluggesellschaft();
	cout << "\nget_abflug:\t" << f.get_abflug();
	cout << "\nget_ankunft:\t" << f.get_ankunft();
	cout << "\nget_dauer:\t" << f.get_dauer();
	cout << "\nget_ort:\t" << f.get_ort();
	cout << "\n\nFlug with values:";
	cout << "\nget_flugnummer:\t" << f2.get_flugnummer();
	cout << "\nget_fluggesellschaft:\t" << f2.get_fluggesellschaft();
	cout << "\nget_abflug:\t" << f2.get_abflug();
	cout << "\nget_ankunft:\t" << f2.get_ankunft();
	cout << "\nget_dauer:\t" << f2.get_dauer();
	cout << "\nget_ort:\t" << f2.get_ort();
	cout << "\nget_passagiere:\t";
	for (auto it = f2.get_passagiere().begin(); it != f2.get_passagiere().end(); ++it) {
		cout << "\n" << (*it).get_vorname()<<" " << (*it).get_nachname();
	}
}