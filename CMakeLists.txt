cmake_minimum_required(VERSION 3.15)

project(substrate-cpp LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost)
find_package(nlohmann_json)
find_package(libsodium)
find_package(sr25519)
find_package(CURL)
find_package(libscale)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(libSubstrate)

if (BUILD_TESTS)
    find_package(GTest)

    enable_testing()

    # lib
    file (GLOB_RECURSE libSubstrate_tests_sources ${CMAKE_CURRENT_SOURCE_DIR}/tests/lib/*.cpp)
    add_executable(libSubstrate_tests ${libSubstrate_tests_sources})
    target_link_libraries(libSubstrate_tests PUBLIC GTest::gtest_main substrate)
    add_test(NAME libSubstrate_tests COMMAND $<TARGET_FILE:libSubstrate_tests>)
    install(TARGETS libSubstrate_tests DESTINATION tests)

    # node
    file (GLOB_RECURSE libSubstrate_node_tests_sources ${CMAKE_CURRENT_SOURCE_DIR}/tests/node/*.cpp)
    add_executable(libSubstrate_node_tests ${libSubstrate_node_tests_sources})
    target_link_libraries(libSubstrate_node_tests PRIVATE GTest::gtest_main substrate)
    add_test(NAME libSubstrate_node_tests COMMAND $<TARGET_FILE:libSubstrate_node_tests>)
    install(TARGETS libSubstrate_node_tests DESTINATION tests)

endif ()
