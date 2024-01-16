#include "merge_sorter.h"

void merge_sorter::sort(file_manipulator::value_t const& file) {

	bool stream_good{ false };
	std::ifstream stream{ "file" };
	if (!stream.eof()) {
		stream_good = true;
	}
	stream.close();

	file_manipulator::cont_t f{ "f0.txt", "f1.txt" };
	file_manipulator::cont_t g{ "g0.txt", "g1.txt" };

	size_t n{ file_manipulator::partition(file, f) };

	size_t run_lenght{ 1 };

	bool is_f{ true };
	while (run_lenght <= n) {
		if (is_f) {
			sort_run(run_lenght, f, g);
			is_f = false;
		}
		else {
			sort_run(run_lenght, g, f);
			is_f = true;
		}

		run_lenght *= 2;
	}
	//does the same as 
	//	sort_run(1, f, g);
	//	sort_run(2, g, f);
	//	sort_run(4, f, g);

	if (stream_good) {
		std::string text{ "" };
		std::ifstream i{ "g0.txt" };
		std::string name{ file };
		name.replace(name.find(".", 0), 1, "_sorted.");
		std::ofstream o{ name };
		while (i >> text) {
			o << text << " ";
		}
	}
}

void merge_sorter::sort_run(std::size_t run_lenght, file_manipulator::cont_t file_to_read,
	file_manipulator::cont_t file_to_write) {
	merge(run_lenght, file_to_read, file_to_write);


}

void merge_sorter::merge(std::size_t const run_lenght, file_manipulator::cont_t file_to_read,
	file_manipulator::cont_t file_to_write) {

	std::vector<std::ifstream* > in;
	for (std::size_t i{ 0 }; i < file_to_read.size(); ++i) {
		in.push_back(new std::ifstream(file_to_read[i]));
	}

	std::vector<std::ofstream* > out;
	for (std::size_t i{ 0 }; i < file_to_write.size(); ++i) {
		out.push_back(new std::ofstream(file_to_write[i]));
	}

	std::string text_0;
	*in[0] >> text_0;
	std::string text_1;
	*in[1] >> text_1;
	std::size_t counter{ 0 };
	std::size_t run_count{ 0 };

	std::size_t count_0{ 1 };
	std::size_t count_1{ 1 };

	while (!in[1]->eof() || !in[0]->eof()) {
		std::ofstream& outFile{ *(out[counter % file_to_write.size()]) };

		if ((text_0 > text_1 || count_0 > run_lenght) && count_1 <= run_lenght && text_1 != "") {
			outFile << text_1 << " ";
			if (!(*in[1] >> text_1)) {

				text_1 = {};
			}
			++count_1;
		}
		else {
			outFile << text_0 << " ";
			if (!(*in[0] >> text_0)) {
				text_0 = {};
			}
			++count_0;
		}
		if (count_0 > run_lenght && count_1 > run_lenght) {
			counter++;
			count_0 = 1;
			count_1 = 1;
		}

	}
	for (std::size_t i{ 0 }; i < file_to_read.size(); ++i) {
		delete in[i];
	}

	for (std::size_t i{ 0 }; i < file_to_write.size(); ++i) {
		delete out[i];
	}

}
