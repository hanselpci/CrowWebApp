
set(PACK_WEB_TEST_FILE_NAME pack_web_test_lite.cpp)
set(PACK_WEB_TEST_DST_FILE ${CMAKE_SOURCE_DIR}/build/lib/${PACK_WEB_TEST_FILE_NAME})
set(PACK_WEB_TEST_SRC_FILE ${CMAKE_SOURCE_DIR}/3rd/binfs/test/${PACK_WEB_TEST_FILE_NAME})

# find all web resources files
file(GLOB_RECURSE WEB_RESOURCES  ${WEB_FILES_DIR}/*)

set(PACK_WEB_CMD $<TARGET_FILE:binfs> --base_dir ${WEB_FILES_DIR} --outfile ${WEB_RESOURCES_HPP} --lite 1 ${WEB_FILES_DIR})

# custom command: generate web.hpp from web resources
add_custom_command(
  OUTPUT ${WEB_RESOURCES_HPP}  # output file
  DEPENDS ${WEB_RESOURCES}  $<TARGET_FILE:binfs>
  COMMAND ${CMAKE_COMMAND} -E echo "CMD: ${PACK_WEB_CMD}"
  COMMAND ${PACK_WEB_CMD}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  BYPRODUCTS ${WEB_RESOURCES_HPP}
  COMMENT "Generating .hpp file from web resources using binfs tool"
  VERBATIM
)

add_custom_command(
  OUTPUT ${PACK_WEB_TEST_DST_FILE}  # output file
  DEPENDS ${WEB_RESOURCES_HPP} ${PACK_WEB_TEST_SRC_FILE}
  COMMAND ${CMAKE_COMMAND} -E copy ${PACK_WEB_TEST_SRC_FILE} ${PACK_WEB_TEST_DST_FILE}
  COMMAND ${CMAKE_CXX_COMPILER}
            ${PACK_WEB_TEST_SRC_FILE}
            ${CMAKE_CXX_FLAGS} -I${CMAKE_SOURCE_DIR}/build/lib /EHsc
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib
  BYPRODUCTS ${PACK_WEB_TEST_DST_FILE}
  COMMENT "copying pack_web_test.cpp to build/lib"
  VERBATIM
)

# custom target: ensure the custom command is triggered
add_custom_target(pack_web
  DEPENDS ${WEB_RESOURCES_HPP} ${PACK_WEB_TEST_DST_FILE}
)

