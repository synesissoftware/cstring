
add_executable(test_scratch_cstring_auto_buffer
    test.scratch.auto_buffer.c
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test_scratch_cstring_auto_buffer
    cstring
    xTests::xTests.core
)

target_compile_options(test_scratch_cstring_auto_buffer PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Werror -Wall -Wextra -pedantic
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /WX /W4
    >
)


# ############################## end of file ############################# #

