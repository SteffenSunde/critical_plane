cmake_minimum_required(VERSION 3.19)
project(critical_plane)

set(CMAKE_CXX_STANDARD 20)

# Use conan package manager (remember to run conan install .. from ./build)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Library and cli wrapper
add_subdirectory(src)

# Testing (Catch2 requires debug mode!)
enable_testing()
add_subdirectory(tests)

# Benchmarking TODO
#add_subdirectory(bench)