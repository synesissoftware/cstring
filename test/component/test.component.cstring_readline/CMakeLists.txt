
add_executable(test_component_cstring_cstring_readline
    test.component.cstring_readline.cpp
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test_component_cstring_cstring_readline
    cstring
    xTests::xTests.core
)

target_compile_options(test_component_cstring_cstring_readline PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Werror -Wall -Wextra -pedantic
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /WX /W4
    >
)


# ############################## end of file ############################# #

