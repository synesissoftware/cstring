/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.cstring.cstring_getStatusCodeString/entry.c
 *
 * Purpose: Unit-tests `cstring_error()`, `cstring_getStatusCodeString()`.
 *
 * Created: 28th July 2011
 * Updated: 2nd August 2026
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
#include <xtests/xtests.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_0(void);
static void test_known(void);
static void test_random(void);

static void test_0_deprecated(void);
static void test_known_deprecated(void);
static void test_random_deprecated(void);


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

static char const TEST_FILE_NAME[] = "test.unit.cstring.cstring_getStatusCodeString.txt";

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

    if (XTESTS_START_RUNNER("test.unit.cstring.cstring_getStatusCodeString", verbosity))
    {
        XTESTS_RUN_CASE(test_0);
        XTESTS_RUN_CASE(test_known);
        XTESTS_RUN_CASE(test_random);

        XTESTS_RUN_CASE(test_0_deprecated);
        XTESTS_RUN_CASE(test_known_deprecated);
        XTESTS_RUN_CASE(test_random_deprecated);

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

static void test_0(void)
{
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("operation completed successfully", cstring_getStatusCodeString((CSTRING_RC)0));
}

static void test_known(void)
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(knownCodes); ++i)
    {
        XTESTS_TEST_MULTIBYTE_STRING_NOT_EQUAL("<<unknown error>>", cstring_getStatusCodeString(knownCodes[i]));
    }}

#ifdef XTESTS_HAS_SHWILD

    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation completed successfully", cstring_getStatusCodeString(CSTRING_RC_SUCCESS));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("out of memory", cstring_getStatusCodeString(CSTRING_RC_OUTOFMEMORY));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the cstring *", cstring_getStatusCodeString(CSTRING_RC_FIXED));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the cstring *", cstring_getStatusCodeString(CSTRING_RC_BORROWED));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the cstring *", cstring_getStatusCodeString(CSTRING_RC_READONLY));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("*invalid*", cstring_getStatusCodeString(CSTRING_RC_INVALIDARENA));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("custom arena functionality not currently supported", cstring_getStatusCodeString(CSTRING_RC_CUSTOMARENANOTSUPPORTED));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the current capacity would be exceeded*", cstring_getStatusCodeString(CSTRING_RC_EXCEEDFIXEDCAPACITY));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the current capacity would be exceeded*", cstring_getStatusCodeString(CSTRING_RC_EXCEEDBORROWEDCAPACITY));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("yield operation from a dynamic-library version of cstring was not allowed", cstring_getStatusCodeString(CSTRING_RC_CANNOTYIELDFROMSO));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("cannot use arena parameter for both borrowed memory and custom arena", cstring_getStatusCodeString(CSTRING_RC_ARENAOVERLOADED));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("*invalid*", cstring_getStatusCodeString(CSTRING_RC_INVALIDSTREAM));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("reached the end of stream", cstring_getStatusCodeString(CSTRING_RC_EOF));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("*invalid*", cstring_getStatusCodeString(CSTRING_RC_INVALIDSECTION));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("an I/O error occured", cstring_getStatusCodeString(CSTRING_RC_IOERROR));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("system-specific failure occurred", cstring_getStatusCodeString(CSTRING_RC_SYSTEMSPECIFICFAILURE));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("request exceeded inherent or runtime limit", cstring_getStatusCodeString(CSTRING_RC_REQUESTTOOLARGE));
#endif /* XTESTS_HAS_SHWILD */
}

static void test_random(void)
{
    { for (size_t i = 0; i != 100000; ++i)
    {
        int         r   =   rand();
        CSTRING_RC  rc  =   (CSTRING_RC)(STLSOFT_NUM_ELEMENTS(knownCodes) + r + 1);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("<<unknown error>>", cstring_getStatusCodeString(rc));
    }}
}


static void test_0_deprecated(void)
{
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("operation completed successfully", cstring_error((CSTRING_RC)0));
}

static void test_known_deprecated(void)
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(knownCodes); ++i)
    {
        XTESTS_TEST_MULTIBYTE_STRING_NOT_EQUAL("<<unknown error>>", cstring_error(knownCodes[i]));
    }}

#ifdef XTESTS_HAS_SHWILD

    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation completed successfully", cstring_error(CSTRING_RC_SUCCESS));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("out of memory", cstring_error(CSTRING_RC_OUTOFMEMORY));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the cstring *", cstring_error(CSTRING_RC_FIXED));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the cstring *", cstring_error(CSTRING_RC_BORROWED));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the cstring *", cstring_error(CSTRING_RC_READONLY));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("*invalid*", cstring_error(CSTRING_RC_INVALIDARENA));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("custom arena functionality not currently supported", cstring_error(CSTRING_RC_CUSTOMARENANOTSUPPORTED));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the current capacity would be exceeded*", cstring_error(CSTRING_RC_EXCEEDFIXEDCAPACITY));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("operation cannot procede because the current capacity would be exceeded*", cstring_error(CSTRING_RC_EXCEEDBORROWEDCAPACITY));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("yield operation from a dynamic-library version of cstring was not allowed", cstring_error(CSTRING_RC_CANNOTYIELDFROMSO));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("cannot use arena parameter for both borrowed memory and custom arena", cstring_error(CSTRING_RC_ARENAOVERLOADED));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("*invalid*", cstring_error(CSTRING_RC_INVALIDSTREAM));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("reached the end of stream", cstring_error(CSTRING_RC_EOF));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("*invalid*", cstring_error(CSTRING_RC_INVALIDSECTION));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("an I/O error occured", cstring_error(CSTRING_RC_IOERROR));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("system-specific failure occurred", cstring_error(CSTRING_RC_SYSTEMSPECIFICFAILURE));
    XTESTS_TEST_MULTIBYTE_STRING_MATCHES("request exceeded inherent or runtime limit", cstring_error(CSTRING_RC_REQUESTTOOLARGE));
#endif /* XTESTS_HAS_SHWILD */
}

static void test_random_deprecated(void)
{
    { for (size_t i = 0; i != 100000; ++i)
    {
        int         r   =   rand();
        CSTRING_RC  rc  =   (CSTRING_RC)(STLSOFT_NUM_ELEMENTS(knownCodes) + r + 1);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("<<unknown error>>", cstring_error(rc));
    }}
}


/* ///////////////////////////// end of file //////////////////////////// */
