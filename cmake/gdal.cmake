#
# GDAL/OGR support (required)
#
find_package(GDAL 1.9.0)
if (GDAL_FOUND)
    #
    # GDAL depends on ICONV?
    #
    include(${PDAL_CMAKE_DIR}/iconv.cmake)

    include_directories("${GDAL_INCLUDE_DIR}")
    mark_as_advanced(CLEAR GDAL_INCLUDE_DIR)
    mark_as_advanced(CLEAR GDAL_LIBRARY)
    message(STATUS "...building with GDAL")
else()
    message(FATAL_ERROR "GDAL support is required")
endif()
