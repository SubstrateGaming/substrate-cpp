project(libSubstrate)

file (GLOB_RECURSE libSubstrate_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB_RECURSE libSubstrate_src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${libSubstrate_headers} ${libSubstrate_src})

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
