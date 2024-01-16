#include "file_manipulator.h"
#include <random>
#include <chrono>

#include "merge_sorter.h"

using std::endl;

namespace globals
{

	char constexpr SEPARATOR(' ');

}

using clck = std::chrono::system_clock;
using rnd = std::default_random_engine;
using real_dist = std::uniform_real_distribution<double>;
using int_dist = std::uniform_int_distribution<int>;
using std::cout;


size_t file_manipulator::write_to_console(value_t_str const& src)
{

	std::ifstream in{ src };

	value_t_str value;

	size_t counter(0);

	//content gets read separated by spaces
	while (in >> value)
	{
		cout << value << globals::SEPARATOR; //write content to console, separated by separator
		++counter;
	}

	cout << endl;

	return counter;

}


void file_manipulator::copy(value_t_str const& src, value_t_str const& dst)
{

	std::ifstream in{ src };

	std::ofstream out{ dst };

	value_t_str value;

	//content gets read separated by spaces
	while (in >> value)
	{
		out << value << ' '; //write content to ofstream, separated by separator
	}

}


void file_manipulator::fill_randomly(value_t_str const& dst, std::size_t n, int const no_letters)
{

	unsigned int seed = clck::now().time_since_epoch().count(); //gets current value from clock

	rnd generator{ seed };

	real_dist dis_r{ 0.0,1.0 }; //random range 1, lowercase or uppercase
	int_dist dis_i{ 0,25 }; //random range 2, which letter

	std::ofstream out{ dst };

	while (out && (n-- > 0))
	{
		//for size of letter groups
		for (int i(0); i < no_letters; ++i)
		{
			char c;
			if (dis_r(generator) < 0.5) //lowercase (randomly generated)
			{
				c = ('a' + dis_i(generator)); //randomly generated letter
			}
			else //uppercase
			{
				c = ('A' + dis_i(generator)); //randomly generated letter
			}
			out << c; //write char to file
		}
		out << globals::SEPARATOR; //write separator after letter group
	}
	out.close();
}


std::size_t file_manipulator::partition(value_t_str const& src, cont_t_str const& dst)
{

	std::ifstream in{ src };

	if (in.good()) {

		//fs is not copyable and not assignable --> usage of pointers
		std::vector<std::ofstream*> out_files(dst.size());

		//fill output-files vec
		for (int i = 0; i < dst.size(); ++i)
		{
			out_files[i] = new std::ofstream(dst[i]);
		}

		std::size_t amount_lettergroups{ 0 };
		value_t_str value;

		int first_in_file_counter(0);

		while (in >> value)
		{

			//alternate between output files
			std::ofstream& out_file(*(out_files[amount_lettergroups % dst.size()]));

			//write to output file with separator
			if (out_file && first_in_file_counter < dst.size())
			{
				++first_in_file_counter;
				out_file << value;
			}
			else if (out_file)
			{
				out_file << globals::SEPARATOR << value;
			}

			++amount_lettergroups;
		}

		//delete all created pointers
		for (int i = 0; i < out_files.size(); ++i)
		{
			delete out_files[i];
		}

		return amount_lettergroups; //returns the amount of lettergroups that were partitioned
	}
	else
	{
		std::cerr << "ERROR: No compatible file found." << endl << endl;
		return 0;
	}
}


void file_manipulator::write_to_file_continuous(std::vector<std::ofstream*> const& out_files, cont_t_str const& sorted_cont, index_t& first_in_file_counter, int const counter)
{
	//alternating out files
	std::ofstream& out_file(*(out_files[counter % out_files.size()]));

	//write to ouput partitions
	for (int i(0); i < sorted_cont.size(); ++i)
	{
		//for first value in each file
		if (i == 0 && first_in_file_counter < out_files.size())
		{
			out_file << sorted_cont[i];
			++first_in_file_counter;
		}

		//for other values
		else {
			out_file << globals::SEPARATOR << sorted_cont[i];
		}
	}
}