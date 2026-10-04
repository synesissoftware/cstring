
add_subdirectory(auto-buffer)
add_subdirectory(cstring)
add_subdirectory(cstring_vector)
if(NOT NO_CSTRING_CPP_API)

	add_subdirectory(test.unit.cstring.hash)
	add_subdirectory(cstring.cxx)
endif()
add_subdirectory(insert-replace)
add_subdirectory(status-codes)


# ############################## end of file ############################# #
