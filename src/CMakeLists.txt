
set(SOURCES 
    convex_hull.cpp
    file_handling.cpp
    geometry.cpp
    stress.cpp
    findley.cpp
    tri_hemisphere.cpp)

# Library target
add_library(critplane ${SOURCES})
target_link_libraries(critplane ${CONAN_LIBS})
target_include_directories(critplane PUBLIC include "../include"})

# CLI target
add_executable(critplane_cli cli_main.cpp)
target_link_libraries(critplane_cli critplane ${CONAN_LIBS})
target_include_directories(critplane_cli PUBLIC "../include")
