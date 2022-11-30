#ifndef MERGE_SORTER_H
#define MERGE_SORTER_H

#include "file_manipulator.h"

class merge_sorter{

public:
	using all_files_t = vector<file_manipulator::cont_t>;

	static void sort(string const& filename);

private:
	static const all_files_t all_files;

};

#endif