#include "merge_sorter.h"

using std::string;
using std::cerr;
using std::endl;
using std::stoi;

namespace globals
{

	string const PARTITION_1 = "prt_prm_0.txt";
	string const PARTITION_2 = "prt_prm_1.txt";
	string const PARTITION_3 = "prt_sec_0.txt";
	string const PARTITION_4 = "prt_sec_1.txt";
	int constexpr RUN_SIZE_START_VALUE = 1;
	int constexpr RUN_START_VALUE = 0;
	int constexpr PART_AMOUNT = 2;
	int constexpr PART_1_IDX = 0;
	int constexpr PART_2_IDX = 1;
	char constexpr SEPARATOR = ' ';

}

void merge_sorter::sort(input_t const& src, bool sort_numeric, input_t const& dst)
{
	//no filename
	if (!src.empty()) {

		//partition groups
		file_manipulator::cont_t_str const primary_partitions{ globals::PARTITION_1, globals::PARTITION_2 };
		file_manipulator::cont_t_str const secondary_partitions{ globals::PARTITION_3, globals::PARTITION_4 };


		//partition file
		index_t const el_amount(file_manipulator::partition(src, primary_partitions));

		//empty file
		if (el_amount != 0) {

			//keeps track of number of sort runs
			index_t no_runs(globals::RUN_START_VALUE);



			//execute external mergesort
			sort(primary_partitions, secondary_partitions, el_amount, globals::RUN_SIZE_START_VALUE, no_runs, sort_numeric);




			//determines location of final result
			if (is_even(no_runs))
			{
				//copies result to dst file
				file_manipulator::copy(globals::PARTITION_3, dst);
			}
			else
			{
				//copies result to dst file
				file_manipulator::copy(globals::PARTITION_1, dst);
			}

			//displays result in console
			file_manipulator::write_to_console(dst);
		}

		//ERROR
		else
		{
			cerr << "ERROR: File could not be sorted." << endl << endl;
		}

	}

	//ERROR
	else
	{
		cerr << "ERROR: No compatible file found." << endl << endl;
	}
}


void merge_sorter::sort(file_manipulator::cont_t_str const& prm_partitions, file_manipulator::cont_t_str const& sec_partitions, index_t const el_amount, index_t const run_size, index_t& no_run, bool sort_numeric)
{

	//in case of "endless" sort runs (should not happen, just in case)
	if (no_run >= el_amount)
	{
		cerr << "ERROR: Run timed out." << endl << endl;
		return;
	}

	std::vector<std::ifstream*> in_files(globals::PART_AMOUNT);

	std::vector<std::ofstream*> out_files(globals::PART_AMOUNT);

	//fill file vecs
	for (int i = 0; i < globals::PART_AMOUNT; ++i)
	{
		in_files[i] = new std::ifstream(prm_partitions[i]);
		out_files[i] = new std::ofstream(sec_partitions[i]);
	}

	//counts loops in run
	int counter(0);


	//executes sort operation
	sort_operation(in_files, out_files, run_size, counter, sort_numeric);


	//if only 1 run --> result
	if (counter > 1) {
		//flip partitions
		sort(sec_partitions, prm_partitions, el_amount, run_size * 2, ++no_run, sort_numeric);
	}
}


void merge_sorter::sort_operation(std::vector<std::ifstream*> const& in_files, std::vector<std::ofstream*> const& out_files, index_t const run_size, int& counter, bool sort_numeric)
{

	//as partition amount is fixed to 2
	std::ifstream& in_file_1(*in_files[globals::PART_1_IDX]);
	std::ifstream& in_file_2(*in_files[globals::PART_2_IDX]);

	//counts first outputs to files
	index_t first_in_file_counter(0);

	//still content in files
	while (in_file_1.good() || in_file_2.good())
	{
		cont_t_str value_cont_1(run_size);
		cont_t_str value_cont_2(run_size);

		//execute read of partitions
		read_for_sort(value_cont_1, value_cont_2, run_size, in_file_1, in_file_2);

		//vec for sorted values
		cont_t_str sorted_cont(value_cont_1.size() + value_cont_2.size());

		detail_sort(sorted_cont, value_cont_1, value_cont_2, sort_numeric);

		write_to_file(out_files, counter, sorted_cont, first_in_file_counter);

		++counter;

	}


	in_file_1.close();
	in_file_2.close();

	//delete all created pointers
	for (int i = 0; i < globals::PART_AMOUNT; ++i)
	{
		delete in_files[i];
		delete out_files[i];
	}

}

void merge_sorter::read_for_sort(cont_t_str& value_cont_1, cont_t_str& value_cont_2, index_t const run_size, std::ifstream& in_file_1, std::ifstream& in_file_2)
{

	value_t_str read_value;

	//last position an input was read
	//default value --> 1 over size --> no action if not changed
	index_t stop_value_1 = run_size + 1;
	index_t stop_value_2 = run_size + 1;

	bool stopped(false);

	for (int i(0); i < run_size; ++i)
	{
		//read from partition 1
		if (in_file_1 >> read_value) {
			value_cont_1[i] = read_value;

			//in case run was already stopped by empty partition 2 read
			if (stopped)
			{
				stop_value_1 = i + 1;
			}
		}

		//if run has not been stopped by partition 2
		else if (!stopped)
		{
			stop_value_1 = i;
			stop_value_2 = i;
		}

		//read from partition 2
		if (in_file_2 >> read_value) {
			value_cont_2[i] = read_value;
		}

		//if run has not been stopped yet
		else if (!stopped)
		{
			stop_value_1 = i + 1;
			stop_value_2 = i;
			stopped = true;
		}
	}
}

void merge_sorter::detail_sort(cont_t_str& sorted_cont, cont_t_str const& value_cont_1, cont_t_str const& value_cont_2, bool sort_numeric)
{
	index_t idx_1(0);
	index_t idx_2(0);

	//sort values read from partition
	for (int i(0); i < sorted_cont.size(); ++i) {

		//index 1 at end
		if (idx_1 >= value_cont_1.size())
		{
			sorted_cont[i] = value_cont_2[idx_2++];
		}
		//index 2 at end
		else if (idx_2 >= value_cont_2.size())
		{
			sorted_cont[i] = value_cont_1[idx_1++];
		}
		//value 1 lower than value 2 - ALSO: sort numeric check
		else if (sort_numeric ? stoi(value_cont_1[idx_1]) < stoi(value_cont_2[idx_2]) : value_cont_1[idx_1] < value_cont_2[idx_2])
		{
			sorted_cont[i] = value_cont_1[idx_1++];
		}
		//value 2 lower than value 1 or same value
		else {
			sorted_cont[i] = value_cont_2[idx_2++];
		}
	}
}

	
	
void merge_sorter::write_to_file(std::vector<std::ofstream*> const& out_files, int const counter, cont_t_str const& sorted_cont, index_t& first_in_file_counter)
{
	//alternating out files
	std::ofstream& out_file(*(out_files[counter % globals::PART_AMOUNT]));

	//write to ouput partitions
	for (int i(0); i < sorted_cont.size(); ++i)
	{
		//for first value in each file
		if (i == 0 && first_in_file_counter < out_files.size())
		{
			out_file << sorted_cont[i];
			++first_in_file_counter;
		}

		else {
			out_file << globals::SEPARATOR << sorted_cont[i];
		}
	}
}

bool merge_sorter::is_even(int const num)
{
	return num % 2 == 0;
}