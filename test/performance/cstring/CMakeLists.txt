# GCC 15 -Wfree-nonheap-object false positive: inlined
# stlsoft::auto_buffer::~auto_buffer() only deallocates external storage.
list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	free-nonheap-object
)
list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	4996
)

define_performance_test_program(test.performance.cstring main.cpp)
