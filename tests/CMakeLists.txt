add_executable(tests run_tests.cpp)

target_link_libraries(tests critplane ${CONAN_LIBS})
target_include_directories(tests PUBLIC "${CONAN_INCLUDE_DIRS_CATCH2}/catch2")