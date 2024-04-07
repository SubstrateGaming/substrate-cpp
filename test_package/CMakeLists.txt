cmake_minimum_required(VERSION 3.15)

project(substrate_test_package LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(substrate CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} substrate::substrate)

if (WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${substrate_LIB_DIRS_DEBUG}/substrate.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    else()
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${substrate_LIB_DIRS_RELEASE}/substrate.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()
endif()
