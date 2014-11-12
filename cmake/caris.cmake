#
# CARIS/BDB support (optional)
#
option(WITH_CARIS "Choose if CARIS/BDB support should be built" FALSE)
if(WITH_CARIS)
    set(CARIS_FOUND 1)
    set(PDAL_HAVE_CARIS 1)
endif()
