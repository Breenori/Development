#include "merge_sorter.h"
#include "file_manipulator.h"
#include <iostream>
#include <fstream>

MergeSorter::value_t MergeSorter::sort(value_t const& filename){
	std::vector<std::string> f{ "f0.txt", "f1.txt" };
	std::vector<std::string> g{ "g0.txt", "g1.txt" };

	//put the values of the source file in two different files
	size_t size = FileManipulator::partition(filename, f);

	//indicator shows which files are the inputfiles and vice versa
	int indicator{ 0 };
	int n{ 0 };

	std::vector<std::string> output = g;
	std::ifstream in0{ f[0] };
	std::ifstream in1{ f[1] };
	std::ofstream out;
		
	int k = 1; //running length

	std::string value = "";
	//read in values are saved in v
	cont_t v;
	
	//read, sort and merge until running length is bigger or equal to amount of elements in source file
	while (k < size) {

		//clear the files
		out.open(output[0], std::ios::trunc);
		out.close();
		out.open(output[1], std::ios::trunc);
		out.close();

		while (!in0.fail() && !in1.fail()) {

			//read running length amount of values
			for (int i{ 1 }; i <= k; ++i) {
				
				if (!in0.fail()) {
					in0 >> value;

					if (value != "") {
						v.push_back(value);
					}
				}

				value = "";

				if (!in1.fail()) {
					in1 >> value;

					if (value != "") {
						v.push_back(value);
					}
				}
			}

			if (v.size() != 0) {
				sort(v);
				//open stream in append mode and let it switch through modulo between the two outputfiles
				out.open(output[n % f.size()], std::ios::app);

				//print values of the vector to the files
				if (out) {
					for (int i{ 0 }; i < v.size(); ++i) {
						out << v[i] << ' ';
					}
				}
				n++;
			}
			v.clear();
			value = "";
			out.close();
		}

		in0.close();
		in1.close();

		//double running length
		k = k * 2;
		n = 0;

		//switch between input- and outputfiles
		if (indicator == 1) {
			in0.open(f[0]);
			in1.open(f[1]);
			output = g;
			indicator = 0;
		}
		else if (indicator == 0) {
			in0.open(g[0]);
			in1.open(g[1]);
			output = f;
			indicator = 1;
		}
		
	}

	if (output[0] == f[0]) {
		return g[0];
	}
	else {
		return f[0];
	}
}

void MergeSorter::sort(cont_t& v){
	cont_t aux(v.size());
	sort(v, aux, 0, v.size() - 1);
}

void MergeSorter::sort(cont_t& v, cont_t& aux, size_t lo, size_t hi){
	if (hi <= lo) {
		return;
	}

	size_t mid{ lo + (hi - lo) / 2 }; //calculate middle of the vector

	//call sort for left and right part
	sort(v, aux, lo, mid);
	sort(v, aux, mid + 1, hi);

	//merge the different parts
	merge(v, aux, lo, mid, hi);
}

void MergeSorter::merge(cont_t& v, cont_t& aux, size_t lo, size_t mid, size_t hi){
	size_t i{ lo };
	size_t j{ mid + 1 };

	//copy v in aux
	for (size_t k{ lo }; k <= hi; ++k) {
		aux[k] = v[k];
	}

	for (size_t k{ lo }; k <= hi; ++k) {

		if (i > mid) {
			v[k] = aux[j++]; //take from right part
		}
		else if (j > hi) {
			v[k] = aux[i++]; //take from left part
		}
		//average case --> smaller value is put to the front
		else if (aux[j] < aux[i]) {
			v[k] = aux[j++];
		}
		else {
			v[k] = aux[i++];
		}
	}
}
