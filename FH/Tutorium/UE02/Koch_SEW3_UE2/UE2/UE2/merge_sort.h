#ifndef merge_sort_h
#define merge_sort_h
#include "file_manipulator.h"
#include <vector>



class MergeSort {

public:

	//typedef std::vector<int> cont_t;
	using cont_t = std::vector<int>;
	using index_t = std::size_t;

	static void sort_file(std::string const& filename, std::vector<std::string>& dst);
	void sort(cont_t& v);


private:

	void sort(cont_t& v, cont_t& aux, index_t lo, index_t hi); //lo = start, hi = ende des arrays

	void merge(cont_t& v, cont_t& aux, index_t lo, index_t mid, index_t hi); //mid= bruch der Teilarrays


};
#endif // !merge_sort_h
