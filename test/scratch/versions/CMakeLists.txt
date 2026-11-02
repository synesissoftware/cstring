define_example_program(test.scratch.versions main.c)

if(shwild_FOUND)

	target_link_libraries(test.scratch.versions
		PRIVATE
			shwild::core
	)
endif()

if(TARGET xTests::core)

	target_link_libraries(test.scratch.versions
		PRIVATE
			xTests::core
	)
endif()

if(TARGET p99::p99)

	target_link_libraries(test.scratch.versions
		PRIVATE
			p99::p99
	)
elseif(TARGET p99::p99_static)

	target_link_libraries(test.scratch.versions
		PRIVATE
			p99::p99_static
	)
endif()
