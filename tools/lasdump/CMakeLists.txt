cmake_minimum_required(VERSION 2.8.6)

set(MAKE_COLOR_MAKEFILE ON)

if(NOT ROOT_DIR)
    project(LASDUMP)
    set(ROOT_DIR "${PROJECT_SOURCE_DIR}/../..")
endif()
include(${ROOT_DIR}/cmake/common.cmake NO_POLICY_SCOPE)

add_subdirectory(${PDAL_UTIL_DIR} "${CMAKE_CURRENT_BINARY_DIR}/util")
include_directories(${PDAL_UTIL_DIR} ${PDAL_INCLUDE_DIR})

set (SOURCES
    Dumper.cpp
    Header.cpp
)

set (HEADERS
    Dumper.hpp
    Header.hpp
    LasDump.hpp
    Vlr.hpp
)

#
# Add necessary modules.
#
find_package(LASzip)

add_executable(lasdump ${SOURCES} ${HEADERS})
target_link_libraries(lasdump
    PdalUtil
    ${LASZIP_LIBRARIES}
)


