if (MSVC)
    set(PDAL_COMPILER_MSVC 1)
    if (MSVC12)
      set(PDAL_COMPILER_VC12 1)
    elseif (MSVC11)
      set(PDAL_COMPILER_VC11 1)
    elseif (MSVC10)
      set(PDAL_COMPILER_VC10 1)
    elseif (MSVC9)
      set(PDAL_COMPILER_VC9 1)
    elseif (MSVC8)
      set(PDAL_COMPILER_VC8 1)
    endif()

    # check for MSVC 8+
    if (NOT (MSVC_VERSION VERSION_LESS 1400))
        add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        add_definitions(-D_CRT_NONSTDC_NO_WARNING)
        add_definitions(-D_SCL_SECURE_NO_WARNINGS)
        add_definitions(-DNOMINMAX)
    endif()

    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4"
               CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()

    # check for MSVC 9+
    if (NOT (MSVC_VERSION VERSION_LESS 1500))
        include(ProcessorCount)
        ProcessorCount(N)
        if(NOT N EQUAL 0)
            set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   /MP${N}")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP${N}")
        endif()
    endif()
endif(MSVC)

#ABELL - WHY?
set(CMAKE_INCLUDE_PATH "c:/OSGeo4W64/include;$ENV{CMAKE_INCLUDE_PATH}")
set(CMAKE_LIBRARY_PATH "c:/OSGeo4W64/lib;$ENV{CMAKE_LIBRARY_PATH}")

#ABELL - WHY?
set(PDAL_PLATFORM_WIN32 1)
