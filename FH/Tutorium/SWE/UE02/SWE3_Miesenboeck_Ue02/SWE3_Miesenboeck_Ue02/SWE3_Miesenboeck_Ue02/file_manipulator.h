#pragma once

#include <iostream>
#include <string>	
#include <fstream>
#include <vector>

class file_manipulator
{

public: //default scope = private

	using value_t_str = std::string;
	using cont_t_str = std::vector<value_t_str>;
	using index_t = std::size_t;

	//console output of file's content
	static size_t write_to_console(value_t_str const& src);

	//creates a copy of a file with custom name
	static void copy(value_t_str const& src, value_t_str const& dst);

	//creates a file with random combinations of letters
	static void fill_randomly(value_t_str const& dst, std::size_t n = 100, int const no_letters = 1); //destination, amount, number of letters

	//partitions a file into multiple files
	static std::size_t partition(value_t_str const& src, cont_t_str const& dst);

	static void write_to_file_continuous(std::vector<std::ofstream*> const& out_files, cont_t_str const& sorted_cont, index_t& first_in_file_counter, int const counter = 0);


};

