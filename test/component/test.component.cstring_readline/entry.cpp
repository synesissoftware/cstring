/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.cstring_readline/entry.cpp
 *
 * Purpose: Component-tests `cstring_readline()`.
 *
 * Created: 23rd May 2009
 * Updated: 2nd October 2026
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
#include <xtests/util/temp_file.hpp>

/* STLSoft header files */
#include <platformstl/exception/platformstl_exception.hpp>
#include <platformstl/system/system_traits.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>

/* Standard C++ header files */
#include <string>
#include <vector>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void TEST_cstring_readline_CALLABILITY();
    static void TEST_cstring_readline_INVALID_STREAM();
    static void TEST_cstring_readline_EMPTY_FILE();
    static void TEST_cstring_readline_SINGLE_LINE_NO_EOL();
    static void TEST_cstring_readline_SHORT_MULTILINE();
    static void TEST_cstring_readline_CRLF_AND_MIXED_EOL();
    static void TEST_cstring_readline_FINAL_EOL_VS_NO_EOL();
    static void TEST_cstring_readline_CONSECUTIVE_EMPTY_LINES();
    static void TEST_cstring_readline_LONG_LINES();
    static void TEST_cstring_readline_MANY_SHORT_LINES();
    static void TEST_cstring_readline_REUSE_AFTER_LONG_LINE();

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
        XTESTS_RUN_CASE(TEST_cstring_readline_EMPTY_FILE);
        XTESTS_RUN_CASE(TEST_cstring_readline_SINGLE_LINE_NO_EOL);
        XTESTS_RUN_CASE(TEST_cstring_readline_SHORT_MULTILINE);
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
 * helper functions
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

    static void write_bytes(char const* fileName, void const* bytes, size_t cb)
    {
        FILE* f = fopen_or_throw(fileName, "wb");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        if (cb != ::fwrite(bytes, 1, cb, f))
        {
            throw platformstl::platform_exception("Could not write test file", platformstl::system_traits<char>::get_last_error());
        }
    }

    static void write_string_bytes(char const* fileName, std::string const& bytes)
    {
        write_bytes(fileName, bytes.data(), bytes.size());
    }

    static std::string make_filled(size_t n, char ch)
    {
        return std::string(n, ch);
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
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{
    using ::xtests::cpp::util::temp_file;


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

static void TEST_cstring_readline_EMPTY_FILE()
{
    /* empty file → first read is EOF with empty payload */
    write_bytes(TEST_FILE_NAME, "", 0);

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_t   cs = cstring_t_DEFAULT;
    size_t      numRead = 123u;
    CSTRING_RC  rc = cstring_readline(f, &cs, &numRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(0u, numRead);
    TEST_INT_EQ(0u, cs.len);
    TEST_MS_EQ("", cs);

    cstring_destroy(&cs);
}

static void TEST_cstring_readline_SINGLE_LINE_NO_EOL()
{
    temp_file ft(temp_file::EmptyOnOpen | temp_file::DeleteOnClose, "abc", 3);

    FILE* f = fopen_or_throw(ft.c_str(), "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_t   cs = cstring_t_DEFAULT;
    size_t      numRead = 123u;
    CSTRING_RC  rc = cstring_readline(f, &cs, &numRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(3u, numRead);
    TEST_INT_EQ(3u, cs.len);
    TEST_MS_EQ("abc", cs);

    cstring_destroy(&cs);
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

        { for (size_t i = 0; i != 7; ++i)
        {
            cstring_destroy(&strings[i]);
        }}
    }
}

static void TEST_cstring_readline_CRLF_AND_MIXED_EOL()
{
    /* CRLF, mixed EOL, and lone CR mid-line (binary I/O so CR is visible) */
    {
        std::string bytes;

        bytes.append("one\r\n");
        bytes.append("two\n");
        bytes.append("three\r\n");
        bytes.append("has\rembed\r\n");
        bytes.append("end");

        write_string_bytes(TEST_FILE_NAME, bytes);
    }

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_t   cs = cstring_t_DEFAULT;
    size_t      numRead;
    CSTRING_RC  rc;

    rc = cstring_readline(f, &cs, &numRead);
    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
    /* CRLF: CR is appended then stripped; numRead still counts the CR */
    TEST_INT_EQ(4u, numRead);
    TEST_INT_EQ(3u, cs.len);
    TEST_MS_EQ("one", cs);

    rc = cstring_readline(f, &cs, &numRead);
    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
    TEST_INT_EQ(3u, numRead);
    TEST_INT_EQ(3u, cs.len);
    TEST_MS_EQ("two", cs);

    rc = cstring_readline(f, &cs, &numRead);
    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
    TEST_INT_EQ(6u, numRead);
    TEST_INT_EQ(5u, cs.len);
    TEST_MS_EQ("three", cs);

    rc = cstring_readline(f, &cs, &numRead);
    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
    TEST_INT_EQ(10u, numRead);
    TEST_INT_EQ(9u, cs.len);
    TEST_MS_EQ("has\rembed", cs);

    rc = cstring_readline(f, &cs, &numRead);
    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(3u, numRead);
    TEST_INT_EQ(3u, cs.len);
    TEST_MS_EQ("end", cs);

    cstring_destroy(&cs);
}

static void TEST_cstring_readline_FINAL_EOL_VS_NO_EOL()
{
    /* final line with EOL vs without EOL */

    {
        static char const               input[] =   "alpha\nbeta\n";
        temp_file                       ft(temp_file::EmptyOnOpen | temp_file::DeleteOnClose, input, STLSOFT_NUM_ELEMENTS(input) - 1);
        FILE* const                     f       =   fopen_or_throw(ft.c_str(), "rb");
        stlsoft::scoped_handle<FILE*>   scoper(f, ::fclose);

        cstring_t   cs = cstring_t_DEFAULT;
        size_t      numRead;
        CSTRING_RC  rc;

        rc = cstring_readline(f, &cs, &numRead);
        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_MS_EQ("alpha", cs);

        rc = cstring_readline(f, &cs, &numRead);
        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_MS_EQ("beta", cs);

        rc = cstring_readline(f, &cs, &numRead);
        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(0u, numRead);
        TEST_INT_EQ(0u, cs.len);

        cstring_destroy(&cs);
    }

    {
        static char const               input[] =   "alpha\nbeta";
        temp_file                       ft(temp_file::EmptyOnOpen | temp_file::DeleteOnClose, input, STLSOFT_NUM_ELEMENTS(input) - 1);
        FILE* const                     f       =   fopen_or_throw(ft.c_str(), "rb");
        stlsoft::scoped_handle<FILE*>   scoper(f, ::fclose);

        cstring_t   cs = cstring_t_DEFAULT;
        size_t      numRead;
        CSTRING_RC  rc;

        rc = cstring_readline(f, &cs, &numRead);
        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_MS_EQ("alpha", cs);

        rc = cstring_readline(f, &cs, &numRead);
        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(4u, numRead);
        TEST_MS_EQ("beta", cs);

        cstring_destroy(&cs);
    }
}

static void TEST_cstring_readline_CONSECUTIVE_EMPTY_LINES()
{
    /* consecutive empty lines */

    static char const               input[] =   "\n\n\n";
    temp_file                       ft(temp_file::EmptyOnOpen | temp_file::DeleteOnClose, input, STLSOFT_NUM_ELEMENTS(input) - 1);
    FILE* const                     f       =   fopen_or_throw(ft.c_str(), "rb");
    stlsoft::scoped_handle<FILE*>   scoper(f, ::fclose);

    cstring_t   cs = cstring_t_DEFAULT;
    size_t      numRead;
    CSTRING_RC  rc;

    { for (int i = 0; i != 3; ++i)
    {
        rc = cstring_readline(f, &cs, &numRead);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(0u, numRead);
        TEST_INT_EQ(0u, cs.len);
        TEST_MS_EQ("", cs);
    }}

    rc = cstring_readline(f, &cs, &numRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(0u, numRead);

    cstring_destroy(&cs);
}

static void TEST_cstring_readline_LONG_LINES()
{
    /* long lines at several lengths */
    static size_t const lengths[] = {
        1024u,
        4096u,
        16384u,
        65536u,
    };

    { for (size_t i = 0; i != sizeof(lengths) / sizeof(lengths[0]); ++i)
    {
        size_t const    len = lengths[i];
        std::string     line = make_filled(len, static_cast<char>('A' + static_cast<int>(i % 26)));
        std::string     bytes = line;

        bytes.push_back('\n');
        bytes.append(make_filled(len / 2u == 0 ? 1u : len / 2u, 'z'));

        write_string_bytes(TEST_FILE_NAME, bytes);

        FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        cstring_t   cs = cstring_t_DEFAULT;
        size_t      numRead;
        CSTRING_RC  rc;

        rc = cstring_readline(f, &cs, &numRead);
        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(len, numRead);
        TEST_INT_EQ(len, cs.len);
        REQUIRE(TEST_MS_EQ(line.c_str(), cs));

        rc = cstring_readline(f, &cs, &numRead);
        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(len / 2u == 0 ? 1u : len / 2u, numRead);

        cstring_destroy(&cs);
    }}
}

static void TEST_cstring_readline_MANY_SHORT_LINES()
{
    /* many short lines */
    size_t const        num_lines = 1000u;
    std::string         bytes;
    std::vector<std::string> expected;

    expected.reserve(num_lines);

    { for (size_t i = 0; i != num_lines; ++i)
    {
        char buf[32];

        snprintf(buf, sizeof(buf), "line-%04u", static_cast<unsigned>(i));

        expected.push_back(buf);
        bytes.append(buf);
        bytes.push_back('\n');
    }}

    write_string_bytes(TEST_FILE_NAME, bytes);

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_t   cs = cstring_t_DEFAULT;
    size_t      numRead;
    CSTRING_RC  rc;

    { for (size_t i = 0; i != num_lines; ++i)
    {
        rc = cstring_readline(f, &cs, &numRead);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(expected[i].size(), numRead);
        TEST_MS_EQ(expected[i].c_str(), cs);
    }}

    rc = cstring_readline(f, &cs, &numRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(0u, numRead);

    cstring_destroy(&cs);
}

static void TEST_cstring_readline_REUSE_AFTER_LONG_LINE()
{
    /* reuse one cstring_t after a long line then a short line; numRead may be NULL */
    std::string const long_line = make_filled(8192u, 'L');
    std::string       bytes = long_line;

    bytes.push_back('\n');
    bytes.append("short");

    write_string_bytes(TEST_FILE_NAME, bytes);

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_t   cs = cstring_t_DEFAULT;
    CSTRING_RC  rc;

    rc = cstring_readline(f, &cs, NULL);
    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
    TEST_INT_EQ(8192u, cs.len);
    TEST_MS_EQ(long_line.c_str(), cs);

    rc = cstring_readline(f, &cs, NULL);
    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(5u, cs.len);
    TEST_MS_EQ("short", cs);

    cstring_destroy(&cs);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

