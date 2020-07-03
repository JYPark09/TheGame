# CMake version
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Declare project
project(TheGame)

# C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# 3rd parties
include_directories(3rdparty/random/include)
include_directories(3rdparty/doctest/doctest)

add_subdirectory(3rdparty/pybind11)
include_directories(3rdparty/pybind11/include)

# compile options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# Include directories
include_directories(Includes)

# Project module
add_subdirectory(Sources/TheGame)

add_subdirectory(Sources/ConsolePlay)
add_subdirectory(Sources/pyTheGame)
add_subdirectory(Tests/UnitTest)
