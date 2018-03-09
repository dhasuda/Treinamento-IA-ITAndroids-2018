cmake_minimum_required(VERSION 3.6)
project(Genetic_Algorithm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Population.cpp Population.h Individual.cpp Individual.h Algorithm.cpp Algorithm.h)
add_executable(Genetic_Algorithm ${SOURCE_FILES})