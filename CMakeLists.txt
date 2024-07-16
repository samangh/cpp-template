cmake_minimum_required(VERSION 3.15.0)

# Allows for setting MSVC static runtime
cmake_policy(SET CMP0091 NEW)

project(template
  VERSION "0.0.1"
  DESCRIPTION "template"
  LANGUAGES C CXX)

set(NAMESPACE template)

##
## CMake module paths
##

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/libsg/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/sanitizers-cmake/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/nilibddc/cmake")

##
## Build options
##

# Set this to OFF to build static libraries
option (BUILD_SHARED_LIBS "Build shared libraries" ON)

if (BUILD_SHARED_LIBS)
  set(USE_STATIC_LIBS_DEFAULT OFF)
else()
  set(USE_STATIC_LIBS_DEFAULT ON)
endif()

option (USE_STATIC_LIBS "Use external static libs if possible" ${USE_STATIC_LIBS_DEFAULT})
option (USE_STATIC_RUNTIME "Statically link against the C++ runtime" USE_STATIC_LIBS)
option (ARCH_NATIVE "Optimise code for current architecture" OFF)
option (USE_SSE "Enable global use of SSE if possible" ARCH_NATIVE)

if(USE_STATIC_LIBS)
  include(prioritise_static_libraries)
  prioritise_static_libraries()
endif()


##
## Compile support
##

# Export compile database for IDEs, needed for QtCreator
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

##
## Import functions
##

include(setup_ide_folders)
include(get_standard_library_name)

# Check for name of standard library, use by common
include(CheckCXXSourceCompiles)
get_standard_library_name(STANDARD_LIBRARY)

##
## Packages
##

# Setup boost variables, in case any of our projects use it
include(setup_boost)
find_package(Sanitizers REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)

if(USE_SSE)
  find_package(SSE OPTIONAL_COMPONENTS COMPONENTS SSE42 AVX2)
endif()

##
## Targets/Sources
##

add_subdirectory(external/libsg/common)
add_subdirectory(external/libsg/imgui)
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
endforeach()

foreach(t ${TARGETS})
  target_compile_features(${t} PRIVATE cxx_std_17)
endforeach()
