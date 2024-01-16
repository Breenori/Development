#if ! defined TEST_H
#define TEST_H

#include "merge_sort.h"
#include "file_manipulator.h"

class test
{
public:
	static void sort_nonexisting();
	static void sort_numbers();
	static void sort_empty();
	static void sort_weird();
	static void sort_5_random();

private:
	static void sort_random(std::string const& chaos_file, std::string const& sorted_file, size_t n, int const no_letters);
	static void sort_files(std::string const& file, std::string const& result);
};

#endif
