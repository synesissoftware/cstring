/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/hash/entry.c
 *
 * Purpose: Unit-tests for the cstring hashing API.
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
 * forward declarations
 */

static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_NULL_AND_EMPTY(void);
static void TEST_cstring_hash_fnv1a_KNOWN_VECTORS(void);
static void TEST_cstring_hash_djb2_KNOWN_VECTORS(void);
static void TEST_cstring_hash_djb2_ci_AND_cstring_hash_fnv1a_ci(void);
static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_SINGLE_CHARACTER(void);
static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_LONG_STRING(void);
static void TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_SLICES(void);


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

    if (XTESTS_START_RUNNER("test.unit.hash", verbosity))
    {
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_NULL_AND_EMPTY);
        XTESTS_RUN_CASE(TEST_cstring_hash_fnv1a_KNOWN_VECTORS);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_KNOWN_VECTORS);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_ci_AND_cstring_hash_fnv1a_ci);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_SINGLE_CHARACTER);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_LONG_STRING);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_SLICES);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_NULL_AND_EMPTY(void)
{
    struct cstring_t const* pcs_null = NULL;
    cstring_t               null_cs = { 0, NULL, 0, 0 };
    cstring_t               default_cs = cstring_t_DEFAULT;
    cstring_t               created_empty;
    CSTRING_RC              rc;

    rc = cstring_create(&created_empty, CSTRING_T_(""));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    /* djb2: initial seed is 5381 */
    TEST_INT_EQ(5381ULL, cstring_hash_djb2(pcs_null));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_ci(pcs_null));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2(&null_cs));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_ci(&null_cs));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2(&default_cs));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_ci(&default_cs));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2(&created_empty));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_ci(&created_empty));

    TEST_INT_EQ(5381ULL, cstring_hash_djb2_len(NULL, 0));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_len_ci(NULL, 0));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_len(NULL, 10));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_len_ci(NULL, 10));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_len(CSTRING_T_(""), 0));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_len_ci(CSTRING_T_(""), 0));

    /* FNV-1a: offset basis is 0xcbf29ce484222325ULL */
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a(pcs_null));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_ci(pcs_null));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a(&null_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_ci(&null_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a(&default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_ci(&default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a(&created_empty));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_ci(&created_empty));

    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_len(NULL, 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_len_ci(NULL, 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_len(NULL, 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_len_ci(NULL, 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_len(CSTRING_T_(""), 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_len_ci(CSTRING_T_(""), 0));

    cstring_destroy(&created_empty);
}

static void TEST_cstring_hash_fnv1a_KNOWN_VECTORS(void)
{
    /* Known FNV-1a 64-bit test vectors:
     *   ""       -> 0xcbf29ce484222325ULL
     *   "a"      -> 0xaf63dc4c8601ec8cULL
     *   "foobar" -> 0x85944171f73967e8ULL
     */
    cstring_t   cs_a;
    cstring_t   cs_foobar;
    CSTRING_RC  rc;

    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_len(CSTRING_T_(""), 0));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a_len(CSTRING_T_("a"), 1));
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a_len(CSTRING_T_("foobar"), 6));

    rc = cstring_create(&cs_a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a(&cs_a));
    cstring_destroy(&cs_a);

    rc = cstring_create(&cs_foobar, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a(&cs_foobar));
    cstring_destroy(&cs_foobar);
}

static void TEST_cstring_hash_djb2_KNOWN_VECTORS(void)
{
    /* Known djb2 test vectors:
     *   ""       -> 5381ULL
     *   "a"      -> 5381 * 33 + 97 = 177670ULL (0x2b606ULL)
     *   "foobar" -> 6953516687550ULL (0x652fde460beULL)
     */
    cstring_t   cs_a;
    cstring_t   cs_foobar;
    CSTRING_RC  rc;

    TEST_INT_EQ(5381ULL, cstring_hash_djb2_len(CSTRING_T_(""), 0));
    TEST_INT_EQ(177670ULL, cstring_hash_djb2_len(CSTRING_T_("a"), 1));
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2_len(CSTRING_T_("foobar"), 6));

    rc = cstring_create(&cs_a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(177670ULL, cstring_hash_djb2(&cs_a));
    cstring_destroy(&cs_a);

    rc = cstring_create(&cs_foobar, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2(&cs_foobar));
    cstring_destroy(&cs_foobar);
}

static void TEST_cstring_hash_djb2_ci_AND_cstring_hash_fnv1a_ci(void)
{
    cstring_hash_t  djb2_ci_base;
    cstring_hash_t  fnv1a_ci_base;
    cstring_t       cs1;
    cstring_t       cs2;
    cstring_t       cs3;
    cstring_t       cs4;
    CSTRING_RC      rc;

    /* Buffer checks */
    djb2_ci_base = cstring_hash_djb2_len_ci(CSTRING_T_("Test"), 4);
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_len_ci(CSTRING_T_("tEst"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_len_ci(CSTRING_T_("TEST"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_len_ci(CSTRING_T_("test"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_len_ci(CSTRING_T_("teSt"), 4));

    fnv1a_ci_base = cstring_hash_fnv1a_len_ci(CSTRING_T_("Test"), 4);
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_len_ci(CSTRING_T_("tEst"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_len_ci(CSTRING_T_("TEST"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_len_ci(CSTRING_T_("test"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_len_ci(CSTRING_T_("teSt"), 4));

    /* Case-sensitive inequality */
    TEST_INT_NE(cstring_hash_djb2_len(CSTRING_T_("Test"), 4), cstring_hash_djb2_len(CSTRING_T_("tEst"), 4));
    TEST_INT_NE(cstring_hash_fnv1a_len(CSTRING_T_("Test"), 4), cstring_hash_fnv1a_len(CSTRING_T_("tEst"), 4));

    /* Instance checks */
    rc = cstring_create(&cs1, CSTRING_T_("Test"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&cs2, CSTRING_T_("tEst"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&cs3, CSTRING_T_("TEST"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&cs4, CSTRING_T_("test"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    TEST_INT_EQ(cstring_hash_djb2_ci(&cs1), cstring_hash_djb2_ci(&cs2));
    TEST_INT_EQ(cstring_hash_djb2_ci(&cs1), cstring_hash_djb2_ci(&cs3));
    TEST_INT_EQ(cstring_hash_djb2_ci(&cs1), cstring_hash_djb2_ci(&cs4));

    TEST_INT_EQ(cstring_hash_fnv1a_ci(&cs1), cstring_hash_fnv1a_ci(&cs2));
    TEST_INT_EQ(cstring_hash_fnv1a_ci(&cs1), cstring_hash_fnv1a_ci(&cs3));
    TEST_INT_EQ(cstring_hash_fnv1a_ci(&cs1), cstring_hash_fnv1a_ci(&cs4));

    TEST_INT_NE(cstring_hash_djb2(&cs1), cstring_hash_djb2(&cs2));
    TEST_INT_NE(cstring_hash_fnv1a(&cs1), cstring_hash_fnv1a(&cs2));

    cstring_destroy(&cs1);
    cstring_destroy(&cs2);
    cstring_destroy(&cs3);
    cstring_destroy(&cs4);
}

static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_SINGLE_CHARACTER(void)
{
    /* Letters */
    TEST_INT_EQ(cstring_hash_djb2_len_ci(CSTRING_T_("a"), 1), cstring_hash_djb2_len_ci(CSTRING_T_("A"), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_len_ci(CSTRING_T_("a"), 1), cstring_hash_fnv1a_len_ci(CSTRING_T_("A"), 1));
    TEST_INT_NE(cstring_hash_djb2_len(CSTRING_T_("a"), 1), cstring_hash_djb2_len(CSTRING_T_("A"), 1));
    TEST_INT_NE(cstring_hash_fnv1a_len(CSTRING_T_("a"), 1), cstring_hash_fnv1a_len(CSTRING_T_("A"), 1));

    TEST_INT_EQ(cstring_hash_djb2_len_ci(CSTRING_T_("z"), 1), cstring_hash_djb2_len_ci(CSTRING_T_("Z"), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_len_ci(CSTRING_T_("z"), 1), cstring_hash_fnv1a_len_ci(CSTRING_T_("Z"), 1));
    TEST_INT_NE(cstring_hash_djb2_len(CSTRING_T_("z"), 1), cstring_hash_djb2_len(CSTRING_T_("Z"), 1));
    TEST_INT_NE(cstring_hash_fnv1a_len(CSTRING_T_("z"), 1), cstring_hash_fnv1a_len(CSTRING_T_("Z"), 1));

    /* Non-letters have identical case-sensitive and case-insensitive hashes */
    TEST_INT_EQ(cstring_hash_djb2_len(CSTRING_T_("0"), 1), cstring_hash_djb2_len_ci(CSTRING_T_("0"), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_len(CSTRING_T_("0"), 1), cstring_hash_fnv1a_len_ci(CSTRING_T_("0"), 1));

    TEST_INT_EQ(cstring_hash_djb2_len(CSTRING_T_("!"), 1), cstring_hash_djb2_len_ci(CSTRING_T_("!"), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_len(CSTRING_T_("!"), 1), cstring_hash_fnv1a_len_ci(CSTRING_T_("!"), 1));

    TEST_INT_EQ(cstring_hash_djb2_len(CSTRING_T_(" "), 1), cstring_hash_djb2_len_ci(CSTRING_T_(" "), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_len(CSTRING_T_(" "), 1), cstring_hash_fnv1a_len_ci(CSTRING_T_(" "), 1));
}

static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_LONG_STRING(void)
{
    cstring_char_t  long_pattern_mixed[1025];
    cstring_char_t  long_pattern_lower[1025];
    size_t const    pattern_len = 1024;
    size_t          i;
    cstring_t       cs_mixed;
    cstring_t       cs_lower;
    CSTRING_RC      rc;

    for (i = 0; i < pattern_len; ++i)
    {
        int const m = (int)(i % 52);

        if (m < 26)
        {
            long_pattern_mixed[i] = (cstring_char_t)(CSTRING_T_('A') + m);
            long_pattern_lower[i] = (cstring_char_t)(CSTRING_T_('a') + m);
        }
        else
        {
            long_pattern_mixed[i] = (cstring_char_t)(CSTRING_T_('a') + (m - 26));
            long_pattern_lower[i] = (cstring_char_t)(CSTRING_T_('a') + (m - 26));
        }
    }
    long_pattern_mixed[pattern_len] = 0;
    long_pattern_lower[pattern_len] = 0;

    rc = cstring_createLen(&cs_mixed, long_pattern_mixed, pattern_len);
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_createLen(&cs_lower, long_pattern_lower, pattern_len);
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    /* Verify consistency between struct and buffer APIs */
    TEST_INT_EQ(cstring_hash_djb2(&cs_mixed), cstring_hash_djb2_len(cs_mixed.ptr, cs_mixed.len));
    TEST_INT_EQ(cstring_hash_djb2_ci(&cs_mixed), cstring_hash_djb2_len_ci(cs_mixed.ptr, cs_mixed.len));
    TEST_INT_EQ(cstring_hash_fnv1a(&cs_mixed), cstring_hash_fnv1a_len(cs_mixed.ptr, cs_mixed.len));
    TEST_INT_EQ(cstring_hash_fnv1a_ci(&cs_mixed), cstring_hash_fnv1a_len_ci(cs_mixed.ptr, cs_mixed.len));

    /* Case-insensitive hashes must match */
    TEST_INT_EQ(cstring_hash_djb2_ci(&cs_mixed), cstring_hash_djb2_ci(&cs_lower));
    TEST_INT_EQ(cstring_hash_fnv1a_ci(&cs_mixed), cstring_hash_fnv1a_ci(&cs_lower));

    /* Case-sensitive hashes must not match */
    TEST_INT_NE(cstring_hash_djb2(&cs_mixed), cstring_hash_djb2(&cs_lower));
    TEST_INT_NE(cstring_hash_fnv1a(&cs_mixed), cstring_hash_fnv1a(&cs_lower));

    cstring_destroy(&cs_mixed);
    cstring_destroy(&cs_lower);
}

static void TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_SLICES(void)
{
    cstring_char_t const    text[] = CSTRING_T_("The quick brown Fox jumps over the lazy Dog.");
    size_t const            total_len = sizeof(text) / sizeof(text[0]) - 1;
    cstring_hash_t          djb2_quick_slice;
    cstring_hash_t          djb2_quick_direct;
    cstring_hash_t          fnv1a_quick_slice;
    cstring_hash_t          fnv1a_quick_direct;
    cstring_t               cs;
    CSTRING_RC              rc;

    /* Slices without constructing cstring_t */
    /* "quick" starts at index 4, length 5 */
    djb2_quick_slice = cstring_hash_djb2_len(text + 4, 5);
    djb2_quick_direct = cstring_hash_djb2_len(CSTRING_T_("quick"), 5);
    TEST_INT_EQ(djb2_quick_direct, djb2_quick_slice);

    fnv1a_quick_slice = cstring_hash_fnv1a_len(text + 4, 5);
    fnv1a_quick_direct = cstring_hash_fnv1a_len(CSTRING_T_("quick"), 5);
    TEST_INT_EQ(fnv1a_quick_direct, fnv1a_quick_slice);

    /* "Fox" starts at index 16, length 3 */
    TEST_INT_EQ(cstring_hash_djb2_len_ci(text + 16, 3), cstring_hash_djb2_len_ci(CSTRING_T_("fox"), 3));
    TEST_INT_EQ(cstring_hash_fnv1a_len_ci(text + 16, 3), cstring_hash_fnv1a_len_ci(CSTRING_T_("fox"), 3));
    TEST_INT_NE(cstring_hash_djb2_len(text + 16, 3), cstring_hash_djb2_len(CSTRING_T_("fox"), 3));
    TEST_INT_NE(cstring_hash_fnv1a_len(text + 16, 3), cstring_hash_fnv1a_len(CSTRING_T_("fox"), 3));

    /* Hashing full text via buffer API */
    rc = cstring_createLen(&cs, text, total_len);
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(cstring_hash_djb2_len(text, total_len), cstring_hash_djb2(&cs));
    TEST_INT_EQ(cstring_hash_fnv1a_len(text, total_len), cstring_hash_fnv1a(&cs));
    cstring_destroy(&cs);
}


/* ///////////////////////////// end of file //////////////////////////// */

