#
# Python
#
option(WITH_PYTHON "Choose if Python support (for PLang filters) should be built" TRUE)
if(WITH_PYTHON)
    FIND_PACKAGE(PythonInterp)
    find_package(PythonLibs 2.4)
    if(PYTHONLIBS_FOUND)
        set(CMAKE_REQUIRED_LIBRARIES "${PYTHON_LIBRARY}")
        include_directories(SYSTEM ${PYTHON_INCLUDE_DIR})
        add_definitions(-DHAVE_PYTHON=1)
        set(PDAL_HAVE_PYTHON 1)

        find_package(NumPy 1.5 REQUIRED)
        include_directories(SYSTEM ${NUMPY_INCLUDE_DIR})
        message(STATUS "Found Python: ${PYTHON_LIBRARY}")
    else()
        set(WITH_PYTHON FALSE)
        set(PYTHON_LIBRARY "")
    endif()
endif()
