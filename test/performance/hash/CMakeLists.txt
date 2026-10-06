define_performance_test_program(test.performance.hash main.cpp)

target_sources(test.performance.hash
	PRIVATE
		lose_lose.c
)
