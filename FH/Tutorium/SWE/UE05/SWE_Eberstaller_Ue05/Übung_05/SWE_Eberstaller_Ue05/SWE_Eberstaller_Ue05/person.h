#ifndef person_h
#define person_h

#include <string>

using std::string;

class person {
private:
	string first_name;
	string last_name;
	string gender;
	int age;
	string address;
	int credit_card_nr;
public:
	person(); // default constructor
	person(string const first_name, string const last_name, string const gender, // assign constructor
		int const age, string const address, int const credit_card_nr);
	~person();
	string get_first_name();
	string get_last_name();
	string get_gender();
	int get_age();
	string get_address();
	int get_credit_card_nr();
};


#endif
