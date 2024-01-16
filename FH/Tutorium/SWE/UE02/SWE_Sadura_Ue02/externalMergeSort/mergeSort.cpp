#include "mergeSort.h"
#include "FileManipulator.h"
#include <iostream>
#include <fstream>

void MergeSort::sort(std::string const& src) {
	std::vector<std::string>* ins = new std::vector<std::string>{ "f0.txt", "f1.txt" };
	size_t numElements = FileManipulator::partition(src, (*ins));

	std::vector<std::string>* outs = new std::vector<std::string>{ "g0.txt","g1.txt" };
	//for k runs, k = 1 to n/2 +1 for rest
	for (size_t k = 1; k < numElements; k = k * 2){
		std::ofstream((*outs)[0]) << "";
		std::ofstream((*outs)[1]) << "";
		//segments to write for each file
		for (size_t s = 0; s < numElements / 2 / k + 1; s++){
			merge(s, k, ins, (*outs)[s % 2]);
		}

		auto temp = outs;
		outs = ins;
		ins = temp;

	}
	//copy result into original file
	FileManipulator::copy((*ins)[0], src);
	//delete
	delete ins;
	delete outs;

}


void MergeSort::merge(int s, int k, cont_t* const& ins, std::string const& out) {
	std::string val1 = "";
	std::string val2 = "";
	int i = 0;
	int j = 0;
	bool p1 = FileManipulator::getValue(s, k, i, (*ins)[0], val1);
	bool p2 = FileManipulator::getValue(s, k, j, (*ins)[1], val2);
	while (p1 && p2) {
		if (val1 <= val2) {
			FileManipulator::writeTo(val1, out);
			++i;
			p1 = FileManipulator::getValue(s, k, i, (*ins)[0], val1);
		}
		else {
			FileManipulator::writeTo(val2, out);
			++j;
			p2 = FileManipulator::getValue(s, k, j, (*ins)[1], val2);
		}
	}
	while (p1) {
		FileManipulator::writeTo(val1, out);
		++i;
		p1 = FileManipulator::getValue(s, k, i, (*ins)[0], val1);
	}
	while (p2) {
		FileManipulator::writeTo(val2, out);
		++j;
		p2 = FileManipulator::getValue(s, k, j, (*ins)[1], val2);
	}
	return;
}