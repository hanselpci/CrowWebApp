
Collect all web files and generate embedded_resources.cpp
file(GLOB_RECURSE WEB_FILES ${CMAKE_SOURCE_DIR}/web/*)

# Create a C++ source file with embedded resources
set(EMBEDDED_RESOURCES ${CMAKE_BINARY_DIR}/embedded_resources.cpp)
file(WRITE ${EMBEDDED_RESOURCES}
    "#include <map>\n#include <string>\nstd::map<std::string, std::string> embedded_resources = {\n")

# Add each file to the map
foreach(FILE ${WEB_FILES})
    # Get relative path
    file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR}/web ${FILE})

    # Read file content and escape
    file(READ ${FILE} CONTENT HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," CONTENT ${CONTENT})

    # Add to resources
    file(APPEND ${EMBEDDED_RESOURCES}
        "    {\"${REL_PATH}\", std::string(reinterpret_cast<const char*>(new unsigned char[] {${CONTENT}}))},\n")
endforeach()

file(APPEND ${EMBEDDED_RESOURCES} "};")