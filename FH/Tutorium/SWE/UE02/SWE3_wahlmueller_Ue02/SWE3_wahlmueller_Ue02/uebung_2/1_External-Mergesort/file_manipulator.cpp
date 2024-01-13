#include "file_manipulator.h"
#include <random>

#include <chrono>

using clck = std::chrono::system_clock;
using rnd = std::default_random_engine;

using real_dist = std::uniform_real_distribution<double>;//same distribution - occurrence of a probability is always the same
using int_dist = std::uniform_int_distribution<int>;

void file_manipulator::fill_randomly(value_t const& dst, size_t n, int const no_letter){

	unsigned int seed = clck::now().time_since_epoch().count();//instead of time.t, set seed
	rnd generator{ seed };

	real_dist dis_r{ 0.0, 1.0 };
	int_dist dis_i{ 0, 25 };

	ofstream out{ dst };

	while (out && (n-- > 0)){

		for (int i = 0; i < no_letter; i++){

			char c;

			if (dis_r(generator) < 0.5) {

				c = ('a' + dis_i(generator));

			}

			else{

				c = ('A' + dis_i(generator));

			}

			out << c;

		}

		out << " ";

	}

	out.close();

}

size_t file_manipulator::partition(value_t const& src, cont_t const& dst){

	ifstream in { src };
	vector<ofstream*> out;

	for (size_t i = 0; i < dst.size(); i++){

		out.push_back(new ofstream(dst[i]));

	}

	size_t n{ 0 };
	value_t value;

	while (in >> value){

		ofstream& outFile{ *(out[n % dst.size()]) };

		if (outFile) {

			outFile << value << " ";

		}

		n++;

	}

	for (size_t i = 0; i < out.size(); i++) {
		out[i]->close();
		delete out[i];

	}

	return n;

}

file_manipulator::value_t file_manipulator::get_next(ifstream& in){

	if (!in.good()) {

		return value_t{};

	}

	value_t c{};

	in >> c;

	return c;

}

void file_manipulator::append(ofstream& out, value_t const& data, value_t const& separator){

	out << data << separator;

}

void file_manipulator::copy(value_t const& src, value_t const& dst){

	if (true) {

		ifstream in{ src  };
		ofstream out{ dst };

		if (in.good() && out.good()) {

			while (!in.eof()) {

				value_t str{};
				in >> str;
				out << str << " ";

			}

		}

		in.close();
		out.close();

	}

	else {

		ifstream in{ src , std::ios::binary};
		ofstream out{ dst, std::ios::binary };

		if (in.good() && out.good()) {

			out << in.rdbuf();

		}

		in.close();
		out.close();
	}

}