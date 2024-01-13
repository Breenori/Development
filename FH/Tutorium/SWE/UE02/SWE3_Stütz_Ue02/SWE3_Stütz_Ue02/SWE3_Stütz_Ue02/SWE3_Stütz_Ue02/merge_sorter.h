#ifndef merge_sorter_h
#define merge_sorter_h

#include <string>
#include <vector>

class MergeSorter {
public:

	using value_t = std::string;
	using cont_t = std::vector<value_t>;

	value_t sort(value_t const& filename);
	//evtl. Name der Datei zurückgeben, in dem alle Daten stehen

private:

	//normal merge sort
	void sort(cont_t& v);
	void sort(cont_t& v, cont_t& aux, size_t lo, size_t hi);
	void merge(cont_t& v, cont_t& aux, size_t lo, size_t mid, size_t hi);

};


#endif // !merge_sorter_h