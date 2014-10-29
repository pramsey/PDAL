cmake_minimum_required(VERSION 2.8.6)

project(LASDUMP)

set(MAKE_COLOR_MAKEFILE ON)

set(ROOT_PATH "${PROJECT_SOURCE_DIR}/../..")
set(PDAL_SRC "${ROOT_PATH}/src")
set(PDAL_INCLUDE "${ROOT_PATH}/include")
set(PDAL_UTIL "${ROOT_PATH}/util")
set(PDAL_CMAKE "${ROOT_PATH}/cmake")
set(PDAL_MODULES "${PDAL_CMAKE}/modules")

set(CMAKE_MODULE_PATH ${PDAL_MODULES} ${CMAKE_MODULE_PATH})

add_subdirectory(${PDAL_UTIL} "${CMAKE_CURRENT_BINARY_DIR}/util")
include_directories(${PDAL_UTIL} "${PDAL_INCLUDE}" ${PROJECT_SOURCE_DIR})

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

find_package(LASZIP)

add_executable(Lasdump ${SOURCES} ${HEADERS} )
target_link_libraries(Lasdump
    PdalUtil
    ${LASZIP_LIBRARIES}
)

