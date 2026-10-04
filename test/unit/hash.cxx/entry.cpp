/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/hash.cxx/entry.cpp
 *
 * Purpose: Unit-tests for the C++ cstring hash access shims.
 *
 * Created: 5th September 2026
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

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


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

    static void TEST_hash_djb2_AND_hash_fnv1a_NULL_AND_EMPTY(void);
    static void TEST_hash_djb2_AND_hash_fnv1a_KNOWN_VECTORS(void);
    static void TEST_hash_djb2_AND_hash_djb2_ci_AND_hash_fnv1a_AND_hash_fnv1a_ci(void);
} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.hash.cxx", verbosity))
    {
        XTESTS_RUN_CASE(TEST_hash_djb2_AND_hash_fnv1a_NULL_AND_EMPTY);
        XTESTS_RUN_CASE(TEST_hash_djb2_AND_hash_fnv1a_KNOWN_VECTORS);
        XTESTS_RUN_CASE(TEST_hash_djb2_AND_hash_djb2_ci_AND_hash_fnv1a_AND_hash_fnv1a_ci);

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

static void TEST_hash_djb2_AND_hash_fnv1a_NULL_AND_EMPTY(void)
{
    cstring_t const default_cs = cstring_t_DEFAULT;

    TEST_INT_EQ(5381ULL, hash_djb2(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2_ci(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2(default_cs));
    TEST_INT_EQ(5381ULL, hash_djb2_ci(default_cs));
    TEST_INT_EQ(5381ULL, hash_djb2(NULL, 0));
    TEST_INT_EQ(5381ULL, hash_djb2_ci(NULL, 0));

    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_ci(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_ci(default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(NULL, 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_ci(NULL, 0));
}

static void TEST_hash_djb2_AND_hash_fnv1a_KNOWN_VECTORS(void)
{
    cstring_t   cs_a;
    cstring_t   cs_foobar;
    CSTRING_RC  rc;

    rc = cstring_create(&cs_a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(177670ULL, hash_djb2(cs_a));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, hash_fnv1a(cs_a));
    cstring_destroy(&cs_a);

    rc = cstring_create(&cs_foobar, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(6953516687550ULL, hash_djb2(cs_foobar));
    TEST_INT_EQ(0x85944171f73967e8ULL, hash_fnv1a(cs_foobar));
    cstring_destroy(&cs_foobar);
}

static void TEST_hash_djb2_AND_hash_djb2_ci_AND_hash_fnv1a_AND_hash_fnv1a_ci(void)
{
    cstring_t   cs;
    CSTRING_RC  rc = cstring_create(&cs, CSTRING_T_("Hello World"));

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    /* Overload by reference */
    TEST_INT_EQ(cstring_hash_djb2(&cs), hash_djb2(cs));
    TEST_INT_EQ(cstring_hash_djb2_ci(&cs), hash_djb2_ci(cs));
    TEST_INT_EQ(cstring_hash_fnv1a(&cs), hash_fnv1a(cs));
    TEST_INT_EQ(cstring_hash_fnv1a_ci(&cs), hash_fnv1a_ci(cs));

    /* Overload by pointer */
    TEST_INT_EQ(cstring_hash_djb2(&cs), hash_djb2(&cs));
    TEST_INT_EQ(cstring_hash_djb2_ci(&cs), hash_djb2_ci(&cs));
    TEST_INT_EQ(cstring_hash_fnv1a(&cs), hash_fnv1a(&cs));
    TEST_INT_EQ(cstring_hash_fnv1a_ci(&cs), hash_fnv1a_ci(&cs));

    /* Overload by slice/buffer */
    TEST_INT_EQ(cstring_hash_djb2_len(cs.ptr, cs.len), hash_djb2(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_djb2_len_ci(cs.ptr, cs.len), hash_djb2_ci(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_fnv1a_len(cs.ptr, cs.len), hash_fnv1a(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_fnv1a_len_ci(cs.ptr, cs.len), hash_fnv1a_ci(cs.ptr, cs.len));

    cstring_destroy(&cs);
}
} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

