cmake_minimum_required(VERSION 3.6)
project(7_2_task)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Request.h)
add_executable(7_2_task ${SOURCE_FILES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)