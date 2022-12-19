#ifndef EXTERNAL_MERGE_SORT_H
#define EXTERNAL_MERGE_SORT_H

#include "file_manipulator.h"

int const INSTREAMF0 = 0;
int const INSTREAMF1 = 1;
int const INSTREAMG0 = 2;
int const INSTREAMG1 = 3;

int const OUTSTREAMF0 = 0;
int const OUTSTREAMF1 = 1;
int const OUTSTREAMG0 = 2;
int const OUTSTREAMG1 = 3;

class ExternalMergeSort {
public:
	typedef std::vector<FileManipulator::ValueType> ContainerType;

	void Sort(std::string const& FileToSort, size_t const NumValues);

private:
	static void Merge(ContainerType& FirstContainer, ContainerType& SecondContainer, ContainerType& MergedContainer);

};

#endif