# Note, DON'T use local Catch2, as we wenat catch to be compiled using
# our C++ standard version, otherwise we can't use string vectors, etc
# inside the tests as they would bb passed thorugh a library boundary!
#
# See:
# - https://github.com/catchorg/Catch2/issues/2046
# - https://github.com/catchorg/Catch2/issues/2210

if(WIN32 OR MSYS2)
  set(BUILD_SHARED_LIBS FALSE)
endif()

CPMAddPackage("gh:catchorg/catch2@3.7.0")
target_compile_features(Catch2 PRIVATE cxx_std_20)
target_compile_features(Catch2WithMain PRIVATE cxx_std_20)

set(TARGET ${NAMESPACE}_test)

##
## Source files
##

setup_executable(
  TARGET
    ${TARGET}
  NAMESPACE
    ${NAMESPACE}
  NAMESPACE_TARGET
     ${TARGET}
  DIRECTORY
     ${CMAKE_CURRENT_SOURCE_DIR}
  SOURCES_PRIVATE
    src/basic_test.cpp
  INCLUDE_PUBLIC
  INCLUDE_PRIVATE
  LINK_PRIVATE
    lib
    Catch2::Catch2WithMain

  COMPILE_FEATURES_PUBLIC
    cxx_std_20
  COMPILE_OPTIONS_PRIVATE
    $<$<COMPILE_LANG_AND_ID:CXX,GNU>:--coverage>
  LINK_OPTIONS_PRIVATE
    $<$<COMPILE_LANG_AND_ID:CXX,GNU>:--coverage>
)

##
## Enable testing
##

include(${catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(${TARGET})
