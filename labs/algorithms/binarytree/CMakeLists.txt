cmake_minimum_required(VERSION 3.2)
project(binarytree)


# Locate Boost libraries: unit_test_framework, date_time and regex
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.55 REQUIRED COMPONENTS iterator_facade)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(gtest-1.7.0/)
include_directories(gtest-1.7.0/include gtest-1.7.0/)

set(SOURCE_FILES
    binarytree.h
    binarytree_unittest.cc)

add_executable(binarytree_unittest ${SOURCE_FILES})
target_link_libraries(binarytree_unittest gtest gtest_main)

add_executable(mytest binarytree.h test.cc)

# We need boost includes
target_include_directories(binarytree_unittest PRIVATE ${Boost_INCLUDE_DIRS})

# We need boost libraries
target_link_libraries(binarytree_unittest ${Boost_LIBRARIES})