set(TARGET gui)
set_property(GLOBAL APPEND PROPERTY ${PROJECT_NAME}_TARGETS ${TARGET})

##
## Source files
##

file(GLOB_RECURSE SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.rc)

add_executable(${TARGET} ${SRC_FILES})

set_property(TARGET ${TARGET} PROPERTY OUTPUT_NAME "${PROJECT_DESCRIPTION}")

##
## Includes
##

target_include_directories(${TARGET}
  INTERFACE
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/src
    )

target_link_libraries(${TARGET}
  INTERFACE
  PUBLIC
  PRIVATE
    SG::common
    SG::imgui
    fmt::fmt
    portable_file_dialogs
  )

##
## Copy dependencies
##

# Note: this only has an effect on DLL-platforms, e.g. Windows
add_custom_command(TARGET ${TARGET} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${TARGET}> $<TARGET_RUNTIME_DLLS:${TARGET}>
  COMMAND_EXPAND_LISTS)

##
## Version
##

configure_file (
  "${PROJECT_SOURCE_DIR}/external/libsg/cmake/version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
  )
