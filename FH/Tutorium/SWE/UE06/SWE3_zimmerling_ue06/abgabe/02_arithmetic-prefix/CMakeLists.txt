cmake_minimum_required(VERSION 3.19)
project(02_arithmetic_prefix)

set(CMAKE_CXX_STANDARD 20)

add_executable(02_arithmetic_prefix main.cpp ArithmeticParserPrefix.cpp ArithmeticParserPrefix.h pfc_scanner.h)