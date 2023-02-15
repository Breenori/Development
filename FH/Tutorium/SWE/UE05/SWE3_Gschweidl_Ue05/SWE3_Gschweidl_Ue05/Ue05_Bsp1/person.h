#ifndef person_h
#define person_h

#include <string>
#include <vector>
#include <iostream>

namespace person {

	struct address {
		std::string street;
		int house_number;
		int postal_code;
		std::string city;
	};

	struct dob {
		int year;
		int month;
		int day;
	};

	enum sex {
		female,
		male,
		divers
	};

	class Person {


	private:
		std::string FirstName;
		std::string LastName;
		dob DateOfBirth;
		int Age;
		sex Sex;
		address Address;
		int CreditCardNo;
	

	public:

		Person();
		~Person();
		void setPerson(std::string first_name, std::string last_name, int dob_year, int dob_month, int dob_day, int age,
			int credit_card_no, person::sex sex, std::string street, int house_no, int postal_code, std::string city);
		void PrintPersonFile();

	};
}

class Customers {
private:
	std::vector<person::Person*> persons;

public:
	Customers();
	~Customers();
	void AddPerson(person::Person* customer);
	std::vector<person::Person*>& getCustomers();
	static void PrintPersons(std::vector<person::Person*> const persons);

};

#endif // !person_h
