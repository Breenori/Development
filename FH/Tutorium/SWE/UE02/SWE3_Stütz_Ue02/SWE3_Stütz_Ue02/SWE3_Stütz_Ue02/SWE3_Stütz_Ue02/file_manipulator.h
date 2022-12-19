#ifndef file_manipulator_h
#define file_manipulator_h

#include <iostream>
#include <string>
#include <vector>

class FileManipulator {
public:

	using value_t = std::string;
	using cont_t = std::vector<value_t>;

	static void fill_randomly(value_t const& dst, std::size_t n = 100, int const no_letters = 1);
	static std::size_t partition(value_t const& src, cont_t const& dst);
	static void copy_print(value_t const& src, std::ostream& out = std::cout);
	//evtl noch ein paar Überprüfungen, falls Datei nicht existiert, Datei leer ist, etc.

};



#endif // !file_manipulator_h
