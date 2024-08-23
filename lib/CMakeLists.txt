set(TARGET "lib")

set_property(GLOBAL APPEND PROPERTY ${PROJECT_NAME}_TARGETS ${TARGET})

##
## Source files
##

file(GLOB_RECURSE SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${TARGET} ${SRC_FILES})

##
## Includes
##

target_include_directories(${TARGET}
  INTERFACE
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
  PRIVATE)

target_link_libraries(${TARGET}
  INTERFACE
  PUBLIC
  PRIVATE)

include (GenerateExportHeader)
generate_export_header(${TARGET}
             EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/include/export/${TARGET}.h")

##
## Version
##

configure_file (
  "${PROJECT_SOURCE_DIR}/external/libsg/cmake/version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
  )

set_target_properties(${TARGET} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR})

