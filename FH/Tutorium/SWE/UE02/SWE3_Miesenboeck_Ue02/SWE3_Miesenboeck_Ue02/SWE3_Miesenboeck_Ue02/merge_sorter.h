#pragma once

#include "file_manipulator.h"

#include <vector>

class merge_sorter {


public:

	using index_t = file_manipulator::index_t;
	using value_t_str = file_manipulator::value_t_str;
	using cont_t_str = file_manipulator::cont_t_str;
	using input_t = std::string;

	//sorts inputfile
	static void sort(input_t const& src, bool const sort_numeric = false, bool const asc = true, input_t const& dst = "sorted.txt");


private:

	static bool sort(file_manipulator::cont_t_str const& prm_partitions, file_manipulator::cont_t_str const& sec_partitions, index_t const el_amount, index_t const run_size, index_t& no_run, bool const sort_numeric, bool const asc);

	static bool sort_operation(std::vector<std::ifstream*> const& in_files, std::vector<std::ofstream*> const& out_files, index_t const run_size, int& counter, bool const sort_numeric, bool const asc);

	static void read_for_sort(cont_t_str& value_cont_1, cont_t_str& value_cont_2, index_t const run_size, std::ifstream& in_file_1, std::ifstream& in_file_2);

	static void detail_sort(cont_t_str& sorted_cont, cont_t_str const& value_cont_1, cont_t_str const& value_cont_2, bool const sort_numeric, bool const asc);

	static bool is_even(int const num);
};