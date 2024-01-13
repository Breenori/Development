#include "merge_sort.h"

void merge_sort::sort(cont_t& vec){

	cont_t vec_copy( vec.size() );

	sort_rec(vec, vec_copy, 0, vec.size() - 1);

}

void merge_sort::sort_rec(cont_t& vec, cont_t& vec_copy, index_t start, index_t end){

	if (end <= start) {//rec bottom

		return;

	}

	index_t middle{ start + (end - start) / 2 };

	sort_rec(vec, vec_copy, start, middle);//decent left
	sort_rec(vec, vec_copy, middle+1, end);//right decent

	merge(vec, vec_copy, start, middle, end);//merge & sort

}

void merge_sort::merge(cont_t& vec, cont_t& vec_copy, index_t start, index_t middle, index_t end){

	index_t i{ start };
	index_t j{ middle+1 };

	for (index_t k = start; k <= end; k++){

		vec_copy[k] = vec[k];//copy from original vector

	}

	for (index_t k = start; k <= end; k++){

		if (i > middle) {

			vec[k] = vec_copy[j++];//elem. from j are sorted

		}

		else if(j > end){

			vec[k] = vec_copy[i++];//i++ otherwise wrong pos.

		}

		else if (vec[j] < vec_copy[i]) {

			vec[k] = vec_copy[j++];

		}

		else{

			vec[k] = vec_copy[i++];

		}

	}

}