#include "address_t.h"

address_t::address_t(int const post_code, std::string const& city_name, std::string const& street_name, 
	int const house_number)
{
	// init address
	this->post_code = post_code;
	this->city_name = city_name;
	this->street_name = street_name;
	this->house_number = house_number;
}

std::ostream& operator<<(std::ostream& out, address_t const& address)
{
	// print address and return out stream
	return out << address.street_name << " " << address.house_number << ", " << address.post_code
		<< " " << address.city_name;
}
