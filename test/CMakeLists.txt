
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

if(_BUILD_AS_UNIX)

	add_definitions(-DUNIX)
	add_definitions(-Dunix)
endif(_BUILD_AS_UNIX)

if(_BUILD_AS_WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		message (STATUS "Compiling for 64-bit Windows")

		add_definitions(-DWIN64)
	else()

		message (STATUS "Compiling for 32-bit Windows")

		add_definitions(-DWIN32)
	endif()

	# suppress implicit-link file
	add_definitions(-DCSTRING_INCL_CSTRING_H_IMPLICIT_LINK)
endif(_BUILD_AS_WIN32)

if((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))

	add_compile_options("/Zc:__cplusplus")

	add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
endif()


foreach(d
	component
	performance
	scratch
	unit
)

	if(CSTRING_USE_WIDE_STRINGS AND d STREQUAL "performance")

		# Competitive suites compare char payloads with std::string and
		# byte-oriented file I/O. They are not a wchar_t build.
		message(STATUS "wide-string build: not building performance tests")
	elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${d}")

		add_subdirectory(${d})
	endif()
endforeach()


# ############################## end of file ############################# #

