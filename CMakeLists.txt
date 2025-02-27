cmake_minimum_required(VERSION 3.10)
project(ProductDBTest)

# Set C++ standard for C++ files
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set C standard for C files (optional, but good practice)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SQLite3
find_package(SQLite3 REQUIRED)
if (SQLite3_FOUND)
    message(STATUS "SQLite3 found: ${SQLite3_VERSION}")
    include_directories(${SQLite3_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "SQLite3 not found. Please install libsqlite3-dev.")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/sql_utils)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add executable, explicitly specifying C and C++ files
add_executable(test_product 
    main/test.cpp  # C++ file
    sql_utils/sql_utils.c  # C file
)

# Link libraries
target_link_libraries(test_product PRIVATE ${SQLite3_LIBRARIES})