#ifndef FILE_MANIPULATOR_H
#define FILE_MANIPULATOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


class file_manipulator {
public:
	using value_t = std::string;
	using cont_t = std::vector<value_t>;
	static void fill_randomly(value_t const& dst, std::size_t n = 100, int const no_letters = 1);
	static std::size_t partition(value_t const& src, cont_t const & dst);		//Ausgabefile als Vektor übergeben
	static void print(value_t const& src);
	static void copy(value_t const& src, value_t const & name_copy);


};






#endif // !FILE_MANIPULATOR_H

