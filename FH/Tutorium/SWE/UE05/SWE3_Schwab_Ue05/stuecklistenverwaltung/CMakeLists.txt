cmake_minimum_required(VERSION 3.22)
project(stuecklistenverwaltung)

set(CMAKE_CXX_STANDARD 20)

add_executable(stuecklistenverwaltung main.cpp part.cpp part.h formatter.cpp formatter.h storable.h)
