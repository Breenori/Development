#include "FileManipulator.h"
#include <fstream>
#include <random>
#include <chrono>
#include <iostream>

using clck = std::chrono::system_clock;
using rnd = std::default_random_engine;
using realDist = std::uniform_real_distribution<double>;
using intDist = std::uniform_int_distribution<int>;

void FileManipulator::fillRandomly(value_t const& dst, size_t n, int const num_letters) {
	//seit 1.1.1970 in Millisekunden
	unsigned int seed = clck::now().time_since_epoch().count();
	rnd generator{ seed };
	realDist rdis{ 0.0,1.0 };
	//returns a number for the letter 
	intDist idis{ 0,25 };
	std::ofstream out{ dst };

	while (out && (n-- > 0)) {
		for (int i = 0; i < num_letters; ++i) {
			//letter written to file
			char c;
			if (rdis(generator) < 0.5) {
				c = ('a' + idis(generator));
			}
			else {
				c = ('A' + idis(generator));
			}
			out << c;
		}
		out << ' ';
	}

}

//dst = Dateinamen, 
std::size_t FileManipulator::partition(value_t const& src, cont_t const& dst) {
	std::ifstream in(src);
	if (!in.good()) {
		std::cout << "File not Found! Check input file name!\n";
		return 0;
	}
	//Referenz auf OutputStream nicht den Outputstream selbst
	std::vector<std::ofstream*> out;

	for (std::size_t i = 0; i < dst.size(); ++i) {
		out.push_back(new std::ofstream(dst[i]));
	}
	//number of variables
	std::size_t n = 0;
	value_t value;

	//liest bis zum ersten Leerzeichen, einlesen Elementweise
	while (in >> value) {
		//mit jedem Element wird der Ausgabestream gewechselt
		//alternates between 0 and 1
		std::ostream& out_f(*(out[n % dst.size()]));
		if (out_f) {
			out_f << value << " ";
		}
		n++;
	}

	for (std::size_t i = 0; i < out.size(); ++i) {
		delete out[i];
	}

	return n;

}

void FileManipulator::copy(std::string const& src, std::string const& dst) {
	std::ofstream out(dst);
	print(src, out);
}

std::ostream& FileManipulator::print(std::string const& src, std::ostream& out) {
	//out << src << ": \n";
	std::ifstream in(src);
	if (!in.good()) {
		out << "File not found! check input!\n";
	}

	std::string v;
	while (in >> v) {
		out << v << ' ';
	}
	//out << "\n\n";
	return out;
}


bool FileManipulator::getValue(int s, int k, int i, std::string inName, std::string& val) {
	val = "";
	std::ifstream in(inName);
	if (i >= k) {
		in.close();
		return false;
	}
	for (size_t x = 0; x < s * k + i; x++)
	{
		if (in.good()) {
			std::string p;
			in >> p;
		}
		else { return false; }
	}
	if (in.good()) {
		in >> val;
		return true;
	}
	in.close();
	return false;
}

void FileManipulator::writeTo(std::string const& Value, std::string outName) {
	std::ofstream(outName, std::ios_base::app) << Value << " ";
}