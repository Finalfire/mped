cmake_minimum_required(VERSION 3.10)
project(MPED)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/)

# this is needed in order to use the angles include, e.g., #include <tclap/CmdLine.h>
#include_directories(${SOURCE_FILES}/include)

add_executable(MPED src/main.cpp src/Matrix.h src/Utility.h src/sequence/AbstractSequence.h src/sequence/SimpleSequence.h src/sequence/DelimitedSequence.h)