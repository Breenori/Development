#include "test.h"

void test::sort_nonexisting() {
	sort_files("nonexisting.txt", "nonexisting_result.txt");
}
void test::sort_numbers() {
	sort_files("numbers.txt", "numbers_result.txt");
}
void test::sort_empty() {
	sort_files("empty.txt", "empty_result.txt");
}
void test::sort_weird() {
	sort_files("weird.txt", "weird_result.txt");
}
void test::sort_5_random() {
	std::string filename{ "random" };
	for (int i{ 0 }; i < 5; ++i) {
		filename = filename + std::to_string(i);

		sort_random(filename + ".txt", filename + "_result.txt", 20, 3);

		std::cout << '\n';

		filename = "random";
	}

}

void test::sort_random(std::string const& chaos_file, std::string const& sorted_file, size_t n, int const no_letters) {

	file_manipulator::fill_randomly(chaos_file, n, no_letters);
	file_manipulator::print(chaos_file, std::cout)<<'\n';

	merge_sorter::sort(chaos_file, sorted_file);
	file_manipulator::print(sorted_file, std::cout) << '\n';

}
void test::sort_files(std::string const& file, std::string const& result) {
	file_manipulator::print(file, std::cout) << '\n';
	merge_sorter::sort(file, result);
	file_manipulator::print(result, std::cout) << '\n';
}