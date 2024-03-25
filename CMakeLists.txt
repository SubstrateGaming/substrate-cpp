cmake_minimum_required(VERSION 3.28)

project(substrate-cpp LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost)
find_package(nlohmann_json)
find_package(libsodium)
find_package(sr25519)

# TODO: Use this as soon as conan exposes ENABLE_WEBSOCKET define.
# find_package(CURL)

set (LIB_SUBSTRATE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set (LIB_SUBSTRATE_DEPS ${LIB_SUBSTRATE_ROOT}/deps)
set (LIB_SUBSTRATE_LIBSCALE ${LIB_SUBSTRATE_DEPS}/scale-codec-cpp)

option(LSUB_WITH_TESTS "Build with tests. Default is ON." ON)

# Dependencies
find_package(CURL)

if (NOT CURL_FOUND)
    message(STATUS "Use cURL from deps/curl.")

    set(BUILD_SHARED_LIBS OFF)
    set(BUILD_TESTING OFF)
    set(USE_ZLIB OFF)
    set(USE_LIBSSH2 OFF)
    set(BUILD_LIBCURL_DOCS OFF)
    set(BUILD_CURL_EXE OFF)

    set(HTTP_ONLY ON)
    set(ENABLE_WEBSOCKETS ON)

    if (WIN32)
        set(CURL_USE_SCHANNEL ON)
    endif ()

    add_subdirectory(deps/curl)

    # Set the CURL library and include directory manually, if needed
    # This step might be unnecessary if cURL's CMakeLists.txt sets everything up automatically
    set(CURL_LIBRARIES libcurl)
    set(CURL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/include)

    unset(BUILD_SHARED_LIBS)
    unset(BUILD_TESTING)
    unset(USE_ZLIB)
    unset(USE_LIBSSH2)
    unset(BUILD_LIBCURL_DOCS)
    unset(BUILD_CURL_EXE)

    unset(HTTP_ONLY)
    unset(ENABLE_WEBSOCKETS)

    if (WIN32)
        unset(CURL_USE_SCHANNEL)
    endif ()
endif ()

add_subdirectory(libSubstrate)
add_subdirectory(app)

if (LSUB_WITH_TESTS)
    find_package(GTest)

    enable_testing()
    file (GLOB_RECURSE libSubstrate_tests_sources ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

    add_executable(libSubstrate_tests ${libSubstrate_tests_sources})
    target_link_libraries(libSubstrate_tests PRIVATE GTest::gtest_main libSubstrate)
    add_test(NAME libSubstrate_tests COMMAND $<TARGET_FILE:libSubstrate_tests>)

    # include(GoogleTest)
    # gtest_discover_tests(libSubstrate_tests)
endif ()
