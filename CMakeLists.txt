cmake_minimum_required(VERSION 3.28)

project(substrate-cpp LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LSUB_WITH_TESTS "Build with tests. Default is ON." ON)

if (LSUB_WITH_TESTS)
    enable_testing()
    # add_subdirectory(test ${CMAKE_BINARY_DIR}/tests)
endif ()

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

add_subdirectory(deps/json)

add_subdirectory(libSubstrate)
add_subdirectory(app)
