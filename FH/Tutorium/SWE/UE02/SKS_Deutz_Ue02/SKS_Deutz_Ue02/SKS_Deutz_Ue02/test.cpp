#include "test.h"

void TestFillRandom(int const AmountValues, int const ValueMin, int const ValueMax){

	FileManipulator TestManipulator;

	TestManipulator.FillRandomly("fill_random_test.txt", AmountValues, ValueMin, ValueMax);

}

void TestSplitFile(FileManipulator::FileName const FileName, std::vector<FileManipulator::FileName> SplittetFileNames){

	FileManipulator TestManipulator;

	TestManipulator.FillRandomly(FileName, 10, 0, 10);

	TestManipulator.SplitFile(FileName, SplittetFileNames);

}

void TestCopyFile(FileManipulator::FileName const& Source, FileManipulator::FileName const& Destination){

	FileManipulator TestManipulator;

	TestManipulator.CopyFile(Source, Destination);

}
