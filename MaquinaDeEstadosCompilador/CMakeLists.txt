cmake_minimum_required(VERSION 3.5)
project(MaquinaDeEstadosCompilador)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp StateMachine.cpp StateMachine.h)
add_executable(MaquinaDeEstadosCompilador main.cpp ${SOURCE_FILES})
add_executable(MaquinaDeEstadosCompilador2 main.cpp ${SOURCE_FILES})
add_executable(la main.cpp ${SOURCE_FILES})