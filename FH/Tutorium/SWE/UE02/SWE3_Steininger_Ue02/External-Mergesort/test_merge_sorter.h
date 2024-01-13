//
// Created by Lukas Steininger on 03.11.22.
//

#ifndef EXTERNAL_MERGESORT_TEST_MERGE_SORTER_H
#define EXTERNAL_MERGESORT_TEST_MERGE_SORTER_H

#include "merge_sorter.h"

class test_merge_sorter {
public:
    static bool test_sort_unsorted();
    static bool test_sort_sorted();
    static bool test_sort_random();
    static bool test_sort_random_long_strings();
    static bool test_sort_empty();
};


#endif //EXTERNAL_MERGESORT_TEST_MERGE_SORTER_H
