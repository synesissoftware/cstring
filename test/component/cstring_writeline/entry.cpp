/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/cstring_writeline/entry.cpp
 *
 * Purpose: Unit-tests of `cstring_write()` and `cstring_writeline()`.
 *
 * Created: 10th August 2020
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <cstring/cstring.h>

/* /////////////////////////////////////
 * general includes
 */

#include "component_fixture.hpp"
#include "../../cstring_testing.h"

/* xTests header files */
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>

/* STLSoft header files */
#include <platformstl/filesystem/file_lines.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void TEST_cstring_writeline_CALLABILITY();
    static void TEST_cstring_writeline_INVALID_STREAM();
    static void TEST_cstring_writeline_MULTIPLE_LINES();
    static void TEST_cstring_write_CONCATENATED();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

const char TEST_FILE_NAME[] = "test.component.cstring_writeline.txt";


/* /////////////////////////////////////////////////////////////////////////
 * compiler compatibility
 */

#if defined(STLSOFT_COMPILER_IS_MSVC)
# if _MSC_VER >= 1200
#  pragma warning(push)
# endif /* compiler */
# pragma warning(disable : 4702)
#endif /* compiler */


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.cstring_writeline", verbosity, cstring_component::setup, cstring_component::teardown, (void*)TEST_FILE_NAME))
    {
        XTESTS_RUN_CASE(TEST_cstring_writeline_CALLABILITY);
        XTESTS_RUN_CASE(TEST_cstring_writeline_INVALID_STREAM);
        XTESTS_RUN_CASE(TEST_cstring_writeline_MULTIPLE_LINES);
        XTESTS_RUN_CASE(TEST_cstring_write_CONCATENATED);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * compiler compatibility
 */

#if defined(STLSOFT_COMPILER_IS_MSVC)
# if _MSC_VER >= 1200
#  pragma warning(pop)
# endif /* compiler */
#endif /* compiler */


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

    using ::xtests::cpp::util::temp_file;


static void TEST_cstring_writeline_CALLABILITY()
{
    false && cstring_writeline(stdout, NULL, NULL);

    TEST_PASSED();
}

static void TEST_cstring_writeline_INVALID_STREAM()
{
#if 0
    cstring_t   cs = cstring_t_DEFAULT;

    TEST_ENUM_EQ(CSTRING_RC_INVALIDSTREAM, cstring_writeline(NULL, &cs, NULL));

    size_t      n;

    TEST_ENUM_EQ(CSTRING_RC_INVALIDSTREAM, cstring_writeline(NULL, &cs, &n));
#endif /* 0 */

    TEST_PASSED();
}

static void TEST_cstring_writeline_MULTIPLE_LINES()
{
    static char const* const s_lines[] =
    {
        "abc",
        "abcdef",
        "abcdefghijkl",
        "abcdefghijklmnopqrstuvwxyz",
        "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "xyz"
    };

    {
        temp_file   tf_in(temp_file::EmptyOnOpen | temp_file::DeleteOnClose);
        temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

        {
            FILE*   in  =   fopen(tf_in.c_str(), "r");
            FILE*   out =   fopen(tf_out.c_str(), "w");

            stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
            stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);


            { for (size_t i = 0; STLSOFT_NUM_ELEMENTS(s_lines) != i; ++i)
            {
                cstring_t   cs;
                CSTRING_RC  rc;
                int         flags = 0;//CSTRING_F_MEMORY_IS_BORROWED;

                rc = cstring_testing_createEx_mb_(&cs, s_lines[i], flags, NULL, 0);

                ((void)&rc);

                rc = cstring_writeline(out, &cs, NULL);

                ((void)&rc);

                cstring_destroy(&cs);
            }}
        }

        platformstl::file_lines out_lines(tf_out);

        REQUIRE(TEST_INT_EQ(6u, out_lines.size()));
        { for (size_t i = 0; STLSOFT_NUM_ELEMENTS(s_lines) != i; ++i)
        {
            TEST_MS_EQ(s_lines[i], out_lines[i]);
        }}
    }
}

static void TEST_cstring_write_CONCATENATED()
{
    static char const* const s_lines[] =
    {
        "abc",
        "abcdef",
        "abcdefghijkl",
        "abcdefghijklmnopqrstuvwxyz",
        "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "xyz"
    };

    {
        temp_file   tf_in(temp_file::EmptyOnOpen | temp_file::DeleteOnClose);
        temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

        {
            FILE*   in  =   fopen(tf_in.c_str(), "r");
            FILE*   out =   fopen(tf_out.c_str(), "w");

            stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
            stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);


            { for (size_t i = 0; STLSOFT_NUM_ELEMENTS(s_lines) != i; ++i)
            {
                cstring_t   cs;
                CSTRING_RC  rc;
                int         flags = 0;//CSTRING_F_MEMORY_IS_BORROWED;

                rc = cstring_testing_createEx_mb_(&cs, s_lines[i], flags, NULL, 0);

                ((void)&rc);

                rc = cstring_write(out, &cs, NULL);

                ((void)&rc);

                cstring_destroy(&cs);
            }}
        }

        platformstl::file_lines out_lines(tf_out);

        REQUIRE(TEST_INT_EQ(1u, out_lines.size()));

        std::string expected;

        { for (size_t i = 0; STLSOFT_NUM_ELEMENTS(s_lines) != i; ++i)
        {
            expected.append(s_lines[i]);
        }}

        TEST_MS_EQ(expected, out_lines[0]);
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

