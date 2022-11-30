#include "file_manipulator.h"
#include <random>
#include <chrono>		//for setting



using clck = std::chrono::system_clock;
using rnd = std::default_random_engine;
using real_dist = std::uniform_real_distribution<double>;
using int_dist = std::uniform_int_distribution<int>;


void file_manipulator::fill_randomly(value_t const& dst, std::size_t n, int const no_letters) {
	unsigned int seed = clck::now().time_since_epoch().count();		//time since unix
	rnd generator{ seed };
	real_dist dis_r{ 0.0, 1.0 };
	int_dist dis_i{ 0,25 };
	std::ofstream out{ dst };

	while (out && (n-- > 0)) {
		for (int i = 0; i < no_letters; ++i) {
			char c;
			if (dis_r(generator) < 0.5) {
				c = ('a' + dis_i(generator));
			}
			else {
				c = ('A' + dis_i(generator));
			}
			out << c;
		}
		out << " ";
	}

	out.close();
}


//src --> file to split, dst --> files splited
std::size_t file_manipulator::partition(value_t const& src, cont_t const& dst) {
	std::ifstream in{ src };
	std::vector<std::ofstream* > out;			//pointer!!! vec muss kopierbar und zuweisbar sein
	for (std::size_t i{ 0 }; i < dst.size(); ++i) {
		out.push_back(new std::ofstream(dst[i]));
	}

	std::size_t n{ 0 };
	value_t value;
	while (in >> value) {	//einzelnen Elemente ohne Leerzeichen
		std::ofstream& outFile{ *(out[n % dst.size()]) };
		if (outFile) {
			outFile << value << ' ';
		}
		n++;
	}

	for (std::size_t i{ 0 }; i < out.size(); ++i) {
		delete out[i];
	}
	return n;
}



void file_manipulator::print(value_t const& src) {

	std::ifstream in{src};
	while (in.good()) {
		value_t line{ "" };
		std::getline(in, line);
		std::cout << line << '\n';
	}
	in.close();
}



void file_manipulator::copy(value_t const& src, value_t const& name_copy) {
	std::ofstream out{ name_copy };
	std::ifstream in{ src };

	value_t line{ "" };
	while (in.good()) {
		std::getline(in, line);
		out << line << '\n';
		std::cout << line << '\n';
	}

	in.close();
	out.close();

}