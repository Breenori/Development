#ifndef mergeSort_h
#define mergeSort_h

#include <vector>
#include <string>

class MergeSort {
public:

	using cont_t = std::vector<std::string>;			//typedef std::vector<int> con_t;
	using index_t = std::size_t;
	static void sort(std::string const& src);

private:
	//merge and print
	static void merge(int s, int k, cont_t* const& ins, std::string const& out);

};


#endif
