add_executable(tests run_tests.cpp)

include(../build/conanbuildinfo.cmake)

target_include_directories(tests PUBLIC ${TARGET_INCLUDE} )

target_link_libraries(tests critplane ${CONAN_LIBS})
#target_include_directories(tests PRIVATE #)