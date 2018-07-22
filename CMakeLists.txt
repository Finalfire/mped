cmake_minimum_required(VERSION 3.10)
project(MPED)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/)

# this is needed in order to use the angles include, e.g., #include <tclap/CmdLine.h>
#include_directories(${SOURCE_FILES}/include)

add_executable(MPED src/main.cpp src/Utility.h src/Jaccard.h src/HillClimbing.h src/AbstractSequence.h src/SimpleSequence.h src/DelimitedSequence.h src/ES_MatchingSchema.h src/Metric.h src/NLP/NLPMatchingSchema.h src/NLP/SparseDictionary.h src/EvaluationFunctions.h)