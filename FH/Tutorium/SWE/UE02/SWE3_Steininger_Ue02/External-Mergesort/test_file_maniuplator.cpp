//
// Created by Lukas Steininger on 03.11.22.
//

#include "test_file_maniuplator.h"
#include "file_manipulator.h"
#include <iostream>
using std::cout;

bool test_file_maniuplator::test_partitioning_of_file() {
    cout << "Test: partitioning a file with an even number of elements:\n";
    file_manipulator::cont_t files = {"../test_files/file_manipulator/partitioning/partition_me_1.txt", "../test_files/file_manipulator/partitioning/partition_me_2.txt"};
    file_manipulator::partition("../test_files/file_manipulator/partitioning/partition_me.txt",files);

    std::cout <<"Original file:\n";
    file_manipulator::print("../test_files/file_manipulator/partitioning/partition_me.txt");

    std::cout <<"Partitioned files:\n";
    file_manipulator::print(files[0]);
    file_manipulator::print(files[1]);

    file_manipulator::cont_t sol_1 = {"ab","ef","ij","mn"};
    file_manipulator::cont_t sol_2 = {"cd","gh","kl","op"};

    std::ifstream in_1 {files[0]};
    std::ifstream in_2 {files[1]};

    bool is_correct = true;
    file_manipulator::value_t value;
    size_t cnt = 0;
    while (in_1 >> value && is_correct){
        if (value != sol_1[cnt]){
            is_correct = false;
        }
        else {
            ++cnt;
        }
    }
    cnt = 0;
    while (in_2 >> value && is_correct){
        if (value != sol_2[cnt]){
            is_correct = false;
        }
        else {
            ++cnt;
        }
    }
    return is_correct;
}

bool test_file_maniuplator::test_partitioning_of_file_empty() {
    cout << "Test: partitioning an empty file:\n";
    file_manipulator::cont_t files = {"../test_files/file_manipulator/partitioning/empty_file_1.txt", "../test_files/file_manipulator/partitioning/empty_file_2.txt"};
    file_manipulator::partition("../test_files/file_manipulator/partitioning/empty_file.txt",files);

    std::cout <<"Original file:\n";
    file_manipulator::print("../test_files/file_manipulator/partitioning/empty_file.txt");

    std::cout <<"Partitioned files:\n";
    file_manipulator::print(files[0]);
    file_manipulator::print(files[1]);

    std::ifstream in_1 {files[0]};
    std::ifstream in_2 {files[1]};

    bool is_correct = true;
    file_manipulator::value_t value;
    size_t cnt = 0;
    while (in_1 >> value && is_correct){
            ++cnt;
    }
    while (in_2 >> value && is_correct){
            ++cnt;
    }
    return cnt==0;

}

bool test_file_maniuplator::test_partitioning_of_file_odd_elements() {
    cout << "Test: partitioning a file with an odd amount of elements:\n";
    file_manipulator::cont_t files = {"../test_files/file_manipulator/partitioning/partition_me_1.txt", "../test_files/file_manipulator/partitioning/partition_me_2.txt"};
    file_manipulator::partition("../test_files/file_manipulator/partitioning/partition_me_odd.txt",files);

    std::cout <<"Original file:\n";
    file_manipulator::print("../test_files/file_manipulator/partitioning/partition_me_odd.txt");

    std::cout <<"Partitioned files:\n";
    file_manipulator::print(files[0]);
    file_manipulator::print(files[1]);

    file_manipulator::cont_t sol_1 = {"ab","ef","ij","mn","qr"};
    file_manipulator::cont_t sol_2 = {"cd","gh","kl","op"};

    std::ifstream in_1 {files[0]};
    std::ifstream in_2 {files[1]};

    bool is_correct = true;
    file_manipulator::value_t value;
    size_t cnt = 0;
    while (in_1 >> value && is_correct){
        if (value != sol_1[cnt]){
            is_correct = false;
        }
        else {
            ++cnt;
        }
    }
    cnt = 0;
    while (in_2 >> value && is_correct){
        if (value != sol_2[cnt]){
            is_correct = false;
        }
        else {
            ++cnt;
        }
    }
    return is_correct;
}

bool test_file_maniuplator::test_filling_randomly() {
    std::cout<<"Test: filling a file randomly with 10 elements of length=1 (standard):\n";
    size_t elem_cnt = 10;
    size_t elem_length = 1;
    file_manipulator::value_t path = "../test_files/file_manipulator/filling_randomly/random_file_standard.txt";
    file_manipulator::fill_randomly(path);

    std::cout <<"Filled file:\n";
    file_manipulator::print(path);

    std::ifstream in{path};
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

bool test_file_maniuplator::test_filling_randomly_amount_and_length_of_elements() {
    size_t elem_cnt = 31;
    size_t elem_length = 4;
    std::cout<<"Test: filling a file randomly with "+std::to_string(elem_cnt)+" elements of length="+std::to_string(elem_length)+":\n";

    file_manipulator::value_t path = "../test_files/file_manipulator/filling_randomly/random_file_"+std::to_string(elem_cnt)+"_"+std::to_string(elem_length)+".txt";
    file_manipulator::fill_randomly(path, elem_cnt,elem_length);

    std::cout <<"Filled file:\n";
    file_manipulator::print(path);

    std::ifstream in{path};
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

bool test_file_maniuplator::test_copy_of_file() {
    std::cout<<"Test: copying the content of a file to another file:\n";
    file_manipulator::value_t src = "../test_files/file_manipulator/copy/file_to_copy.txt";
    file_manipulator::value_t dst = "../test_files/file_manipulator/copy/copy_of_file_to_copy.txt";
    file_manipulator::copy(src,dst );

    std::cout <<"Source file:\n";
    file_manipulator::print(src);

    std::cout <<"Copied file:\n";
    file_manipulator::print(dst);

    std::ifstream in_1{src};
    std::ifstream in_2{dst};

    bool is_correct = true;
    file_manipulator::value_t value1;
    file_manipulator::value_t value2;

    while (in_1>>value1 && in_2>>value2 && is_correct){
        if (value1 != value2){
            is_correct=false;
        }
    }

    return is_correct;
}

bool test_file_maniuplator::test_copy_of_file_empty() {
    std::cout<<"Test: copying the content of an empty file to another file:\n";
    file_manipulator::value_t src = "../test_files/file_manipulator/copy/empty_file.txt";
    file_manipulator::value_t dst = "../test_files/file_manipulator/copy/copy_of_empty_file.txt";
    file_manipulator::copy(src,dst );

    std::cout <<"Source files:\n";
    file_manipulator::print(src);

    std::cout <<"Copied file:\n";
    file_manipulator::print(dst);

    std::ifstream in_1{src};
    std::ifstream in_2{dst};

    bool is_correct = true;
    file_manipulator::value_t value1;
    size_t cnt = 0;

    while (in_1>>value1){
        ++cnt;
    }

    while (in_2>>value1){
        ++cnt;
    }

    return cnt==0;
}

bool test_file_maniuplator::test_copy_container() {
    std::cout<<"Test: copying the content of a container to a file:\n";
    file_manipulator::cont_t src = {"this", "is", "the", "content", "of", "the", "container"};
    file_manipulator::value_t dst = "../test_files/file_manipulator/copy_container/copy_of_container.txt";
    file_manipulator::copy(src,dst );

    std::cout <<"Copied file:\n";
    file_manipulator::print(dst);


    std::ifstream in_2{dst};

    bool is_correct = true;
    file_manipulator::value_t value2;
    size_t cnt = 0;

    while (in_2>>value2 && is_correct){
        if (value2 != src[cnt]){
            is_correct=false;
        }
        else{
            ++cnt;
        }
    }

    return is_correct;
}

bool test_file_maniuplator::test_copy_container_empty() {
    std::cout<<"Test: copying the content of an empty container to a file:\n";
    file_manipulator::cont_t src = {};
    file_manipulator::value_t dst = "../test_files/file_manipulator/copy_container/copy_of_empty_container.txt";
    file_manipulator::copy(src,dst );

    std::cout <<"Copied file:\n";
    file_manipulator::print(dst);

    std::ifstream in_2{dst};

    bool is_correct = true;
    file_manipulator::value_t value2;
    size_t cnt = 0;

    while (in_2>>value2 && is_correct){
        ++cnt;
    }

    return cnt==0;
}

bool test_file_maniuplator::test_print() {
    std::cout<<"Test: printing the contents of a file:\n";
    file_manipulator::value_t src = "../test_files/file_manipulator/print/file_to_print.txt";
    file_manipulator::print(src );

    std::ifstream in_2{src};

    return true;
}

bool test_file_maniuplator::test_print_empty() {
    std::cout<<"Test: printing the contents of an empty file:\n";
    file_manipulator::value_t src = "../test_files/file_manipulator/print/empty_file_to_print.txt";
    file_manipulator::print(src );

    std::ifstream in_2{src};

    return true;
}

