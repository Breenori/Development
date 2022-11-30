//#include "merge_sort.h"
//#include "file_manipulator.h"
//#include <iostream>
//
//using std::cout;
//
//
//
//int testing()
//{
//	std::string file = "random_file_int.txt";
//
//	//genereating files
//	cout << "\nGenerating 10 random integers(<= 10), writing them into a file...\n";
//	fileManipulator::fill_randomly_int(file, 10, 10);
//	cout << "Printing generated elements:\n";
//	fileManipulator::print(file);
//
//
//	cout << "\n\nGenerating 20 random strings(no of letters 3), writing them into a file...\n";
//	fileManipulator::fill_randomly_str("random_file_str.txt", 20, 3);
//	cout << "Printing generated elements:\n";
//	fileManipulator::print("random_file_str.txt");
//
//	//Partitioning
//	cout << "\n\nPartitioning File in smaller files (f0 & f1)...\n";
//	std::vector<std::string> dst{ "f0.txt", "f1.txt" };
//	fileManipulator::partition(file, dst);
//	cout << "large file:\n";
//	fileManipulator::print(file);
//	cout << "\nFile 0:\n";
//	fileManipulator::print("f0.txt");
//	cout << "\nFile 1:\n";
//	fileManipulator::print("f1.txt");
//
//	//Sorting
//	cout << "\n\nSorting a vector containing integers using Merge Sort...\n";
//	std::vector<int> v = fileManipulator::read("f0.txt");
//	cout << "Vector to sort:\n";
//	fileManipulator::print("f0.txt");
//	MergeSort ms;
//	ms.sort(v);
//	cout << "\nSorted vector:\n";
//	for (size_t i : v)
//	{
//		cout << i << ' ';
//	}
//
//	cout << "\n\nWriting a vector to a file and printing it";
//	cout << "\nVector:\n";
//	for (size_t i : v)
//	{
//		cout << i << ' ';
//	}
//	cout << "\nFile content:\n";
//	fileManipulator::write(v, "savedFile.txt");
//	fileManipulator::print("savedFile.txt");
//
//	//Using external Merge Sort
//	cout << "\n\nSorting the large generated File using partitioning and Merge Sort...\n";
//	cout << "File to sort:\n";
//	fileManipulator::print(file);
//	ms.sort_file(file, dst);
//	cout << "\nSorted file:\n";
//	fileManipulator::print("sorted_file.txt");
//
//
//	return 0;
//}
//
