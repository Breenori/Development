#include "file_manipulator.h"

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using clck = std::chrono::system_clock;
using rnd = std::default_random_engine;
using real_dist = std::uniform_real_distribution<double>; //Gleitkomma zwischen 0 und 1
using int_dist = std::uniform_int_distribution<int>; //ganzzahlige Zufallszahl zwischen x und y


void fileManipulator::fill_randomly_str(value_t const& dst, std::size_t n, int const no_letters) {
	unsigned int seed = clck::now().time_since_epoch().count();
	rnd generator{ seed };
	real_dist rdis{ 0.0, 1.0 };
	int_dist idis{ 0,25 };
	std::ofstream out{ dst };

	while (out && (n-- > 0)) {
		for (int i{ 0 }; i < no_letters; ++i) {
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

void fileManipulator::fill_randomly_int(value_t const& dst, std::size_t n, int const max_nr) {
	unsigned int seed = clck::now().time_since_epoch().count();
	rnd generator{ seed };
	int_dist idis{ 0,max_nr };
	std::ofstream out{ dst };

	while (out && (n-- > 0)) {
		int nr;
		nr = idis(generator);
		out << nr << ' ';
	}
}


std::size_t fileManipulator::partition(value_t const& src, cont_t const& dst) {
	std::ifstream in(src); //file in in laden
	std::vector<std::ofstream*> out;

	for (std::size_t i{ 0 }; i < dst.size(); ++i) {
		//f¸r jeden dateinamen einen output filestream
		out.push_back(new std::ofstream(dst[i]));
	}

	//anzahl Elemente tracken
	std::size_t n{ 0 };
	value_t value;
	while (in >> value) { //lieﬂt bis zum n‰chsten Leerzeichen ein
		std::ofstream& out_f{ *(out[n % dst.size()]) }; //mit jedem eingelesenen Element ausgabestream wechseln, Restwertdivision wechselt zwischen 0 und 1 stream
		if (out_f) {
			out_f << value << ' ';
		}
		n++;
	}
	
	//files in src abwechselnd in container schreiben


	for (std::size_t i{ 0 }; i < dst.size(); ++i) {
		//lˆsche mit new erzeugte ostreams
		delete out[i];
	}

	return n;
}

void fileManipulator::print(value_t const& file) {
	std::ifstream in(file);
	
	value_t value;
	while (in >> value)
	{
		std::cout << value << " ";
	}
	in.close();
}

void fileManipulator::copy(value_t const& src, value_t const& dst) {
	std::ifstream in(src);
	std::ofstream out(dst);

	value_t value;
	while (in >> value)
	{
		out << value << ' ';
	}
	in.close();
	out.close();
}

std::vector<int> fileManipulator::read(value_t const& src)
{
	std::ifstream in(src);
	std::vector<int> v{};

	int value;
	while (in >> value)
	{
		v.push_back(value);
	}
	in.close();
	return v;


}

void fileManipulator::write(std::vector<int>v_tmp, value_t dst)
{
	std::ofstream out(dst);
	for (int value : v_tmp)
	{
		out << value << ' ';
	}
	out.close();
}

std::size_t fileManipulator::re_partition(value_t const& src0, value_t const& src1, value_t const& dst) {

	std::vector<int> v_0{ fileManipulator::read("tmp_"+src0)};
	std::vector<int> v_1{ fileManipulator::read("tmp_"+src1)};
	std::vector<int> v;



	//repartition / merge the two sorted files into one sorted file
	size_t n{ 0 };
	size_t i{ 0 };
	size_t j{ 0 };
	bool finished{ false };
	while ( i < v_0.size() && j < v_1.size())
	{
		if (v_0[i] <= v_1[j])
		{
			v.push_back(v_0[i]);
			++i;
			if (i==v_0.size())//if v_0 is fully added, add v_0
			{
				while (j < v_1.size())
				{
					v.push_back(v_1[j]);
					++j;
				}
			}
		}
		else
		{
			v.push_back(v_1[j]);
			++j;
			if (j == v_1.size())//if v_1 is fully added, add v_1
			{
				while (i < v_0.size())
				{
					v.push_back(v_0[i]);
					++i;
				}
			}
		}

	}


	fileManipulator::write(v, dst);
	return n;

}