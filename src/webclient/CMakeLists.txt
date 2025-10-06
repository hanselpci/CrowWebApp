
# Web client executable
add_executable(webclient
    webclient.cpp
)
target_include_directories(webclient PRIVATE ${COMMON_INCLUDE_DIRS})
target_link_libraries(webclient PRIVATE webview::core_static)

# Enable console window on Windows if building in Debug mode
# Remove console window on Windows if building in Release mode
if (MSVC)
    set_target_properties(webclient PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

