/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.cstring.hash/entry.cpp
 *
 * Purpose: Unit-tests for cstring hashing extensions.
 *
 * Created: 5th September 2026
 * Updated: 5th September 2026
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
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    static void test_null_and_empty(void);
    static void test_fnv1a_known_vectors(void);
    static void test_djb2_known_vectors(void);
    static void test_case_insensitivity(void);
    static void test_single_character(void);
    static void test_long_string(void);
    static void test_slices(void);
    static void test_cpp_shims(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.cstring.hash", verbosity))
    {
        XTESTS_RUN_CASE(test_null_and_empty);
        XTESTS_RUN_CASE(test_fnv1a_known_vectors);
        XTESTS_RUN_CASE(test_djb2_known_vectors);
        XTESTS_RUN_CASE(test_case_insensitivity);
        XTESTS_RUN_CASE(test_single_character);
        XTESTS_RUN_CASE(test_long_string);
        XTESTS_RUN_CASE(test_slices);
        XTESTS_RUN_CASE(test_cpp_shims);

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

static void test_null_and_empty(void)
{
    struct cstring_t const* pcs_null = NULL;
    cstring_t               null_cs = { 0, NULL, 0, 0 };
    cstring_t               default_cs = cstring_t_DEFAULT;
    cstring_t               created_empty;

    CSTRING_RC rc = cstring_create(&created_empty, CSTRING_T_(""));
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

    TEST_INT_EQ(5381ULL, hash_djb2(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2_ci(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2(default_cs));
    TEST_INT_EQ(5381ULL, hash_djb2_ci(default_cs));
    TEST_INT_EQ(5381ULL, hash_djb2(NULL, 0));
    TEST_INT_EQ(5381ULL, hash_djb2_ci(NULL, 0));

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

    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_ci(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_ci(default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(NULL, 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_ci(NULL, 0));

    cstring_destroy(&created_empty);
}

static void test_fnv1a_known_vectors(void)
{
    /* Known FNV-1a 64-bit test vectors:
     *   ""       -> 0xcbf29ce484222325ULL
     *   "a"      -> 0xaf63dc4c8601ec8cULL
     *   "foobar" -> 0x85944171f73967e8ULL
     */
    TEST_INT_EQ(0xcbf29ce484222325ULL, cstring_hash_fnv1a_len(CSTRING_T_(""), 0));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a_len(CSTRING_T_("a"), 1));
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a_len(CSTRING_T_("foobar"), 6));

    cstring_t cs_a;
    CSTRING_RC rc = cstring_create(&cs_a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, cstring_hash_fnv1a(&cs_a));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, hash_fnv1a(cs_a));
    cstring_destroy(&cs_a);

    cstring_t cs_foobar;
    rc = cstring_create(&cs_foobar, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(0x85944171f73967e8ULL, cstring_hash_fnv1a(&cs_foobar));
    TEST_INT_EQ(0x85944171f73967e8ULL, hash_fnv1a(cs_foobar));
    cstring_destroy(&cs_foobar);
}

static void test_djb2_known_vectors(void)
{
    /* Known djb2 test vectors:
     *   ""       -> 5381ULL
     *   "a"      -> 5381 * 33 + 97 = 177670ULL (0x2b606ULL)
     *   "foobar" -> 6953516687550ULL (0x652fde460beULL)
     */
    TEST_INT_EQ(5381ULL, cstring_hash_djb2_len(CSTRING_T_(""), 0));
    TEST_INT_EQ(177670ULL, cstring_hash_djb2_len(CSTRING_T_("a"), 1));
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2_len(CSTRING_T_("foobar"), 6));

    cstring_t cs_a;
    CSTRING_RC rc = cstring_create(&cs_a, CSTRING_T_("a"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(177670ULL, cstring_hash_djb2(&cs_a));
    TEST_INT_EQ(177670ULL, hash_djb2(cs_a));
    cstring_destroy(&cs_a);

    cstring_t cs_foobar;
    rc = cstring_create(&cs_foobar, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(6953516687550ULL, cstring_hash_djb2(&cs_foobar));
    TEST_INT_EQ(6953516687550ULL, hash_djb2(cs_foobar));
    cstring_destroy(&cs_foobar);
}

static void test_case_insensitivity(void)
{
    /* Buffer checks */
    uint64_t djb2_ci_base = cstring_hash_djb2_len_ci(CSTRING_T_("Test"), 4);
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_len_ci(CSTRING_T_("tEst"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_len_ci(CSTRING_T_("TEST"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_len_ci(CSTRING_T_("test"), 4));
    TEST_INT_EQ(djb2_ci_base, cstring_hash_djb2_len_ci(CSTRING_T_("teSt"), 4));

    uint64_t fnv1a_ci_base = cstring_hash_fnv1a_len_ci(CSTRING_T_("Test"), 4);
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_len_ci(CSTRING_T_("tEst"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_len_ci(CSTRING_T_("TEST"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_len_ci(CSTRING_T_("test"), 4));
    TEST_INT_EQ(fnv1a_ci_base, cstring_hash_fnv1a_len_ci(CSTRING_T_("teSt"), 4));

    /* Case-sensitive inequality */
    TEST_INT_NE(cstring_hash_djb2_len(CSTRING_T_("Test"), 4), cstring_hash_djb2_len(CSTRING_T_("tEst"), 4));
    TEST_INT_NE(cstring_hash_fnv1a_len(CSTRING_T_("Test"), 4), cstring_hash_fnv1a_len(CSTRING_T_("tEst"), 4));

    /* Instance checks */
    cstring_t cs1;
    cstring_t cs2;
    cstring_t cs3;
    cstring_t cs4;

    CSTRING_RC rc;
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

static void test_single_character(void)
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

static void test_long_string(void)
{
    cstring_char_t long_pattern_mixed[1025];
    cstring_char_t long_pattern_lower[1025];
    size_t const   pattern_len = 1024;
    size_t         i;

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

    cstring_t cs_mixed;
    cstring_t cs_lower;

    CSTRING_RC rc;
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

static void test_slices(void)
{
    cstring_char_t const text[] = CSTRING_T_("The quick brown Fox jumps over the lazy Dog.");
    size_t const         total_len = sizeof(text) / sizeof(text[0]) - 1;

    /* Slices without constructing cstring_t */
    /* "quick" starts at index 4, length 5 */
    uint64_t djb2_quick_slice = cstring_hash_djb2_len(text + 4, 5);
    uint64_t djb2_quick_direct = cstring_hash_djb2_len(CSTRING_T_("quick"), 5);
    TEST_INT_EQ(djb2_quick_direct, djb2_quick_slice);

    uint64_t fnv1a_quick_slice = cstring_hash_fnv1a_len(text + 4, 5);
    uint64_t fnv1a_quick_direct = cstring_hash_fnv1a_len(CSTRING_T_("quick"), 5);
    TEST_INT_EQ(fnv1a_quick_direct, fnv1a_quick_slice);

    /* "Fox" starts at index 16, length 3 */
    TEST_INT_EQ(cstring_hash_djb2_len_ci(text + 16, 3), cstring_hash_djb2_len_ci(CSTRING_T_("fox"), 3));
    TEST_INT_EQ(cstring_hash_fnv1a_len_ci(text + 16, 3), cstring_hash_fnv1a_len_ci(CSTRING_T_("fox"), 3));
    TEST_INT_NE(cstring_hash_djb2_len(text + 16, 3), cstring_hash_djb2_len(CSTRING_T_("fox"), 3));
    TEST_INT_NE(cstring_hash_fnv1a_len(text + 16, 3), cstring_hash_fnv1a_len(CSTRING_T_("fox"), 3));

    /* Hashing full text via buffer API */
    cstring_t cs;
    CSTRING_RC rc = cstring_createLen(&cs, text, total_len);
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(cstring_hash_djb2_len(text, total_len), cstring_hash_djb2(&cs));
    TEST_INT_EQ(cstring_hash_fnv1a_len(text, total_len), cstring_hash_fnv1a(&cs));
    cstring_destroy(&cs);
}

static void test_cpp_shims(void)
{
    cstring_t cs;
    CSTRING_RC rc = cstring_create(&cs, CSTRING_T_("Hello World"));
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
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

