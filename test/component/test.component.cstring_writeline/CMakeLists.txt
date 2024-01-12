
add_executable(test_component_cstring_cstring_writeline
    test.component.cstring_writeline.cpp
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test_component_cstring_cstring_writeline
    cstring
    xTests::xTests.core
)

target_compile_options(test_component_cstring_cstring_writeline PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Werror -Wall -Wextra -pedantic
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /WX /W4
    >
)


# ############################## end of file ############################# #

