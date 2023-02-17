cmake_minimum_required(VERSION 3.19)
project(03_arithmetic_variables)

set(CMAKE_CXX_STANDARD 20)

add_executable(03_arithmetic_variables main.cpp arithmeticVariableParser.cpp arithmeticVariableParser.h pfc_scanner.h)