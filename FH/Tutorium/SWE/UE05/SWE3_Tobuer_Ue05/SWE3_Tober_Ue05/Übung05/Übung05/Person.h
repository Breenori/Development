#if!defined PERSON_H
#define PERSON_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Person {
public:
	Person();  //default constructor
	~Person(); //deconstructor

	std::string get_first_name() const;
	std::string get_last_name() const;
	char get_gender() const;
	int get_age() const;
	std::string get_address() const;
	int get_creditcard_number() const;

	void new_person(std::string const& _first_name, std::string const& _last_name, char const& _gender, int const& _age, std::string const& _address, int const _creditcard_number);
	void print_person(std::ostream& out = std::cout) const;

private:
	std::string first_name;
	std::string last_name;
	char gender;
	int age;
	std::string address;
	int creditcard_number;
};

#endif