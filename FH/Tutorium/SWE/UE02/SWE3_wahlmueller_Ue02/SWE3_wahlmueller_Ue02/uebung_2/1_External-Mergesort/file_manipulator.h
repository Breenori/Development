#ifndef FILE_MAIPULATOR_H
#define FILE_MAIPULATOR_H

#include <iostream>
#include <string>

#include <vector>
#include <fstream>

#include "merge_sort.h"

using std::string;
using std::vector;

using std::size_t;
using std::ofstream;

using std::ifstream;

class file_manipulator{

public:
	using value_t = string;
	using cont_t = vector<value_t>;

	static void fill_randomly(value_t const& dst, size_t n = 100, int const no_letter = 1);
	static size_t partition(value_t const& src, cont_t const& dst);

	static value_t get_next(ifstream& in);
	static void append(ofstream& out, value_t const& data, value_t const& separator = " ");

	static void copy(value_t const& src, value_t const& dst);

private:


};

#endif