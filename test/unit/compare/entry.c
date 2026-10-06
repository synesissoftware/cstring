/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/compare/entry.c
 *
 * Purpose: Unit-tests for cstring_equal and cstring_compare.
 *
 * Created: 6th October 2026
 * Updated: 6th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>

#include <xtests/terse-api.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_cstring_equal_AND_cstring_compare_NULL_AND_EMPTY(void);
static void TEST_cstring_equal_AND_cstring_compare_ORDER(void);
static void TEST_cstring_equal_AND_cstring_compare_EMBEDDED_NUL(void);
static void TEST_cstring_equal_IGNORES_CAPACITY_AND_FLAGS(void);


/* /////////////////////////////////////////////////////////////////////////
 * character encoding
 */

#ifdef CSTRING_USE_WIDE_STRINGS
# define CSTRING_T_(x)                                      L ## x
#else /* ? CSTRING_USE_WIDE_STRINGS */
# define CSTRING_T_(x)                                      x
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.compare", verbosity))
    {
        XTESTS_RUN_CASE(TEST_cstring_equal_AND_cstring_compare_NULL_AND_EMPTY);
        XTESTS_RUN_CASE(TEST_cstring_equal_AND_cstring_compare_ORDER);
        XTESTS_RUN_CASE(TEST_cstring_equal_AND_cstring_compare_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_cstring_equal_IGNORES_CAPACITY_AND_FLAGS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_cstring_equal_AND_cstring_compare_NULL_AND_EMPTY(void)
{
    cstring_t const empty = cstring_t_DEFAULT;
    cstring_char_t  unused;
    cstring_t       zero_len;

    unused = 0;
    zero_len.len = 0;
    zero_len.ptr = &unused;
    zero_len.capacity = 8;
    zero_len.flags = 1;

    TEST_INT_NE(0, cstring_equal(NULL, NULL));
    TEST_INT_EQ(0, cstring_compare(NULL, NULL));

    TEST_INT_NE(0, cstring_equal(NULL, &empty));
    TEST_INT_EQ(0, cstring_compare(NULL, &empty));
    TEST_INT_NE(0, cstring_equal(&empty, NULL));
    TEST_INT_EQ(0, cstring_compare(&empty, NULL));

    TEST_INT_NE(0, cstring_equal(&empty, &zero_len));
    TEST_INT_EQ(0, cstring_compare(&empty, &zero_len));

    {
        /* unequal lengths: the longer payload must not be read */
        cstring_t   shorter;
        cstring_t   longer;

        shorter.len = 0;
        shorter.ptr = NULL;
        shorter.capacity = 0;
        shorter.flags = 0;
        longer.len = 4;
        longer.ptr = (cstring_char_t*)(void*)1;
        longer.capacity = 4;
        longer.flags = 0;

        TEST_INT_EQ(0, cstring_equal(&shorter, &longer));
        TEST_INT_EQ(0, cstring_equal(&longer, &shorter));
    }
}

static void TEST_cstring_equal_AND_cstring_compare_ORDER(void)
{
    cstring_t   a;
    cstring_t   b;
    cstring_t   ab;
    CSTRING_RC  rc;

    rc = cstring_create(&a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&b, CSTRING_T_("b"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&ab, CSTRING_T_("ab"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    TEST_INT_NE(0, cstring_equal(&a, &a));
    TEST_INT_EQ(0, cstring_compare(&a, &a));

    TEST_INT_EQ(0, cstring_equal(&a, &b));
    TEST_INT_LT(0, cstring_compare(&a, &b));
    TEST_INT_GT(0, cstring_compare(&b, &a));

    TEST_INT_EQ(0, cstring_equal(&a, &ab));
    TEST_INT_LT(0, cstring_compare(&a, &ab));
    TEST_INT_GT(0, cstring_compare(&ab, &a));

    cstring_destroy(&a);
    cstring_destroy(&b);
    cstring_destroy(&ab);

#ifndef CSTRING_USE_WIDE_STRINGS

    {
        cstring_char_t const    lo[1] = { (cstring_char_t)1 };
        cstring_char_t const    hi[1] = { (cstring_char_t)(unsigned char)0xFF };
        cstring_t               low;
        cstring_t               high;

        low.len = 1;
        low.ptr = (cstring_char_t*)lo;
        low.capacity = 1;
        low.flags = 0;
        high.len = 1;
        high.ptr = (cstring_char_t*)hi;
        high.capacity = 1;
        high.flags = 0;

        /* unsigned char order: 0x01 is less than 0xFF */
        TEST_INT_EQ(0, cstring_equal(&low, &high));
        TEST_INT_LT(0, cstring_compare(&low, &high));
        TEST_INT_GT(0, cstring_compare(&high, &low));
    }
#else /* ? CSTRING_USE_WIDE_STRINGS */

    {
        /* code-unit order: U+00FF is less than U+0100 */
        cstring_char_t const    lo[1] = { (cstring_char_t)0x00FF };
        cstring_char_t const    hi[1] = { (cstring_char_t)0x0100 };
        cstring_t               low;
        cstring_t               high;

        low.len = 1;
        low.ptr = (cstring_char_t*)lo;
        low.capacity = 1;
        low.flags = 0;
        high.len = 1;
        high.ptr = (cstring_char_t*)hi;
        high.capacity = 1;
        high.flags = 0;

        TEST_INT_EQ(0, cstring_equal(&low, &high));
        TEST_INT_LT(0, cstring_compare(&low, &high));
        TEST_INT_GT(0, cstring_compare(&high, &low));
    }
#endif /* CSTRING_USE_WIDE_STRINGS */
}

static void TEST_cstring_equal_AND_cstring_compare_EMBEDDED_NUL(void)
{
    /* cstring_createLen() stops at the first NUL, so the slice is built
     * here.
     */
    cstring_char_t  a_nul_b[3];
    cstring_char_t  a_nul_c[3];
    cstring_t       left;
    cstring_t       right;

    a_nul_b[0] = CSTRING_T_('a');
    a_nul_b[1] = 0;
    a_nul_b[2] = CSTRING_T_('b');
    a_nul_c[0] = CSTRING_T_('a');
    a_nul_c[1] = 0;
    a_nul_c[2] = CSTRING_T_('c');
    left.len = 3;
    left.ptr = a_nul_b;
    left.capacity = 3;
    left.flags = 0;
    right.len = 3;
    right.ptr = a_nul_c;
    right.capacity = 3;
    right.flags = 0;

    TEST_INT_NE(0, cstring_equal(&left, &left));
    TEST_INT_EQ(0, cstring_equal(&left, &right));
    TEST_INT_LT(0, cstring_compare(&left, &right));
}

static void TEST_cstring_equal_IGNORES_CAPACITY_AND_FLAGS(void)
{
    cstring_char_t  text[2];
    cstring_t       lhs;
    cstring_t       rhs;

    text[0] = CSTRING_T_('a');
    text[1] = 0;
    lhs.len = 1;
    lhs.ptr = text;
    lhs.capacity = 1;
    lhs.flags = 0;
    rhs.len = 1;
    rhs.ptr = text;
    rhs.capacity = 40;
    rhs.flags = 7;

    TEST_INT_NE(0, cstring_equal(&lhs, &rhs));
    TEST_INT_EQ(0, cstring_compare(&lhs, &rhs));
}


/* ///////////////////////////// end of file //////////////////////////// */

