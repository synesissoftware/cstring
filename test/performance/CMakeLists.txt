# Performance tests (human attention; not CTest-gated)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test.performance.cstring)
add_subdirectory(test.performance.cstring_vector)


# ############################## end of file ############################# #
