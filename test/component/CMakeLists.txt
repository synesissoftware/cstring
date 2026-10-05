# Shared component fixtures (component_fixture.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(NOT NO_CSTRING_CPP_API)

	add_subdirectory(cstring_readline)
	add_subdirectory(cstring_vector_readLines)
	add_subdirectory(cstring_writeline)
endif()


# ############################## end of file ############################# #
