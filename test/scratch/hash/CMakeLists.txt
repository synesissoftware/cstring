define_example_program(test.scratch.hash main.cpp)

target_include_directories(test.scratch.hash
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../../performance/hash
)

target_sources(test.scratch.hash
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../../performance/hash/lose_lose.c
)
