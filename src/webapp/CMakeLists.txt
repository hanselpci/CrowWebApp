
# For Release builds, we'll embed web resources
if(PACK_WEB_FOR_WEBAPP)
    set(WEB_FILES_DIR ${CMAKE_SOURCE_DIR}/web)
    set(WEB_RESOURCES_HPP ${CMAKE_BINARY_DIR}/lib/web_resources.hpp)
    # pack web resources to web_resources.cpp
    add_subdirectory(${CMAKE_SOURCE_DIR}/3rd/binfs ${CMAKE_BINARY_DIR}/binfs)

    add_executable(webapp ${WEB_RESOURCES_HPP} ${COMMON_SOURCES} webapp.cpp)

    include(${CMAKE_SOURCE_DIR}/cmake/pack_web.cmake)
    add_dependencies(webapp binfs pack_web)
else()
    # use regular files
    add_executable(webapp webapp.cpp ${COMMON_SOURCES})
endif()

target_include_directories(webapp PRIVATE ${COMMON_INCLUDE_DIRS})
target_link_libraries(webapp PRIVATE webview::core_static)
target_compile_options(webapp PRIVATE ${CROW_COMPILE_OPTS} ${ASIO_COMPILE_OPTS} ${WEBVIEW_COMPILE_OPTS})

# Copy web resources to build directory
if(NOT PACK_WEB_FOR_WEBAPP)
    add_custom_command(TARGET webapp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/web $<TARGET_FILE_DIR:webapp>/web)
endif()

# Enable console window on Windows if building in Debug mode
# Remove console window on Windows if building in Release mode
if (MSVC)
    set_target_properties(webapp PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()
