# Performance tests (human attention; not CTest-gated)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cstring)
add_subdirectory(cstring_readline)
add_subdirectory(cstring_vector)
add_subdirectory(hash)


# ############################## end of file ############################# #
