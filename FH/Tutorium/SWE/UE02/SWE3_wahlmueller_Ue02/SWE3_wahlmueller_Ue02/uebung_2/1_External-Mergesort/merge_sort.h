#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include<iostream>
#include<iomanip>

#include<vector>
#include "file_manipulator.h"

using std::vector;

class merge_sort{
	
public:
	//c++11
	using index_t = size_t;
	using cont_t = vector<int>;

	void sort(cont_t& vec);

private:
	void sort_rec(cont_t& vec, cont_t& vec_copy, index_t start, index_t end);

	void merge(cont_t& vec, cont_t& vec_copy, index_t start, index_t middle, index_t end);

};

#endif