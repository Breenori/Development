cmake_minimum_required(VERSION 3.19)
project(011_arithmetic_parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(011_arithmetic_parser main.cpp arithmetic_parser.h pfc_scanner.h arithmetic_parser.cpp)
