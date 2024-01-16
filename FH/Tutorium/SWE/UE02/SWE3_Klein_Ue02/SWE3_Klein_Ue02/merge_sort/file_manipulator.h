#if ! defined FILE_MANIPULATOR_H
#define FILE_MANIPULATOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class file_manipulator {

public:
	using value_t = std::string;
	using cont_t = std::vector<value_t> ;


	static void fill_randomly(value_t const& dst, std::size_t n = 100, int const no_letters = 1);
	static std::ostream& print(value_t const& src, std::ostream& out);
	static std::size_t partition(value_t const& src, cont_t const& dst);
	static void copy(value_t const& src, value_t const& dst);

};




#endif