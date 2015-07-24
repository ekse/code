cmake_minimum_required(VERSION 3.0)
project(tcp_streams_dump)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(libtins)
include_directories(${LIBTINS_INCLUDE_DIRS})
link_libraries(${LIBTINS_LIBRARIES})


set(SOURCE_FILES main.cpp)
add_executable(tcp_streams_dump ${SOURCE_FILES} ${LIBTINS_LIBRAIRIES})