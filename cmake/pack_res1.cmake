
# Function to download a file if it doesn't exist
# function(download_file url dest)
#     if(NOT EXISTS ${dest})
#         message(STATUS "Downloading ${url} to ${dest}")
#         file(DOWNLOAD ${url} ${dest} SHOW_PROGRESS)
#     endif()
# endfunction()

set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/lib)
set(EMBEDDED_RESOURCES ${CMAKE_BINARY_DIR}/web_resources.cpp)  # resource file
set(WEB_DIR ${CMAKE_SOURCE_DIR}/web)                      # web directory to pack

# Automatically traverse all files in the web directory and generate a resource mapping table
file(WRITE ${EMBEDDED_RESOURCES}
    "#include <string>\n#include <unordered_map>\n\n"
    "// resource map (filename -> file content)\n"
    "const std::unordered_map<std::string, std::string> web_resource_map = {\n"
)

file(GLOB_RECURSE WEB_FILES LIST_DIRECTORIES false "${WEB_DIR}/*")
foreach(WEB_FILE ${WEB_FILES})
    # 1) get relative filename (e.g. web/style.css -> style.css, web/img/icon.png -> img/icon.png)
    file(RELATIVE_PATH RELATIVE_FILENAME ${WEB_DIR} ${WEB_FILE})

    # 2) read file content, escape double quotes, newlines (to avoid C++ string syntax errors)
    file(READ ${WEB_FILE} FILE_CONTENT)
    #     # Read file content and escape
    # file(READ ${WEB_FILE} CONTENT HEX)
    # string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," CONTENT ${CONTENT})

    # string(REPLACE "\"" "\\\"" FILE_CONTENT_ESCAPED ${FILE_CONTENT})
    # string(REPLACE "\n" "\\n" FILE_CONTENT_ESCAPED ${FILE_CONTENT_ESCAPED})
    # string(REPLACE "\r" "\\r" FILE_CONTENT_ESCAPED ${FILE_CONTENT_ESCAPED})  # for Windows line ending

    # Read file content and escape
    file(READ ${WEB_FILE} CONTENT HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," FILE_CONTENT_ESCAPED ${CONTENT})

    # add file to resource map (filename -> file content)
    file(APPEND ${EMBEDDED_RESOURCES}
        "    {\"${RELATIVE_FILENAME}\", \"${FILE_CONTENT_ESCAPED}\"},\n"
    )
endforeach()

#  complete resource map and add MIME type
file(APPEND ${EMBEDDED_RESOURCES}
    "};\n\n"
    "// auto match MIME type (support common front-end files)\n"
    "std::string getExtension(const std::string& filename) {\n"
    "    // find last dot position in filename\n"
    "    size_t lastDot = filename.find_last_of(\".\");\n"
    "    if (lastDot == std::string::npos) {\n"
    "        return \"\";  // no dot found, no extension \n"
    "    }\n"
    "    return filename.substr(lastDot + 1);\n"
    "}\n\n"
    "inline std::string get_mime_type(const std::string& filename) {\n"
    "    if (getExtension(filename) == \"html\" || getExtension(filename) == \"htm\") return \"text/html\";\n"
    "    if (getExtension(filename) == \"css\") return \"text/css\";\n"
    "    if (getExtension(filename) == \"js\") return \"application/javascript\";\n"
    "    if (getExtension(filename) == \"png\") return \"image/png\";\n"
    "    if (getExtension(filename) == \"jpg\" || getExtension(filename) == \"jpeg\") return \"image/jpeg\";\n"
    "    if (getExtension(filename) == \"svg\") return \"image/svg+xml\";\n"
    "    return \"application/octet-stream\"; // default\n"
    "}\n\n"
)
