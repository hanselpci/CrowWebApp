cmake_minimum_required(VERSION 3.10)
project(WebAppDemo)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_WEBCLIENT "Build web client app" ON)
option(BUILD_WEBSERVER "Build web server app" ON)
option(BUILD_WEBAPP "Build web app" ON)

# Configure build types
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Create directories if they don't exist
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Function to download a file if it doesn't exist
# function(download_file url dest)
#     if(NOT EXISTS ${dest})
#         message(STATUS "Downloading ${url} to ${dest}")
#         file(DOWNLOAD ${url} ${dest} SHOW_PROGRESS)
#     endif()
# endfunction()

include(FetchContent)

# avoid warning when using FetchContent by URL
if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif ()

# Do not build webview as a shared library
set(WEBVIEW_BUILD_SHARED_LIBRARY OFF)
# webviewlibrary
FetchContent_Declare(
    webview
    URL https://github.com/webview/webview/archive/refs/tags/0.12.0.zip
    URL_HASH MD5=f2d7eba372417fe37c98be15c0237922
)
FetchContent_MakeAvailable(webview)

set(WEBVIEW_COMPILE_OPTS /wd4819)

# asio library
FetchContent_Declare(
    asio
    URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-36-0.zip
    URL_MD5 fc5e68a8a124f5cde0147329faeec126
)
FetchContent_MakeAvailable(asio)

# For Asio standalone mode
set(ASIO_COMPILE_OPTS -DASIO_STANDALONE -D_WIN32_WINNT=0x0A00)


# crow library
# using URL instead of GIT_REPOSITORY to avoid big size of git repo
FetchContent_Declare(
    crow
    URL https://github.com/CrowCpp/Crow/releases/download/v1.2.1.2/crow_all.h
    DOWNLOAD_NO_EXTRACT TRUE
    URL_MD5 9c94cfb884039e0e1c5bda09bde22795
)
FetchContent_MakeAvailable(crow)

# disable warning C4244 and C4267
set(CROW_COMPILE_OPTS /wd4244 /wd4267)

# Include directories
set(COMMON_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib
    ${asio_SOURCE_DIR}/asio/include/
    ${crow_SOURCE_DIR}
)


# Collect all web files and generate embedded_resources.cpp
# file(GLOB_RECURSE WEB_FILES ${CMAKE_SOURCE_DIR}/web/*)

# # Create a C++ source file with embedded resources
# set(EMBEDDED_RESOURCES ${CMAKE_BINARY_DIR}/embedded_resources.cpp)
# file(WRITE ${EMBEDDED_RESOURCES}
#     "#include <map>\n#include <string>\nstd::map<std::string, std::string> embedded_resources = {\n")

# # Add each file to the map
# foreach(FILE ${WEB_FILES})
#     # Get relative path
#     file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR}/web ${FILE})

#     # Read file content and escape
#     file(READ ${FILE} CONTENT HEX)
#     string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," CONTENT ${CONTENT})

#     # Add to resources
#     file(APPEND ${EMBEDDED_RESOURCES}
#         "    {\"${REL_PATH}\", std::string(reinterpret_cast<const char*>(new unsigned char[] {${CONTENT}}))},\n")
# endforeach()

# file(APPEND ${EMBEDDED_RESOURCES} "};")

# pack web resources to web_resources.cpp
include(${CMAKE_SOURCE_DIR}/cmake/pack_res.cmake)

# Common source files
set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/src/common/server.cpp
    ${CMAKE_SOURCE_DIR}/src/common/api_handler.cpp
)

# Add subdirectories
if(BUILD_WEBCLIENT)
    add_subdirectory(src/webclient)
endif()

if(BUILD_WEBSERVER)
    add_subdirectory(src/webserver)
endif()

if(BUILD_WEBAPP)
    add_subdirectory(src/webapp)
endif()