#
# top-level CMake configuration file for PDAL
#
# (based originally on the libLAS files copyright Mateusz Loskot)

cmake_minimum_required(VERSION 2.8.6)

project(PDAL)

set(ROOT_DIR "${PROJECT_SOURCE_DIR}")
#include(${ROOT_DIR}/cmake/common.cmake NO_POLICY_SCOPE)
include(${ROOT_DIR}/cmake/common.cmake)

#------------------------------------------------------------------------------
# internal cmake settings
#------------------------------------------------------------------------------

set(CMAKE_COLOR_MAKEFILE ON)

# Allow advanced users to generate Makefiles printing detailed commands
mark_as_advanced(CMAKE_VERBOSE_MAKEFILE)

# per http://www.cmake.org/Wiki/CMake_RPATH_handling
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

#------------------------------------------------------------------------------

# PDAL general settings
#------------------------------------------------------------------------------

include("${PDAL_CMAKE_DIR}/pdal_options.cmake")
include("${PDAL_CMAKE_DIR}/pdal_utils.cmake")

# the next line is the ONLY place in the entire pdal system where
# the version info is hard-coded
set(PDAL_VERSION_STRING 0.9.9 CACHE STRING "PDAL version")

DISSECT_VERSION()
GET_OS_INFO()
SET_INSTALL_DIRS()

SET(PDAL_LIB_SOVERSION ${PDAL_VERSION_MAJOR})
SET(PDAL_C_LIB_SOVERSION ${PDAL_VERSION_MAJOR})

# Name of C++ library
set(PDAL_LIB_NAME pdalcpp)

set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)

set(PDAL_OUTPUT_LIB_DIR "${PDAL_BINARY_DIR}/${PDAL_LIB_DIR}")
set(PDAL_OUTPUT_BIN_DIR "${PDAL_BINARY_DIR}/${PDAL_BIN_DIR}")
file(MAKE_DIRECTORY "${PDAL_OUTPUT_LIB_DIR}")
file(MAKE_DIRECTORY "${PDAL_OUTPUT_BIN_DIR}")
if(WIN32)
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} "${PDAL_OUTPUT_LIB_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} "${PDAL_OUTPUT_BIN_DIR}")
    # ---[ Windows requires DLLs (shared libraries) to be installed in the same directory as executables
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} "${PDAL_OUTPUT_BIN_DIR}")
  endforeach(config)
else(WIN32)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PDAL_OUTPUT_LIB_DIR}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PDAL_OUTPUT_BIN_DIR}")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PDAL_OUTPUT_LIB_DIR}")
endif(WIN32)


#------------------------------------------------------------------------------
# misc user options
#------------------------------------------------------------------------------

# Choose package components
option(WITH_APPS "Choose if PDAL utilities should be built" TRUE)
option(WITH_GREYHOUND "Choose if Greyhound support should be built" FALSE)
option(WITH_PCL "Choose if PCL support should be built" FALSE)
option(WITH_TESTS "Choose if PDAL unit tests should be built" TRUE)

# Choose to use pkg-config or not
option(WITH_PKGCONFIG "Choose whether a pkgconfig file (PDAL.pc) should be installed" TRUE)


#------------------------------------------------------------------------------
# test harness settings
#------------------------------------------------------------------------------

# Name of test suite runner
set(PDAL_UNIT_TEST pdal_test)

# Enable CTest and submissions to PDAL dashboard at CDash
# http://my.cdash.org/index.php?project=PDAL
option(ENABLE_CTEST "Enable CTest to support submissions of results to CDash at http://cdash.org" FALSE)

#------------------------------------------------------------------------------
# General build settings
#------------------------------------------------------------------------------

if(WIN32)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  if(MSVC)
    option(PDAL_USE_STATIC_RUNTIME "Use the static runtime" FALSE)

    if(PDAL_USE_STATIC_RUNTIME)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")

      # Note that the CMake cache will still show /MD
      # http://www.cmake.org/Wiki/CMake_FAQ#Dynamic_Replace
      foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
      endforeach(flag_var)
    endif(PDAL_USE_STATIC_RUNTIME)
  endif(MSVC)
endif(WIN32)

# note we default to debug mode
if(NOT MSVC_IDE)
  if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel" FORCE)
  endif()
  message(STATUS "Setting PDAL build type - ${CMAKE_BUILD_TYPE}")
endif()

set(PDAL_BUILD_TYPE ${CMAKE_BUILD_TYPE})

#------------------------------------------------------------------------------
# Platform and compiler specific settings
#------------------------------------------------------------------------------

#ABELL - Think this is magic now.
#if (APPLE)
#    set(SO_EXT dylib)
#    set(CMAKE_FIND_FRAMEWORK "LAST")
#elseif(WIN32)
#    set(SO_EXT dll)
#else()
#    set(SO_EXT so)
#endif(APPLE)

find_package(Threads)

include(${PDAL_CMAKE_DIR}/boost.cmake)
include(${PDAL_CMAKE_DIR}/caris.cmake)  # Optional
include(${PDAL_CMAKE_DIR}/gdal.cmake)
include(${PDAL_CMAKE_DIR}/geos.cmake)  # Optional
include(${PDAL_CMAKE_DIR}/geotiff.cmake) # Optional
include(${PDAL_CMAKE_DIR}/hdf5.cmake) # Optional
include(${PDAL_CMAKE_DIR}/hexer.cmake) # Optional
include(${PDAL_CMAKE_DIR}/laszip.cmake) # Optional
include(${PDAL_CMAKE_DIR}/mrsid.cmake) # Optional
include(${PDAL_CMAKE_DIR}/nitro.cmake) # Optional
include(${PDAL_CMAKE_DIR}/oracle.cmake) # Optional
include(${PDAL_CMAKE_DIR}/python.cmake) # Optional
include(${PDAL_CMAKE_DIR}/sqlite.cmake) # Optional
include(${PDAL_CMAKE_DIR}/points2grid.cmake) # Optional
include(${PDAL_CMAKE_DIR}/pgpointcloud.cmake) # Optional
include(${PDAL_CMAKE_DIR}/zlib.cmake)

option(USE_PDAL_PLUGIN_TEXT "Build the text driver as a plugin rather than embedding" FALSE)
option(USE_PDAL_PLUGIN_SOCI "Build the soci driver as a plugin rather than embedding" FALSE)
option(USE_PDAL_PLUGIN_OCI "Build the oci driver as a plugin rather than embedding" FALSE)
option(USE_PDAL_PLUGIN_MRSID "Build the MrSID driver as a plugin rather than embedding" FALSE)
option(USE_PDAL_PLUGIN_CARIS "Build the Caris driver as a plugin rather than embedding" FALSE)
option(USE_PDAL_PLUGIN_NITRO "Build the NITF writer as a plugin rather than embedding" FALSE)

if (USE_PDAL_PLUGIN_TEXT OR USE_PDAL_PLUGIN_SOCI OR USE_PDAL_PLUGIN_OCI OR
    USE_PDAL_PLUGIN_MRSID OR USE_PDAL_PLUGIN_CARIS OR USE_PDAL_PLUGIN_NITRO)
  if (PDAL_BUILD_STATIC)
    message(SEND_ERROR "Cannot build separate plugins with statically compiled PDAL")
  endif()
endif()

#------------------------------------------------------------------------------
# generate the pdal_defines.h header
#------------------------------------------------------------------------------

# from http://stackoverflow.com/questions/1435953/how-can-i-pass-git-sha1-to-compiler-as-definition-using-cmake
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

configure_file(
  "${PROJECT_SOURCE_DIR}/gitsha.cpp.in"
  "${PROJECT_SOURCE_DIR}/src/gitsha.cpp")

set(pdal_defines_h_in "${CMAKE_CURRENT_SOURCE_DIR}/pdal_defines.h.in")
set(pdal_defines_h "${CMAKE_CURRENT_BINARY_DIR}/include/pdal/pdal_defines.h")
configure_file(${pdal_defines_h_in} ${pdal_defines_h})
PDAL_ADD_INCLUDES("" "" ${pdal_defines_h})
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")

#------------------------------------------------------------------------------
# subdirectory controls
#------------------------------------------------------------------------------

add_subdirectory(src)
add_subdirectory(plugins)

if(WITH_APPS)
  add_subdirectory(apps)
endif()

if (WITH_TESTS)
  message(STATUS "Building with PDAL unit tests")
  enable_testing()

  if(ENABLE_CTEST)
    message(STATUS
      "Enable CTest to support submissions of results to CDash at http://cdash.org")
    cmake_minimum_required(VERSION 2.8.0)
    # Dashboard has been prepared for experiments
    # http://my.cdash.org/index.php?project=PDAL
    include(CTest)
    message(STATUS
      "Enable CTest to support submissions of results to CDash at http://cdash.org - done")
  endif()

  add_subdirectory(test)
else()
  if(ENABLE_CTEST)
    message(WARNING
      "CTest support requested but WITH_TESTS option not specified to build of PDAL unit tests")
  endif()
endif()

#------------------------------------------------------------------------------
# CPACK controls
#------------------------------------------------------------------------------

SET(CPACK_PACKAGE_VERSION_MAJOR ${PDAL_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${PDAL_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${PDAL_VERSION_MINOR})

SET(CPACK_SOURCE_GENERATOR "TBZ2")
SET(CPACK_PACKAGE_VENDOR "PDAL Development Team")

set(CPACK_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${VERSION}")

set(CPACK_SOURCE_IGNORE_FILES
"/\\\\.gitattributes;/\\\\.vagrant;/\\\\.DS_Store;/CVS/;/\\\\.git/;\\\\.swp$;~$;\\\\.\\\\#;/\\\\#")

list(APPEND CPACK_SOURCE_IGNORE_FILES "CMakeScripts/")
list(APPEND CPACK_SOURCE_IGNORE_FILES "CMakeCache.txt")
list(APPEND CPACK_SOURCE_IGNORE_FILES ".xcodeproj")
list(APPEND CPACK_SOURCE_IGNORE_FILES "build.make")
list(APPEND CPACK_SOURCE_IGNORE_FILES "_CPack_Packages")
list(APPEND CPACK_SOURCE_IGNORE_FILES "cmake_install.cmake")
list(APPEND CPACK_SOURCE_IGNORE_FILES "Testing")
list(APPEND CPACK_SOURCE_IGNORE_FILES "PDAL.build/")
list(APPEND CPACK_SOURCE_IGNORE_FILES "bin/")
list(APPEND CPACK_SOURCE_IGNORE_FILES "Makefile")
list(APPEND CPACK_SOURCE_IGNORE_FILES "CMakeFiles")
list(APPEND CPACK_SOURCE_IGNORE_FILES "CTestTestfile.cmake")
list(APPEND CPACK_SOURCE_IGNORE_FILES "/test/data/local/")
list(APPEND CPACK_SOURCE_IGNORE_FILES "/doc/doxygen/")
list(APPEND CPACK_SOURCE_IGNORE_FILES "/doc/build/")
list(APPEND CPACK_SOURCE_IGNORE_FILES "/doc/presentations/")
list(APPEND CPACK_SOURCE_IGNORE_FILES "pdal-s3cmd.conf")
list(APPEND CPACK_SOURCE_IGNORE_FILES "import-pdal-boost.sh")

include(CPack)

add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
