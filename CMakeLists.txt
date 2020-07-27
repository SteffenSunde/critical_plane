cmake_minimum_required(VERSION 3.5)
project(test)

# See example at https://github.com/EmbersArc/Epigraph/blob/master/CMakeLists.txt

set(CMAKE_CXX_STANDARD 20)

find_package(Eigen3 REQUIRED NO_MODULE)
# set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR/extern})
# add_library(Catch2::Catch IMPORTED INTERFACE)
# set_property(Catch2::Catch PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CATCH_INCLUDE_DIR}")


set(SOURCES 
    src/convex_hull.cpp
    src/file_handling.cpp
    src/geometry.cpp
    src/stress.cpp
    src/findley.cpp
    src/tri_hemisphere.cpp)
    
set(TARGET_INCLUDE 
    include
    extern
    $ENV{Eigen3_INCLUDE_DIR}
    $ENV{INCLUDEDIR}
    "D:\\include"
)

add_library(critplane ${SOURCES})
target_link_libraries(critplane Eigen3::Eigen)
target_include_directories(critplane PUBLIC ${TARGET_INCLUDE}})
#target_include_directories(critplane PUBLIC )
# add_executable(critplane_cli ${SOURCES})  # TODO: Write into library
# target_link_libraries(critplane_cli critplane)
# target_include_directories(critplane_cl)

# CLI
add_executable(critplane_cli main.cpp ${SOURCES})
target_link_libraries(critplane_cli Eigen3::Eigen critplane)
target_include_directories(critplane_cli PUBLIC ${TARGET_INCLUDE})

#find_package(Catch2)
option(ENABLE_TESTING "Building test suite for Catch2" TRUE)
if (ENABLE_TESTING)
    include_directories(tests)
    add_executable(run_tests tests/run_tests.cpp)
    target_include_directories(run_tests PUBLIC ${TARGET_INCLUDE})
    target_link_libraries(run_tests Eigen3::Eigen)
    target_link_libraries(run_tests critplane)
    #target_compile_options(run_tests PRIVATE -mbig-obj) 
endif()

# Benchmarking
add_subdirectory(bench)