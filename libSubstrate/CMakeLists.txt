project(libSubstrate)

include(GenerateExportHeader)

file (GLOB_RECURSE libSubstrate_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB_RECURSE libSubstrate_src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(${PROJECT_NAME} ${libSubstrate_headers} ${libSubstrate_src})

generate_export_header(${PROJECT_NAME}
    BASE_NAME LIB_SUBSTRATE
    EXPORT_MACRO_NAME LIB_SUBSTRATE_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/public/substrate/substrate_export.h
)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Public exposed libraries
target_link_libraries(${PROJECT_NAME} PUBLIC boost::boost nlohmann_json::nlohmann_json)

# Private libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    libsodium::libsodium
    sr25519::sr25519
    libcurl::libcurl
    libscale::libscale)
