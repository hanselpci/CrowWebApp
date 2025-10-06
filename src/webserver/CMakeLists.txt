
# Web server executable
add_executable(webserver
    webserver.cpp
    ${COMMON_SOURCES}
)

target_compile_options(webserver PRIVATE ${CROW_COMPILE_OPTS} ${ASIO_COMPILE_OPTS})
target_include_directories(webserver PRIVATE ${COMMON_INCLUDE_DIRS})

# Copy web resources to build directory for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET webserver POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/web $<TARGET_FILE_DIR:webserver>/web)
endif()

