#include "FileManipulator.h"
#include "mergeSort.h"
#include "tests.h"

int main() {
	testPartition();
	testPrint();
	testCopy();
	testFillRandomly();

	testSortEmptyFile();
	testSortFileNotFound();
	testSortFileSize1();

	testSortFileSize2();
	testSortFileSize10();
	testSortFileSize100();
	testAlreadySorted();
	return 0;
}