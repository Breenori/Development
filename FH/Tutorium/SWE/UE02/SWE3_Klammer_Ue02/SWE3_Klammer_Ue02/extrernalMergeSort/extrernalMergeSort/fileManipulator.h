#ifndef FILE_MAIPULATOR_H
#define FILE_MAIPULATOR_H
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
#include <iostream>

class fileManipulator {

public:
	// usings
	using container_t = std::vector<std::string>;

	// functions
	fileManipulator();
	fileManipulator(container_t const& source);
	~fileManipulator();
	static void fill_randomly(std::string const& destination, std::size_t n = 100, int const number_of_letters = 1);
	static std::size_t partition(std::string const& source, container_t const& destination);
	static void print(std::string const& source);

};

#endif // !FILE_MAIPULATOR_H