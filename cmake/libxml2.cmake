
get_property(EXISTS GLOBAL PROPERTY _LIBXML2_INCLUDED)
if(EXISTS)
    return()
endif()
#
# libxml2
#

#
# Depends on iconv
#
include(${PDAL_CMAKE_DIR}/iconv.cmake)

find_package(LibXml2 REQUIRED)
mark_as_advanced(CLEAR LIBXML2_INCLUDE_DIR)
mark_as_advanced(CLEAR LIBXML2_LIBRARIES)
include_directories(${LIBXML2_INCLUDE_DIR})
set(PDAL_HAVE_LIBXML2 1)

set_property(GLOBAL PROPERTY _LIBXML2_INCLUDED TRUE)
