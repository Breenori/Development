cmake_minimum_required(VERSION 3.22)
project(flugreisen)

set(CMAKE_CXX_STANDARD 20)

add_executable(flugreisen main.cpp person.cpp person.h flight.cpp flight.h flight_trip.cpp flight_trip.h)
