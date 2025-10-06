# Common source files
set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/src/common/server.cpp
    ${CMAKE_SOURCE_DIR}/src/common/api_handler.cpp
)

if(BUILD_WEBCLIENT)
    add_subdirectory(webclient)
endif()

if(BUILD_WEBSERVER)
    add_subdirectory(webserver)
endif()

if(BUILD_WEBAPP)
    add_subdirectory(webapp)
endif()

