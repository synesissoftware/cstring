/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.cstring_readline/entry.cpp
 *
 * Purpose: Component-tests `cstring_readline()`.
 *
 * Created: 23rd May 2009
 * Updated: 27th September 2026
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
#include <xtests/terse-api.h>

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

    static void TEST_cstring_readline_CALLABILITY(void);
    static void TEST_cstring_readline_INVALID_STREAM(void);
    static void TEST_cstring_readline_SHORT_MULTILINE(void);
    static void TEST_cstring_readline_EMPTY_FILE(void);
    static void TEST_cstring_readline_CRLF_AND_MIXED_EOL(void);
    static void TEST_cstring_readline_FINAL_EOL_VS_NO_EOL(void);
    static void TEST_cstring_readline_CONSECUTIVE_EMPTY_LINES(void);
    static void TEST_cstring_readline_LONG_LINES(void);
    static void TEST_cstring_readline_MANY_SHORT_LINES(void);
    static void TEST_cstring_readline_REUSE_AFTER_LONG_LINE(void);

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

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.cstring_readline", verbosity, setup, teardown, (void*)TEST_FILE_NAME))
    {
        XTESTS_RUN_CASE(TEST_cstring_readline_CALLABILITY);
        XTESTS_RUN_CASE(TEST_cstring_readline_INVALID_STREAM);
        XTESTS_RUN_CASE(TEST_cstring_readline_SHORT_MULTILINE);
        XTESTS_RUN_CASE(TEST_cstring_readline_EMPTY_FILE);
        XTESTS_RUN_CASE(TEST_cstring_readline_CRLF_AND_MIXED_EOL);
        XTESTS_RUN_CASE(TEST_cstring_readline_FINAL_EOL_VS_NO_EOL);
        XTESTS_RUN_CASE(TEST_cstring_readline_CONSECUTIVE_EMPTY_LINES);
        XTESTS_RUN_CASE(TEST_cstring_readline_LONG_LINES);
        XTESTS_RUN_CASE(TEST_cstring_readline_MANY_SHORT_LINES);
        XTESTS_RUN_CASE(TEST_cstring_readline_REUSE_AFTER_LONG_LINE);

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

    static FILE* fopen_or_throw(char const* fileName, char const* mode)
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



static void TEST_cstring_readline_CALLABILITY()
{
    false && cstring_readline(stdout, NULL, NULL);

    TEST_PASSED();
}

static void TEST_cstring_readline_INVALID_STREAM()
{
    cstring_t   cs = cstring_t_DEFAULT;

    TEST_ENUM_EQ(CSTRING_RC_INVALIDSTREAM, cstring_readline(NULL, &cs, NULL));

    size_t      n;

    TEST_ENUM_EQ(CSTRING_RC_INVALIDSTREAM, cstring_readline(NULL, &cs, &n));
}

static void TEST_cstring_readline_SHORT_MULTILINE()
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
        cstring_t   strings[7] = {
            cstring_t_DEFAULT,
            cstring_t_DEFAULT,
            cstring_t_DEFAULT,
            cstring_t_DEFAULT,
            cstring_t_DEFAULT,
            cstring_t_DEFAULT,
            cstring_t_DEFAULT,
        };
        size_t      lengths[7];

        rc = cstring_readline(f, &strings[0], &lengths[0]);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(0u, lengths[0]);
        TEST_MS_EQ("", strings[0]);

        rc = cstring_readline(f, &strings[1], &lengths[1]);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(3u, lengths[1]);
        TEST_MS_EQ("abc", strings[1]);

        rc = cstring_readline(f, &strings[2], &lengths[2]);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(6u, lengths[2]);
        TEST_MS_EQ("abcdef", strings[2]);

        rc = cstring_readline(f, &strings[3], &lengths[3]);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(12u, lengths[3]);
        TEST_MS_EQ("abcdefghijkl", strings[3]);

        rc = cstring_readline(f, &strings[4], &lengths[4]);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(26u, lengths[4]);
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", strings[4]);

        rc = cstring_readline(f, &strings[5], &lengths[5]);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(62u, lengths[5]);
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", strings[5]);

        rc = cstring_readline(f, &strings[6], &lengths[6]);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(3u, lengths[6]);
        TEST_MS_EQ("xyz", strings[6]);
    }
}

static void TEST_cstring_readline_EMPTY_FILE()
{
}

static void TEST_cstring_readline_CRLF_AND_MIXED_EOL()
{
}

static void TEST_cstring_readline_FINAL_EOL_VS_NO_EOL()
{
}

static void TEST_cstring_readline_CONSECUTIVE_EMPTY_LINES()
{
}

static void TEST_cstring_readline_LONG_LINES()
{
}

static void TEST_cstring_readline_MANY_SHORT_LINES()
{
}

static void TEST_cstring_readline_REUSE_AFTER_LONG_LINE()
{
}



} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

