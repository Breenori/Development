#include "person.h"
#include <time.h>
#include <ctime>

person::Person::Person() {
	//nothing here
}

person::Person::~Person() {
	//nothing here
}

void person::Person::setPerson(std::string first_name, std::string last_name, int dob_year, int dob_month, int dob_day, int age, int credit_card_no, person::sex sex, std::string street, int house_no, int postal_code, std::string city) {
	this->FirstName = first_name;
	this->LastName = last_name;
	this->DateOfBirth.year = dob_year;
	this->DateOfBirth.month = dob_month;
	this->DateOfBirth.day = dob_day;
	this->Age = age;
	this->Sex = sex;
	this->CreditCardNo = credit_card_no;
	this->Address.street = street;
	this->Address.house_number = house_no;
	this->Address.postal_code = postal_code;
	this->Address.city = city;
}

void person::Person::PrintPersonFile() {
	std::cout <<"Name: " << this->FirstName << " " << this->LastName <<" (";
	if (this->Sex == 0) {
		std::cout << "f";
	}
	else if (this->Sex == 1) {
		std::cout << "m";
	}
	else {
		std::cout << "d";
	}
	std::cout << ")\n";
	std::cout << "Age: " << this->Age << "\n";
	std::cout << "Address: ";
	std::cout << this->Address.street << " " << this->Address.house_number << ", ";
	std::cout << this->Address.postal_code << " " << this->Address.city << "\n";
	std::cout << "Credit Card Number: " << this->CreditCardNo << "\n";
}

Customers::Customers() {
	// nothing here
}

Customers::~Customers() {
	// nothing here
}

void Customers::AddPerson(person::Person* customer) {
	this->persons.push_back(customer);
}

std::vector<person::Person*>& Customers::getCustomers() {
	return this->persons;
}

void Customers::PrintPersons(std::vector<person::Person*> const persons) {
	for (std::size_t i{ 0 }; i < persons.size(); ++i) {
		std::cout << i << ": ";
		(*persons[i]).PrintPersonFile();
		std::cout << "\n";
	}
}
