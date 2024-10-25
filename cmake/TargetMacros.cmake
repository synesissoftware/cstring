
macro(define_target_compile_options target_name)

	set(X_GCC_CUSTOM_WARNINGS_ "")

	if(X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
		foreach(warning ${X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

			list(APPEND X_GCC_CUSTOM_WARNINGS_ "-Wno-${warning}")
		endforeach()
	endif()

	set(X_MSVC_CUSTOM_WARNINGS_ "")

	if(X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
			foreach(warning ${X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

					list(APPEND X_MSVC_CUSTOM_WARNINGS_ "/wd${warning}")
			endforeach()
	endif()

	target_compile_options(${target_name}
		PRIVATE
			$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
				-Werror -Wall -Wextra -pedantic

				${GCC_WARN_NO_cxx11_long_long}
				${X_GCC_CUSTOM_WARNINGS_}
			>
			$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
				-Wno-unused-lambda-capture
			>
			$<$<CXX_COMPILER_ID:MSVC>:
				/WX /W4

				${X_MSVC_CUSTOM_WARNINGS_}
			>
	)
endmacro(define_target_compile_options)


function(define_automated_test_program program_name entry_point_source_name)

	add_executable(${program_name}
		${entry_point_source_name}
	)

	target_link_libraries(${program_name}
		PRIVATE
			core
			$<$<STREQUAL:${STLSOFT_INCLUDE_DIR},>:STLSoft::STLSoft>
			$<IF:$<VERSION_LESS:${xTests_VERSION},"0.23">,xTests::xTests.core,xTests::core>
	)

	if(WIN32)

		target_link_libraries(${program_name}
			PRIVATE
				wininet
		)
	endif(WIN32)

	define_target_compile_options(${program_name})
endfunction(define_automated_test_program)


function(define_example_program program_name entry_point_source_name)

	add_executable(${program_name}
		${entry_point_source_name}
	)

	target_link_libraries(${program_name}
		PRIVATE
			core
			$<$<STREQUAL:${STLSOFT_INCLUDE_DIR},>:STLSoft::STLSoft>
	)

	if(WIN32)

		target_link_libraries(${program_name}
			PRIVATE
				wininet
		)
	endif(WIN32)

	define_target_compile_options(${program_name})
endfunction(define_example_program)


# ############################## end of file ############################# #

