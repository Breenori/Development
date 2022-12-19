#ifndef TEST_H
#define TEST_H

#include "external_merge_sort.h"

void TestFillRandom(int const AmountValues, int const ValueMin, int const ValueMax);
void TestSplitFile(FileManipulator::FileName const FileName, std::vector<FileManipulator::FileName> SplittetFileNames);
void TestCopyFile(FileManipulator::FileName const& Source, FileManipulator::FileName const& Destination);
std::ostream& TestWriteRead(FileManipulator::FileName const& Source, std::ostream& OutStream);

#endif