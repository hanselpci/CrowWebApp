# Common source files
set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/src/common/server.cpp
    ${CMAKE_SOURCE_DIR}/src/common/api_handler.cpp
)

# Add subdirectories
add_subdirectory(webserver)
add_subdirectory(webclient)
add_subdirectory(webapp)

