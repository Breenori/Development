#include "merge_sort.h"
#include "file_manipulator.h"
#include <iostream>


void MergeSort::sort(cont_t& v) {
	cont_t aux( v.size() );
	sort(v, aux,0, v.size() - 1);
}

void MergeSort::sort(cont_t& v, cont_t& aux, index_t lo, index_t hi) {
	if (hi <= lo) {
		return;
	}

	index_t mid{ lo + (hi - lo) / 2 };
	sort(v, aux, lo, mid);
	sort(v, aux, mid + 1, hi);
	merge(v, aux, lo, mid, hi);
}

void MergeSort::merge(cont_t& v, cont_t& aux, index_t lo, index_t mid, index_t hi) {
	index_t i{ lo }; //index linker Teil
	index_t j{ mid + 1 }; //index rechter Teil

	for (index_t k{ lo }; k <= hi; ++k) {
		aux[k] = v[k];
	}

	for (index_t k{ lo }; k <= hi; ++k) {
		if (i > mid) {
			v[k] = aux[j++]; //take from right part, if left part is ended (less members in left part)
		}
		else if (j > hi) {
			v[k] = aux[i++]; //take from left part, if right part is ended

		}
		else if (aux[j] < aux[i]) {
			v[k] = aux[j++];
		}
		else {
			v[k] = aux[i++];
		}
	}

}

void MergeSort::sort_file(std::string const& filename, std::vector<std::string>& dst )
{
	fileManipulator::partition(filename,  dst);

	for (size_t i{ 0 }; i < dst.size(); ++i)
	{
		std::string tmp_file = "tmp_" + dst[i];
		std::vector<int>v_tmp{ fileManipulator::read(dst[i]) };

		MergeSort ms;
		ms.sort(v_tmp);
		fileManipulator::write(v_tmp, tmp_file);
	}
	fileManipulator::re_partition(dst[0], dst[1], "sorted_file.txt");

}