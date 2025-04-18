cmake_minimum_required(VERSION 3.15.0)

project(template
  VERSION "0.0.1"
  DESCRIPTION "template"
  LANGUAGES C CXX)

set(NAMESPACE template)

##
## CMake module paths
##

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/libsg/external/libsg_cmake/cmake")

##
## Build options
##

include(DefaultPreamble)

##
## Packages
##

# Setup boost variables, in case any of our projects use it
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(HDF5 COMPONENTS CXX HL REQUIRED)

##
## Targets/Sources
##

add_subdirectory(external/libsg)
add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(gui)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()


##
## Postamble
##
include(DefaultPostamble)
