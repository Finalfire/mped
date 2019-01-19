cmake_minimum_required(VERSION 3.10)
project(MPED)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/)

# this is needed in order to use the angles include, e.g., #include <tclap/CmdLine.h>
#include_directories(${SOURCE_FILES}/include)

add_executable(MPED src/main.cpp src/Matrix.h src/Utility.h src/sequence/AbstractSequence.h src/sequence/SimpleSequence.h src/sequence/DelimitedSequence.h src/heuristic/EvolutionStrategy/EvolutionStrategy.h src/heuristic/Heuristic.h src/MPED.h src/metric/Metric.h src/heuristic/EvolutionStrategy/Individual.h src/heuristic/EvolutionStrategy/Mutator/Shuffle.h src/heuristic/EvolutionStrategy/Mutator/Swap2.h src/heuristic/EvolutionStrategy/Mutator/Swap2_E.h src/heuristic/EvolutionStrategy/Mutator/Swap3.h src/heuristic/EvolutionStrategy/Mutator/Scramble.h src/heuristic/EvolutionStrategy/Mutator/Inversion.h src/heuristic/EvolutionStrategy/Mutator/Translocation.h src/heuristic/EvolutionStrategy/Mutator/Swap2_Swap3.h src/Permutation.h src/heuristic/EvolutionStrategy/Mutator/Mutator.h src/heuristic/EvolutionStrategy/EvolutionStrategyThread.h src/heuristic/EvolutionStrategy/EvolutionStrategyThread2.h)