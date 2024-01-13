#include "file_manipulator.h"
#include <fstream>
#include <random>
#include <chrono>

using clck = std::chrono::system_clock;
using rnd = std::default_random_engine;
using real_dist = std::uniform_real_distribution<double>;
using int_dist = std::uniform_int_distribution<int>;

void FileManipulator::fill_randomly(value_t const& dst, std::size_t n, int const no_letters) {
	unsigned int seed = clck::now().time_since_epoch().count(); 
	rnd generator{ seed };
	real_dist rdis{ 0.0, 1.0 }; //under 0.5 lower case letters, over 0.5 capital letters
	int_dist idis{ 0,25 }; //generator for letters
	std::ofstream out{ dst };

	while (out && (n-- > 0)) {
		for (int i{ 0 }; i < no_letters; ++i) {
			char c;
			if (rdis(generator) < 0.5) { //generate random lower case letter
				c = ('a' + idis(generator));
			}
			else { //generate random capital letter
				c = ('A' + idis(generator));
			}
			out << c;
		}
		out << ' ';
	}
}

std::size_t FileManipulator::partition(value_t const& src, cont_t const& dst) { //writes values alternating in two files
	std::ifstream in{ src };
	std::vector<std::ofstream*> out; //vector of filenames

	for (std::size_t i{ 0 }; i < dst.size(); ++i) {
		out.push_back(new std::ofstream(dst[i]));
	}

	std::size_t n{ 0 };
	value_t value;

	while (in >> value) {
		//alternates between 0 and 1 and therefor between the two files
		std::ofstream& out_f{ *(out[n % dst.size()]) }; 

		if (out_f) {
			out_f << value << ' ';
		}
		n++;
	}

	for (std::size_t i{ 0 }; i < out.size(); ++i) {
		delete out[i];
	}
	return n;
}

void FileManipulator::copy_print(value_t const& src, std::ostream& out){
	std::ifstream in{ src };
	value_t value;
	
	if (!in.fail()) {
		while (in >> value) {
			out << value << ' ';
		}
	}
	else {
		out << "file doesn't exist\n";
	}
}
