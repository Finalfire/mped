cmake_minimum_required(VERSION 3.12)
project(MPED)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)
include_directories(src/NLP)
include_directories(src/weighted-matching)

add_executable(MPED
        src/NLP/MegaSigma.h
        src/NLP/NLPMatchingSchema.h
        src/NLP/NLPMatchingSchemaFixed.h
        src/NLP/SparseDictionary.h
        "src/(mu+lambda)-ES.h"
        src/sequence/AbstractSequence.h
        src/sequence/DelimitedSequence.h
        src/ES_MatchingSchema.h
        src/EvaluationFunctions.h
        src/Jaro.h
        src/main.cpp
        src/MatchingSchema.h
        src/utility/Matrix.h
        src/sequence/SimpleSequence.h
        src/utility/Utility.h)
