/* /////////////////////////////////////////////////////////////////////////
 * File:        test.unit.cstring.2.cpp
 *
 * Purpose:     Implementation file for the test.unit.cstring.2 project.
 *
 * Created:     4th June 2009
 * Updated:     20th February 2021
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2009-2021, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <cstring/cstring.h>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <comstl/memory/functions.h>
#include <platformstl/error/exceptions.hpp>
#include <platformstl/filesystem/file_lines.hpp>
#include <platformstl/system/system_traits.hpp>

/* Standard C header files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void test_createN(void);
    static void test_insert(void);
    static void test_insertLen(void);
    static void test_replace(void);
    static void test_replaceLen(void);
    static void test_replaceAll_1(void);
    static void test_replaceAll_2(void);
    static void test_replaceAll_3(void);

} // anonymous namespace

/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

const char TEST_FILE_NAME[] = "test.unit.cstring.2.txt";

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

    if (XTESTS_START_RUNNER("test.unit.cstring.2", verbosity))
    {
        XTESTS_RUN_CASE(test_createN);
        XTESTS_RUN_CASE(test_insert);
        XTESTS_RUN_CASE(test_insertLen);
        XTESTS_RUN_CASE(test_replace);
        XTESTS_RUN_CASE(test_replaceLen);
        XTESTS_RUN_CASE(test_replaceAll_1);
        XTESTS_RUN_CASE(test_replaceAll_2);
        XTESTS_RUN_CASE(test_replaceAll_3);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    STLSOFT_SUPPRESS_UNUSED(TEST_FILE_NAME);

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

    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

static void test_createN()
{
    { for (size_t volatile i = 0; i != 1000000u; i = (0u == i) ? 1u : i * 10u)
    {
        cstring_t str;

        CSTRING_RC rc = cstring_createN(&str, '~', i);

        if (CSTRING_RC_SUCCESS == rc)
        {
            XTESTS_TEST_INTEGER_EQUAL(size_t(i), str.len);
            XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
            XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);

            XTESTS_TEST_POINTER_EQUAL(NULL, strpbrk(str.ptr, "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890,<.>/?'\";:[{]}`!@#$%^&*()-_=+\\|"));

            cstring_destroy(&str);

            XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
            XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
            XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
            XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        }
        else
        {
            XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_OUTOFMEMORY, rc);
        }
    }}
}

static void test_insert()
{
    { // Forwards

        cstring_t str = cstring_t_DEFAULT;

        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            const char  sz[2] = { alphabet[i], '\0' };
            cstring_insert(&str, int(i), sz);

            XTESTS_TEST_MULTIBYTE_STRING_EQUAL_N(alphabet, str.ptr, int(i));
        }}

        cstring_destroy(&str);

        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
    }

    { // Backwards

        cstring_t str = cstring_t_DEFAULT;

        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            const char  sz[2] = { alphabet[(STLSOFT_NUM_ELEMENTS(alphabet) - 1) - (1 + i)], '\0' };
            cstring_insert(&str, 0, sz);

            XTESTS_TEST_MULTIBYTE_STRING_EQUAL_N(alphabet + ((STLSOFT_NUM_ELEMENTS(alphabet) - 1) - (1 + i)), static_cast<char const*>(str.ptr), int(i));
        }}

        cstring_destroy(&str);

        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
    }
}

static void test_insertLen()
{
    cstring_t   str = cstring_t_DEFAULT;

    cstring_insertLen(&str, -1, "abc", 3);

    XTESTS_TEST_INTEGER_EQUAL(3u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", str.ptr);

    cstring_insertLen(&str, 3, "jkl", 3);

    XTESTS_TEST_INTEGER_EQUAL(6u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcjkl", str.ptr);

    cstring_insertLen(&str, -4, "ghi", 3);

    XTESTS_TEST_INTEGER_EQUAL(9u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcghijkl", str.ptr);

    cstring_insertLen(&str, 3, "def", 3);

    XTESTS_TEST_INTEGER_EQUAL(12u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijkl", str.ptr);

    cstring_insertLen(&str, -1, "m", 1);

    XTESTS_TEST_INTEGER_EQUAL(13u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklm", str.ptr);

    cstring_insertLen(&str, CSTRING_FROM_END(str.len), "[", 1);

    XTESTS_TEST_INTEGER_EQUAL(14u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("[abcdefghijklm", str.ptr);

    cstring_insertLen(&str, CSTRING_FROM_END(0), "]", 1);

    XTESTS_TEST_INTEGER_EQUAL(15u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("[abcdefghijklm]", str.ptr);

    { for (size_t i = 0; i != 13; ++i)
    {
        const char ch = (char)('z' - i);
        cstring_insertLen(&str, CSTRING_FROM_END(1 + i), &ch, 1);
    }}

    XTESTS_TEST_INTEGER_EQUAL(28u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("[abcdefghijklmnopqrstuvwxyz]", str.ptr);

    cstring_destroy(&str);

    XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
    XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
    XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
}

static void test_replace()
{
    cstring_t   str = cstring_t_DEFAULT;

    XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
    XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);

    cstring_replace(&str, 0, 0, "abcdefghijklmnopqrstuvwxyz");

    XTESTS_TEST_INTEGER_EQUAL(26u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklmnopqrstuvwxyz", str.ptr);

    cstring_replace(&str, 0, 26, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    XTESTS_TEST_INTEGER_EQUAL(26u, str.len);
    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("ABCDEFGHIJKLMNOPQRSTUVWXYZ", str.ptr);

    cstring_destroy(&str);

    XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
    XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
    XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
    XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
}

static void test_replaceLen()
{
    cstring_t   str;
    CSTRING_RC  rc = cstring_create(&str, "abcdefghijklmnopqrstuvwxyz");

    if (CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create string", cstring_error(rc));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(26u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklmnopqrstuvwxyz", str.ptr);

        { for (size_t i = 0; i != str.len; ++i)
        {
            char ch = static_cast<char>(toupper(str.ptr[i]));

            cstring_replaceLen(&str, int(i), 1u, &ch, 1u);
        }}

        XTESTS_TEST_INTEGER_EQUAL(26u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("ABCDEFGHIJKLMNOPQRSTUVWXYZ", str.ptr);

        cstring_destroy(&str);

        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
    }
}

static void test_replaceAll_1()
{
    {
        cstring_t   str = cstring_t_DEFAULT;
        CSTRING_RC  rc;
        size_t      n;

        rc = cstring_replaceAll(&str, NULL, NULL, NULL);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);

        rc = cstring_replaceAll(&str, NULL, NULL, &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "abc", "def", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        cstring_destroy(&str);

        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
    }
}

static void test_replaceAll_2()
{
    {
        cstring_t   str;
        CSTRING_RC  rc = cstring_create(&str, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
        size_t      n;

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));

        rc = cstring_replaceAll(&str, NULL, NULL, NULL);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(52u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(52u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);

        rc = cstring_replaceAll(&str, NULL, NULL, &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(52u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(52u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "abc", "def", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(52u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("defdefghijklmnopqrstuvwxyzdefdefghijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(52u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        cstring_destroy(&str);

        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
    }
}

static void test_replaceAll_3()
{
    {
        cstring_t   str;
        CSTRING_RC  rc = cstring_create(&str, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
        size_t      n;

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));

        rc = cstring_replaceAll(&str, NULL, NULL, NULL);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(52u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(52u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);

        rc = cstring_replaceAll(&str, NULL, NULL, &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(52u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(52u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "abc", "de", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(50u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("dedefghijklmnopqrstuvwxyzdedefghijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(50u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "de", "g", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(46u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("ggfghijklmnopqrstuvwxyzggfghijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(46u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "fg", "", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(42u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("gghijklmnopqrstuvwxyzgghijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(42u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "g", "", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(38u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("hijklmnopqrstuvwxyzhijklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(38u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "xyzhij", "", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(32u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("hijklmnopqrstuvwklmnopqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(32u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "mno", "MNO", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(32u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("hijklMNOpqrstuvwklMNOpqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(32u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "MNO", "<<mno>>", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(40u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("hijkl<<mno>>pqrstuvwkl<<mno>>pqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(40u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, ">>", ">>>", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(42u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("hijkl<<mno>>>pqrstuvwkl<<mno>>>pqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(42u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "<<", "<<  <<", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(50u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("hijkl<<  <<mno>>>pqrstuvwkl<<  <<mno>>>pqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(50u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "hijkl<<  <<mno>>>", NULL, &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(33u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("pqrstuvwkl<<  <<mno>>>pqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(33u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "<<  <<mno>>>", NULL, &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(21u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("pqrstuvwklpqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(21u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        rc = cstring_replaceAll(&str, "kl", "xyz", &n);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        XTESTS_TEST_INTEGER_EQUAL(22u, str.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("pqrstuvwxyzpqrstuvwxyz", str.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(22u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, n);

        { for (size_t i = 0; 0 != str.len; ++i)
        {
            const char sz[2] = { str.ptr[0], '\0' };

            rc = cstring_replaceAll(&str, sz, NULL, &n);

            XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
            XTESTS_TEST_INTEGER_EQUAL(22u - 2 * (1 + i), str.len);
            XTESTS_TEST_POINTER_NOT_EQUAL(NULL, str.ptr);
//          XTESTS_TEST_MULTIBYTE_STRING_EQUAL("pqrstuvwklpqrstuvwxyz", str.ptr);
            XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(str.len, str.capacity);
            XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
            XTESTS_TEST_INTEGER_EQUAL(0u, n);
        }}

        cstring_destroy(&str);

        XTESTS_TEST_INTEGER_EQUAL(0u, str.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, str.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0u, str.capacity);
        XTESTS_TEST_INTEGER_EQUAL(0, str.flags);
    }
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
