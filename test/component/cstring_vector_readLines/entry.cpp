/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/cstring_vector_readLines/entry.cpp
 *
 * Purpose: Component-tests `cstring_vector_readLines()`.
 *
 * Created: 27th September 2026
 * Updated: 4th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <cstring/cstring.vector.h>

/* /////////////////////////////////////
 * general includes
 */

#include "component_fixture.hpp"

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
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

    static void TEST_cstring_vector_readLines_CALLABILITY();
    static void TEST_cstring_vector_readLines_EMPTY_FILE();
    static void TEST_cstring_vector_readLines_SHORT_MULTILINE();
    static void TEST_cstring_vector_readLines_CRLF_AND_MIXED_EOL();
    static void TEST_cstring_vector_readLines_FINAL_EOL_AND_EMPTY_AT_EOF();
    static void TEST_cstring_vector_readLines_CONSECUTIVE_EMPTY_LINES();
    static void TEST_cstring_vector_readLines_APPEND_ONTO_EXISTING();
    static void TEST_cstring_vector_readLines_LONG_LINES();
    static void TEST_cstring_vector_readLines_MANY_SHORT_LINES();
    static void TEST_cstring_vector_readLines_EMPTY_LINE_IN_MIDDLE();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

const char TEST_FILE_NAME[] = "test.component.cstring_vector_readLines.txt";


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

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.cstring_vector_readLines", verbosity, cstring_component::setup, cstring_component::teardown, (void*)TEST_FILE_NAME))
    {
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_CALLABILITY);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_EMPTY_FILE);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_SHORT_MULTILINE);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_CRLF_AND_MIXED_EOL);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_FINAL_EOL_AND_EMPTY_AT_EOF);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_CONSECUTIVE_EMPTY_LINES);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_APPEND_ONTO_EXISTING);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_LONG_LINES);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_MANY_SHORT_LINES);
        XTESTS_RUN_CASE(TEST_cstring_vector_readLines_EMPTY_LINE_IN_MIDDLE);

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

    using namespace cstring_component;


static void TEST_cstring_vector_readLines_CALLABILITY()
{
    false && cstring_vector_readLines(stdout, NULL, NULL);

    TEST_PASSED();
}

static void TEST_cstring_vector_readLines_EMPTY_FILE()
{
    /* empty file → EOF, no lines pushed */
    write_bytes(TEST_FILE_NAME, "", 0);

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_vector_t    csv = cstring_vector_t_DEFAULT;
    size_t              numLinesRead = 99u;
    CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(0u, numLinesRead);
    TEST_INT_EQ(0u, csv.len);

    cstring_vector_destroy(&csv);
}

static void TEST_cstring_vector_readLines_SHORT_MULTILINE()
{
    /* short multi-line file ending without EOL (mirrors readline baseline) */
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

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "r");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_vector_t    csv = cstring_vector_t_DEFAULT;
    size_t              numLinesRead = 0u;
    CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(7u, numLinesRead);
    REQUIRE(TEST_INT_EQ(7u, csv.len));
    TEST_MS_EQ("", csv.ptr[0]);
    TEST_MS_EQ("abc", csv.ptr[1]);
    TEST_MS_EQ("abcdef", csv.ptr[2]);
    TEST_MS_EQ("abcdefghijkl", csv.ptr[3]);
    TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", csv.ptr[4]);
    TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", csv.ptr[5]);
    TEST_MS_EQ("xyz", csv.ptr[6]);

    cstring_vector_destroy(&csv);
}

static void TEST_cstring_vector_readLines_CRLF_AND_MIXED_EOL()
{
    /* CRLF / mixed EOL / lone CR (binary I/O) */
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

    cstring_vector_t    csv = cstring_vector_t_DEFAULT;
    size_t              numLinesRead = 0u;
    CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(6u, numLinesRead);
    REQUIRE(TEST_INT_EQ(6u, csv.len));
    TEST_MS_EQ("one", csv.ptr[0]);
    TEST_MS_EQ("two", csv.ptr[1]);
    TEST_MS_EQ("three", csv.ptr[2]);
    TEST_MS_EQ("has", csv.ptr[3]);
    TEST_MS_EQ("embed", csv.ptr[4]);
    TEST_MS_EQ("end", csv.ptr[5]);

    cstring_vector_destroy(&csv);
}

static void TEST_cstring_vector_readLines_FINAL_EOL_AND_EMPTY_AT_EOF()
{
    /* final EOL vs no final EOL; empty trailing unterminated line omitted */
    {
        write_string_bytes(TEST_FILE_NAME, std::string("a\nb\n"));

        FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        cstring_vector_t    csv = cstring_vector_t_DEFAULT;
        size_t              numLinesRead = 0u;
        CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(2u, numLinesRead);
        REQUIRE(TEST_INT_EQ(2u, csv.len));
        TEST_MS_EQ("a", csv.ptr[0]);
        TEST_MS_EQ("b", csv.ptr[1]);

        cstring_vector_destroy(&csv);
    }

    {
        write_string_bytes(TEST_FILE_NAME, std::string("a\nb"));

        FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        cstring_vector_t    csv = cstring_vector_t_DEFAULT;
        size_t              numLinesRead = 0u;
        CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(2u, numLinesRead);
        REQUIRE(TEST_INT_EQ(2u, csv.len));
        TEST_MS_EQ("a", csv.ptr[0]);
        TEST_MS_EQ("b", csv.ptr[1]);

        cstring_vector_destroy(&csv);
    }

    {
        /* "a\n" then EOF on empty → only "a" (empty-at-EOF omitted) */
        write_string_bytes(TEST_FILE_NAME, std::string("a\n"));

        FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        cstring_vector_t    csv = cstring_vector_t_DEFAULT;
        size_t              numLinesRead = 0u;
        CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(1u, numLinesRead);
        REQUIRE(TEST_INT_EQ(1u, csv.len));
        TEST_MS_EQ("a", csv.ptr[0]);

        cstring_vector_destroy(&csv);
    }

    {
        /* unterminated single line */
        write_string_bytes(TEST_FILE_NAME, std::string("xyz"));

        FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        cstring_vector_t    csv = cstring_vector_t_DEFAULT;
        size_t              numLinesRead = 0u;
        CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(1u, numLinesRead);
        REQUIRE(TEST_INT_EQ(1u, csv.len));
        TEST_MS_EQ("xyz", csv.ptr[0]);

        cstring_vector_destroy(&csv);
    }
}

static void TEST_cstring_vector_readLines_CONSECUTIVE_EMPTY_LINES()
{
    /* consecutive empty lines (SUCCESS empties are kept) */
    write_string_bytes(TEST_FILE_NAME, std::string("\n\n"));

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_vector_t    csv = cstring_vector_t_DEFAULT;
    size_t              numLinesRead = 0u;
    CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(2u, numLinesRead);
    REQUIRE(TEST_INT_EQ(2u, csv.len));
    TEST_INT_EQ(0u, csv.ptr[0].len);
    TEST_INT_EQ(0u, csv.ptr[1].len);
    TEST_MS_EQ("", csv.ptr[0]);
    TEST_MS_EQ("", csv.ptr[1]);

    cstring_vector_destroy(&csv);
}

static void TEST_cstring_vector_readLines_APPEND_ONTO_EXISTING()
{
    /* append onto a non-empty vector; numLinesRead may be NULL */
    write_string_bytes(TEST_FILE_NAME, std::string("new-one\nnew-two\n"));

    cstring_t prior = cstring_t_DEFAULT;

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, cstring_create(&prior, "prior")));

    cstring_vector_t csv = cstring_vector_t_DEFAULT;

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, cstring_vector_append(&csv, &prior, 1)));

    cstring_destroy(&prior);

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    CSTRING_RC rc = cstring_vector_readLines(f, &csv, NULL);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    REQUIRE(TEST_INT_EQ(3u, csv.len));
    TEST_MS_EQ("prior", csv.ptr[0]);
    TEST_MS_EQ("new-one", csv.ptr[1]);
    TEST_MS_EQ("new-two", csv.ptr[2]);

    cstring_vector_destroy(&csv);
}

static void TEST_cstring_vector_readLines_LONG_LINES()
{
    /* long lines */
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
        bytes.append("tail");

        write_string_bytes(TEST_FILE_NAME, bytes);

        FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

        stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

        cstring_vector_t    csv = cstring_vector_t_DEFAULT;
        size_t              numLinesRead = 0u;
        CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

        REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
        TEST_INT_EQ(2u, numLinesRead);
        REQUIRE(TEST_INT_EQ(2u, csv.len));
        TEST_INT_EQ(len, csv.ptr[0].len);
        TEST_MS_EQ(line.c_str(), csv.ptr[0]);
        TEST_MS_EQ("tail", csv.ptr[1]);

        cstring_vector_destroy(&csv);
    }}
}

static void TEST_cstring_vector_readLines_MANY_SHORT_LINES()
{
    /* many short lines */
    size_t const                num_lines = 1000u;
    std::string                 bytes;
    std::vector<std::string>    expected;

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

    cstring_vector_t    csv = cstring_vector_t_DEFAULT;
    size_t              numLinesRead = 0u;
    CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(num_lines, numLinesRead);
    REQUIRE(TEST_INT_EQ(num_lines, csv.len));

    { for (size_t i = 0; i != num_lines; ++i)
    {
        TEST_MS_EQ(expected[i].c_str(), csv.ptr[i]);
    }}

    cstring_vector_destroy(&csv);
}

static void TEST_cstring_vector_readLines_EMPTY_LINE_IN_MIDDLE()
{
    /* empty lines in the middle */
    write_string_bytes(TEST_FILE_NAME, std::string("top\n\nbottom\n"));

    FILE* f = fopen_or_throw(TEST_FILE_NAME, "rb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    cstring_vector_t    csv = cstring_vector_t_DEFAULT;
    size_t              numLinesRead = 0u;
    CSTRING_RC          rc = cstring_vector_readLines(f, &csv, &numLinesRead);

    REQUIRE(TEST_ENUM_EQ(CSTRING_RC_EOF, rc));
    TEST_INT_EQ(3u, numLinesRead);
    REQUIRE(TEST_INT_EQ(3u, csv.len));
    TEST_MS_EQ("top", csv.ptr[0]);
    TEST_MS_EQ("", csv.ptr[1]);
    TEST_MS_EQ("bottom", csv.ptr[2]);

    cstring_vector_destroy(&csv);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

