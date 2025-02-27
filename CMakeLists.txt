cmake_minimum_required(VERSION 3.10)
project(UnitTests)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(test main/test.cpp)