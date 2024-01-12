/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.cstring_writeline.cpp
 *
 * Purpose: Unit-tests of `cstring_write()` and `cstring_writeline()`.
 *
 * Created: 10th August 2020
 * Updated: 12th January 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <cstring/cstring.h>
#include <cstring/internal/safestr.h>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/util/temp_file.hpp>

/* STLSoft header files */
#include <platformstl/exception/platformstl_exception.hpp>
#include <platformstl/filesystem/file_lines.hpp>
#include <platformstl/system/system_traits.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>

/* Standard C header files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void test_1_0(void);
    static void test_1_1(void);
    static void test_1_2(void);
    static void test_1_3(void);
    static void test_1_4(void);
    static void test_1_5(void);
    static void test_1_6(void);
    static void test_1_7(void);
    static void test_1_8(void);
    static void test_1_9(void);

    int setup(void*);
    int teardown(void*);

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

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.cstring_writeline", verbosity, setup, teardown, (void*)TEST_FILE_NAME))
    {
        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_2);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_4);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);
        XTESTS_RUN_CASE(test_1_7);
        XTESTS_RUN_CASE(test_1_8);
        XTESTS_RUN_CASE(test_1_9);

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


    int setup(void*)
    {
        return 0;
    }

    int teardown(void* arg)
    {
        char const* filename = static_cast<char const*>(arg);

        ::remove(filename);

        return 0;
    }



static void test_1_0()
{
    false && cstring_writeline(stdout, NULL, NULL);

    XTESTS_TEST_PASSED();
}

static void test_1_1()
{
#if 0
    cstring_t   cs = cstring_t_DEFAULT;

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_INVALIDSTREAM, cstring_writeline(NULL, &cs, NULL));

    size_t      n;

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_INVALIDSTREAM, cstring_writeline(NULL, &cs, &n));
#endif /* 0 */
}

static void test_1_2()
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

                rc = cstring_createEx(&cs, s_lines[i], flags, NULL, 0);

                ((void)&rc);

                rc = cstring_writeline(out, &cs, NULL);

                ((void)&rc);

                cstring_destroy(&cs);
            }}
        }

        platformstl::file_lines out_lines(tf_out);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(6u, out_lines.size()));
        { for (size_t i = 0; STLSOFT_NUM_ELEMENTS(s_lines) != i; ++i)
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL(s_lines[i], out_lines[i]);
        }}
    }
}

static void test_1_3()
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

                rc = cstring_createEx(&cs, s_lines[i], flags, NULL, 0);

                ((void)&rc);

                rc = cstring_write(out, &cs, NULL);

                ((void)&rc);

                cstring_destroy(&cs);
            }}
        }

        platformstl::file_lines out_lines(tf_out);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(1u, out_lines.size()));

        std::string expected;

        { for (size_t i = 0; STLSOFT_NUM_ELEMENTS(s_lines) != i; ++i)
        {
            expected.append(s_lines[i]);
        }}

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL(expected, out_lines[0]);
    }
}

static void test_1_4()
{
}

static void test_1_5()
{
}

static void test_1_6()
{
}

static void test_1_7()
{
}

static void test_1_8()
{
}

static void test_1_9()
{
}



} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

