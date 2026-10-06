list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	4996
)

define_performance_test_program(test.performance.hash main.cpp)

target_sources(test.performance.hash
	PRIVATE
		lose_lose.c
)
