cmake_minimum_required(VERSION 3.23)
project(SWE_BAJIM_UE03)

set(CMAKE_CXX_STANDARD 20)

add_executable(SWE_BAJIM_UE03 main.cpp content/rational_t.cpp content/rational_t.h content/div_by_zero.h test/test_rational.cpp)
