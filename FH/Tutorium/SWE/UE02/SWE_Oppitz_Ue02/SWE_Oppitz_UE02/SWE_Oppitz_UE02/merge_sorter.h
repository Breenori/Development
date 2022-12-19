#ifndef MERGE_SORTER_H
#define MERGE_SORTER_H

#include "file_manipulator.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>


using std::string;
class merge_sorter {
public:
	file_manipulator file_manip;
	static void sort(file_manipulator::value_t const& file);

private:
	using index_t = std::size_t;
	static void sort_run(std::size_t run_lenght, file_manipulator::cont_t file_to_read,
		file_manipulator::cont_t file_to_write);

	static void merge(std::size_t const run_lenght, file_manipulator::cont_t file_to_read,
		file_manipulator::cont_t file_to_write);


 };



#endif // !MERGE_SORTER_H

