#include "tests.h"

// ------------------------------------------------------------------------ //
// ------------------------ TESTS fileManipulatr -------------------------- //
void test_fill_ranomly() {

	fileManipulator::fill_randomly("randomly_filled_file.txt", 100, 3);
}
void test_partition() {

	fileManipulator::container_t destination{ "part1.txt", "part2.txt" };
	fileManipulator::partition("randomly_filled_file.txt", destination);
}
void test_copy() {

	fileManipulator destination;
	fileManipulator::container_t source{ "randomly_filled_file.txt" };
	destination.fileManipulator::fileManipulator(source);
}
void test_print() {

	fileManipulator destination;
	fileManipulator::container_t source{ "randomly_filled_file.txt" };
	destination.fileManipulator::fileManipulator(source);
	fileManipulator::print(source[0]);
}

// --------------------------------------------------------------------- //
// ------------------------ TESTS mergeSorter -------------------------- //
void test_emptyFile() {

	mergeSorter sort;
	std::string source{ "fileToSort_Empty.txt" };
	mergeSorter::container_type destination{ "part1.txt", "part2.txt" };
	sort.sort(source, destination);
}
void test_sortingNumbers() {

	mergeSorter sort;
	std::string source{ "fileToSort.txt" };
	mergeSorter::container_type destination{ "part1.txt", "part2.txt" };
	sort.sort(source, destination);
}
void test_sortingCharacters() {

	mergeSorter sort;
	std::string source{ "fileToSort_Chars.txt" };
	mergeSorter::container_type destination{ "part1.txt", "part2.txt" };
	sort.sort(source, destination);
}
void test_sortingStrings() {

	mergeSorter sort;
	std::string source{ "fileToSort_Strings.txt" };
	mergeSorter::container_type destination{ "part1.txt", "part2.txt" };
	sort.sort(source, destination);
}
void test_specialCharacter() {

	mergeSorter sort;
	std::string source{ "fileToSort_SpecialChars.txt" };
	mergeSorter::container_type destination{ "part1.txt", "part2.txt" };
	sort.sort(source, destination);
}
void test_sortingEvenNumber() {

	mergeSorter sort;
	std::string source{ "fileToSort_Even.txt" };
	mergeSorter::container_type destination{ "part1.txt", "part2.txt" };
	sort.sort(source, destination);
}
void test_sortigOddNumber() {

	mergeSorter sort;
	std::string source{ "fileToSort_Odd.txt" };
	mergeSorter::container_type destination{ "part1.txt", "part2.txt" };
	sort.sort(source, destination);
}
