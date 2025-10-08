cmake_minimum_required(VERSION 3.10)
project(binfs)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SUPRESS_REGENERATION true)
set(CMAKE_BUILD_TYPE Debug)

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include  ${TOP_DIR}/3rd/cmdline)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${INCLUDE_DIRS})
add_executable(binfs ${SOURCE_FILES})

add_custom_command(
    TARGET binfs
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:binfs> $<TARGET_FILE_DIR:binfs>/../binfs.exe
)


