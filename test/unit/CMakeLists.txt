
add_subdirectory(auto-buffer)
add_subdirectory(cstring_vector)
if(NOT NO_CSTRING_CPP_API)

	add_subdirectory(cstring.cxx)
endif()
add_subdirectory(cstring)
add_subdirectory(hash)
if(NOT NO_CSTRING_CPP_API)

	add_subdirectory(hash.cxx)
endif()
add_subdirectory(insert-replace)
add_subdirectory(status-codes)


# ############################## end of file ############################# #
