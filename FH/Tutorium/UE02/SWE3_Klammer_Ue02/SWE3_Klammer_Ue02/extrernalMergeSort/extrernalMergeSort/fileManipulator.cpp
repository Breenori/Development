#include "fileManipulator.h"

using clck = std::chrono::system_clock;
using rnd = std::default_random_engine;
using real_dist = std::uniform_real_distribution<double>;
using int_dist = std::uniform_int_distribution<int>;

fileManipulator::fileManipulator() {

}
fileManipulator::fileManipulator(container_t const& source) {

	container_t destination(source.size());
	container_t temp = source;
	std::string replaceText = ".txt";
	int pos = 0;
	for (int i = 0; i < source.size(); i++) {

		pos = source[i].find(".");
		temp[i] = temp[i].replace(pos, replaceText.length(), "_copy.txt");
		partition(source[i], destination);
	}

}
fileManipulator::~fileManipulator() {

}
void fileManipulator::fill_randomly(std::string const& destination, std::size_t n, int const number_of_letters) {

	unsigned int seed = clck::now().time_since_epoch().count(); // seed berechnen bzw zusammensetzen, same as letztes semester but anders zusammengesetzt
	rnd generator{ seed };
	real_dist rdis{ 0.0, 1.0 };
	int_dist idis{ 0, 25 }; // multiplukator mit buchstaben um an zufälligen zu bekommen
	std::ofstream out{ destination };

	while (out && (n-- > 0)) {

		for (int i{ 0 }; i < number_of_letters; i++) {

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
std::size_t fileManipulator::partition(std::string const& source, container_t const& destination) {

	std::ifstream in{ source };
	std::vector<std::ofstream*> out;

	for (std::size_t i{ 0 }; i < destination.size(); i++) {

		out.push_back(new std::ofstream(destination[i]));
	}

	int n{ 0 };
	std::string value;
	while (in >> value) {

		// alternates between 0 and 1
		std::ofstream& out_file{ *(out[n % destination.size()]) };
		if (out_file) {

			out_file << value << " ";
		}

		n++;
	}

	for (std::size_t i{ 0 }; i < out.size(); i++) {

		delete out[i];
	}

	return n;
}
void fileManipulator::print(std::string const& source) {

	std::ifstream file;
	file.open(source);
	
	if (!file) {

		std::cout << "No such file.";
	}
	else {

		while (!file.eof()) {

			std::string temp;
			std::getline(file, temp);
			std::cout << temp;
		}
	}
}
