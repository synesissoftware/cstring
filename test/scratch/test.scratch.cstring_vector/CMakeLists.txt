
add_executable(test_scratch_cstring_vector
    test.scratch.cstring_vector.c
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test_scratch_cstring_vector
    cstring
    xTests::xTests.core
)

target_compile_options(test_scratch_cstring_vector PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Werror -Wall -Wextra -pedantic

        -Wno-format
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /WX /W4
    >
)


# ############################## end of file ############################# #

