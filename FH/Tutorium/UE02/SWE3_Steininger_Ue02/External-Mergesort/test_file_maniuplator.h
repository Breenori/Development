//
// Created by Lukas Steininger on 03.11.22.
//

#ifndef EXTERNAL_MERGESORT_TEST_FILE_MANIUPLATOR_H
#define EXTERNAL_MERGESORT_TEST_FILE_MANIUPLATOR_H


class test_file_maniuplator {
public:
    static bool test_partitioning_of_file();
    static bool test_partitioning_of_file_empty();
    static bool test_partitioning_of_file_odd_elements();
    static bool test_filling_randomly();
    static bool test_filling_randomly_amount_and_length_of_elements();
    static bool test_copy_of_file();
    static bool test_copy_of_file_empty();
    static bool test_copy_container();
    static bool test_copy_container_empty();
    static bool test_print();
    static bool test_print_empty();
};


#endif //EXTERNAL_MERGESORT_TEST_FILE_MANIUPLATOR_H
