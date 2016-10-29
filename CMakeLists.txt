cmake_minimum_required(VERSION 3.6)
project(TKOM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Source.cpp Source.h Scanner.cpp Scanner.h Atoms.h)
add_executable(TKOM ${SOURCE_FILES})