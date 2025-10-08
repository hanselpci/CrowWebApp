# find all web resources files
file(GLOB_RECURSE WEB_RESOURCES  ${WEB_FILES_DIR}/*)

set(PACK_WEB_CMD ${TOOL_BIN_DIR}/binfs --outfile ${WEB_RESOURCES_HPP} ${WEB_FILES_DIR})

# custom command: generate web.hpp from web resources
add_custom_command(
  OUTPUT ${WEB_RESOURCES_HPP}  # output file
  DEPENDS ${WEB_RESOURCES}  # dependencies, when these files change, re-generate
  COMMAND ${CMAKE_COMMAND} -E echo "CMD: ${PACK_WEB_CMD}"
  COMMAND ${PACK_WEB_CMD}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  BYPRODUCTS ${WEB_RESOURCES_HPP}
  COMMENT "Generating .hpp file from web resources using binfs tool"
  VERBATIM
)

# custom target: ensure the custom command is triggered
add_custom_target(pack_web
  DEPENDS ${WEB_RESOURCES_HPP}
)