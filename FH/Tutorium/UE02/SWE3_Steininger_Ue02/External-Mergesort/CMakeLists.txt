cmake_minimum_required(VERSION 3.23)
project(External_Mergesort)

set(CMAKE_CXX_STANDARD 17)

add_executable(External_Mergesort main.cpp file_manipulator.cpp file_manipulator.h merge_sorter.cpp merge_sorter.h test_file_maniuplator.cpp test_file_maniuplator.h test_merge_sorter.cpp test_merge_sorter.h)
