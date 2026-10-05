/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/insert-replace/entry.c
 *
 * Purpose: Unit-tests for cstring insert and replace functionality.
 *
 * Created: 4th June 2009
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

#include "../../cstring_testing.h"

#ifdef XTESTS_HAS_SHWILD
 /* shwild header files */
# include <shwild/shwild.h>
#endif /* XTESTS_HAS_SHWILD */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_cstring_createN(void);
static void TEST_cstring_insert(void);
static void TEST_cstring_insertLen(void);
static void TEST_cstring_replace(void);
static void TEST_cstring_replaceLen(void);
static void TEST_cstring_replaceAll_EMPTY(void);
static void TEST_cstring_replaceAll_SAME_LENGTH(void);
static void TEST_cstring_replaceAll_CHAINED(void);


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

static cstring_char_t const alphabet[] = CSTRING_T_("abcdefghijklmnopqrstuvwxyz");


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

    if (XTESTS_START_RUNNER("test.unit.insert-replace", verbosity))
    {
        XTESTS_RUN_CASE(TEST_cstring_createN);
        XTESTS_RUN_CASE(TEST_cstring_insert);
        XTESTS_RUN_CASE(TEST_cstring_insertLen);
        XTESTS_RUN_CASE(TEST_cstring_replace);
        XTESTS_RUN_CASE(TEST_cstring_replaceLen);
        XTESTS_RUN_CASE(TEST_cstring_replaceAll_EMPTY);
        XTESTS_RUN_CASE(TEST_cstring_replaceAll_SAME_LENGTH);
        XTESTS_RUN_CASE(TEST_cstring_replaceAll_CHAINED);

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


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_cstring_createN(void)
{
    { for (size_t volatile i = 0; i != 1000000u; i = (0u == i) ? 1u : i * 10u)
    {
        cstring_t str;

        CSTRING_RC rc = cstring_createN(&str, CSTRING_T_('~'), i);

        if (CSTRING_RC_SUCCESS == rc)
        {
            TEST_INT_EQ((size_t)i, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_INT_GE(str.len, str.capacity);

#if defined(XTESTS_HAS_SHWILD) && !defined(CSTRING_USE_WIDE_STRINGS)

            /* created string must be entirely '~' */
            TEST_MS_DOES_NOT_MATCH("*[a-zA-Z0-9]*", str.ptr);
            TEST_MS_DOES_NOT_MATCH("*[ ,.<>/?'\";:[{]}`!@#$%^&*()=_+\\\\|-]*", str.ptr);
#else /* ? shwild && !wide */

            TEST_PTR_EQ(NULL, cstring_testing_strpbrk_(str.ptr, CSTRING_T_("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890,<.>/?'\";:[{]}`!@#$%^&*()-_=+\\|")));
#endif /* shwild && !wide */

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
        else
        {
            TEST_ENUM_EQ(CSTRING_RC_OUTOFMEMORY, rc);
        }
    }}
}

static void TEST_cstring_insert(void)
{
    { /* Forwards */

        cstring_t str = cstring_t_DEFAULT;

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_GE(str.len, str.capacity);

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            cstring_char_t const sz[2] = { alphabet[i], '\0' };
            cstring_insert(&str, (int)i, sz);

            TEST_STR_EQ_N_(alphabet, str.ptr, (int)i);
        }}

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }

    { /* Backwards */

        cstring_t str = cstring_t_DEFAULT;

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_GE(str.len, str.capacity);

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            cstring_char_t const sz[2] = { alphabet[(STLSOFT_NUM_ELEMENTS(alphabet) - 1) - (1 + i)], '\0' };
            cstring_insert(&str, 0, sz);

            TEST_STR_EQ_N_(alphabet + ((STLSOFT_NUM_ELEMENTS(alphabet) - 1) - (1 + i)), str.ptr, (int)i);
        }}

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }
}

static void TEST_cstring_insertLen(void)
{
    cstring_t   str = cstring_t_DEFAULT;

    cstring_insertLen(&str, -1, CSTRING_T_("abc"), 3);

    TEST_INT_EQ(3u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("abc"), str.ptr);

    cstring_insertLen(&str, 3, CSTRING_T_("jkl"), 3);

    TEST_INT_EQ(6u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("abcjkl"), str.ptr);

    cstring_insertLen(&str, -4, CSTRING_T_("ghi"), 3);

    TEST_INT_EQ(9u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("abcghijkl"), str.ptr);

    cstring_insertLen(&str, 3, CSTRING_T_("def"), 3);

    TEST_INT_EQ(12u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("abcdefghijkl"), str.ptr);

    cstring_insertLen(&str, -1, CSTRING_T_("m"), 1);

    TEST_INT_EQ(13u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("abcdefghijklm"), str.ptr);

    cstring_insertLen(&str, CSTRING_FROM_END(str.len), CSTRING_T_("["), 1);

    TEST_INT_EQ(14u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("[abcdefghijklm"), str.ptr);

    cstring_insertLen(&str, CSTRING_FROM_END(0), CSTRING_T_("]"), 1);

    TEST_INT_EQ(15u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("[abcdefghijklm]"), str.ptr);

    { for (size_t i = 0; i != 13; ++i)
    {
        cstring_char_t const ch = (cstring_char_t)(CSTRING_T_('z') - (int)i);
        cstring_insertLen(&str, CSTRING_FROM_END(1 + i), &ch, 1);
    }}

    TEST_INT_EQ(28u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("[abcdefghijklmnopqrstuvwxyz]"), str.ptr);

    cstring_destroy(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_EQ(0, str.flags);
}

static void TEST_cstring_replace(void)
{
    cstring_t   str = cstring_t_DEFAULT;

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);

    cstring_replace(&str, 0, 0, CSTRING_T_("abcdefghijklmnopqrstuvwxyz"));

    TEST_INT_EQ(26u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("abcdefghijklmnopqrstuvwxyz"), str.ptr);

    cstring_replace(&str, 0, 26, CSTRING_T_("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));

    TEST_INT_EQ(26u, str.len);
    TEST_PTR_NE(NULL, str.ptr);
    TEST_INT_GE(str.len, str.capacity);
    TEST_STR_EQ_(CSTRING_T_("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), str.ptr);

    cstring_destroy(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_EQ(0, str.flags);
}

static void TEST_cstring_replaceLen(void)
{
    cstring_t   str;
    CSTRING_RC  rc = cstring_create(&str, CSTRING_T_("abcdefghijklmnopqrstuvwxyz"));

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_FAIL_WITH_QUALIFIER("could not create string", cstring_getStatusCodeString(rc));
    }
    else
    {
        TEST_INT_EQ(26u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_INT_GE(str.len, str.capacity);
        TEST_STR_EQ_(CSTRING_T_("abcdefghijklmnopqrstuvwxyz"), str.ptr);

        { for (size_t i = 0; i != str.len; ++i)
        {
            cstring_char_t ch = (cstring_char_t)toupper((unsigned char)str.ptr[i]);

            cstring_replaceLen(&str, (int)i, 1u, &ch, 1u);
        }}

        TEST_INT_EQ(26u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_INT_GE(str.len, str.capacity);
        TEST_STR_EQ_(CSTRING_T_("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), str.ptr);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }
}

static void TEST_cstring_replaceAll_EMPTY(void)
{
    {
        cstring_t   str = cstring_t_DEFAULT;
        CSTRING_RC  rc;
        size_t      n;

        rc = cstring_replaceAll(&str, NULL, NULL, NULL);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        rc = cstring_replaceAll(&str, NULL, NULL, &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("abc"), CSTRING_T_("def"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }
}

static void TEST_cstring_replaceAll_SAME_LENGTH(void)
{
    {
        cstring_t   str;
        CSTRING_RC  rc = cstring_create(&str, CSTRING_T_("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"));
        size_t      n;

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));

        rc = cstring_replaceAll(&str, NULL, NULL, NULL);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(52u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(52u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        rc = cstring_replaceAll(&str, NULL, NULL, &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(52u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(52u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("abc"), CSTRING_T_("def"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(52u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("defdefghijklmnopqrstuvwxyzdefdefghijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(52u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }
}

static void TEST_cstring_replaceAll_CHAINED(void)
{
    {
        cstring_t   str;
        CSTRING_RC  rc = cstring_create(&str, CSTRING_T_("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"));
        size_t      n;

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));

        rc = cstring_replaceAll(&str, NULL, NULL, NULL);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(52u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(52u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        rc = cstring_replaceAll(&str, NULL, NULL, &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(52u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(52u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("abc"), CSTRING_T_("de"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(50u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("dedefghijklmnopqrstuvwxyzdedefghijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(50u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("de"), CSTRING_T_("g"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(46u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("ggfghijklmnopqrstuvwxyzggfghijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(46u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("fg"), CSTRING_T_(""), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(42u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("gghijklmnopqrstuvwxyzgghijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(42u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("g"), CSTRING_T_(""), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(38u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("hijklmnopqrstuvwxyzhijklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(38u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("xyzhij"), CSTRING_T_(""), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(32u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("hijklmnopqrstuvwklmnopqrstuvwxyz"), str.ptr);
        TEST_INT_GE(32u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("mno"), CSTRING_T_("MNO"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(32u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("hijklMNOpqrstuvwklMNOpqrstuvwxyz"), str.ptr);
        TEST_INT_GE(32u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("MNO"), CSTRING_T_("<<mno>>"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(40u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("hijkl<<mno>>pqrstuvwkl<<mno>>pqrstuvwxyz"), str.ptr);
        TEST_INT_GE(40u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_(">>"), CSTRING_T_(">>>"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(42u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("hijkl<<mno>>>pqrstuvwkl<<mno>>>pqrstuvwxyz"), str.ptr);
        TEST_INT_GE(42u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("<<"), CSTRING_T_("<<  <<"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(50u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("hijkl<<  <<mno>>>pqrstuvwkl<<  <<mno>>>pqrstuvwxyz"), str.ptr);
        TEST_INT_GE(50u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("hijkl<<  <<mno>>>"), NULL, &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(33u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("pqrstuvwkl<<  <<mno>>>pqrstuvwxyz"), str.ptr);
        TEST_INT_GE(33u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("<<  <<mno>>>"), NULL, &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(21u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("pqrstuvwklpqrstuvwxyz"), str.ptr);
        TEST_INT_GE(21u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        rc = cstring_replaceAll(&str, CSTRING_T_("kl"), CSTRING_T_("xyz"), &n);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(22u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(CSTRING_T_("pqrstuvwxyzpqrstuvwxyz"), str.ptr);
        TEST_INT_GE(22u, str.capacity);
        TEST_INT_EQ(0, str.flags);
        TEST_INT_EQ(0u, n);

        { for (size_t i = 0; 0 != str.len; ++i)
        {
            cstring_char_t const sz[2] = { str.ptr[0], '\0' };

            rc = cstring_replaceAll(&str, sz, NULL, &n);

            XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
            TEST_INT_EQ(22u - 2 * (1 + i), str.len);
            TEST_PTR_NE(NULL, str.ptr);
/*          TEST_STR_EQ_(CSTRING_T_("pqrstuvwklpqrstuvwxyz"), str.ptr); */
            TEST_INT_GE(str.len, str.capacity);
            TEST_INT_EQ(0, str.flags);
            TEST_INT_EQ(0u, n);
        }}

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }
}


/* ///////////////////////////// end of file //////////////////////////// */
