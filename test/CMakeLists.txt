
include_directories(${CMAKE_SOURCE_DIR}/include)

if (APPLE)

    message("adding '/usr/local/include' to include-directories for 'test'")

    include_directories("/usr/local/include")
endif()


# include_directories(${OPENBSD_LOCALBASE}/include)

# include(CheckIncludeFiles)
# CHECK_INCLUDE_FILES("<shwild/shwild.h>" HAVE_shwild_h LANGUAGE CXX)
# if (not HAVE_shwild_h)
#     message(FATAL_ERROR "cannot locate header 'shwild/shwild.h'")
# endif()

# CHECK_INCLUDE_FILES("<stlsoft/stlsoft.h>" HAVE_stlsoft_h LANGUAGE CXX)
# if (not HAVE_stlsoft_h)
#     message(FATAL_ERROR "cannot locate header 'stlsoft/stlsoft.h'")
# endif()


if(UNIX)

    add_definitions(-DUNIX)
    add_definitions(-Dunix)
endif()

if(WIN32)

    message(FATAL_ERROR "Use of CMake on Windows not currently supported")
endif()


add_subdirectory(component)
add_subdirectory(performance)
add_subdirectory(scratch)
add_subdirectory(unit)


# ############################## end of file ############################# #

