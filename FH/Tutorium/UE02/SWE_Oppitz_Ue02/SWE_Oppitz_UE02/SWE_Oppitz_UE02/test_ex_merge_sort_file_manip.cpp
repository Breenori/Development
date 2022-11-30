#include "test_ex_merge_sort_file_manip.h"


void test_file_manip_print() {
	file_manipulator::print("test.txt");
}


void test_file_manip_fill_randomly() {
	//test case 1
	std::cout << "test case fill_randomly 1" << " (file_manipulator), " << " Parameter: " << "test_fill_randomly_1.txt" << ", 100, 3";
	file_manipulator::fill_randomly("test_fill_randomly_1.txt", 100, 3);
	std::cout << "\nrandom File: ";
	file_manipulator::print("test_fill_randomly_1.txt");
	std::cout << "\n";
	//------------------------------------------------------------------
	//test case 2
	std::cout << "test case fill_randomly 2" << " (file_manipulator), " << " Parameter: " << "test_fill_randomly_2.txt" << ", 10, 2";
	//test case fill_randomly 2 (file_manipulator), Parameter: "test_fill_randomly_2.txt", 10, 2
	file_manipulator::fill_randomly("test_fill_randomly_2.txt", 10, 2);
	std::cout << "\nrandom File: ";
	file_manipulator::print("test_fill_randomly_2.txt");
	std::cout << "\n";
}


void test_file_manip_copy() {
	//test case 1
	std::cout << "test case copy (\"test_007.txt\"): \n";
	std::cout << "file to copy: ";
	file_manipulator::print("test_007.txt");
	std::cout << "copy: ";
	file_manipulator::copy("test_007.txt", "test_007_copy.txt");

	std::cout << "\n";


}


void test_sort() {
	//test case 1
	std::cout << "test case sort 1 (\"test_007.txt\"): \n" << "File to sort : " ;
	file_manipulator::print("test_007.txt");
	merge_sorter::sort("test_007.txt");
	std::cout << "Sorted File: ";
	file_manipulator::print("g0.txt");

	std::cout << "\n";

	//----------------------------------------
	//test case 2
	std::cout << "test case sort 2 (\"not_existing_file.txt\"): \n" << "File to sort : ";
	file_manipulator::print("not_existing_file.txt");
	merge_sorter::sort("not_existing_file.txt");
	std::cout << "\n";
	std::cout << "\n";

	//----------------------------------------
	//test case 3
	std::cout << "test case sort 3 (\"file_is_empty.txt\"): \n" << "File to sort : ";
	file_manipulator::print("file_is_empty.tx.txt");
	merge_sorter::sort("file_is_empty.tx.txt");
	std::cout << "\n";

	//----------------------------------------
	//test case 4
	std::cout << "test case sort 4, gerade Zahl an Woertern (\"random_file.txt\"): \n" << "File to sort : ";
	file_manipulator::fill_randomly("random_file.txt", 100, 3);
	file_manipulator::print("random_file.txt");
	merge_sorter::sort("random_file.txt");
	std::cout << "\nSorted File: ";
	file_manipulator::print("g0.txt");
	std::cout << "\n";

	//----------------------------------------
//test case 5
	std::cout << "test case sort 5, ungerade Anzahl an Woertern (\"random_file_2.txt\"): \n" << "File to sort : ";
	file_manipulator::fill_randomly("random_file_2.txt", 101, 3);
	file_manipulator::print("random_file_2.txt");
	merge_sorter::sort("random_file_2.txt");
	std::cout << "\nSorted File: ";
	file_manipulator::print("g0.txt");
	std::cout << "\n";

	//----------------------------------------

	//test case 6
	std::cout << "test case sort 6, negative Zahlen und doppelte Zahlen (\"negativ.txt\"): \n" << "File to sort : ";
	file_manipulator::print("negativ.txt");
	merge_sorter::sort("negativ.txt");
	std::cout << "\nSorted File: ";
	file_manipulator::print("g0.txt");
	std::cout << "\n";
}
