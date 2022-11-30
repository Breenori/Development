#include "merge_sort.h"

// initializing the helper files
file_manipulator::cont_t merge_sorter::f_files = { "f0.txt", "f1.txt" }; 
file_manipulator::cont_t merge_sorter::g_files = { "g0.txt", "g1.txt" };


void merge_sorter::sort(std::string const& infilename, std::string const& outfilename) {
	size_t const n{ file_manipulator::partition(infilename, f_files) }; //n is the amount of strings
	size_t k{ 1 }; //current run length
	file_types current_srcfiles{ f }; //the current source files (f or g)
	while (k < n) {
		if (current_srcfiles == f) {
			k = sort_step(k, f_files, g_files);
			current_srcfiles = g; //changing the current source files to the opposite
		}
		else {
			k = sort_step(k, g_files, f_files);
			current_srcfiles = f; //changing the current source files to the opposite
		}

	}
	// copying the right file into the result file
	if (current_srcfiles == f) {
		file_manipulator::copy(f_files[0], outfilename);
	}
	else {
		file_manipulator::copy(g_files[0], outfilename);
	}
}


size_t merge_sorter::sort_step(size_t k, file_manipulator::cont_t const& src, file_manipulator::cont_t const& dst) {
	std::vector<std::ofstream*> out;
	std::vector<std::ifstream*> in;

	// putting the output streams for both dst files in the vector
	for (std::size_t i{ 0 }; i < dst.size(); ++i) {
		out.push_back(new std::ofstream(dst[i]));
	}
	// putting the input streams for both src files in the vector
	for (std::size_t i{ 0 }; i < src.size(); ++i) {
		in.push_back(new std::ifstream(src[i]));
	}

	size_t current_out_ind{ 0 }; // to remember which output stream to use

	file_manipulator::value_t value;

	while (*(in[0]) >> value) {

		merge(k, out[current_out_ind], in, value);
		
		current_out_ind = (current_out_ind + 1) % 2; // changing the output stream to the other one
	}

	//deleting all the streams from the heap
	for (std::size_t i{ 0 }; i < out.size(); ++i) {
		delete out[i];
	}
	for (std::size_t i{ 0 }; i < in.size(); ++i) {
		delete in[i];
	}

	return k * 2; // doubleing the run length
}

void merge_sorter::merge(size_t const k, std::ofstream* out, std::vector<std::ifstream*> in, file_manipulator::value_t& value1) {
	file_manipulator::value_t value2;
	size_t read_count_0{ 1 }; // to count how many values have been read from input file index 0
	size_t read_count_1{ 0 }; // to count how many values have been read from input file index 1

	bool good{ true };
	
	// for every value in the run in inputfile index 1
	while (read_count_1 < k && *in[1] >> value2) {
		++read_count_1;
		// all the values from inputfile 0 in the run, that are smaller than the current value from inputfile 1
		while (good && value1 < value2) {
			*out << value1 << ' ';
			if (read_count_0 < k && *in[0] >> value1) {
				++read_count_0;
			}
			else {
				good = false;
			}
		}
		*out << value2 << ' ';
	}

	// all the values from inputfile 0 in the run that are left 
	while (good) {
		*out << value1 << ' ';
		if (read_count_0 < k && *in[0] >> value1) {
			++read_count_0;
		}
		else {
			good = false;
		}
	}


}
