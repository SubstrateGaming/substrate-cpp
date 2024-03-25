project(libSubstrate)

include(GenerateExportHeader)

file (GLOB_RECURSE libSubstrate_headers
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${LIB_SUBSTRATE_LIBSCALE}/include/*.h
)

file (GLOB_RECURSE libSubstrate_src
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${LIB_SUBSTRATE_LIBSCALE}/src/*.cpp
)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(${PROJECT_NAME} STATIC ${libSubstrate_headers} ${libSubstrate_src})

generate_export_header(${PROJECT_NAME}
    BASE_NAME LIB_SUBSTRATE
    EXPORT_MACRO_NAME LIB_SUBSTRATE_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/public/substrate/substrate_export.h
)

target_include_directories (${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/public
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CURL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${LIB_SUBSTRATE_LIBSCALE}/include
)

# Right now boost is the only library we expose to public.
target_link_libraries(${PROJECT_NAME} PUBLIC boost::boost)

target_link_libraries(${PROJECT_NAME} PRIVATE
    nlohmann_json::nlohmann_json
    libsodium::libsodium
    sr25519::sr25519
    ${CURL_LIBRARIES})
