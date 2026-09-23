list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	4996
)

define_performance_test_program(test.performance.cstring_vector main.cpp)
