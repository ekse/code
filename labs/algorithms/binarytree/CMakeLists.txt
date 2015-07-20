cmake_minimum_required(VERSION 3.2)
project(binarytree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(gtest-1.7.0/)
include_directories(gtest-1.7.0/include gtest-1.7.0/)

set(SOURCE_FILES
    binarytree.h
    binarytree_unittest.cc)

add_executable(binarytree_unittest ${SOURCE_FILES})
target_link_libraries(binarytree_unittest gtest gtest_main)