
include(ExternalProject)
ExternalProject_Add(
    binfs
    GIT_REPOSITORY https://github.com/bleenco/binfs.git
    # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/tools
    CMAKE_ARGS -DCMAKE_CXX_FLAGS="/EHsc"
    UPDATE_DISCONNECTED TRUE
    # INSTALL_COMMAND "file(COPY ${CMAKE_CURRENT_BINARY_DIR}/binfs.exe DESTINATION ${CMAKE_BINARY_DIR}/tools)"
)