#
# HDF5
#
option(WITH_HDF5 "Choose if HDF5 support should be built" FALSE)
if(WITH_HDF5)
    set (HDF5_FIND_COMPONENTS "CXX")
    find_package(HDF5 COMPONENTS CXX)
    if(HDF5_FOUND)
        include_directories(${HDF5_INCLUDE_DIR})
        add_definitions(-DHAVE_HDF5=1)
        set(PDAL_HAVE_HDF5 1)
        message(STATUS "Found HDF5")
    else()
        set(WITH_HDF5 FALSE)
        set(PDAL_HAVE_HDF5 0)
        message(STATUS "HDF5 not found")
    endif()
endif()
