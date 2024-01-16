#include "merge_sorter.h"
#include <cstdio>

using std::remove;

const merge_sorter::all_files_t merge_sorter::all_files = { {"g0.txt" ,"g1.txt"}, {"h0.txt" ,"h1.txt" } };

void merge_sorter::sort(string const& filename){

	//seperating into two files
	file_manipulator::partition(filename, all_files[0]);

	vector<ofstream*> outfiles;
	vector<ifstream*> infiles;

	bool sorted{ false };
	size_t sqare_number_symbol{ 0 };

	//does nothing if sorted
	while (!sorted) {

		//clearing
		infiles.clear();
		outfiles.clear();

		//putting file input into the file streams
		for (size_t i = 0; i < all_files[sqare_number_symbol % 2].size(); i++) {

			infiles.push_back(new ifstream(all_files[sqare_number_symbol % 2][i]));
			outfiles.push_back(new ofstream(all_files[(sqare_number_symbol+1) % 2][i]));

		}

		size_t count{ 0 };
		size_t number_of_symbols = pow(2, sqare_number_symbol);

		while (!infiles[0]->eof() && !infiles[1]->eof()) {

			//get 1 symbol from each file
			vector<file_manipulator::value_t> in_symbols{ 2 };

			for (size_t i = 0; i < in_symbols.size(); i++) {

				in_symbols[i] = file_manipulator::get_next(*infiles[i]);

			}

			//symbol numbers
			int written_symbol_0 = 0;
			int written_symbol_1 = 0;
			int written_symbol = -1;

			for (int k = 0; k < 2*number_of_symbols; k++) {

				if (written_symbol_0 >= number_of_symbols) {

					if (in_symbols[1] == "") {

						break;

					}

					file_manipulator::append(*outfiles[count % 2], in_symbols[1]);
					written_symbol_1++;

					if (written_symbol_1 < number_of_symbols) {

						in_symbols[1] = file_manipulator::get_next(*infiles[1]);

					}

				}

				else {

					if (written_symbol_1 >= number_of_symbols) {

						if (in_symbols[0] == "") {

							file_manipulator::append(*outfiles[count % 2], in_symbols[1]);
							written_symbol = 1;
							written_symbol_1++;

						}

						file_manipulator::append(*outfiles[count % 2], in_symbols[0]);
						written_symbol_0++;

						if (written_symbol_0 < number_of_symbols) {

							in_symbols[0] = file_manipulator::get_next(*infiles[0]);

						}

					}

					else {

						if (written_symbol == 0) {

							in_symbols[0] = file_manipulator::get_next(*infiles[0]);

						}

						if (written_symbol == 1) {

							in_symbols[1] = file_manipulator::get_next(*infiles[1]);

						}

						// compensate uneven distribution
						if (in_symbols[0] == "") {

							if (in_symbols[1] == "") {

								if (count == 0) {

									sorted = true;

								}

								break;

							}

							file_manipulator::append(*outfiles[count % 2], in_symbols[1]);
							written_symbol = 1;
							written_symbol_1++;

						}

						else {

							if (in_symbols[1] == "") {

								if (in_symbols[0] == "") {

									if (count == 0) {

										sorted = true;

									}

								break;

								}

								file_manipulator::append(*outfiles[count % 2], in_symbols[0]);
								written_symbol = 0;
								written_symbol_0++;

							}

							else {

								//write the sorted symbols
								if (stoi(in_symbols[0]) > stoi(in_symbols[1])) {

									//file_manipulator::append(*outfiles[count % 2], in_symbols[0]);
									file_manipulator::append(*outfiles[count % 2], in_symbols[1]);
									written_symbol = 1;
									written_symbol_1++;

								}

								else {

									//file_manipulator::append(*outfiles[count % 2], in_symbols[1]);
									file_manipulator::append(*outfiles[count % 2], in_symbols[0]);
									written_symbol = 0;
									written_symbol_0++;

								}

							}

						}

					}

				}

			}

			++count;

		}

		//close all
		for (size_t i = 0; i < all_files[sqare_number_symbol%2].size(); i++) {

			infiles[i]->close();

		}

		for (size_t i = 0; i < all_files[sqare_number_symbol % 2].size(); i++) {

			outfiles[i]->close();

		}

		sqare_number_symbol++;
	}

	//test = file_manipulator::get_next(*infiles[0]);
	
	//for debugging
	//file_manipulator::copy(all_files[sqare_number_symbol % 2][0], filename);

	//copy of sorted file into new file
	file_manipulator::copy(all_files[sqare_number_symbol % 2][0], "after.txt");

	for (size_t i = 0; i < all_files[0].size(); i++) {

		remove(all_files[1][i].c_str());
		remove(all_files[0][i].c_str());

	}

}