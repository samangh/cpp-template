cmake_minimum_required(VERSION 3.15.0)

project(template
  VERSION "0.0.1"
  DESCRIPTION "template"
  LANGUAGES C CXX)

set(NAMESPACE template)

##
## CMake module paths
##

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/libsg/cmake")

##
## Build options
##

include(DefaultCMakePreamble)

##
## Packages
##

# Setup boost variables, in case any of our projects use it
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)

##
## Targets/Sources
##

add_subdirectory(external/libsg)
add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(gui)

##
## Compile options
##

# Generate target list
get_property(TARGETS GLOBAL PROPERTY ${PROJECT_NAME}_TARGETS)

include(setup_target_options)
foreach(t ${TARGETS})
  setup_target_options(TARGET ${t})
  target_compile_features(${t} PRIVATE cxx_std_20)
endforeach()
