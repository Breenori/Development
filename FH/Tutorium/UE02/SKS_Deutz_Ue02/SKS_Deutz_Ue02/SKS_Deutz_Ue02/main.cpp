#include "test.h"
#include "external_merge_sort.h"

int main() {

	//TestCopyFile("fill_random_test.txt", "fill_random_test_copy.txt");
	ExternalMergeSort* merger = new ExternalMergeSort();
	merger->Sort("test.txt", 7);
}