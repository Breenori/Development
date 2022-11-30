#if ! defined MERGE_SORT_H
#define MERGE_SORT_H

#include "file_manipulator.h"

#include <string>
#include <vector>

class merge_sorter {
public:
	static void sort(std::string const& infilename, std::string const& outfilename);

private:
	// to remember what files the algorithm is currently working on
	enum file_types {
		g,
		f
	};

	// the helper files
	static file_manipulator::cont_t f_files;
	static file_manipulator::cont_t g_files;

	static size_t sort_step(size_t k, file_manipulator::cont_t const & src, file_manipulator::cont_t const& dst);
	static void merge(size_t const k, std::ofstream* out, std::vector<std::ifstream*> in, file_manipulator::value_t& value1);
};


#endif
