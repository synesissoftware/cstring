/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/cstring.cxx/entry.cpp
 *
 * Purpose: Unit-tests for cstring instance general functionality.
 *
 * Created: 23rd May 2009
 * Updated: 4th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#define CSTRING_OBSOLETE


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
#ifdef WIN32
# include <comstl/memory/functions.h>
#endif
#include <stlsoft/smartptr/scoped_handle.hpp>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void TEST_cstring_t_DEFAULT();
    static void TEST_cstring_init();
    static void TEST_cstring_setCapacity();
    static void TEST_cstring_assign_AND_cstring_create_AND_cstring_createLen_NULL_AND_EMPTY();
    static void TEST_cstring_assign_AND_cstring_create();
    static void TEST_cstring_assignLen_AND_cstring_createLen();
    static void TEST_cstring_append_AND_cstring_appendLen();
    static void TEST_cstring_truncate();
    static void TEST_cstring_appendLen_KEEPS_CAPACITY();

    static void TEST_cstring_init_AND_cstring_destroy();
    static void TEST_cstring_create();
    static void TEST_cstring_createLen();
    static void TEST_cstring_createEx();
    static void TEST_cstring_createLenEx();
    static void TEST_cstring_assignLen_KEEPS_CAPACITY();
    static void TEST_cstring_assign_KEEPS_CAPACITY();
    static void TEST_cstring_copy();
    static void TEST_cstring_yield();
    static void TEST_cstring_yield2();
    static void TEST_cstring_swap();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

const size_t    APPEND_ITERATIONS   =   1000000u;
const size_t    ASSIGN_ITERATIONS   =   100000u;


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

    if (XTESTS_START_RUNNER("test.unit.cstring.cxx", verbosity))
    {
        XTESTS_RUN_CASE(TEST_cstring_t_DEFAULT);
        XTESTS_RUN_CASE(TEST_cstring_init);
        XTESTS_RUN_CASE(TEST_cstring_setCapacity);
        XTESTS_RUN_CASE(TEST_cstring_assign_AND_cstring_create_AND_cstring_createLen_NULL_AND_EMPTY);
        XTESTS_RUN_CASE(TEST_cstring_assign_AND_cstring_create);
        XTESTS_RUN_CASE(TEST_cstring_assignLen_AND_cstring_createLen);
        XTESTS_RUN_CASE(TEST_cstring_append_AND_cstring_appendLen);
        XTESTS_RUN_CASE(TEST_cstring_truncate);
        XTESTS_RUN_CASE(TEST_cstring_appendLen_KEEPS_CAPACITY);

        XTESTS_RUN_CASE(TEST_cstring_init_AND_cstring_destroy);
        XTESTS_RUN_CASE(TEST_cstring_create);
        XTESTS_RUN_CASE(TEST_cstring_createLen);
        XTESTS_RUN_CASE(TEST_cstring_createEx);
        XTESTS_RUN_CASE(TEST_cstring_createLenEx);
        XTESTS_RUN_CASE(TEST_cstring_assignLen_KEEPS_CAPACITY);
        XTESTS_RUN_CASE(TEST_cstring_assign_KEEPS_CAPACITY);
        XTESTS_RUN_CASE(TEST_cstring_copy);
        XTESTS_RUN_CASE(TEST_cstring_yield);
        XTESTS_RUN_CASE(TEST_cstring_yield2);
        XTESTS_RUN_CASE(TEST_cstring_swap);

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
 * compatibility
 */

#ifdef CSTRING_USE_WIDE_STRINGS

# define CSTRING_T_(x)                                      L ## x
# define TEST_STR_EQ_                                       TEST_WS_EQ
# define TEST_STR_EQ_N_                                     TEST_WS_EQ_N
#else /* ? CSTRING_USE_WIDE_STRINGS */

# define CSTRING_T_(x)                                      x
# define TEST_STR_EQ_                                       TEST_MS_EQ
# define TEST_STR_EQ_N_                                     TEST_MS_EQ_N
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

#ifdef CSTRING_USE_WIDE_STRINGS
    typedef std::wstring                                    string_t;
#else /* ? CSTRING_USE_WIDE_STRINGS */
    typedef std::string                                     string_t;
#endif /* CSTRING_USE_WIDE_STRINGS */

    static const cstring_char_t alphabet[] = CSTRING_T_("abcdefghijklmnopqrstuvwxyz");


static void TEST_cstring_t_DEFAULT()
{
    cstring_t str = cstring_t_DEFAULT;

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, stlsoft::apply_const_ptr(str.ptr));
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_GE(str.len, str.capacity);
}

static void TEST_cstring_init()
{
    cstring_t str;

    cstring_init(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_GE(str.len, str.capacity);
}

static void TEST_cstring_setCapacity()
{
    cstring_t   str =   cstring_t_DEFAULT;
    CSTRING_RC  rc  =   cstring_setCapacity(&str, 10);

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_FAIL_WITH_QUALIFIER("could not set capacity", cstring_getStatusCodeString(rc));
    }
    else
    {
        TEST_INT_EQ(0u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_INT_GE(10u, str.capacity);
        TEST_INT_GE(str.len, str.capacity);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }
}

static void TEST_cstring_assign_AND_cstring_create_AND_cstring_createLen_NULL_AND_EMPTY()
{
    {
        cstring_t   str =   cstring_t_DEFAULT;
        CSTRING_RC  rc  =   cstring_assign(&str, NULL);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not assign", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(CSTRING_T_(""), str.ptr);
            TEST_INT_GT(0u, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }

    {
        cstring_t   str =   cstring_t_DEFAULT;
        CSTRING_RC  rc  =   cstring_assign(&str, CSTRING_T_(""));

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not assign", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(CSTRING_T_(""), str.ptr);
            TEST_INT_GT(0u, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }

    {
        cstring_t   str;
        CSTRING_RC  rc  =   cstring_create(&str, NULL);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not create", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(CSTRING_T_(""), str.ptr);
            TEST_INT_GT(0u, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }

    {
        cstring_t   str;
        CSTRING_RC  rc  =   cstring_create(&str, CSTRING_T_(""));

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not create", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(CSTRING_T_(""), str.ptr);
            TEST_INT_GT(0u, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }

    {
        cstring_t   str;
        CSTRING_RC  rc  =   cstring_createLen(&str, NULL, 0u);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(CSTRING_T_(""), str.ptr);
            TEST_INT_GT(0u, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }

    {
        cstring_t   str;
        CSTRING_RC  rc  =   cstring_createLen(&str, CSTRING_T_(""), 0u);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(CSTRING_T_(""), str.ptr);
            TEST_INT_GT(0u, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }

    {
        cstring_t   str;
        CSTRING_RC  rc  =   cstring_createLen(&str, NULL, 5u);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(5u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(CSTRING_T_(""), str.ptr);
            TEST_CHAR_EQ('\0', str.ptr[0]);
            TEST_CHAR_EQ('\0', str.ptr[1]);
            TEST_CHAR_EQ('\0', str.ptr[2]);
            TEST_CHAR_EQ('\0', str.ptr[3]);
            TEST_CHAR_EQ('\0', str.ptr[4]);
            TEST_CHAR_EQ('\0', str.ptr[5]);
            TEST_INT_GE(5u, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }

    {
        cstring_t   str;
        CSTRING_RC  rc  =   cstring_createLen(&str, CSTRING_T_(""), 5u);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(5u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(CSTRING_T_(""), str.ptr);
            TEST_CHAR_EQ('\0', str.ptr[0]);
            TEST_CHAR_EQ('\0', str.ptr[1]);
            TEST_CHAR_EQ('\0', str.ptr[2]);
            TEST_CHAR_EQ('\0', str.ptr[3]);
            TEST_CHAR_EQ('\0', str.ptr[4]);
            TEST_CHAR_EQ('\0', str.ptr[5]);
            TEST_INT_GE(5u, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }
}

static void TEST_cstring_assign_AND_cstring_create()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s   =   alphabet + i;
        const size_t            cch =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str =   cstring_t_DEFAULT;
        CSTRING_RC              rc  =   cstring_assign(&str, s);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not assign", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(cch, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str.ptr));
            TEST_INT_GE(cch, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }}

    {
        cstring_t       str =   cstring_t_DEFAULT;

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            cstring_char_t const*   s   =   alphabet + i;
            const size_t            cch =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
            CSTRING_RC              rc  =   cstring_assign(&str, s);

            if (CSTRING_RC_SUCCESS != rc)
            {
                TEST_FAIL_WITH_QUALIFIER("could not assign", cstring_getStatusCodeString(rc));
            }
            else
            {
                TEST_INT_EQ(cch, str.len);
                TEST_PTR_NE(NULL, str.ptr);
                TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str.ptr));
                TEST_INT_GT(cch, str.capacity);
                TEST_INT_GE(str.len, str.capacity);
            }
        }}

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s   =   alphabet + i;
        const size_t            cch =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str;
        CSTRING_RC              rc  =   cstring_create(&str, s);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not create", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(cch, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str.ptr));
            TEST_INT_GE(cch, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }}
}

static void TEST_cstring_assignLen_AND_cstring_createLen()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s   =   alphabet;
        const size_t            cch =   i;
        cstring_t               str =   cstring_t_DEFAULT;
        CSTRING_RC              rc  =   cstring_assignLen(&str, s, i);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not assign (with length)", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(cch, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_N_(s, stlsoft::apply_const_ptr(str.ptr), int(i));
            TEST_INT_GE(cch, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }}

    {
        cstring_t       str =   cstring_t_DEFAULT;

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            cstring_char_t const*   s   =   alphabet;
            const size_t            cch =   i;
            CSTRING_RC              rc  =   cstring_assignLen(&str, s, i);

            if (CSTRING_RC_SUCCESS != rc)
            {
                TEST_FAIL_WITH_QUALIFIER("could not assign (with length)", cstring_getStatusCodeString(rc));
            }
            else
            {
                TEST_INT_EQ(cch, str.len);
                TEST_PTR_NE(NULL, str.ptr);
                TEST_STR_EQ_N_(s, stlsoft::apply_const_ptr(str.ptr), int(i));
                TEST_INT_GE(cch, str.capacity);
                TEST_INT_GE(str.len, str.capacity);
            }
        }}

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s   =   alphabet;
        const size_t            cch =   i;
        cstring_t               str;
        CSTRING_RC              rc  =   cstring_createLen(&str, s, i);

        if (CSTRING_RC_SUCCESS != rc)
        {
            TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_getStatusCodeString(rc));
        }
        else
        {
            TEST_INT_EQ(cch, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            TEST_STR_EQ_N_(s, stlsoft::apply_const_ptr(str.ptr), int(i));
            TEST_INT_GE(cch, str.capacity);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }}
}

static void TEST_cstring_append_AND_cstring_appendLen()
{
    {
        cstring_t str = cstring_t_DEFAULT;

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            cstring_char_t  s[2]    =   { alphabet[i], '\0' };
            CSTRING_RC      rc      =   cstring_append(&str, s);

            if (CSTRING_RC_SUCCESS != rc)
            {
                TEST_FAIL_WITH_QUALIFIER("could not append", cstring_getStatusCodeString(rc));
            }
            else
            {
                TEST_INT_EQ(i + 1, str.len);
                TEST_PTR_NE(NULL, str.ptr);
                TEST_STR_EQ_N_(alphabet, str.ptr, int(i));
                TEST_INT_GE(i + 1, str.capacity);
                TEST_INT_GE(str.len, str.capacity);
            }
        }}

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }

    {
        cstring_t str = cstring_t_DEFAULT;

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            CSTRING_RC rc = cstring_appendLen(&str, &alphabet[i], 1);

            if (CSTRING_RC_SUCCESS != rc)
            {
                TEST_FAIL_WITH_QUALIFIER("could not append (with length)", cstring_getStatusCodeString(rc));
            }
            else
            {
                TEST_INT_EQ(i + 1, str.len);
                TEST_PTR_NE(NULL, str.ptr);
                TEST_STR_EQ_N_(alphabet, str.ptr, int(i));
                TEST_INT_GT(i, str.capacity);
                TEST_INT_GE(str.len, str.capacity);
            }
        }}

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }
}

static void TEST_cstring_truncate()
{
    {
        cstring_t str = cstring_t_DEFAULT;

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, cstring_truncate(&str, 0u));
        TEST_INT_EQ(0u, str.len);
        TEST_INT_EQ(0u, str.capacity);

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, cstring_truncate(&str, 1u));
        TEST_INT_EQ(0u, str.len);
        TEST_INT_EQ(0u, str.capacity);

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, cstring_truncate(&str, 100u));
        TEST_INT_EQ(0u, str.len);
        TEST_INT_EQ(0u, str.capacity);

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, cstring_truncate(&str, 100000u));
        TEST_INT_EQ(0u, str.len);
        TEST_INT_EQ(0u, str.capacity);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }

    {
        cstring_t str;

        if (CSTRING_RC_SUCCESS == cstring_create(&str, alphabet))
        {
            { for (size_t i = 1000; ; --i)
            {
                cstring_truncate(&str, i);

                TEST_INT_LE(26u, str.len);

                if (i < 26u)
                {
                    TEST_INT_EQ(i, str.len);
                }

                if (0u == i)
                {
                    break;
                }
            }}
        }

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }
}

static void TEST_cstring_appendLen_KEEPS_CAPACITY()
{
    cstring_t str = cstring_t_DEFAULT;

    { for (size_t c = 1u; c != APPEND_ITERATIONS; c *= 10u)
    {
        cstring_setCapacity(&str, c);

        cstring_char_t const* const p = str.ptr;

        { for (size_t i = 0; i != str.capacity; ++i)
        {
            cstring_appendLen(&str, CSTRING_T_("~"), 1);

            TEST_INT_EQ(i + 1, str.len);
            TEST_PTR_EQ(p, str.ptr);
            TEST_INT_GE(c, str.capacity);
        }}

        cstring_truncate(&str, 0u);
    }}

    cstring_destroy(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_EQ(0, str.flags);
}


static void TEST_cstring_init_AND_cstring_destroy()
{
    cstring_t   str;

    cstring_init(&str);

    TEST_INT_GE(str.len, str.capacity);

    cstring_destroy(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_EQ(0, str.flags);
}

static void TEST_cstring_create()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n   =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s   =   alphabet + n;

        cstring_create(&str, s);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
}

static void TEST_cstring_createLen()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n   =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s   =   alphabet + n;

        cstring_createLen(&str, s, i);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
}

static void TEST_cstring_createEx()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   0;

        cstring_createEx(&str, s, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   CSTRING_F_MEMORY_IS_BORROWED;
        cstring_char_t              buff[]  =   CSTRING_T_("[01234567890123456789]");
        CSTRING_RC                  rc;

        rc = cstring_createEx(&str, s, flags, &buff[0] + 1, STLSOFT_NUM_ELEMENTS(buff) - 3);

        TEST_CHAR_EQ(CSTRING_T_('['), buff[0]);
        TEST_CHAR_EQ(CSTRING_T_(']'), buff[STLSOFT_NUM_ELEMENTS(buff) - 2]);
        TEST_CHAR_EQ(CSTRING_T_('\0'), buff[STLSOFT_NUM_ELEMENTS(buff) - 1]);

        if (i < STLSOFT_NUM_ELEMENTS(buff) - 3)
        {
            TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

            TEST_INT_GE(i, str.len);
            TEST_STR_EQ_(s, str.ptr);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
        else
        {
            TEST_ENUM_EQ(CSTRING_RC_EXCEEDBORROWEDCAPACITY, rc);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }}

#ifdef WIN32

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   CSTRING_F_USE_WINDOWS_GLOBAL_MEMORY;

        cstring_createEx(&str, s, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);
        TEST_INT_GE(str.capacity, ::GlobalSize(str.ptr));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   CSTRING_F_USE_WINDOWS_PROCESSHEAP_MEMORY;

        cstring_createEx(&str, s, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);
        TEST_INT_GE(str.capacity, ::HeapSize(::GetProcessHeap(), 0, str.ptr));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   CSTRING_F_USE_WINDOWS_COM_TASK_MEMORY;

        cstring_createEx(&str, s, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);
        TEST_INT_GE(str.capacity, comstl::CoTaskMemGetSize(str.ptr));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
#endif /* WIN32 */
}

static void TEST_cstring_createLenEx()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   0;

        cstring_createLenEx(&str, s, i, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   CSTRING_F_MEMORY_IS_BORROWED;
        cstring_char_t              buff[]  =   CSTRING_T_("[01234567890123456789]");
        CSTRING_RC                  rc;

        rc = cstring_createLenEx(&str, s, i, flags, &buff[0] + 1, STLSOFT_NUM_ELEMENTS(buff) - 3);

        TEST_CHAR_EQ(CSTRING_T_('['), buff[0]);
        TEST_CHAR_EQ(CSTRING_T_(']'), buff[STLSOFT_NUM_ELEMENTS(buff) - 2]);
        TEST_CHAR_EQ(CSTRING_T_('\0'), buff[STLSOFT_NUM_ELEMENTS(buff) - 1]);

        if (i < STLSOFT_NUM_ELEMENTS(buff) - 3)
        {
            TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

            TEST_INT_GE(i, str.len);
            TEST_STR_EQ_(s, str.ptr);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
        else
        {
            TEST_ENUM_EQ(CSTRING_RC_EXCEEDBORROWEDCAPACITY, rc);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
    }}

#ifdef WIN32

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   CSTRING_F_USE_WINDOWS_GLOBAL_MEMORY;

        cstring_createLenEx(&str, s, i, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);
        TEST_INT_GE(str.capacity, ::GlobalSize(str.ptr));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   CSTRING_F_USE_WINDOWS_PROCESSHEAP_MEMORY;

        cstring_createLenEx(&str, s, i, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);
        TEST_INT_GE(str.capacity, ::HeapSize(::GetProcessHeap(), 0, str.ptr));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   CSTRING_F_USE_WINDOWS_COM_TASK_MEMORY;

        cstring_createLenEx(&str, s, i, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        TEST_STR_EQ_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);
        TEST_INT_GE(str.capacity, comstl::CoTaskMemGetSize(str.ptr));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
#endif /* WIN32 */
}

static void TEST_cstring_assignLen_KEEPS_CAPACITY()
{
    cstring_t   str =   cstring_t_DEFAULT;

    { for (size_t c = 1u; c != ASSIGN_ITERATIONS; c *= 10u)
    {
        cstring_setCapacity(&str, c);

        string_t                    s(str.capacity, '~');
        cstring_char_t const* const p = str.ptr;

        { for (size_t i = 0; i != str.capacity + 1; ++i)
        {
            cstring_assignLen(&str, s.c_str(), i);

            TEST_INT_EQ(i, str.len);
            TEST_PTR_EQ(p, str.ptr);
            TEST_INT_GE(c, str.capacity);
        }}

        cstring_truncate(&str, 0u);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_INT_NE(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    cstring_destroy(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_EQ(0, str.flags);
}

static void TEST_cstring_assign_KEEPS_CAPACITY()
{
    cstring_t   str =   cstring_t_DEFAULT;

    { for (size_t c = 1u; c != ASSIGN_ITERATIONS; c *= 10u)
    {
        cstring_setCapacity(&str, c);

        string_t                s(str.capacity, '~');
        cstring_char_t const*   p = str.ptr;

        { for (size_t i = 0; i != str.capacity + 1; ++i)
        {
            cstring_assign(&str, s.c_str() + i);

            TEST_INT_EQ(s.size() - i, str.len);
            TEST_PTR_EQ(p, str.ptr);
            TEST_INT_GE(c, str.capacity);
        }}

        cstring_truncate(&str, 0u);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_INT_NE(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    cstring_destroy(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_EQ(0, str.flags);
}

static void TEST_cstring_copy()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s       =   alphabet + i;
        const size_t            cch     =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str1    =   cstring_t_DEFAULT;
        cstring_t               str2    =   cstring_t_DEFAULT;
        CSTRING_RC              rc      =   cstring_assign(&str1, s);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str1.len);
        TEST_PTR_NE(NULL, str1.ptr);
        TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str1.ptr));
        TEST_INT_GE(cch, str1.capacity);
        TEST_INT_GE(str1.len, str1.capacity);

        rc = cstring_copy(&str2, &str1);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str2.len);
        TEST_PTR_NE(NULL, str2.ptr);
        TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str2.ptr));
        TEST_INT_GE(cch, str2.capacity);
        TEST_INT_GE(str2.len, str2.capacity);

        TEST_PTR_NE(str1.ptr, str2.ptr);

        cstring_destroy(&str1);
        cstring_destroy(&str2);

        TEST_INT_EQ(0u, str1.len);
        TEST_PTR_EQ(NULL, str1.ptr);
        TEST_INT_EQ(0u, str1.capacity);
        TEST_INT_EQ(0, str1.flags);

        TEST_INT_EQ(0u, str2.len);
        TEST_PTR_EQ(NULL, str2.ptr);
        TEST_INT_EQ(0u, str2.capacity);
        TEST_INT_EQ(0, str2.flags);
    }}
}

static void TEST_cstring_yield()
{
    {
        cstring_t       str =   cstring_t_DEFAULT;
        cstring_char_t* p;
        CSTRING_RC      rc  =   cstring_yield(&str, &p);

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

        TEST_PTR_EQ(NULL, stlsoft::apply_const_ptr(stlsoft::apply_const_ptr(str.ptr)));
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        TEST_PTR_EQ(NULL, p);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s   =   alphabet + i;
        const size_t            cch =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str =   cstring_t_DEFAULT;
        CSTRING_RC              rc  =   cstring_assign(&str, s);
        cstring_char_t*         p;

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str.ptr));
        TEST_INT_GE(cch, str.capacity);
        TEST_INT_GE(str.len, str.capacity);

        rc = cstring_yield(&str, &p);

        stlsoft::scoped_handle<void*>   scoper(p, ::free);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        TEST_PTR_NE(NULL, p);
        TEST_STR_EQ_(s, stlsoft::apply_const_ptr(p));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, stlsoft::apply_const_ptr(str.ptr));
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
}

static void TEST_cstring_yield2()
{
    {
        cstring_t       str =   cstring_t_DEFAULT;
        cstring_char_t* p;
        void*           raw;
        CSTRING_RC      rc  =   cstring_yield2(&str, &p, &raw);

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);

        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        TEST_PTR_EQ(NULL, p);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s   =   alphabet + i;
        const size_t            cch =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str =   cstring_t_DEFAULT;
        CSTRING_RC              rc  =   cstring_assign(&str, s);
        cstring_char_t*         p;
        void*                   raw;

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str.ptr));
        TEST_INT_GE(cch, str.capacity);
        TEST_INT_GE(str.len, str.capacity);

        rc = cstring_yield2(&str, &p, &raw);

        stlsoft::scoped_handle<void*>   scoper(raw, ::free);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        TEST_PTR_NE(NULL, p);
        TEST_STR_EQ_(s, stlsoft::apply_const_ptr(p));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, stlsoft::apply_const_ptr(str.ptr));
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
}

static void TEST_cstring_swap()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s       =   alphabet + i;
        const size_t            cch     =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str1    =   cstring_t_DEFAULT;
        cstring_t               str2    =   cstring_t_DEFAULT;
        CSTRING_RC              rc      =   cstring_assign(&str1, s);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str1.len);
        TEST_PTR_NE(NULL, str1.ptr);
        TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str1.ptr));
        TEST_INT_GE(cch, str1.capacity);
        TEST_INT_GE(str1.len, str1.capacity);

        TEST_INT_EQ(0u, str2.len);
        TEST_PTR_EQ(NULL, str2.ptr);
        TEST_INT_EQ(0u, str2.capacity);
        TEST_INT_EQ(0, str2.flags);

        rc = cstring_swap(&str2, &str1);

        XTESTS_REQUIRE(TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(0u, str1.len);
        TEST_PTR_EQ(NULL, str1.ptr);
        TEST_INT_EQ(0u, str1.capacity);
        TEST_INT_EQ(0, str1.flags);

        TEST_INT_EQ(cch, str2.len);
        TEST_PTR_NE(NULL, str2.ptr);
        TEST_STR_EQ_(s, stlsoft::apply_const_ptr(str2.ptr));
        TEST_INT_GE(cch, str2.capacity);
        TEST_INT_GE(str2.len, str2.capacity);

        TEST_PTR_NE(str1.ptr, str2.ptr);

        cstring_destroy(&str1);
        cstring_destroy(&str2);

        TEST_INT_EQ(0u, str1.len);
        TEST_PTR_EQ(NULL, str1.ptr);
        TEST_INT_EQ(0u, str1.capacity);
        TEST_INT_EQ(0, str1.flags);

        TEST_INT_EQ(0u, str2.len);
        TEST_PTR_EQ(NULL, str2.ptr);
        TEST_INT_EQ(0u, str2.capacity);
        TEST_INT_EQ(0, str2.flags);
    }}
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

