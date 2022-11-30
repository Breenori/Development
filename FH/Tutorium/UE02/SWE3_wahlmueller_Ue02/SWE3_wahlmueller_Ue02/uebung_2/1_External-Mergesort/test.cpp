#include "test.h"

using std::cout;

//not needed for task
void test_megre_sort() {

	merge_sort ms;

	merge_sort::cont_t data = { 19, 29, 1, 6, 345, 2, 13 };

	ms.sort(data);

	for (int element : data) {

		cout << element << " ";

	}

	cout << "\n";

}

//tests for task
//random file + seperation
void test_1() {

	file_manipulator::cont_t out{ "f0.txt", "f1.txt" };
	file_manipulator::fill_randomly("file_to_sort.txt", 100, 3);
	file_manipulator::fill_randomly("file_to_sort_2.txt");//do not open with editor

	file_manipulator::partition("file_to_sort.txt", out);

}

//test of okay file
void test_2() {

	merge_sorter::sort("test.txt");

}

//test of empty file
void test_3() {

	merge_sorter::sort("empty.txt");

}

//letters
void test_4() {

	merge_sorter::sort("letters.txt");

}

//already sorted - should have no effect
void test_5(){

	merge_sorter::sort("after_1.txt");

}

//bigger data
void test_6(){

	merge_sorter::sort("big.txt");

}