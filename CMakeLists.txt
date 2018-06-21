cmake_minimum_required(VERSION 3.10)
project(MPED)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/)

add_executable(MPED src/main.cpp src/Utility.h src/Jaccard.h src/HillClimbing.h src/AbstractSequence.h src/SimpleSequence.h src/DelimitedSequence.h)