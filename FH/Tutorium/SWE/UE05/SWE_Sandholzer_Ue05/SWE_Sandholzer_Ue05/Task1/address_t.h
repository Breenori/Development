#ifndef ADDRESS_T_H
#define	ADDRESS_T_H

#include <string>
#include <iostream>

class address_t
{
	int post_code;
	std::string city_name;
	std::string street_name;
	int house_number;

	friend std::ostream& operator<< (std::ostream& out, address_t const& address);

public:
	address_t() = delete;
	address_t(int const post_code, std::string const& city_name, std::string const& street_name, 
		int const house_number);
	address_t(address_t const& src) = delete;
	~address_t() = default;
};

std::ostream& operator<< (std::ostream& out, address_t const& address);

#endif // !ADDRESS_T_H
