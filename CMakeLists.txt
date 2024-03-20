cmake_minimum_required(VERSION 3.28)

project(substrate-cpp LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WITH_TESTS "Build with tests. Default is ON." ON)

if (WITH_TESTS)
    enable_testing()
    # add_subdirectory(test ${CMAKE_BINARY_DIR}/tests)
endif ()

add_subdirectory(libSubstrate)
