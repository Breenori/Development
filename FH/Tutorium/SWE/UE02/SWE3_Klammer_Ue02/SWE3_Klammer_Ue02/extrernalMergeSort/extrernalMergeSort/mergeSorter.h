#ifndef MERGE_SORTER_H
#define MERGE_SORTER_H

#include <vector>
#include <iostream>
#include "fileManipulator.h"
#include <string>
#include <fstream>
#include <algorithm>

class mergeSorter {

	friend std::size_t fileManipulator::partition(std::string const& source, container_t const& destination);
public:
	using container_type = std::vector<std::string>;

	void sort(std::string const& source, container_type const& destination);

private:
	container_type splitStream(std::string const& source);
	void sort(container_type const& source, container_type const& destination, int const k = 1);
	int calcRuns(container_type const& source, int const k);
	static void writeToFile(container_type const& temp, std::string const& destination);
};

#endif // !MERGE_SORTER_H