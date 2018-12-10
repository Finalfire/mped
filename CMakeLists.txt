cmake_minimum_required(VERSION 3.10)
project(MPED)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/)

# this is needed in order to use the angles include, e.g., #include <tclap/CmdLine.h>
#include_directories(${SOURCE_FILES}/include)

add_executable(MPED src/main.cpp src/Matrix.h src/Utility.h src/sequence/AbstractSequence.h src/sequence/SimpleSequence.h src/sequence/DelimitedSequence.h src/heuristic/EvolutionStrategy.h src/heuristic/Heuristic.h src/MPED.h src/metric/Metric.h src/heuristic/individual/Individual.h src/heuristic/individual/Shuffle.h src/heuristic/individual/Swap2.h src/heuristic/individual/Swap2_E.h src/heuristic/individual/Swap3.h src/heuristic/individual/Scramble.h src/heuristic/individual/Inversion.h src/heuristic/individual/Translocation.h src/heuristic/individual/Swap2_Swap3.h)