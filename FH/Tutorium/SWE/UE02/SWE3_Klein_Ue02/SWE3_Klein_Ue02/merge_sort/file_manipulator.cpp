#include "file_manipulator.h"

#include <random>
#include <chrono>

using clck = std::chrono::system_clock;
using rnd = std::default_random_engine;
using real_dist = std::uniform_real_distribution<double>;
using int_dist = std::uniform_int_distribution<int>;



void file_manipulator::fill_randomly(value_t const& dst, std::size_t n, int const no_letters) {

	unsigned int seed = clck::now().time_since_epoch().count();
	rnd generator{ seed };
	real_dist dis_r{ 0.0,1.0 };  //decides between upper and lower -case letters
	int_dist dis_i{ 0, 25 };  //decides the actual letter
	std::ofstream out{ dst };

	// generating n sets of random chars [A-Za-z] as long as the output stream is fine
	while (out && (n-- > 0)) {
		// generating no_letters chars for each set
		for (int i{ 0 }; i < no_letters; ++i) {
			char c;
			if (dis_r(generator) < 0.5) {
				c = ('a' + dis_i(generator));
			}
			else {
				c = ('A' + dis_i(generator));
			}
			out << c;
		}
		out << ' ';
	}
}

std::size_t file_manipulator::partition(value_t const& src, cont_t const& dst) {
	std::ifstream in { src };
	std::vector<std::ofstream*> out;

	// putting the output streams for all files in the vector
	for (std::size_t i{ 0 }; i < dst.size(); ++i) {
		out.push_back(new std::ofstream(dst[i]));
	}

	std::size_t n{ 0 };
	value_t value;
	// as long as the input streams delievers new input -> the whole file gets read 
	while (in >> value) {
		// the current outputstream calculated with n (a counter)
		std::ofstream& outFile{ *(out[n % dst.size()]) };
		if (outFile) {
			outFile << value << ' ';
		}
		n++;
	}

	// deleting the streams from the heap -> closing the streams
	for (std::size_t i{ 0 }; i < out.size(); ++i) {
		delete out[i];
	}
	return n;
}

std::ostream& file_manipulator::print(value_t const& src, std::ostream& out) {

	std::ifstream in{ src };

	value_t value;

	// as long as the input streams delievers new input -> the whole file gets read 
	while (in >> value) {
		if (out) {
			// each value gets printed on the given output stream
			out << value << ' ';
		}
	}
	return out;
}

void file_manipulator::copy(value_t const& src, value_t const& dst) {
	std::ofstream out{ dst };
	// printing the source on the dst via output stream
	print(src, out);
}

