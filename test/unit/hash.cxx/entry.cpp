/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/hash.cxx/entry.cpp
 *
 * Purpose: Unit-tests for the C++ cstring hash access shims.
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
    static void TEST_hash_djb2_AND_hash_djb2_ci_AND_hash_fnv1a_AND_hash_fnv1a_case(void);
    static void TEST_hash_mbs_AND_wcs_OVERLOADS(void);
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
        XTESTS_RUN_CASE(TEST_hash_djb2_AND_hash_djb2_ci_AND_hash_fnv1a_AND_hash_fnv1a_case);
        XTESTS_RUN_CASE(TEST_hash_mbs_AND_wcs_OVERLOADS);

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
    using cstring::hash_djb2;
    using cstring::hash_djb2_case;
    using cstring::hash_fnv1a;
    using cstring::hash_fnv1a_case;
    using cstring::hash_sdbm;
    using cstring::hash_sdbm_case;


static void TEST_hash_djb2_AND_hash_fnv1a_NULL_AND_EMPTY(void)
{
    cstring_t const default_cs = cstring_t_DEFAULT;

    TEST_INT_EQ(5381ULL, hash_djb2(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2_case(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2(default_cs));
    TEST_INT_EQ(5381ULL, hash_djb2_case(default_cs));
    TEST_INT_EQ(5381ULL, hash_djb2(static_cast<char const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2(static_cast<wchar_t const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2(static_cast<char const*>(NULL), 0));
    TEST_INT_EQ(5381ULL, hash_djb2(static_cast<wchar_t const*>(NULL), 10));
    TEST_INT_EQ(5381ULL, hash_djb2_case(static_cast<char const*>(NULL)));
    TEST_INT_EQ(5381ULL, hash_djb2_case(static_cast<wchar_t const*>(NULL), 0));

    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_case(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_case(default_cs));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(static_cast<char const*>(NULL)));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a(static_cast<wchar_t const*>(NULL), 0));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_case(static_cast<char const*>(NULL), 10));
    TEST_INT_EQ(0xcbf29ce484222325ULL, hash_fnv1a_case(static_cast<wchar_t const*>(NULL)));

    TEST_INT_EQ(0ULL, hash_sdbm(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(0ULL, hash_sdbm_case(static_cast<struct cstring_t const*>(NULL)));
    TEST_INT_EQ(0ULL, hash_sdbm(default_cs));
    TEST_INT_EQ(0ULL, hash_sdbm_case(default_cs));
    TEST_INT_EQ(0ULL, hash_sdbm(static_cast<char const*>(NULL)));
    TEST_INT_EQ(0ULL, hash_sdbm(static_cast<wchar_t const*>(NULL), 0));
    TEST_INT_EQ(0ULL, hash_sdbm_case(static_cast<char const*>(NULL), 10));
    TEST_INT_EQ(0ULL, hash_sdbm_case(static_cast<wchar_t const*>(NULL)));
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
    TEST_INT_EQ(97ULL, hash_sdbm(cs_a));
    cstring_destroy(&cs_a);

    rc = cstring_create(&cs_foobar, CSTRING_T_("foobar"));
    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(6953516687550ULL, hash_djb2(cs_foobar));
    TEST_INT_EQ(0x85944171f73967e8ULL, hash_fnv1a(cs_foobar));
    TEST_INT_EQ(0x430d469aa6437b0dULL, hash_sdbm(cs_foobar));
    cstring_destroy(&cs_foobar);
}

static void TEST_hash_djb2_AND_hash_djb2_ci_AND_hash_fnv1a_AND_hash_fnv1a_case(void)
{
    cstring_t   cs;
    CSTRING_RC  rc = cstring_create(&cs, CSTRING_T_("Hello World"));

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

    /* Overload by reference */
    TEST_INT_EQ(cstring_hash_djb2(&cs), hash_djb2(cs));
    TEST_INT_EQ(cstring_hash_djb2_case(&cs), hash_djb2_case(cs));
    TEST_INT_EQ(cstring_hash_fnv1a(&cs), hash_fnv1a(cs));
    TEST_INT_EQ(cstring_hash_fnv1a_case(&cs), hash_fnv1a_case(cs));
    TEST_INT_EQ(cstring_hash_sdbm(&cs), hash_sdbm(cs));
    TEST_INT_EQ(cstring_hash_sdbm_case(&cs), hash_sdbm_case(cs));

    /* Overload by pointer */
    TEST_INT_EQ(cstring_hash_djb2(&cs), hash_djb2(&cs));
    TEST_INT_EQ(cstring_hash_djb2_case(&cs), hash_djb2_case(&cs));
    TEST_INT_EQ(cstring_hash_fnv1a(&cs), hash_fnv1a(&cs));
    TEST_INT_EQ(cstring_hash_fnv1a_case(&cs), hash_fnv1a_case(&cs));
    TEST_INT_EQ(cstring_hash_sdbm(&cs), hash_sdbm(&cs));
    TEST_INT_EQ(cstring_hash_sdbm_case(&cs), hash_sdbm_case(&cs));

    /* Overload by slice/buffer */
    TEST_INT_EQ(cstring_hash_djb2_buf(cs.ptr, cs.len), hash_djb2(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_djb2_buf_case(cs.ptr, cs.len), hash_djb2_case(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_fnv1a_buf(cs.ptr, cs.len), hash_fnv1a(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_fnv1a_buf_case(cs.ptr, cs.len), hash_fnv1a_case(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_sdbm_buf(cs.ptr, cs.len), hash_sdbm(cs.ptr, cs.len));
    TEST_INT_EQ(cstring_hash_sdbm_buf_case(cs.ptr, cs.len), hash_sdbm_case(cs.ptr, cs.len));

    cstring_destroy(&cs);
}

static void TEST_hash_mbs_AND_wcs_OVERLOADS(void)
{
    char const      a_nul_b[3] = { 'a', '\0', 'b' };
    wchar_t const   wide_alias[1] = { static_cast<wchar_t>(0x161) };
    wchar_t const   wa_nul_b[3] = { L'a', L'\0', L'b' };

    TEST_INT_EQ(177670ULL, hash_djb2("a"));
    TEST_INT_EQ(177670ULL, hash_djb2(L"a"));
    TEST_INT_EQ(177670ULL, hash_djb2("a", 1));
    TEST_INT_EQ(177670ULL, hash_djb2(L"a", 1));
    TEST_INT_EQ(6953516687550ULL, hash_djb2("foobar"));
    TEST_INT_EQ(6953516687550ULL, hash_djb2(L"foobar", 6));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, hash_fnv1a("a"));
    TEST_INT_EQ(0xaf63dc4c8601ec8cULL, hash_fnv1a(L"a"));
    TEST_INT_EQ(0x85944171f73967e8ULL, hash_fnv1a("foobar", 6));
    TEST_INT_EQ(0x85944171f73967e8ULL, hash_fnv1a(L"foobar"));
    TEST_INT_EQ(97ULL, hash_sdbm("a"));
    TEST_INT_EQ(97ULL, hash_sdbm(L"a"));
    TEST_INT_EQ(97ULL, hash_sdbm("a", 1));
    TEST_INT_EQ(97ULL, hash_sdbm(L"a", 1));
    TEST_INT_EQ(0x430d469aa6437b0dULL, hash_sdbm("foobar"));
    TEST_INT_EQ(0x430d469aa6437b0dULL, hash_sdbm(L"foobar", 6));

    TEST_INT_EQ(hash_djb2_case("Test"), hash_djb2_case(L"tEst"));
    TEST_INT_EQ(hash_fnv1a_case("TEST", 4), hash_fnv1a_case(L"test"));
    TEST_INT_EQ(hash_sdbm_case("Test"), hash_sdbm_case(L"tEst"));
    TEST_INT_NE(hash_djb2("Test"), hash_djb2(L"test"));
    TEST_INT_NE(hash_sdbm("Test"), hash_sdbm(L"test"));

    TEST_INT_NE(hash_djb2("ab"), hash_djb2(a_nul_b, 3));
    TEST_INT_EQ(hash_djb2(a_nul_b, 3), hash_djb2(wa_nul_b, 3));
    TEST_INT_NE(hash_djb2(L"ab"), hash_djb2(wa_nul_b, 3));
    TEST_INT_EQ(hash_djb2("a"), hash_djb2(wide_alias, 1));
    TEST_INT_EQ(hash_fnv1a(L"a"), hash_fnv1a(wide_alias, 1));
    TEST_INT_NE(hash_sdbm("ab"), hash_sdbm(a_nul_b, 3));
    TEST_INT_EQ(hash_sdbm(a_nul_b, 3), hash_sdbm(wa_nul_b, 3));
    TEST_INT_EQ(hash_sdbm("a"), hash_sdbm(wide_alias, 1));

    TEST_INT_EQ(cstring_hash_djb2_mbs("foobar"), hash_djb2("foobar"));
    TEST_INT_EQ(cstring_hash_djb2_wcs(L"foobar"), hash_djb2(L"foobar"));
    TEST_INT_EQ(cstring_hash_fnv1a_mbuf("foobar", 6), hash_fnv1a("foobar", 6));
    TEST_INT_EQ(cstring_hash_fnv1a_wbuf(L"foobar", 6), hash_fnv1a(L"foobar", 6));
    TEST_INT_EQ(cstring_hash_sdbm_mbs("foobar"), hash_sdbm("foobar"));
    TEST_INT_EQ(cstring_hash_sdbm_wcs(L"foobar"), hash_sdbm(L"foobar"));
    TEST_INT_EQ(cstring_hash_sdbm_mbuf("foobar", 6), hash_sdbm("foobar", 6));
    TEST_INT_EQ(cstring_hash_sdbm_wbuf(L"foobar", 6), hash_sdbm(L"foobar", 6));
}
} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

