# For Release builds, we'll embed web resources
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Add embedded resources to webapp
    set(WEBAPP_SOURCES
        webapp.cpp
        ${COMMON_SOURCES}
        ${EMBEDDED_RESOURCES}
    )
else()
    # For Debug builds, use regular files
    set(WEBAPP_SOURCES
        webapp.cpp
        ${COMMON_SOURCES}
    )
endif()


# Combined web application executable
add_executable(webapp
    ${WEBAPP_SOURCES}
)

target_include_directories(webapp PRIVATE ${COMMON_INCLUDE_DIRS})
target_link_libraries(webapp PRIVATE webview::core_static)
target_compile_options(webapp PRIVATE ${CROW_COMPILE_OPTS} ${ASIO_COMPILE_OPTS} ${WEBVIEW_COMPILE_OPTS})

# Copy web resources to build directory for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    add_custom_command(TARGET webapp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/web $<TARGET_FILE_DIR:webapp>/web)
endif()

# Enable console window on Windows if building in Debug mode
# Remove console window on Windows if building in Release mode
# if (MSVC)
#     set_target_properties(webclient PROPERTIES
#         LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
#         LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
#     )
# endif()
