#include "tests.h"
#include <iostream>


void testPartition() {
	std::cout << "Testcases:\n";
	std::cout << "This tests partition with not existing file\n";
	std::vector<std::string> ins{ "f0.txt","f1.txt" };
	std::string fileName = "test_partition.txt";

	std::cout << "original file size & content: \n";
	std::cout << FileManipulator::partition(fileName, ins) << "(size) \n";
	FileManipulator::print(fileName, std::cout);
	std::cout << "\nf0: ";
	FileManipulator::print("f0.txt", std::cout);
	std::cout << "\nf1: ";
	FileManipulator::print("f1.txt", std::cout);


	std::cout << "\nThis tests partition with empty file\n";
	std::string fileName0 = "test_partition.txt";
	FileManipulator::fillRandomly(fileName0, 0);
	std::cout << "original file size & content: \n";
	std::cout << FileManipulator::partition(fileName0, ins) << "(size) \n";
	FileManipulator::print(fileName0, std::cout);
	std::cout << "\nf0: ";
	FileManipulator::print("f0.txt", std::cout);
	std::cout << "\nf1: ";
	FileManipulator::print("f1.txt", std::cout);


	std::cout << "\n\nThis tests partition with n=10 and 2 partitions\n";
	std::string fileName2 = "test_partition10_2.txt";
	FileManipulator::fillRandomly(fileName2, 10);
	std::cout << "original file size & content: \nsize: ";
	std::cout << FileManipulator::partition(fileName2, ins) << "\n";
	FileManipulator::print(fileName2, std::cout);
	std::cout << "\nf0: ";
	FileManipulator::print("f0.txt", std::cout);
	std::cout << "\nf1: ";
	FileManipulator::print("f1.txt", std::cout);

	std::cout << "\n\nThis tests partition with n=50 and 5 partitions\n";
	ins.push_back("f2.txt");
	ins.push_back("f3.txt");
	ins.push_back("f4.txt");
	std::string fileName3 = "test_partition100_5.txt";
	FileManipulator::fillRandomly(fileName3, 50);
	std::cout << "original file size & content: \nsize: ";
	std::cout << FileManipulator::partition(fileName3, ins) << "\n";
	FileManipulator::print(fileName3, std::cout);

	for (auto fileN : ins) {
		std::cout << "\n" << fileN << ": ";
		FileManipulator::print(fileN, std::cout);
	}
}

void testPrint() {
	std::cout << "\n\nThis tests print with file not found\n";
	std::string fileName0 = "test_print_where_dis.txt";
	FileManipulator::print(fileName0, std::cout);

	std::cout << "\n\nThis tests print with file n=0 \n";
	std::string fileName1 = "empty.txt";
	FileManipulator::print(fileName1, std::cout);

	std::cout << "\n\nThis tests print with file n=10 and cout\n";
	std::string fileName2 = "test_print_10.txt";
	FileManipulator::print(fileName2, std::cout);
}

void testCopy() {
	std::cout << "\n\nThis tests copy with file not found\n";
	std::string fileName0 = "test_copy_where_dis.txt";
	FileManipulator::copy(fileName0, "copy_not_found.txt");

	std::cout << "\n\nThis tests copy\n";
	std::string fileName1 = "f2.txt";
	FileManipulator::copy(fileName1, "f2_copy.txt");

}

void testFillRandomly() {
	std::cout << "\n\nThis tests fillRandomly with n = 0 \n";
	std::string fileName0 = "test_rand_0.txt";
	FileManipulator::fillRandomly(fileName0, 0);
	FileManipulator::print(fileName0, std::cout);

	std::cout << "\n\nThis tests fillRandomly with n = 10 \n";
	std::string fileName1 = "test_rand_10.txt";
	FileManipulator::fillRandomly(fileName1, 10);
	FileManipulator::print(fileName1, std::cout);

	std::cout << "\n\nThis tests fillRandomly with n = 100 \n";
	std::string fileName2 = "test_rand_0.txt";
	FileManipulator::fillRandomly(fileName2, 100);
	FileManipulator::print(fileName2, std::cout);
}

void testSortEmptyFile() {
	std::cout << "\n\nThis tests sort with n = 0 \n";
	std::string fileName = "empty.txt";
	MergeSort::sort(fileName);
}

void testSortFileNotFound() {
	std::cout << "\n\nThis tests sort with file not found \n";
	std::string fileName = "ghost.txt";
	MergeSort::sort(fileName);
}

void testSortFileSize1() {
	std::cout << "\n\nThis tests sort with n = 1 \n";
	std::string fileName = "test_sort_n1.txt";
	FileManipulator::fillRandomly(fileName, 1);
	FileManipulator::print(fileName, std::cout);
	std::cout << "\nsorted: \n";
	MergeSort::sort(fileName);
	FileManipulator::print(fileName, std::cout);
}

void testSortFileSize2() {
	std::cout << "\n\nThis tests sort with n = 2 \n";
	std::string fileName = "test_sort_n2.txt";
	FileManipulator::fillRandomly(fileName, 2);
	FileManipulator::print(fileName, std::cout);
	std::cout << "\nsorted: \n";
	MergeSort::sort(fileName);
	FileManipulator::print(fileName, std::cout);
}

void testSortFileSize10() {
	std::cout << "\n\nThis tests sort with n = 10 \n";
	std::string fileName = "test_sort_n10.txt";
	FileManipulator::fillRandomly(fileName, 10);
	FileManipulator::print(fileName, std::cout);
	std::cout << "\nsorted: \n";
	MergeSort::sort(fileName);
	FileManipulator::print(fileName, std::cout);

}

void testSortFileSize100() {
	std::cout << "\n\nThis tests sort with n = 100 \n";
	std::string fileName = "test_sort_n100.txt";
	FileManipulator::fillRandomly(fileName, 100);
	FileManipulator::print(fileName, std::cout);
	std::cout << "\nsorted: \n";
	MergeSort::sort(fileName);
	FileManipulator::print(fileName, std::cout);

}

void testAlreadySorted() {
	std::cout << "\n\nThis tests sort with sorted File \n";
	std::string fileName = "test_already_sorted.txt";
	//FileManipulator::fillRandomly(fileName, 17);
	FileManipulator::print(fileName, std::cout);
	std::cout << "\nsorted: \n";
	MergeSort::sort(fileName);
	FileManipulator::print(fileName, std::cout);
}