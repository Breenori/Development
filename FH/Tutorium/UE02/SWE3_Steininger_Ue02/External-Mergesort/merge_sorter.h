//
// Created by Lukas Steininger on 24.10.22.
//

#ifndef EXTERNAL_MERGESORT_MERGE_SORTER_H
#define EXTERNAL_MERGESORT_MERGE_SORTER_H

#include <string>
#include "file_manipulator.h"

class merge_sorter {
public:
    using index_t = std::size_t;
    using value_t = std::string;
    using cont_t = std::vector<std::string>;
    //sort the given file with merge sort
    value_t sort(value_t const &  path);
private:
    //process the elements according to the order of the run
    //source file, destination files, order of run, flag for done
    void do_run(cont_t const& src, cont_t const& dst, std::size_t k, bool &done);
    //read n elements from the files alternating
    //file 1 to read from, file 2 to read from, start index for merging, middle index for merging, end index for merging, order of run
    void read_elements(std::ifstream* file1, std::ifstream* file2, cont_t& cont, size_t& cnt_lo, size_t& cnt_mid, size_t& cnt_hi, size_t const k);
    //merge a given interval in v so that it is in order
    //container to sort, auxiliary container same size as v, start index for merging, middle index for merging, end index for merging
    void merge(cont_t &v,cont_t &aux, index_t lo, index_t mid, index_t hi);
};


#endif //EXTERNAL_MERGESORT_MERGE_SORTER_H
