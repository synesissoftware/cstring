/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/hash/entry.c
 *
 * Purpose: Unit-tests for the cstring hashing API.
 *
 * Created: 5th September 2026
 * Updated: 6th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <cstring/hash.h>

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
static void TEST_cstring_hash_sdbm_KNOWN_VECTORS(void);
static void TEST_cstring_hash_djb2_ci_AND_cstring_hash_fnv1a_case(void);
static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_SINGLE_CHARACTER(void);
static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_LONG_STRING(void);
static void TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_SLICES(void);
static void TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_OCTET_ABOVE_7F(void);
static void TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_EMBEDDED_NUL(void);
static void TEST_cstring_hash_mbs_AND_wcs_AND_mbuf_AND_wbuf(void);


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
        XTESTS_RUN_CASE(TEST_cstring_hash_sdbm_KNOWN_VECTORS);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_ci_AND_cstring_hash_fnv1a_case);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_SINGLE_CHARACTER);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_LONG_STRING);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_SLICES);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_OCTET_ABOVE_7F);
        XTESTS_RUN_CASE(TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_cstring_hash_mbs_AND_wcs_AND_mbuf_AND_wbuf);

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

    TEST_INT_EQ(5381ULL, CSTRING_HASH_DJB2_SEED);
    TEST_INT_EQ(0xcbf29ce484222325ULL, CSTRING_HASH_FNV1A_OFFSET);
    TEST_INT_EQ(0x100000001b3ULL, CSTRING_HASH_FNV1A_PRIME);
    TEST_INT_EQ(65599ULL, CSTRING_HASH_SDBM_MULTIPLIER);
    TEST_INT_EQ(0ULL, CSTRING_HASH_SDBM_SEED);

    rc = cstring_create(&created_empty, CSTRING_T_(""));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    /* djb2: initial seed is 5381 */
    TEST_INT_EQ(5381ULL, cstring_hash_djb2(pcs_null));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_case(pcs_null));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2(&null_cs));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_case(&null_cs));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2(&default_cs));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_case(&default_cs));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2(&created_empty));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_case(&created_empty));

    TEST_INT_EQ(5381ULL, cstring_hash_djb2_buf(NULL, 0));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_buf_case(NULL, 0));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_buf(NULL, 10));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_buf_case(NULL, 10));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_buf(CSTRING_T_(""), 0));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_buf_case(CSTRING_T_(""), 0));

    /* FNV-1a: offset basis is 0xcbf29ce484222325ULL */
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a(pcs_null));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_case(pcs_null));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a(&null_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_case(&null_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a(&default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_case(&default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a(&created_empty));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_case(&created_empty));

    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf(NULL, 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf_case(NULL, 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf(NULL, 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf_case(NULL, 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf(CSTRING_T_(""), 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf_case(CSTRING_T_(""), 0));

    /* SDBM: the seed, and the hash of empty input, is 0 */
    TEST_INT_EQ(0ULL, cstring_hash_sdbm(pcs_null));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_case(pcs_null));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm(&null_cs));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_case(&null_cs));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm(&default_cs));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_case(&default_cs));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm(&created_empty));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_case(&created_empty));

    TEST_INT_EQ(0ULL, cstring_hash_sdbm_buf(NULL, 0));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_buf_case(NULL, 0));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_buf(NULL, 10));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_buf_case(NULL, 10));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_buf(CSTRING_T_(""), 0));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_buf_case(CSTRING_T_(""), 0));

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

    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf(CSTRING_T_(""), 0));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a_buf(CSTRING_T_("a"), 1));
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a_buf(CSTRING_T_("foobar"), 6));

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

    TEST_INT_EQ(5381ULL, cstring_hash_djb2_buf(CSTRING_T_(""), 0));
    TEST_INT_EQ(177670ULL, cstring_hash_djb2_buf(CSTRING_T_("a"), 1));
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2_buf(CSTRING_T_("foobar"), 6));

    rc = cstring_create(&cs_a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(177670ULL, cstring_hash_djb2(&cs_a));
    cstring_destroy(&cs_a);

    rc = cstring_create(&cs_foobar, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2(&cs_foobar));
    cstring_destroy(&cs_foobar);
}

static void TEST_cstring_hash_sdbm_KNOWN_VECTORS(void)
{
    /* Known sdbm test vectors, 64-bit accumulator, seed 0:
     *   ""       -> 0ULL
     *   "a"      -> 97ULL
     *   "foobar" -> 0x430d469aa6437b0dULL
     */
    cstring_t   cs_a;
    cstring_t   cs_foobar;
    CSTRING_RC  rc;

    TEST_INT_EQ(0ULL, cstring_hash_sdbm_buf(CSTRING_T_(""), 0));
    TEST_INT_EQ(97ULL, cstring_hash_sdbm_buf(CSTRING_T_("a"), 1));
    TEST_INT_EQ(0x430d469aa6437b0dULL, cstring_hash_sdbm_buf(CSTRING_T_("foobar"), 6));

    rc = cstring_create(&cs_a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(97ULL, cstring_hash_sdbm(&cs_a));
    cstring_destroy(&cs_a);

    rc = cstring_create(&cs_foobar, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(0x430d469aa6437b0dULL, cstring_hash_sdbm(&cs_foobar));
    cstring_destroy(&cs_foobar);
}

static void TEST_cstring_hash_djb2_ci_AND_cstring_hash_fnv1a_case(void)
{
    cstring_hash_t  djb2_ci_base;
    cstring_hash_t  fnv1a_ci_base;
    cstring_hash_t  sdbm_ci_base;
    cstring_t       cs1;
    cstring_t       cs2;
    cstring_t       cs3;
    cstring_t       cs4;
    CSTRING_RC      rc;

    /* Buffer checks */
    djb2_ci_base = cstring_hash_djb2_buf_case(CSTRING_T_("Test"), 4);
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_buf_case(CSTRING_T_("tEst"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_buf_case(CSTRING_T_("TEST"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_buf_case(CSTRING_T_("test"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_buf_case(CSTRING_T_("teSt"), 4));

    fnv1a_ci_base = cstring_hash_fnv1a_buf_case(CSTRING_T_("Test"), 4);
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_buf_case(CSTRING_T_("tEst"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_buf_case(CSTRING_T_("TEST"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_buf_case(CSTRING_T_("test"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_buf_case(CSTRING_T_("teSt"), 4));

    sdbm_ci_base = cstring_hash_sdbm_buf_case(CSTRING_T_("Test"), 4);
    TEST_INT_EQ(sdbm_ci_base, cstring_hash_sdbm_buf_case(CSTRING_T_("tEst"), 4));
    TEST_INT_EQ(sdbm_ci_base, cstring_hash_sdbm_buf_case(CSTRING_T_("TEST"), 4));
    TEST_INT_EQ(sdbm_ci_base, cstring_hash_sdbm_buf_case(CSTRING_T_("test"), 4));
    TEST_INT_EQ(sdbm_ci_base, cstring_hash_sdbm_buf_case(CSTRING_T_("teSt"), 4));

    /* Case-sensitive inequality */
    TEST_INT_NE(cstring_hash_djb2_buf(CSTRING_T_("Test"), 4), cstring_hash_djb2_buf(CSTRING_T_("tEst"), 4));
    TEST_INT_NE(cstring_hash_fnv1a_buf(CSTRING_T_("Test"), 4), cstring_hash_fnv1a_buf(CSTRING_T_("tEst"), 4));
    TEST_INT_NE(cstring_hash_sdbm_buf(CSTRING_T_("Test"), 4), cstring_hash_sdbm_buf(CSTRING_T_("tEst"), 4));

    /* Instance checks */
    rc = cstring_create(&cs1, CSTRING_T_("Test"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&cs2, CSTRING_T_("tEst"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&cs3, CSTRING_T_("TEST"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    rc = cstring_create(&cs4, CSTRING_T_("test"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    TEST_INT_EQ(cstring_hash_djb2_case(&cs1), cstring_hash_djb2_case(&cs2));
    TEST_INT_EQ(cstring_hash_djb2_case(&cs1), cstring_hash_djb2_case(&cs3));
    TEST_INT_EQ(cstring_hash_djb2_case(&cs1), cstring_hash_djb2_case(&cs4));

    TEST_INT_EQ(cstring_hash_fnv1a_case(&cs1), cstring_hash_fnv1a_case(&cs2));
    TEST_INT_EQ(cstring_hash_fnv1a_case(&cs1), cstring_hash_fnv1a_case(&cs3));
    TEST_INT_EQ(cstring_hash_fnv1a_case(&cs1), cstring_hash_fnv1a_case(&cs4));

    TEST_INT_EQ(cstring_hash_sdbm_case(&cs1), cstring_hash_sdbm_case(&cs2));
    TEST_INT_EQ(cstring_hash_sdbm_case(&cs1), cstring_hash_sdbm_case(&cs3));
    TEST_INT_EQ(cstring_hash_sdbm_case(&cs1), cstring_hash_sdbm_case(&cs4));

    TEST_INT_NE(cstring_hash_djb2(&cs1), cstring_hash_djb2(&cs2));
    TEST_INT_NE(cstring_hash_fnv1a(&cs1), cstring_hash_fnv1a(&cs2));
    TEST_INT_NE(cstring_hash_sdbm(&cs1), cstring_hash_sdbm(&cs2));

    cstring_destroy(&cs1);
    cstring_destroy(&cs2);
    cstring_destroy(&cs3);
    cstring_destroy(&cs4);
}

static void TEST_cstring_hash_djb2_AND_cstring_hash_fnv1a_SINGLE_CHARACTER(void)
{
    /* Letters */
    TEST_INT_EQ(cstring_hash_djb2_buf_case(CSTRING_T_("a"), 1), cstring_hash_djb2_buf_case(CSTRING_T_("A"), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_buf_case(CSTRING_T_("a"), 1), cstring_hash_fnv1a_buf_case(CSTRING_T_("A"), 1));
    TEST_INT_EQ(cstring_hash_sdbm_buf_case(CSTRING_T_("a"), 1), cstring_hash_sdbm_buf_case(CSTRING_T_("A"), 1));
    TEST_INT_NE(cstring_hash_djb2_buf(CSTRING_T_("a"), 1), cstring_hash_djb2_buf(CSTRING_T_("A"), 1));
    TEST_INT_NE(cstring_hash_fnv1a_buf(CSTRING_T_("a"), 1), cstring_hash_fnv1a_buf(CSTRING_T_("A"), 1));
    TEST_INT_NE(cstring_hash_sdbm_buf(CSTRING_T_("a"), 1), cstring_hash_sdbm_buf(CSTRING_T_("A"), 1));

    TEST_INT_EQ(cstring_hash_djb2_buf_case(CSTRING_T_("z"), 1), cstring_hash_djb2_buf_case(CSTRING_T_("Z"), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_buf_case(CSTRING_T_("z"), 1), cstring_hash_fnv1a_buf_case(CSTRING_T_("Z"), 1));
    TEST_INT_EQ(cstring_hash_sdbm_buf_case(CSTRING_T_("z"), 1), cstring_hash_sdbm_buf_case(CSTRING_T_("Z"), 1));
    TEST_INT_NE(cstring_hash_djb2_buf(CSTRING_T_("z"), 1), cstring_hash_djb2_buf(CSTRING_T_("Z"), 1));
    TEST_INT_NE(cstring_hash_fnv1a_buf(CSTRING_T_("z"), 1), cstring_hash_fnv1a_buf(CSTRING_T_("Z"), 1));
    TEST_INT_NE(cstring_hash_sdbm_buf(CSTRING_T_("z"), 1), cstring_hash_sdbm_buf(CSTRING_T_("Z"), 1));

    /* Non-letters have identical case-sensitive and case-insensitive hashes */
    TEST_INT_EQ(cstring_hash_djb2_buf(CSTRING_T_("0"), 1), cstring_hash_djb2_buf_case(CSTRING_T_("0"), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_buf(CSTRING_T_("0"), 1), cstring_hash_fnv1a_buf_case(CSTRING_T_("0"), 1));
    TEST_INT_EQ(cstring_hash_sdbm_buf(CSTRING_T_("0"), 1), cstring_hash_sdbm_buf_case(CSTRING_T_("0"), 1));

    TEST_INT_EQ(cstring_hash_djb2_buf(CSTRING_T_("!"), 1), cstring_hash_djb2_buf_case(CSTRING_T_("!"), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_buf(CSTRING_T_("!"), 1), cstring_hash_fnv1a_buf_case(CSTRING_T_("!"), 1));
    TEST_INT_EQ(cstring_hash_sdbm_buf(CSTRING_T_("!"), 1), cstring_hash_sdbm_buf_case(CSTRING_T_("!"), 1));

    TEST_INT_EQ(cstring_hash_djb2_buf(CSTRING_T_(" "), 1), cstring_hash_djb2_buf_case(CSTRING_T_(" "), 1));
    TEST_INT_EQ(cstring_hash_fnv1a_buf(CSTRING_T_(" "), 1), cstring_hash_fnv1a_buf_case(CSTRING_T_(" "), 1));
    TEST_INT_EQ(cstring_hash_sdbm_buf(CSTRING_T_(" "), 1), cstring_hash_sdbm_buf_case(CSTRING_T_(" "), 1));
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
    TEST_INT_EQ(cstring_hash_djb2(&cs_mixed), cstring_hash_djb2_buf(cs_mixed.ptr, cs_mixed.len));
    TEST_INT_EQ(cstring_hash_djb2_case(&cs_mixed), cstring_hash_djb2_buf_case(cs_mixed.ptr, cs_mixed.len));
    TEST_INT_EQ(cstring_hash_fnv1a(&cs_mixed), cstring_hash_fnv1a_buf(cs_mixed.ptr, cs_mixed.len));
    TEST_INT_EQ(cstring_hash_fnv1a_case(&cs_mixed), cstring_hash_fnv1a_buf_case(cs_mixed.ptr, cs_mixed.len));
    TEST_INT_EQ(cstring_hash_sdbm(&cs_mixed), cstring_hash_sdbm_buf(cs_mixed.ptr, cs_mixed.len));
    TEST_INT_EQ(cstring_hash_sdbm_case(&cs_mixed), cstring_hash_sdbm_buf_case(cs_mixed.ptr, cs_mixed.len));

    /* Case-insensitive hashes must match */
    TEST_INT_EQ(cstring_hash_djb2_case(&cs_mixed), cstring_hash_djb2_case(&cs_lower));
    TEST_INT_EQ(cstring_hash_fnv1a_case(&cs_mixed), cstring_hash_fnv1a_case(&cs_lower));
    TEST_INT_EQ(cstring_hash_sdbm_case(&cs_mixed), cstring_hash_sdbm_case(&cs_lower));

    /* Case-sensitive hashes must not match */
    TEST_INT_NE(cstring_hash_djb2(&cs_mixed), cstring_hash_djb2(&cs_lower));
    TEST_INT_NE(cstring_hash_fnv1a(&cs_mixed), cstring_hash_fnv1a(&cs_lower));
    TEST_INT_NE(cstring_hash_sdbm(&cs_mixed), cstring_hash_sdbm(&cs_lower));

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
    cstring_hash_t          sdbm_quick_slice;
    cstring_hash_t          sdbm_quick_direct;
    cstring_t               cs;
    CSTRING_RC              rc;

    /* Slices without constructing cstring_t */
    /* "quick" starts at index 4, length 5 */
    djb2_quick_slice = cstring_hash_djb2_buf(text + 4, 5);
    djb2_quick_direct = cstring_hash_djb2_buf(CSTRING_T_("quick"), 5);
    TEST_INT_EQ(djb2_quick_direct, djb2_quick_slice);

    fnv1a_quick_slice = cstring_hash_fnv1a_buf(text + 4, 5);
    fnv1a_quick_direct = cstring_hash_fnv1a_buf(CSTRING_T_("quick"), 5);
    TEST_INT_EQ(fnv1a_quick_direct, fnv1a_quick_slice);

    sdbm_quick_slice = cstring_hash_sdbm_buf(text + 4, 5);
    sdbm_quick_direct = cstring_hash_sdbm_buf(CSTRING_T_("quick"), 5);
    TEST_INT_EQ(sdbm_quick_direct, sdbm_quick_slice);

    /* "Fox" starts at index 16, length 3 */
    TEST_INT_EQ(cstring_hash_djb2_buf_case(text + 16, 3), cstring_hash_djb2_buf_case(CSTRING_T_("fox"), 3));
    TEST_INT_EQ(cstring_hash_fnv1a_buf_case(text + 16, 3), cstring_hash_fnv1a_buf_case(CSTRING_T_("fox"), 3));
    TEST_INT_EQ(cstring_hash_sdbm_buf_case(text + 16, 3), cstring_hash_sdbm_buf_case(CSTRING_T_("fox"), 3));
    TEST_INT_NE(cstring_hash_djb2_buf(text + 16, 3), cstring_hash_djb2_buf(CSTRING_T_("fox"), 3));
    TEST_INT_NE(cstring_hash_fnv1a_buf(text + 16, 3), cstring_hash_fnv1a_buf(CSTRING_T_("fox"), 3));
    TEST_INT_NE(cstring_hash_sdbm_buf(text + 16, 3), cstring_hash_sdbm_buf(CSTRING_T_("fox"), 3));

    /* Hashing full text via buffer API */
    rc = cstring_createLen(&cs, text, total_len);
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(cstring_hash_djb2_buf(text, total_len), cstring_hash_djb2(&cs));
    TEST_INT_EQ(cstring_hash_fnv1a_buf(text, total_len), cstring_hash_fnv1a(&cs));
    TEST_INT_EQ(cstring_hash_sdbm_buf(text, total_len), cstring_hash_sdbm(&cs));
    cstring_destroy(&cs);
}

static void TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_OCTET_ABOVE_7F(void)
{
    cstring_char_t const    hi[1] = { (cstring_char_t)0xFF };
    cstring_char_t const    mid[1] = { (cstring_char_t)0x7F };

#ifndef CSTRING_USE_WIDE_STRINGS
    /* djb2: 5381 * 33 + octet. FNV-1a and SDBM: one-byte vectors. */
    TEST_INT_EQ(177828ULL, cstring_hash_djb2_buf(hi, 1));
    TEST_INT_EQ(0xaf64724c8602eb6eULL, cstring_hash_fnv1a_buf(hi, 1));
    TEST_INT_EQ(255ULL, cstring_hash_sdbm_buf(hi, 1));
    TEST_INT_EQ(177700ULL, cstring_hash_djb2_buf(mid, 1));
    TEST_INT_EQ(0xaf63f24c860211eeULL, cstring_hash_fnv1a_buf(mid, 1));
    TEST_INT_EQ(127ULL, cstring_hash_sdbm_buf(mid, 1));

    TEST_INT_NE(5381ULL, cstring_hash_djb2_buf(hi, 1));
    TEST_INT_NE(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf(hi, 1));
    TEST_INT_NE(0ULL, cstring_hash_sdbm_buf(hi, 1));

    /* tolower of octets above 0x7F follows the process locale. */
    TEST_INT_NE(cstring_hash_djb2_buf_case(mid, 1), cstring_hash_djb2_buf_case(hi, 1));
    TEST_INT_NE(5381ULL, cstring_hash_djb2_buf_case(hi, 1));
    TEST_INT_NE(cstring_hash_fnv1a_buf_case(mid, 1), cstring_hash_fnv1a_buf_case(hi, 1));
    TEST_INT_NE(0xcbf29ce484222325ULL, cstring_hash_fnv1a_buf_case(hi, 1));
    TEST_INT_NE(cstring_hash_sdbm_buf_case(mid, 1), cstring_hash_sdbm_buf_case(hi, 1));
    TEST_INT_NE(0ULL, cstring_hash_sdbm_buf_case(hi, 1));
#else /* ? CSTRING_USE_WIDE_STRINGS */
    /* Distinct code units only; exact octets would freeze truncation. */
    TEST_INT_NE(cstring_hash_djb2_buf(mid, 1), cstring_hash_djb2_buf(hi, 1));
    TEST_INT_NE(cstring_hash_djb2_buf(hi, 0), cstring_hash_djb2_buf(hi, 1));
    TEST_INT_NE(cstring_hash_djb2_buf_case(mid, 1), cstring_hash_djb2_buf_case(hi, 1));
    TEST_INT_NE(cstring_hash_djb2_buf_case(hi, 0), cstring_hash_djb2_buf_case(hi, 1));
    TEST_INT_NE(cstring_hash_fnv1a_buf(mid, 1), cstring_hash_fnv1a_buf(hi, 1));
    TEST_INT_NE(cstring_hash_fnv1a_buf(hi, 0), cstring_hash_fnv1a_buf(hi, 1));
    TEST_INT_NE(cstring_hash_fnv1a_buf_case(mid, 1), cstring_hash_fnv1a_buf_case(hi, 1));
    TEST_INT_NE(cstring_hash_fnv1a_buf_case(hi, 0), cstring_hash_fnv1a_buf_case(hi, 1));
    TEST_INT_NE(cstring_hash_sdbm_buf(mid, 1), cstring_hash_sdbm_buf(hi, 1));
    TEST_INT_NE(cstring_hash_sdbm_buf(hi, 0), cstring_hash_sdbm_buf(hi, 1));
    TEST_INT_NE(cstring_hash_sdbm_buf_case(mid, 1), cstring_hash_sdbm_buf_case(hi, 1));
    TEST_INT_NE(cstring_hash_sdbm_buf_case(hi, 0), cstring_hash_sdbm_buf_case(hi, 1));
#endif /* CSTRING_USE_WIDE_STRINGS */
}

static void TEST_cstring_hash_djb2_len_AND_cstring_hash_fnv1a_len_EMBEDDED_NUL(void)
{
    cstring_char_t const    a_nul_b[3] = { CSTRING_T_('a'), (cstring_char_t)0, CSTRING_T_('b') };
    cstring_char_t const    a_only[1] = { CSTRING_T_('a') };
    cstring_char_t const    ab[2] = { CSTRING_T_('a'), CSTRING_T_('b') };
    cstring_char_t const    a_nul_c[3] = { CSTRING_T_('a'), (cstring_char_t)0, CSTRING_T_('c') };

    /* Explicit length, so an interior NUL does not end the slice. */
    TEST_INT_NE(cstring_hash_djb2_buf(a_only, 1), cstring_hash_djb2_buf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_djb2_buf(ab, 2), cstring_hash_djb2_buf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_djb2_buf(a_nul_c, 3), cstring_hash_djb2_buf(a_nul_b, 3));

    TEST_INT_NE(cstring_hash_djb2_buf_case(a_only, 1), cstring_hash_djb2_buf_case(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_djb2_buf_case(ab, 2), cstring_hash_djb2_buf_case(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_djb2_buf_case(a_nul_c, 3), cstring_hash_djb2_buf_case(a_nul_b, 3));

    TEST_INT_NE(cstring_hash_fnv1a_buf(a_only, 1), cstring_hash_fnv1a_buf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_fnv1a_buf(ab, 2), cstring_hash_fnv1a_buf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_fnv1a_buf(a_nul_c, 3), cstring_hash_fnv1a_buf(a_nul_b, 3));

    TEST_INT_NE(cstring_hash_fnv1a_buf_case(a_only, 1), cstring_hash_fnv1a_buf_case(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_fnv1a_buf_case(ab, 2), cstring_hash_fnv1a_buf_case(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_fnv1a_buf_case(a_nul_c, 3), cstring_hash_fnv1a_buf_case(a_nul_b, 3));

    TEST_INT_NE(cstring_hash_sdbm_buf(a_only, 1), cstring_hash_sdbm_buf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_sdbm_buf(ab, 2), cstring_hash_sdbm_buf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_sdbm_buf(a_nul_c, 3), cstring_hash_sdbm_buf(a_nul_b, 3));

    TEST_INT_NE(cstring_hash_sdbm_buf_case(a_only, 1), cstring_hash_sdbm_buf_case(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_sdbm_buf_case(ab, 2), cstring_hash_sdbm_buf_case(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_sdbm_buf_case(a_nul_c, 3), cstring_hash_sdbm_buf_case(a_nul_b, 3));

#ifndef CSTRING_USE_WIDE_STRINGS
    TEST_INT_EQ(193482728ULL, cstring_hash_djb2_buf(a_nul_b, 3));
    TEST_INT_EQ(0xe5d29919042666b2ULL, cstring_hash_fnv1a_buf(a_nul_b, 3));
    TEST_INT_EQ(0x612fc3e043ULL, cstring_hash_sdbm_buf(a_nul_b, 3));
#endif /* CSTRING_USE_WIDE_STRINGS */
}

static void TEST_cstring_hash_mbs_AND_wcs_AND_mbuf_AND_wbuf(void)
{
    char const      hi[1] = { (char)(unsigned char)0xFF };
    char const      a_nul_b[3] = { 'a', '\0', 'b' };
    wchar_t const   wide_alias[1] = { (wchar_t)0x161 };
    wchar_t const   wa_nul_b[3] = { L'a', L'\0', L'b' };
    cstring_t       cs;
    CSTRING_RC      rc;

    /* NULL and empty */
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_mbs(NULL));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_wcs(NULL));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_mbs_case(NULL));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_wcs_case(NULL));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_mbuf(NULL, 10));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_wbuf(NULL, 10));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_mbuf_case(NULL, 10));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_wbuf_case(NULL, 10));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_mbs(""));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_wcs(L""));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_mbuf("", 0));
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_wbuf(L"", 0));

    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_mbs(NULL));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_wcs(NULL));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_mbs_case(NULL));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_wcs_case(NULL));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_mbuf(NULL, 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_wbuf(NULL, 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_mbuf_case(NULL, 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_wbuf_case(NULL, 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_mbs(""));
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_wcs(L""));

    TEST_INT_EQ(0ULL, cstring_hash_sdbm_mbs(NULL));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_wcs(NULL));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_mbs_case(NULL));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_wcs_case(NULL));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_mbuf(NULL, 10));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_wbuf(NULL, 10));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_mbuf_case(NULL, 10));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_wbuf_case(NULL, 10));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_mbs(""));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_wcs(L""));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_mbuf("", 0));
    TEST_INT_EQ(0ULL, cstring_hash_sdbm_wbuf(L"", 0));

    /* Published octet vectors, identical for multibyte and wide ASCII */
    TEST_INT_EQ(177670ULL, cstring_hash_djb2_mbs("a"));
    TEST_INT_EQ(177670ULL, cstring_hash_djb2_mbuf("a", 1));
    TEST_INT_EQ(177670ULL, cstring_hash_djb2_wcs(L"a"));
    TEST_INT_EQ(177670ULL, cstring_hash_djb2_wbuf(L"a", 1));
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2_mbs("foobar"));
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2_mbuf("foobar", 6));
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2_wcs(L"foobar"));
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2_wbuf(L"foobar", 6));

    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a_mbs("a"));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a_mbuf("a", 1));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a_wcs(L"a"));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a_wbuf(L"a", 1));
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a_mbs("foobar"));
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a_mbuf("foobar", 6));
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a_wcs(L"foobar"));
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a_wbuf(L"foobar", 6));

    TEST_INT_EQ(97ULL, cstring_hash_sdbm_mbs("a"));
    TEST_INT_EQ(97ULL, cstring_hash_sdbm_mbuf("a", 1));
    TEST_INT_EQ(97ULL, cstring_hash_sdbm_wcs(L"a"));
    TEST_INT_EQ(97ULL, cstring_hash_sdbm_wbuf(L"a", 1));
    TEST_INT_EQ(0x430d469aa6437b0dULL, cstring_hash_sdbm_mbs("foobar"));
    TEST_INT_EQ(0x430d469aa6437b0dULL, cstring_hash_sdbm_mbuf("foobar", 6));
    TEST_INT_EQ(0x430d469aa6437b0dULL, cstring_hash_sdbm_wcs(L"foobar"));
    TEST_INT_EQ(0x430d469aa6437b0dULL, cstring_hash_sdbm_wbuf(L"foobar", 6));

    /* Case fold agrees across encodings for ASCII */
    TEST_INT_EQ(cstring_hash_djb2_mbs_case("Test"), cstring_hash_djb2_mbs_case("test"));
    TEST_INT_EQ(cstring_hash_djb2_mbs_case("Test"), cstring_hash_djb2_wcs_case(L"TEST"));
    TEST_INT_EQ(cstring_hash_djb2_mbs_case("Test"), cstring_hash_djb2_wbuf_case(L"tEst", 4));
    TEST_INT_EQ(cstring_hash_fnv1a_mbs_case("Test"), cstring_hash_fnv1a_wcs_case(L"test"));
    TEST_INT_EQ(cstring_hash_sdbm_mbs_case("Test"), cstring_hash_sdbm_mbs_case("test"));
    TEST_INT_EQ(cstring_hash_sdbm_mbs_case("Test"), cstring_hash_sdbm_wcs_case(L"TEST"));
    TEST_INT_EQ(cstring_hash_sdbm_mbs_case("Test"), cstring_hash_sdbm_wbuf_case(L"tEst", 4));
    TEST_INT_NE(cstring_hash_djb2_mbs("Test"), cstring_hash_djb2_wcs(L"test"));
    TEST_INT_NE(cstring_hash_fnv1a_mbs("Test"), cstring_hash_fnv1a_wcs(L"test"));
    TEST_INT_NE(cstring_hash_sdbm_mbs("Test"), cstring_hash_sdbm_wcs(L"test"));

    /* Sized forms include an embedded NUL; NUL-terminated forms stop */
    TEST_INT_NE(cstring_hash_djb2_mbs("a"), cstring_hash_djb2_mbuf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_djb2_mbs("ab"), cstring_hash_djb2_mbuf(a_nul_b, 3));
    TEST_INT_EQ(193482728ULL, cstring_hash_djb2_mbuf(a_nul_b, 3));
    TEST_INT_EQ(0xe5d29919042666b2ULL, cstring_hash_fnv1a_mbuf(a_nul_b, 3));
    TEST_INT_EQ(0x612fc3e043ULL, cstring_hash_sdbm_mbuf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_sdbm_mbs("a"), cstring_hash_sdbm_mbuf(a_nul_b, 3));
    TEST_INT_NE(cstring_hash_sdbm_mbs("ab"), cstring_hash_sdbm_mbuf(a_nul_b, 3));
    TEST_INT_EQ(cstring_hash_djb2_mbuf(a_nul_b, 3), cstring_hash_djb2_wbuf(wa_nul_b, 3));
    TEST_INT_EQ(cstring_hash_fnv1a_mbuf(a_nul_b, 3), cstring_hash_fnv1a_wbuf(wa_nul_b, 3));
    TEST_INT_EQ(cstring_hash_sdbm_mbuf(a_nul_b, 3), cstring_hash_sdbm_wbuf(wa_nul_b, 3));
    TEST_INT_NE(cstring_hash_sdbm_wcs(L"ab"), cstring_hash_sdbm_wbuf(wa_nul_b, 3));
    TEST_INT_NE(cstring_hash_djb2_wcs(L"ab"), cstring_hash_djb2_wbuf(wa_nul_b, 3));

    /* Wide code units contribute the low 8 bits */
    TEST_INT_EQ(177670ULL, cstring_hash_djb2_wbuf(wide_alias, 1));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a_wbuf(wide_alias, 1));
    TEST_INT_EQ(97ULL, cstring_hash_sdbm_wbuf(wide_alias, 1));
    TEST_INT_EQ(cstring_hash_djb2_mbuf("a", 1), cstring_hash_djb2_wbuf(wide_alias, 1));
    TEST_INT_EQ(cstring_hash_sdbm_mbuf("a", 1), cstring_hash_sdbm_wbuf(wide_alias, 1));

    /* Octet above 0x7F is hashed as that octet on every build */
    TEST_INT_EQ(177828ULL, cstring_hash_djb2_mbuf(hi, 1));
    TEST_INT_EQ(0xaf64724c8602eb6eULL, cstring_hash_fnv1a_mbuf(hi, 1));
    TEST_INT_EQ(255ULL, cstring_hash_sdbm_mbuf(hi, 1));

    rc = cstring_create(&cs, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
#ifdef CSTRING_USE_WIDE_STRINGS

    TEST_INT_EQ(cstring_hash_djb2_wbuf(L"foobar", 6), cstring_hash_djb2_buf(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_djb2_wbuf_case(L"foobar", 6), cstring_hash_djb2_buf_case(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_fnv1a_wbuf(L"foobar", 6), cstring_hash_fnv1a_buf(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_fnv1a_wbuf_case(L"foobar", 6), cstring_hash_fnv1a_buf_case(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_sdbm_wbuf(L"foobar", 6), cstring_hash_sdbm_buf(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_sdbm_wbuf_case(L"foobar", 6), cstring_hash_sdbm_buf_case(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_djb2_wcs(L"foobar"), cstring_hash_djb2(&cs));
    TEST_INT_EQ(cstring_hash_sdbm_wcs(L"foobar"), cstring_hash_sdbm(&cs));
#else /* ? CSTRING_USE_WIDE_STRINGS */

    TEST_INT_EQ(cstring_hash_djb2_mbuf("foobar", 6), cstring_hash_djb2_buf(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_djb2_mbuf_case("foobar", 6), cstring_hash_djb2_buf_case(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_fnv1a_mbuf("foobar", 6), cstring_hash_fnv1a_buf(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_fnv1a_mbuf_case("foobar", 6), cstring_hash_fnv1a_buf_case(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_sdbm_mbuf("foobar", 6), cstring_hash_sdbm_buf(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_sdbm_mbuf_case("foobar", 6), cstring_hash_sdbm_buf_case(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_djb2_mbs("foobar"), cstring_hash_djb2(&cs));
    TEST_INT_EQ(cstring_hash_sdbm_mbs("foobar"), cstring_hash_sdbm(&cs));
#endif /* CSTRING_USE_WIDE_STRINGS */
    cstring_destroy(&cs);
}


/* ///////////////////////////// end of file //////////////////////////// */

