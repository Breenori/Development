#ifndef PERSON_T_H
#define PERSON_T_H

#include "address_t.h"
#include "trip_t.h"

enum gender_t
{
	unknown,
	female,
	male
};

class person_t
{
	using bookings_t = std::vector<trip_t const*>;

	std::string first_name;
	std::string last_name;
	gender_t sex;
	int age;
	std::string credit_card_number;
	address_t* address;

	bookings_t bookings;

	friend std::ostream& operator<< (std::ostream& out, person_t const& person);

public:
	person_t(std::string const& first_name, std::string const& last_name, gender_t const& sex,
		int const age, std::string const& credit_card_number, address_t* address);
	person_t() = delete;
	person_t(person_t const& src) = delete;
	~person_t() = default;

	void add_booking(trip_t const* const booking);

private:
	std::ostream& print_bookings(std::ostream& out) const;
};

std::ostream& operator<< (std::ostream& out, person_t const& person);

#endif // !PERSON_T_H
