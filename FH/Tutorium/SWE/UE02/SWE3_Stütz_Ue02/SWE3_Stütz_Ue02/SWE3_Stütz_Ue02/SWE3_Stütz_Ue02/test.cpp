#include "test.h"
#include "file_manipulator.h"
#include "merge_sorter.h"

#include <fstream>

void test_fill_randomly(){
	FileManipulator::fill_randomly("test_partition.txt", 100, 2);
}

void test_partition(){
	std::vector<std::string> dst{ "partition_0.txt", "partition_1.txt" };
	FileManipulator::partition("test_partition.txt", dst);
}

void test_copy(){
	std::ofstream in{ "test_copy.txt" };
	FileManipulator::copy_print("files_to_sort.txt", in);
}

void test_print(){
	FileManipulator::copy_print("test_sort.txt");
}

void test_copy_print(){
	FileManipulator::copy_print("abc.txt");
}

void test_mergesort_1(){
	MergeSorter m;
	FileManipulator::copy_print("test_partition.txt");
	std::cout << "\n\n";
	std::string file = m.sort("test_partition.txt");
	FileManipulator::copy_print(file);
}

void test_mergesort_2(){
	MergeSorter m;
	FileManipulator::copy_print("test_sort.txt");
	std::cout << "\n\n";
	std::string file = m.sort("test_sort.txt");
	FileManipulator::copy_print(file);
}

void test_mergesort_3(){
	MergeSorter m;
	FileManipulator::copy_print("files_to_sort.txt");
	std::cout << "\n\n";
	std::string file = m.sort("files_to_sort.txt");
	FileManipulator::copy_print(file);
}

void test_mergesort_4(){
	MergeSorter m;
	FileManipulator::copy_print("abc.txt");
	std::cout << "\n\n";
	std::string file = m.sort("abc.txt");
	FileManipulator::copy_print(file);
}
