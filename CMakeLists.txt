cmake_minimum_required(VERSION 3.10)

project(benchmarks VERSION 1.0)

add_executable(dijkstra-benchmarks main.cpp)

target_include_directories(dijkstra-benchmarks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(dijkstra-benchmarks PRIVATE cxx_std_20)