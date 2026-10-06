/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/compare.cxx/entry.cpp
 *
 * Purpose: Unit-tests for cstring comparison operators.
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
#if (__cplusplus >= 201103L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
# include <unordered_map>
# define CSTRING_TEST_HAS_unordered_map_
#endif


/* /////////////////////////////////////////////////////////////////////////
 * character encoding
 */

#ifdef CSTRING_USE_WIDE_STRINGS
# define CSTRING_T_(x)                                      L ## x
#else /* ? CSTRING_USE_WIDE_STRINGS */
# define CSTRING_T_(x)                                      x
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void TEST_operator_equal_USES_cstring_equal(void);
#ifdef CSTRING_TEST_HAS_unordered_map_
    static void TEST_unordered_map_cstring_t(void);
#endif /* CSTRING_TEST_HAS_unordered_map_ */
} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.compare.cxx", verbosity))
    {
        XTESTS_RUN_CASE(TEST_operator_equal_USES_cstring_equal);
#ifdef CSTRING_TEST_HAS_unordered_map_
        XTESTS_RUN_CASE(TEST_unordered_map_cstring_t);
#endif /* CSTRING_TEST_HAS_unordered_map_ */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

static void TEST_operator_equal_USES_cstring_equal(void)
{
    cstring_t   a;
    cstring_t   b;
    CSTRING_RC  rc;

    rc = cstring_create(&a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&b, CSTRING_T_("b"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    TEST_BOOLEAN_TRUE(a == a);
    TEST_BOOLEAN_TRUE(a != b);
    TEST_BOOLEAN_TRUE(a < b);
    TEST_BOOLEAN_EQ(0 != cstring_equal(&a, &a), a == a);
    TEST_BOOLEAN_EQ(0 != cstring_equal(&a, &b), a == b);

    cstring_destroy(&a);
    cstring_destroy(&b);
}

#ifdef CSTRING_TEST_HAS_unordered_map_
static void TEST_unordered_map_cstring_t(void)
{
    cstring_char_t                          text[2];
    cstring_t                               key;
    std::unordered_map<cstring_t, int>      values;

    text[0] = CSTRING_T_('a');
    text[1] = 0;
    key.len = 1;
    key.ptr = text;
    key.capacity = 1;
    key.flags = 0;

    values[key] = 7;

    TEST_INT_EQ(1, static_cast<int>(values.size()));
    TEST_INT_EQ(7, values[key]);
}
#endif /* CSTRING_TEST_HAS_unordered_map_ */
} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

