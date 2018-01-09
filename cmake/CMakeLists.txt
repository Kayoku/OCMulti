cmake_minimum_required(VERSION 2.6)

project (OCMulti)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
set (CMAKE_CXX_FLAGS "-O2")

include_directories(
    ../
)

add_executable(tsp
    ../tsp_main.cpp
    ../TSP.cpp
    ../TSP_Random.cpp
    ../TSP_Scalar.cpp
    ../TSP_GenPareto.cpp
    ../TSP_GreedyPareto.cpp
    ../Instance.cpp
)

add_executable(test
    ../test.cpp
)
