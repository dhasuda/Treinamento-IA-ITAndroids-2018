cmake_minimum_required(VERSION 3.9)
project(PotentialField)

set(CMAKE_CXX_STANDARD 11)

add_executable(PotentialField main.cpp PotentialFieldPlanner.cpp PotentialFieldPlanner.h)