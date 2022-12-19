cmake_minimum_required(VERSION 3.20)
project(01_rational)

set(CMAKE_CXX_STANDARD 14)

add_executable(01_rational main.cpp rationalType.cpp rationalType.h testRationalType.cpp testRationalType.h DivByZeroException.h InvalidRationalException.h)
