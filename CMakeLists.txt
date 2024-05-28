cmake_minimum_required(VERSION 3.15.0)

# Allows for setting MSVC static runtime
cmake_policy(SET CMP0091 NEW)

project(template
  VERSION "0.0.1"
  DESCRIPTION "template"
  LANGUAGES C CXX)

set(NAMESPACE template)

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
option (ARCH_NATIVE "Optimise code for current architecture" OFF)
option (USE_SSE "Enable global use of SSE if possible" OPTIMISE_NATIVE)

if(MSVC)
  # Note: if using SDL2, will require SDL2 to be compiled with
  # FORCE_STATIC_VCRT=ON
  option(USE_STATIC_RUNTIME "Statically link against the C++ runtime" USE_STATIC_LIBS)
endif()

##
## CMake module paths
##

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/libsg/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/sanitizers-cmake/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/nilibddc/cmake")

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

foreach(t ${TARGETS})
  target_compile_options(${t}
    PRIVATE
     ## Warnings
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall -Wextra>
     $<$<CXX_COMPILER_ID:MSVC>:/permissive->

     # Set arch to native (i.e. use all processor flags)
     $<$<AND:$<BOOL:${ARCH_NATIVE}>,$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>>:-march=native>)

target_link_libraries(${t}
    PRIVATE
     # Enable SSE if
     $<$<AND:$<BOOL:${USE_SSE}>,$<BOOL:${SSE_SSE41_FOUND}>>:SSE::SSE42>
     $<$<AND:$<BOOL:${USE_SSE}>,$<BOOL:${SSE_AVX2_FOUND}>>:SSE::AVX2>)

  # Link against MSVC statically if enabled
  if (USE_STATIC_RUNTIME AND MSVC)
    set_property(TARGET ${t} PROPERTY
      MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()

  add_sanitizers(${t})
endforeach()

foreach(t ${TARGETS})
  target_compile_features(${t} PRIVATE cxx_std_17)
endforeach()
