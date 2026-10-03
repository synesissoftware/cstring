/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/cstring_getStatusCodeString/entry.c
 *
 * Purpose: Unit-tests `cstring_error()`, `cstring_getStatusCodeString()`.
 *
 * Created: 28th July 2011
 * Updated: 3rd October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <cstring/cstring.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifdef XTESTS_HAS_SHWILD
 /* shwild header files */
# include <shwild/shwild.h>
#endif /* XTESTS_HAS_SHWILD */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_cstring_getStatusCodeString_SUCCESS(void);
static void TEST_cstring_getStatusCodeString_KNOWN_CODES(void);
static void TEST_cstring_getStatusCodeString_UNKNOWN_CODES(void);

static void TEST_cstring_error_SUCCESS(void);
static void TEST_cstring_error_KNOWN_CODES(void);
static void TEST_cstring_error_UNKNOWN_CODES(void);


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

static CSTRING_RC const knownCodes[] =
{
        CSTRING_RC_SUCCESS
    ,   CSTRING_RC_OUTOFMEMORY
    ,   CSTRING_RC_FIXED
    ,   CSTRING_RC_BORROWED
    ,   CSTRING_RC_READONLY
    ,   CSTRING_RC_INVALIDARENA
    ,   CSTRING_RC_CUSTOMARENANOTSUPPORTED
    ,   CSTRING_RC_EXCEEDFIXEDCAPACITY
    ,   CSTRING_RC_EXCEEDBORROWEDCAPACITY
    ,   CSTRING_RC_CANNOTYIELDFROMSO
    ,   CSTRING_RC_ARENAOVERLOADED
    /* cstring 3.5+ */
    ,   CSTRING_RC_INVALIDSTREAM
    ,   CSTRING_RC_EOF
    ,   CSTRING_RC_INVALIDSECTION
    ,   CSTRING_RC_IOERROR
    /* cstring 3.6.2+ */
    ,   CSTRING_RC_SYSTEMSPECIFICFAILURE
    /* cstring 4.0+ */
    ,   CSTRING_RC_REQUESTTOOLARGE
};


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

    if (XTESTS_START_RUNNER("test.unit.cstring_getStatusCodeString", verbosity))
    {
        XTESTS_RUN_CASE(TEST_cstring_getStatusCodeString_SUCCESS);
        XTESTS_RUN_CASE(TEST_cstring_getStatusCodeString_KNOWN_CODES);
        XTESTS_RUN_CASE(TEST_cstring_getStatusCodeString_UNKNOWN_CODES);

        XTESTS_RUN_CASE(TEST_cstring_error_SUCCESS);
        XTESTS_RUN_CASE(TEST_cstring_error_KNOWN_CODES);
        XTESTS_RUN_CASE(TEST_cstring_error_UNKNOWN_CODES);

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

static void TEST_cstring_getStatusCodeString_SUCCESS(void)
{
    TEST_MS_EQ("operation completed successfully", cstring_getStatusCodeString((CSTRING_RC)0));
}

static void TEST_cstring_getStatusCodeString_KNOWN_CODES(void)
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(knownCodes); ++i)
    {
        TEST_MS_NE("<<unknown error>>", cstring_getStatusCodeString(knownCodes[i]));
    }}

#ifdef XTESTS_HAS_SHWILD

    TEST_MS_MATCHES("operation completed successfully", cstring_getStatusCodeString(CSTRING_RC_SUCCESS));
    TEST_MS_MATCHES("out of memory", cstring_getStatusCodeString(CSTRING_RC_OUTOFMEMORY));
    TEST_MS_MATCHES("operation cannot procede because the cstring *", cstring_getStatusCodeString(CSTRING_RC_FIXED));
    TEST_MS_MATCHES("operation cannot procede because the cstring *", cstring_getStatusCodeString(CSTRING_RC_BORROWED));
    TEST_MS_MATCHES("operation cannot procede because the cstring *", cstring_getStatusCodeString(CSTRING_RC_READONLY));
    TEST_MS_MATCHES("*invalid*", cstring_getStatusCodeString(CSTRING_RC_INVALIDARENA));
    TEST_MS_MATCHES("custom arena functionality not currently supported", cstring_getStatusCodeString(CSTRING_RC_CUSTOMARENANOTSUPPORTED));
    TEST_MS_MATCHES("operation cannot procede because the current capacity would be exceeded*", cstring_getStatusCodeString(CSTRING_RC_EXCEEDFIXEDCAPACITY));
    TEST_MS_MATCHES("operation cannot procede because the current capacity would be exceeded*", cstring_getStatusCodeString(CSTRING_RC_EXCEEDBORROWEDCAPACITY));
    TEST_MS_MATCHES("yield operation from a dynamic-library version of cstring was not allowed", cstring_getStatusCodeString(CSTRING_RC_CANNOTYIELDFROMSO));
    TEST_MS_MATCHES("cannot use arena parameter for both borrowed memory and custom arena", cstring_getStatusCodeString(CSTRING_RC_ARENAOVERLOADED));
    TEST_MS_MATCHES("*invalid*", cstring_getStatusCodeString(CSTRING_RC_INVALIDSTREAM));
    TEST_MS_MATCHES("reached the end of stream", cstring_getStatusCodeString(CSTRING_RC_EOF));
    TEST_MS_MATCHES("*invalid*", cstring_getStatusCodeString(CSTRING_RC_INVALIDSECTION));
    TEST_MS_MATCHES("an I/O error occured", cstring_getStatusCodeString(CSTRING_RC_IOERROR));
    TEST_MS_MATCHES("system-specific failure occurred", cstring_getStatusCodeString(CSTRING_RC_SYSTEMSPECIFICFAILURE));
    TEST_MS_MATCHES("request exceeded inherent or runtime limit", cstring_getStatusCodeString(CSTRING_RC_REQUESTTOOLARGE));
#endif /* XTESTS_HAS_SHWILD */
}

static void TEST_cstring_getStatusCodeString_UNKNOWN_CODES(void)
{
    { for (size_t i = 0; i != 100000; ++i)
    {
        int         r   =   rand();
        CSTRING_RC  rc  =   (CSTRING_RC)(STLSOFT_NUM_ELEMENTS(knownCodes) + r + 1);

        TEST_MS_EQ("<<unknown error>>", cstring_getStatusCodeString(rc));
    }}
}


static void TEST_cstring_error_SUCCESS(void)
{
    TEST_MS_EQ("operation completed successfully", cstring_error((CSTRING_RC)0));
}

static void TEST_cstring_error_KNOWN_CODES(void)
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(knownCodes); ++i)
    {
        TEST_MS_NE("<<unknown error>>", cstring_error(knownCodes[i]));
    }}

#ifdef XTESTS_HAS_SHWILD

    TEST_MS_MATCHES("operation completed successfully", cstring_error(CSTRING_RC_SUCCESS));
    TEST_MS_MATCHES("out of memory", cstring_error(CSTRING_RC_OUTOFMEMORY));
    TEST_MS_MATCHES("operation cannot procede because the cstring *", cstring_error(CSTRING_RC_FIXED));
    TEST_MS_MATCHES("operation cannot procede because the cstring *", cstring_error(CSTRING_RC_BORROWED));
    TEST_MS_MATCHES("operation cannot procede because the cstring *", cstring_error(CSTRING_RC_READONLY));
    TEST_MS_MATCHES("*invalid*", cstring_error(CSTRING_RC_INVALIDARENA));
    TEST_MS_MATCHES("custom arena functionality not currently supported", cstring_error(CSTRING_RC_CUSTOMARENANOTSUPPORTED));
    TEST_MS_MATCHES("operation cannot procede because the current capacity would be exceeded*", cstring_error(CSTRING_RC_EXCEEDFIXEDCAPACITY));
    TEST_MS_MATCHES("operation cannot procede because the current capacity would be exceeded*", cstring_error(CSTRING_RC_EXCEEDBORROWEDCAPACITY));
    TEST_MS_MATCHES("yield operation from a dynamic-library version of cstring was not allowed", cstring_error(CSTRING_RC_CANNOTYIELDFROMSO));
    TEST_MS_MATCHES("cannot use arena parameter for both borrowed memory and custom arena", cstring_error(CSTRING_RC_ARENAOVERLOADED));
    TEST_MS_MATCHES("*invalid*", cstring_error(CSTRING_RC_INVALIDSTREAM));
    TEST_MS_MATCHES("reached the end of stream", cstring_error(CSTRING_RC_EOF));
    TEST_MS_MATCHES("*invalid*", cstring_error(CSTRING_RC_INVALIDSECTION));
    TEST_MS_MATCHES("an I/O error occured", cstring_error(CSTRING_RC_IOERROR));
    TEST_MS_MATCHES("system-specific failure occurred", cstring_error(CSTRING_RC_SYSTEMSPECIFICFAILURE));
    TEST_MS_MATCHES("request exceeded inherent or runtime limit", cstring_error(CSTRING_RC_REQUESTTOOLARGE));
#endif /* XTESTS_HAS_SHWILD */
}

static void TEST_cstring_error_UNKNOWN_CODES(void)
{
    { for (size_t i = 0; i != 100000; ++i)
    {
        int         r   =   rand();
        CSTRING_RC  rc  =   (CSTRING_RC)(STLSOFT_NUM_ELEMENTS(knownCodes) + r + 1);

        TEST_MS_EQ("<<unknown error>>", cstring_error(rc));
    }}
}


/* ///////////////////////////// end of file //////////////////////////// */
