#include "person_t.h"

person_t::person_t(std::string const& first_name, std::string const& last_name, gender_t const& sex, 
	int const age, std::string const& credit_card_number, address_t* address)
{
	// init person
	this->first_name = first_name;
	this->last_name = last_name;
	this->age = age;
	this->sex = sex;
	this->credit_card_number = credit_card_number;
	this->address = address;
	this->bookings.clear();
}

void person_t::add_booking(trip_t const* const booking)
{
	// add trip if not nullptr
	if (booking != nullptr)
	{
		this->bookings.push_back(booking);
	}
}

std::ostream& person_t::print_bookings(std::ostream& out) const
{
	// prints all booked trips from a person
	for (size_t i{ 0 }; i < this->bookings.size(); ++i)
	{
		out << *(this->bookings[i]) << std::endl;
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, person_t const& person)
{
	// print credit card no first
	out << "Card No: " << person.credit_card_number << "\n";

	// print Mr. or Mrs. if gender is provided
	switch (person.sex)
	{
	case gender_t::female:
		out << "Mrs. ";
		break;
	case gender_t::male:
		out << "Mr. ";
		break;
	}

	// print person
	out << person.first_name << " " << person.last_name << "(" << person.age << ") from ";
	if (person.address == nullptr)
	{
		out << "no address given";
	}
	else
	{
		out << *person.address;
	}
	
	out << " has booked:\n";
	
	// add bookings to output stream
	return person.print_bookings(out);
}
