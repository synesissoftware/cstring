/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.cstring.cstring_getStatusCodeString.cpp
 *
 * Purpose: Unit-tests `cstring_error()`, `cstring_getStatusCodeString()`.
 *
 * Created: 28th July 2011
 * Updated: 12th January 2024
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
#include <xtests/xtests.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#ifdef WIN32
# include <comstl/memory/functions.h>
#endif
#include <platformstl/exception/platformstl_exception.hpp>
#include <platformstl/filesystem/file_lines.hpp>
#include <platformstl/system/system_traits.hpp>

/* Standard C header files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void test_0(void);
    static void test_known(void);
    static void test_random(void);

    static void test_0_deprecated(void);
    static void test_known_deprecated(void);
    static void test_random_deprecated(void);

} // anonymous namespace

/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

const char TEST_FILE_NAME[] = "test.unit.cstring.cstring_getStatusCodeString.txt";

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

namespace
{

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

static void test_0()
{
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("operation completed successfully", cstring_getStatusCodeString((CSTRING_RC)0));
}

static void test_known()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(knownCodes); ++i)
    {
        XTESTS_TEST_MULTIBYTE_STRING_NOT_EQUAL("<<unknown error>>", cstring_getStatusCodeString(knownCodes[i]));
    }}
}

static void test_random()
{
    { for (size_t i = 0; i != 100000; ++i)
    {
        int         r   =   ::rand();
        CSTRING_RC  rc  =   static_cast<CSTRING_RC>(STLSOFT_NUM_ELEMENTS(knownCodes) + r + 1);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("<<unknown error>>", cstring_getStatusCodeString(rc));
    }}
}


static void test_0_deprecated()
{
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("operation completed successfully", cstring_error((CSTRING_RC)0));
}

static void test_known_deprecated()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(knownCodes); ++i)
    {
        XTESTS_TEST_MULTIBYTE_STRING_NOT_EQUAL("<<unknown error>>", cstring_error(knownCodes[i]));
    }}
}

static void test_random_deprecated()
{
    { for (size_t i = 0; i != 100000; ++i)
    {
        int         r   =   ::rand();
        CSTRING_RC  rc  =   static_cast<CSTRING_RC>(STLSOFT_NUM_ELEMENTS(knownCodes) + r + 1);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("<<unknown error>>", cstring_error(rc));
    }}
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

