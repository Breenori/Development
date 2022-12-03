//
// Created by Lukas Steininger on 03.11.22.
//

#include "test_merge_sorter.h"
#include <vector>
#include <iostream>
using std::cout;


 bool test_merge_sorter::test_sort_unsorted() {
    cout << "Test: sorting an unsorted file, of which the solution is known:\n";
    merge_sorter ms;
    merge_sorter::value_t result_path = ms.sort("../../test_files/merge_sorter/unsorted.txt");
    std::vector<merge_sorter::value_t> solution = {"a","b","c", "d", "e","f","g","h","i","j"};
    std::ifstream in{result_path};
    bool is_correct = true;
    merge_sorter::value_t value;
    size_t cnt =0;
    while(in >> value && is_correct){
        if (value != solution[cnt]){
            is_correct = false;
        }
        else {
            ++cnt;
        }
    }
    return is_correct;
}

bool test_merge_sorter::test_sort_sorted() {
    cout << "Test: sorting a sorted.txt file. Sorting should not change the outcome:\n";
    merge_sorter ms;
    merge_sorter::value_t result_path = ms.sort("test_files/merge_sorter/sorted.txt");
    std::vector<merge_sorter::value_t> solution = {"a","b","c", "d", "e","f","g","h","i","j", "k", "l"};
    std::ifstream in{result_path};
    bool is_correct = true;
    merge_sorter::value_t value;
    size_t cnt =0;
    while(in >> value && is_correct){
        if (value != solution[cnt]){
            is_correct = false;
        }
        else {
            ++cnt;
        }
    }
    return is_correct;
}

bool test_merge_sorter::test_sort_random() {
    size_t elem_length = 1;
    size_t elem_cnt = 10;

    cout << "Test: sorting a randomly filled file (10 elements of length=1 ):\n";
    merge_sorter ms;
    merge_sorter::value_t path = "../test_files/merge_sorter/random_filled_1.txt";
    file_manipulator::fill_randomly(path);
    merge_sorter::value_t result_path = ms.sort(path);

    std::ifstream in{result_path};
    bool is_correct = true;
    file_manipulator::value_t value;
    size_t cnt = 0;

    while(in >> value && is_correct){
        if (value.size()!=elem_length){
            is_correct=false;
        }
        else{
            ++cnt;
        }
    }
    return cnt==elem_cnt && is_correct;
}

bool test_merge_sorter::test_sort_random_long_strings() {
     size_t elem_length = 3;
     size_t elem_cnt = 111;
    cout << "Test: sorting a randomly filled file (111 elements of length=3 ):\n";
    merge_sorter ms;
    merge_sorter::value_t path = "../test_files/merge_sorter/random_filled_2.txt";
    file_manipulator::fill_randomly(path,elem_cnt,elem_length);
    merge_sorter::value_t result_path = ms.sort(path);


    std::ifstream in{result_path};
    bool is_correct = true;
    file_manipulator::value_t value;
    size_t cnt = 0;

    while(in >> value && is_correct){
        if (value.size()!=elem_length){
            is_correct=false;
        }
        else{
            ++cnt;
        }
    }
    return cnt==elem_cnt && is_correct;

}

bool test_merge_sorter::test_sort_empty() {
    cout << "Test: sorting an empty file:\n";
    merge_sorter ms;
    merge_sorter::value_t result_path = ms.sort("../test_files/merge_sorter/empty_file.txt");
    std::ifstream in{result_path};
    bool is_correct = true;
    merge_sorter::value_t value;
    size_t cnt =0;
    while(in >> value && is_correct){
        ++cnt;
    }
    return cnt==0;

}
