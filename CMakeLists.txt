cmake_minimum_required(VERSION 3.5)
project(critical_plane)

set(CMAKE_CXX_STANDARD 20)

#find_package(Eigen3 REQUIRED NO_MODULE)
# set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR/extern})
# add_library(Catch2::Catch IMPORTED INTERFACE)
# set_property(Catch2::Catch PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CATCH_INCLUDE_DIR}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


set(SOURCES 
    src/convex_hull.cpp
    src/file_handling.cpp
    src/geometry.cpp
    src/stress.cpp
    src/findley.cpp
    src/tri_hemisphere.cpp)

set(TARGET_INCLUDE
    include
)

# LIB
add_library(critplane ${SOURCES})
target_link_libraries(critplane ${CONAN_LIBS})
target_include_directories(critplane PUBLIC include ${TARGET_INCLUDE}})

# CLI
add_executable(critplane_cli src/cli_main.cpp)
target_link_libraries(critplane_cli critplane ${CONAN_LIBS})
target_include_directories(critplane_cli PUBLIC include ${TARGET_INCLUDE})

# Testing
enable_testing()
add_subdirectory(tests)

# Benchmarking
#add_subdirectory(bench)