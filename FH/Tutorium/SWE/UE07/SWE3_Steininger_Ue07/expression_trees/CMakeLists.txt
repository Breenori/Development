cmake_minimum_required(VERSION 3.23)
project(expression_trees)

set(CMAKE_CXX_STANDARD 20)

add_executable(expression_trees main.cpp test_parse_syntax_tree.cpp test_parse_syntax_tree.h)
