cmake_minimum_required(VERSION 3.10)
project(2_semester)
set(CMAKE_CXX_STANDARD 17)

add_executable(testtest main/test.cpp) # May want to link the SQLite3 library
target_link_libraries(test sqlite3)
