project(app)

file (GLOB_RECURSE app_src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${app_src})

target_link_libraries(${PROJECT_NAME} PRIVATE libSubstrate)
