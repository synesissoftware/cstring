
# ######################################################################## #
# File:     /src/CMakeLists.txt
#
# Purpose:  CMake lists file for cstring core library
#
# Created:  ...
# Updated:  26th October 2024
#
# ######################################################################## #


if(UNIX)

	add_definitions(-DUNIX)
	add_definitions(-Dunix)
endif(UNIX)

if(WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		message (STATUS "Compiling for 64-bit Windows")

		add_definitions(-DWIN64)
	else()

		message (STATUS "Compiling for 32-bit Windows")

		add_definitions(-DWIN32)
	endif()

	# suppress implicit-link file
	add_definitions(-DCSTRING_INCL_CSTRING_H_IMPLICIT_LINK)

	add_definitions(-DCLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS)
endif(WIN32)

if((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))

	add_compile_options("/Zc:__cplusplus")

	add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
endif()


set(CORE_SRCS
	cstring.vector.c
	cstring.core.c
)

add_library(core
	${CORE_SRCS}
)

# specify the primary public headers for the library, which controls whether
# they'll be installed
#
# NOTE: it is not yet known (to me, at least) how to include additional
# header files from sub-directories, so this is done below in an additional
# `install()` step
set(CORE_PUBLIC_HEADERS
	"${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/${PROJECT_NAME_LOWER}.h"
	"${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/cstring.vector.h"
)

set_target_properties(core PROPERTIES
	OUTPUT_NAME "cstring"
	PUBLIC_HEADER "${CORE_PUBLIC_HEADERS}"
)

target_include_directories(core
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(core
	PRIVATE
		$<$<STREQUAL:${STLSOFT_INCLUDE_DIR},>:STLSoft::STLSoft>
)

target_compile_options(core
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra -pedantic
		>
		$<$<CXX_COMPILER_ID:MSVC>:
			/WX /W4
		>
)


# ##########################################################
# install

install(TARGETS core
	EXPORT project-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LOWER}
)

install(
	DIRECTORY ${CMAKE_SOURCE_DIR}/include/cstring/internal
	DESTINATION include/cstring
	FILES_MATCHING
	PATTERN "*.h*"
)



# ############################## end of file ############################# #

