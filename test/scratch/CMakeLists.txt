if(NOT NO_CSTRING_CPP_API)

	add_subdirectory(libver)
endif()
add_subdirectory(test.scratch.auto_buffer)
add_subdirectory(test.scratch.cstring)
add_subdirectory(test.scratch.cstring_create)
add_subdirectory(test.scratch.cstring_vector)
if(NOT NO_CSTRING_CPP_API)

	add_subdirectory(test.scratch.cstring.dynload)
	add_subdirectory(test.scratch.HGLOBAL_on_x64)
endif()
