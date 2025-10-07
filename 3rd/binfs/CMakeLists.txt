cmake_minimum_required(VERSION 3.10)
project(binfs)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SUPRESS_REGENERATION true)
set(CMAKE_BUILD_TYPE Release)

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${INCLUDE_DIRS})
add_executable(binfs ${SOURCE_FILES})
target_link_libraries(binfs)
