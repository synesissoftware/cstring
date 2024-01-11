/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.cstring_readline.cpp
 *
 * Purpose: Unit-tests `cstring_readline()`.
 *
 * Created: 23rd May 2009
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

const char TEST_FILE_NAME[] = "test.component.cstring_readline.txt";

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

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.cstring_readline", verbosity, setup, teardown, (void*)TEST_FILE_NAME))
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

    static FILE* fopen_or_throw(char const* fileName, char const* mode /* = "r" */)
    {
#ifdef CSTRING_USING_SAFE_STR_FUNCTIONS
        FILE*   f;

        if (0 != ::fopen_s(&f, fileName, mode))
#else /* ? CSTRING_USING_SAFE_STR_FUNCTIONS */
        FILE*   f = ::fopen(fileName, mode);

        if (NULL == f)
#endif /* CSTRING_USING_SAFE_STR_FUNCTIONS */
        {
            throw platformstl::platform_exception((std::string("Could not open file '") + fileName + "'").c_str(), platformstl::system_traits<char>::get_last_error());
        }

        return f;
    }

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
    false && cstring_readline(stdout, NULL, NULL);

    XTESTS_TEST_PASSED();
}

static void test_1_1()
{
    cstring_t   cs = cstring_t_DEFAULT;

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_INVALIDSTREAM, cstring_readline(NULL, &cs, NULL));

    size_t      n;

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_INVALIDSTREAM, cstring_readline(NULL, &cs, &n));
}

static void test_1_2()
{
    {
        FILE* f = fopen_or_throw(TEST_FILE_NAME, "w");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        fprintf(f, "\n");
        fprintf(f, "abc\n");
        fprintf(f, "abcdef\n");
        fprintf(f, "abcdefghijkl\n");
        fprintf(f, "abcdefghijklmnopqrstuvwxyz\n");
        fprintf(f, "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
        fprintf(f, "xyz");
    }

    {
        FILE* f = fopen_or_throw(TEST_FILE_NAME, "r");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        CSTRING_RC  rc;
        cstring_t   strings[7] = { cstring_t_DEFAULT, cstring_t_DEFAULT, cstring_t_DEFAULT, cstring_t_DEFAULT, cstring_t_DEFAULT, cstring_t_DEFAULT };
        size_t      lengths[7];

        rc = cstring_readline(f, &strings[0], &lengths[0]);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(0u, lengths[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", strings[0]);

        rc = cstring_readline(f, &strings[1], &lengths[1]);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(3u, lengths[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", strings[1]);

        rc = cstring_readline(f, &strings[2], &lengths[2]);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(6u, lengths[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdef", strings[2]);

        rc = cstring_readline(f, &strings[3], &lengths[3]);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(12u, lengths[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijkl", strings[3]);

        rc = cstring_readline(f, &strings[4], &lengths[4]);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(26u, lengths[4]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklmnopqrstuvwxyz", strings[4]);

        rc = cstring_readline(f, &strings[5], &lengths[5]);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(62u, lengths[5]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", strings[5]);

        rc = cstring_readline(f, &strings[6], &lengths[6]);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_EOF, rc));
        XTESTS_TEST_INTEGER_EQUAL(3u, lengths[6]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("xyz", strings[6]);
    }
}

static void test_1_3()
{
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

