#include "mergeSorter.h"

mergeSorter::container_type mergeSorter::splitStream(std::string const& source) {

	std::ifstream in{ source };
	std::string temp;
	container_type resultList;

	while (std::getline(in, temp, ' ')) {

		resultList.push_back(temp);
	}

	return resultList;
}
int mergeSorter::calcRuns(container_type const& source, int const k) {

	container_type file1 = splitStream(source[0]);
	container_type file2 = splitStream(source[1]);

	int check1 = file1.size() / k;
	int check2 = file2.size() / k;

	return check1 >= check2 ? check1 : check2;
}
void mergeSorter::writeToFile(container_type const& temp, std::string const& destination) {

	std::ofstream out{ destination };
	for (int i = 0; i < temp.size(); i++) {

		out << temp[i] << " ";
	}
}
void mergeSorter::sort(std::string const& source, container_type const& destination) {

	fileManipulator::partition(source, destination);
	container_type newDestination{ "g0.txt", "g1.txt" };
	sort(destination, newDestination);
}
void mergeSorter::sort(container_type const& source, container_type const& destination, int const k) {

	if (k > source[0].size()) {

		return;
	}

	// splitting stream into several strings
	container_type file1 = splitStream(source[0]);
	container_type file2 = splitStream(source[1]);

	container_type newFile1;
	container_type newFile2;

	container_type temp;
	bool evenOrNull = true;
	int run = calcRuns(source, k);

	int currentIndex = 0;
	for (int i = 0; i < run; i++) {

		// add needed values for comparison
		for (int j = 0; j < k; j++) {

			temp.push_back(file1[currentIndex]);

			if (currentIndex < file2.size()) {

				temp.push_back(file2[currentIndex]);
			}

			currentIndex++;
		}

		std::sort(temp.begin(), temp.end());

		// add sorted values to new File
		for (int i = 0; i < temp.size(); i++) {

			if (evenOrNull) {

				newFile1.push_back(temp[i]);
			}
			else {

				newFile2.push_back(temp[i]);
			}
		}

		evenOrNull = evenOrNull ? false : true;
		temp.clear();
	}

	writeToFile(newFile1, destination[0]);
	writeToFile(newFile2, destination[1]);

	container_type newSource;
	container_type newDestination;

	if (k == 1) {

		newSource = { "g0.txt", "g1.txt" };
		newDestination = { "f0.txt", "f1.txt" };
	}
	else {
		newSource = destination;
		newDestination = source;
	}

	sort(newSource, newDestination, k * 2);
}