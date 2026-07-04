/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.cstring.1.cpp
 *
 * Purpose: Unit-tests for general functionality.
 *
 * Created: 23rd May 2009
 * Updated: 2nd September 2025
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

    static void test_1_0(void);
    static void test_1_1(void);
    static void test_1_2(void);
    static void test_1_3(void);
    static void test_1_4(void);
    static void test_1_5(void);
    static void test_1_6(void);
    static void test_1_7(void);
    static void test_1_8(void);
    static void test_1_9(void);

    static void test_2_0(void);
    static void test_2_1(void);
    static void test_2_2(void);
    static void test_2_3(void);
    static void test_2_4(void);
    static void test_2_5(void);
    static void test_2_6(void);
    static void test_2_7(void);
    static void test_2_8(void);
    static void test_2_9(void);
    static void test_2_10(void);
    static void test_2_11(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

const char TEST_FILE_NAME[] = "test.unit.cstring.1.txt";

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

    if (XTESTS_START_RUNNER("test.unit.cstring.1", verbosity))
    {
        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_2);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_4);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);
        XTESTS_RUN_CASE(test_1_7);
        XTESTS_RUN_CASE(test_1_8);
        XTESTS_RUN_CASE(test_1_9);

        XTESTS_RUN_CASE(test_2_0);
        XTESTS_RUN_CASE(test_2_1);
        XTESTS_RUN_CASE(test_2_2);
        XTESTS_RUN_CASE(test_2_3);
        XTESTS_RUN_CASE(test_2_4);
        XTESTS_RUN_CASE(test_2_5);
        XTESTS_RUN_CASE(test_2_6);
        XTESTS_RUN_CASE(test_2_7);
        XTESTS_RUN_CASE(test_2_8);
        XTESTS_RUN_CASE(test_2_9);
        XTESTS_RUN_CASE(test_2_10);
        XTESTS_RUN_CASE(test_2_11);

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

#ifdef CSTRING_USE_WIDE_STRINGS

# define CSTRING_T_(x)                                      L ## x
# define XTESTS_TEST_STRING_EQUAL_                          XTESTS_TEST_WIDE_STRING_EQUAL
# define XTESTS_TEST_STRING_EQUAL_N_                        XTESTS_TEST_WIDE_STRING_EQUAL_N
#else /* ? CSTRING_USE_WIDE_STRINGS */

# define CSTRING_T_(x)                                      x
# define XTESTS_TEST_STRING_EQUAL_                          XTESTS_TEST_MULTIBYTE_STRING_EQUAL
# define XTESTS_TEST_STRING_EQUAL_N_                        XTESTS_TEST_MULTIBYTE_STRING_EQUAL_N
#endif /* CSTRING_USE_WIDE_STRINGS */


namespace
{

#ifdef CSTRING_USE_WIDE_STRINGS
    typedef std::wstring                                    string_t;
#else /* ? CSTRING_USE_WIDE_STRINGS */
    typedef std::string                                     string_t;
#endif /* CSTRING_USE_WIDE_STRINGS */

    static const cstring_char_t alphabet[] = CSTRING_T_("abcdefghijklmnopqrstuvwxyz");


static void test_1_0()
{
    cstring_t str = cstring_t_DEFAULT;

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, stlsoft::apply_const_ptr(str.ptr));
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_GE(str.len, str.capacity);
}

static void test_1_1()
{
    cstring_t str;

    cstring_init(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_GE(str.len, str.capacity);
}

static void test_1_2()
{
    cstring_t   str =   cstring_t_DEFAULT;
    CSTRING_RC  rc  =   cstring_setCapacity(&str, 10);

    if (CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not set capacity", cstring_error(rc));
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

static void test_1_3()
{
    {
        cstring_t   str =   cstring_t_DEFAULT;
        CSTRING_RC  rc  =   cstring_assign(&str, NULL);

        if (CSTRING_RC_SUCCESS != rc)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not assign", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(CSTRING_T_(""), str.ptr);
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not assign", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(CSTRING_T_(""), str.ptr);
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(CSTRING_T_(""), str.ptr);
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(CSTRING_T_(""), str.ptr);
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(CSTRING_T_(""), str.ptr);
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(0u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(CSTRING_T_(""), str.ptr);
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(5u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(CSTRING_T_(""), str.ptr);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[0]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[1]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[2]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[3]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[4]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[5]);
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(5u, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(CSTRING_T_(""), str.ptr);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[0]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[1]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[2]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[3]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[4]);
            XTESTS_TEST_CHARACTER_EQUAL('\0', str.ptr[5]);
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

static void test_1_4()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s   =   alphabet + i;
        const size_t            cch =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str =   cstring_t_DEFAULT;
        CSTRING_RC              rc  =   cstring_assign(&str, s);

        if (CSTRING_RC_SUCCESS != rc)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not assign", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(cch, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str.ptr));
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
                XTESTS_TEST_FAIL_WITH_QUALIFIER("could not assign", cstring_error(rc));
            }
            else
            {
                TEST_INT_EQ(cch, str.len);
                TEST_PTR_NE(NULL, str.ptr);
                XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str.ptr));
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(cch, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str.ptr));
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

static void test_1_5()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s   =   alphabet;
        const size_t            cch =   i;
        cstring_t               str =   cstring_t_DEFAULT;
        CSTRING_RC              rc  =   cstring_assignLen(&str, s, i);

        if (CSTRING_RC_SUCCESS != rc)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not assign (with length)", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(cch, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_N_(s, stlsoft::apply_const_ptr(str.ptr), int(i));
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
                XTESTS_TEST_FAIL_WITH_QUALIFIER("could not assign (with length)", cstring_error(rc));
            }
            else
            {
                TEST_INT_EQ(cch, str.len);
                TEST_PTR_NE(NULL, str.ptr);
                XTESTS_TEST_STRING_EQUAL_N_(s, stlsoft::apply_const_ptr(str.ptr), int(i));
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
            XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create (with length)", cstring_error(rc));
        }
        else
        {
            TEST_INT_EQ(cch, str.len);
            TEST_PTR_NE(NULL, str.ptr);
            XTESTS_TEST_STRING_EQUAL_N_(s, stlsoft::apply_const_ptr(str.ptr), int(i));
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

static void test_1_6()
{
    {
        cstring_t str = cstring_t_DEFAULT;

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
        {
            cstring_char_t  s[2]    =   { alphabet[i], '\0' };
            CSTRING_RC      rc      =   cstring_append(&str, s);

            if (CSTRING_RC_SUCCESS != rc)
            {
                XTESTS_TEST_FAIL_WITH_QUALIFIER("could not append", cstring_error(rc));
            }
            else
            {
                TEST_INT_EQ(i + 1, str.len);
                TEST_PTR_NE(NULL, str.ptr);
                XTESTS_TEST_STRING_EQUAL_N_(alphabet, str.ptr, int(i));
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
                XTESTS_TEST_FAIL_WITH_QUALIFIER("could not append (with length)", cstring_error(rc));
            }
            else
            {
                TEST_INT_EQ(i + 1, str.len);
                TEST_PTR_NE(NULL, str.ptr);
                XTESTS_TEST_STRING_EQUAL_N_(alphabet, str.ptr, int(i));
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

static void test_1_7()
{
    {
        cstring_t str = cstring_t_DEFAULT;

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, cstring_truncate(&str, 0u));
        TEST_INT_EQ(0u, str.len);
        TEST_INT_EQ(0u, str.capacity);

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, cstring_truncate(&str, 1u));
        TEST_INT_EQ(0u, str.len);
        TEST_INT_EQ(0u, str.capacity);

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, cstring_truncate(&str, 100u));
        TEST_INT_EQ(0u, str.len);
        TEST_INT_EQ(0u, str.capacity);

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, cstring_truncate(&str, 100000u));
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

                XTESTS_TEST_INTEGER_LESS_OR_EQUAL(26u, str.len);

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

static void test_1_8()
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

static void test_1_9()
{
}



static void test_2_0()
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

static void test_2_1()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n   =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s   =   alphabet + n;

        cstring_create(&str, s);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
}

static void test_2_2()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n   =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s   =   alphabet + n;

        cstring_createLen(&str, s, i);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
        TEST_INT_GE(str.len, str.capacity);

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
}

static void test_2_3()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   0;

        cstring_createEx(&str, s, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
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

        XTESTS_TEST_CHARACTER_EQUAL(CSTRING_T_('['), buff[0]);
        XTESTS_TEST_CHARACTER_EQUAL(CSTRING_T_(']'), buff[STLSOFT_NUM_ELEMENTS(buff) - 2]);
        XTESTS_TEST_CHARACTER_EQUAL(CSTRING_T_('\0'), buff[STLSOFT_NUM_ELEMENTS(buff) - 1]);

        if (i < STLSOFT_NUM_ELEMENTS(buff) - 3)
        {
            XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);

            TEST_INT_GE(i, str.len);
            XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
        else
        {
            XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_EXCEEDBORROWEDCAPACITY, rc);

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
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
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
        cstring_flags_t             flags   =   CSTRING_F_USE_WIN32_PROCESSHEAP_MEMORY;

        cstring_createEx(&str, s, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
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
        cstring_flags_t             flags   =   CSTRING_F_USE_WIN32_COM_TASK_MEMORY;

        cstring_createEx(&str, s, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
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

static void test_2_4()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_t                   str;
        const size_t                n       =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_char_t const* const s       =   alphabet + n;
        cstring_flags_t             flags   =   0;

        cstring_createLenEx(&str, s, i, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
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

        XTESTS_TEST_CHARACTER_EQUAL(CSTRING_T_('['), buff[0]);
        XTESTS_TEST_CHARACTER_EQUAL(CSTRING_T_(']'), buff[STLSOFT_NUM_ELEMENTS(buff) - 2]);
        XTESTS_TEST_CHARACTER_EQUAL(CSTRING_T_('\0'), buff[STLSOFT_NUM_ELEMENTS(buff) - 1]);

        if (i < STLSOFT_NUM_ELEMENTS(buff) - 3)
        {
            XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);

            TEST_INT_GE(i, str.len);
            XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
            TEST_INT_GE(str.len, str.capacity);

            cstring_destroy(&str);

            TEST_INT_EQ(0u, str.len);
            TEST_PTR_EQ(NULL, str.ptr);
            TEST_INT_EQ(0u, str.capacity);
            TEST_INT_EQ(0, str.flags);
        }
        else
        {
            XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_EXCEEDBORROWEDCAPACITY, rc);

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
        cstring_flags_t             flags   =   CSTRING_F_USE_WIN32_GLOBAL_MEMORY;

        cstring_createLenEx(&str, s, i, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
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
        cstring_flags_t             flags   =   CSTRING_F_USE_WIN32_PROCESSHEAP_MEMORY;

        cstring_createLenEx(&str, s, i, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
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
        cstring_flags_t             flags   =   CSTRING_F_USE_WIN32_COM_TASK_MEMORY;

        cstring_createLenEx(&str, s, i, flags, NULL, 0);

        TEST_INT_GE(i, str.len);
        XTESTS_TEST_STRING_EQUAL_(s, str.ptr);
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

static void test_2_5()
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
        XTESTS_TEST_INTEGER_NOT_EQUAL(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    cstring_destroy(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_EQ(0, str.flags);
}

static void test_2_6()
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
        XTESTS_TEST_INTEGER_NOT_EQUAL(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}

    cstring_destroy(&str);

    TEST_INT_EQ(0u, str.len);
    TEST_PTR_EQ(NULL, str.ptr);
    TEST_INT_EQ(0u, str.capacity);
    TEST_INT_EQ(0, str.flags);
}

static void test_2_7()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s       =   alphabet + i;
        const size_t            cch     =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str1    =   cstring_t_DEFAULT;
        cstring_t               str2    =   cstring_t_DEFAULT;
        CSTRING_RC              rc      =   cstring_assign(&str1, s);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str1.len);
        TEST_PTR_NE(NULL, str1.ptr);
        XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str1.ptr));
        TEST_INT_GE(cch, str1.capacity);
        TEST_INT_GE(str1.len, str1.capacity);

        rc = cstring_copy(&str2, &str1);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str2.len);
        TEST_PTR_NE(NULL, str2.ptr);
        XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str2.ptr));
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

static void test_2_8()
{
    {
        cstring_t       str =   cstring_t_DEFAULT;
        cstring_char_t* p;
        CSTRING_RC      rc  =   cstring_yield(&str, &p);

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);

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

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str.ptr));
        TEST_INT_GE(cch, str.capacity);
        TEST_INT_GE(str.len, str.capacity);

        rc = cstring_yield(&str, &p);

        stlsoft::scoped_handle<void*>   scoper(p, ::free);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        TEST_PTR_NE(NULL, p);
        XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(p));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, stlsoft::apply_const_ptr(str.ptr));
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
}

static void test_2_9()
{
    {
        cstring_t       str =   cstring_t_DEFAULT;
        cstring_char_t* p;
        void*           raw;
        CSTRING_RC      rc  =   cstring_yield2(&str, &p, &raw);

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);

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

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str.len);
        TEST_PTR_NE(NULL, str.ptr);
        XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str.ptr));
        TEST_INT_GE(cch, str.capacity);
        TEST_INT_GE(str.len, str.capacity);

        rc = cstring_yield2(&str, &p, &raw);

        stlsoft::scoped_handle<void*>   scoper(raw, ::free);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        TEST_PTR_EQ(NULL, str.ptr);
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);

        TEST_PTR_NE(NULL, p);
        XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(p));

        cstring_destroy(&str);

        TEST_INT_EQ(0u, str.len);
        TEST_PTR_EQ(NULL, stlsoft::apply_const_ptr(str.ptr));
        TEST_INT_EQ(0u, str.capacity);
        TEST_INT_EQ(0, str.flags);
    }}
}

static void test_2_10()
{
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(alphabet) - 1; ++i)
    {
        cstring_char_t const*   s       =   alphabet + i;
        const size_t            cch     =   (STLSOFT_NUM_ELEMENTS(alphabet) - 1) - i;
        cstring_t               str1    =   cstring_t_DEFAULT;
        cstring_t               str2    =   cstring_t_DEFAULT;
        CSTRING_RC              rc      =   cstring_assign(&str1, s);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(cch, str1.len);
        TEST_PTR_NE(NULL, str1.ptr);
        XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str1.ptr));
        TEST_INT_GE(cch, str1.capacity);
        TEST_INT_GE(str1.len, str1.capacity);

        TEST_INT_EQ(0u, str2.len);
        TEST_PTR_EQ(NULL, str2.ptr);
        TEST_INT_EQ(0u, str2.capacity);
        TEST_INT_EQ(0, str2.flags);

        rc = cstring_swap(&str2, &str1);

        XTESTS_REQUIRE(XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc));
        TEST_INT_EQ(0u, str1.len);
        TEST_PTR_EQ(NULL, str1.ptr);
        TEST_INT_EQ(0u, str1.capacity);
        TEST_INT_EQ(0, str1.flags);

        TEST_INT_EQ(cch, str2.len);
        TEST_PTR_NE(NULL, str2.ptr);
        XTESTS_TEST_STRING_EQUAL_(s, stlsoft::apply_const_ptr(str2.ptr));
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

static void test_2_11()
{
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

