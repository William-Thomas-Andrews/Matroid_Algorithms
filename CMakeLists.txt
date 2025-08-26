cmake_minimum_required(VERSION 4.1.0)

project(MATROID)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(MATROID test/Test.cpp)

target_include_directories(MATROID
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PUBLIC ${CMAKE_SOURCE_DIR}/src/bipartite_graph
    PUBLIC ${CMAKE_SOURCE_DIR}/src/graph
    PUBLIC ${CMAKE_SOURCE_DIR}/src/partition
    PUBLIC ${CMAKE_SOURCE_DIR}/src/utils
    PUBLIC ${CMAKE_SOURCE_DIR}/src/vector_space
    PUBLIC ${CMAKE_SOURCE_DIR}/test
)