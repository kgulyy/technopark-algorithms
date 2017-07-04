cmake_minimum_required(VERSION 3.7)
project(1_1_task_3_mod)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp StringSet.cpp StringSet.h)
add_executable(1_1_task_3_mod ${SOURCE_FILES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)