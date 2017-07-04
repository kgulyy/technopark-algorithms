cmake_minimum_required(VERSION 3.6)
project(2_2_task_mod_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MinHeap.h MinHeap.cpp)
add_executable(2_2_task_mod_2 ${SOURCE_FILES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)