cmake_minimum_required(VERSION 3.31)
project(01_jthread)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexperimental-library")

add_executable(01_jthread main.cpp)
