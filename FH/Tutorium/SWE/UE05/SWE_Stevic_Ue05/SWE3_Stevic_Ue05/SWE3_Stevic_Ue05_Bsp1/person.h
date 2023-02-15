#ifndef person_h
#define person_h

#include <string>

using std::string;

enum gender_type
{
	male,
	female,
	diverse
};

struct adress_type
{
	string street_name;
	string street_number; //house_number; string because there may be letters added (for instance 16a)
	string post_code; //string because some may have letters in them
	string city_name;
	string country;
};

class person
{
private:
	string first_name;
	string last_name;
	gender_type gender;
	size_t age;
	adress_type adress;
	string credit_card_number; //string because it's not used for arithmetic operations

public:

	person(string const& _first_name, string const& _last_name, gender_type const& _gender, size_t const _age, adress_type const& _adress, string const& _credit_card_number)
	{
		this->first_name = _first_name;
		this->last_name = _last_name;
		this->gender = _gender;
		this->age = _age;
		this->adress = _adress;
		this->credit_card_number = _credit_card_number;
	}

	string get_first_name() const
	{
		return this->first_name;
	}

	string get_last_name() const
	{
		return this->last_name;
	}

	adress_type get_adress() const
	{
		return this->adress;
	}

	string get_credit_card_number() const
	{
		return this->credit_card_number;
	}
};

#endif