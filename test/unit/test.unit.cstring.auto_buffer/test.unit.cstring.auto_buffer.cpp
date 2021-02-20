/* /////////////////////////////////////////////////////////////////////////
 * File:        test.unit.cstring.auto_buffer.cpp
 *
 * Purpose:     Implementation file for the test.unit.cstring.auto_buffer project.
 *
 * Created:     28th July 2011
 * Updated:     20th February 2021
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2011-2021, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
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
#include <comstl/memory/functions.h>
#include <platformstl/error/exceptions.hpp>
#include <platformstl/filesystem/file_lines.hpp>
#include <platformstl/system/system_traits.hpp>

/* Standard C header files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void test_badFlags(void);
    static void test_createEx(void);
    static void test_createLenEx(void);
    static void test_setCapacity(void);
    static void test_assign(void);
    static void test_assignLen(void);
    static void test_append(void);
    static void test_appendLen(void);

} // anonymous namespace

/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

const char TEST_FILE_NAME[] = "test.unit.cstring.auto_buffer.txt";

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

    if(XTESTS_START_RUNNER("test.unit.cstring.auto_buffer", verbosity))
    {
        XTESTS_RUN_CASE(test_badFlags);
        XTESTS_RUN_CASE(test_createEx);
        XTESTS_RUN_CASE(test_createLenEx);
        XTESTS_RUN_CASE(test_setCapacity);
        XTESTS_RUN_CASE(test_assign);
        XTESTS_RUN_CASE(test_assignLen);
        XTESTS_RUN_CASE(test_append);
        XTESTS_RUN_CASE(test_appendLen);

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

    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

static void test_badFlags(void)
{
    static int const goods[] =
    {
        CSTRING_F_MEMORY_IS_BORROWED
    ,   CSTRING_F_MEMORY_IS_BORROWED | CSTRING_F_MEMORY_IS_FIXED
    ,   CSTRING_F_MEMORY_IS_BORROWED | CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
    };

    static int const bads[] =
    {
        0
    ,   CSTRING_F_MEMORY_IS_FIXED
    ,   CSTRING_F_MEMORY_IS_OFFSET
    };

    { for(size_t i = 0; i != STLSOFT_NUM_ELEMENTS(goods); ++i)
    {
        int const   flags   =   0
                            |   goods[i]
                            ;
        char        buff[10];
        cstring_t   cs;
        CSTRING_RC  rc;

        rc = cstring_createEx(&cs, "string: ", flags, buff, sizeof(buff));

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
    }}

    { for(size_t i = 0; i != STLSOFT_NUM_ELEMENTS(bads); ++i)
    {
        int const   flags   =   0
                            |   bads[i]
                            ;
        char        buff[10];
        cstring_t   cs;
        CSTRING_RC  rc;

        rc = cstring_createEx(&cs, "string: ", flags, buff, sizeof(buff));

        XTESTS_TEST_ENUM_NOT_EQUAL(CSTRING_RC_SUCCESS, rc);
    }}
};

static void test_createEx(void)
{
    int const   flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    char        buff[8];
    cstring_t   cs;
    CSTRING_RC  rc;


    /* must succeed in stack buffer. */

    rc = cstring_createEx(&cs, "small", flags, buff, sizeof(buff));

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
    XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
    XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);

    cstring_destroy(&cs);


    /* try to resize. */

    rc = cstring_createEx(&cs, "oversized", flags, buff, sizeof(buff));

    if(CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_OUTOFMEMORY, rc);
        XTESTS_TEST_INTEGER_EQUAL(flags, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
        XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("oversized", cs.ptr);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);

        cstring_destroy(&cs);
    }
}

static void test_createLenEx(void)
{
    int const   flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    char        buff[8];
    cstring_t   cs;
    CSTRING_RC  rc;


    /* must succeed in stack buffer. */

    rc = cstring_createEx(&cs, "small", flags, buff, sizeof(buff));

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
    XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
    XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);

    cstring_destroy(&cs);


    /* try to resize. */

    rc = cstring_createLenEx(&cs, "oversized string", 9, flags, buff, sizeof(buff));

    if(CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_OUTOFMEMORY, rc);
        XTESTS_TEST_INTEGER_EQUAL(flags, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
        XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("oversized", cs.ptr);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);

        cstring_destroy(&cs);
    }
}

static void test_setCapacity(void)
{
    int const   flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    char        buff[8];
    cstring_t   cs;
    CSTRING_RC  rc;


    /* must succeed in stack buffer. */

    rc = cstring_createEx(&cs, "small", flags, buff, sizeof(buff));

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
    XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
    XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_setCapacity(&cs, 9);

    if(CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_OUTOFMEMORY, rc);
        XTESTS_TEST_INTEGER_EQUAL(flags, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
        XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(9u - 1u, cs.capacity);
    }

    cstring_destroy(&cs);
}

static void test_assign(void)
{
    int const   flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    char        buff[8];
    cstring_t   cs;
    CSTRING_RC  rc;


    /* must succeed in stack buffer. */

    rc = cstring_createEx(&cs, "small", flags, buff, sizeof(buff));

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
    XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
    XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_assign(&cs, "oversized");

    if(CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_OUTOFMEMORY, rc);
        XTESTS_TEST_INTEGER_EQUAL(flags, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
        XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("oversized", cs.ptr);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);


        /* shrink again */
        rc = cstring_assign(&cs, "small");

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
    }

    cstring_destroy(&cs);
}

static void test_assignLen(void)
{
    int const   flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    char        buff[8];
    cstring_t   cs;
    CSTRING_RC  rc;


    /* must succeed in stack buffer. */

    rc = cstring_createEx(&cs, "small", flags, buff, sizeof(buff));

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
    XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
    XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_assignLen(&cs, "oversized", 9);

    if(CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_OUTOFMEMORY, rc);
        XTESTS_TEST_INTEGER_EQUAL(flags, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
        XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("oversized", cs.ptr);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);


        /* shrink again */
        rc = cstring_assign(&cs, "small");

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
    }

    cstring_destroy(&cs);
}

static void test_append(void)
{
    int const   flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    char        buff[8];
    cstring_t   cs;
    CSTRING_RC  rc;


    /* must succeed in stack buffer. */

    rc = cstring_createEx(&cs, "small", flags, buff, sizeof(buff));

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
    XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
    XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_append(&cs, "ish, but big enough");

    if(CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_OUTOFMEMORY, rc);
        XTESTS_TEST_INTEGER_EQUAL(flags, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
        XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("smallish, but big enough", cs.ptr);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);


        /* shrink again */
        rc = cstring_assign(&cs, "small");

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
    }

    cstring_destroy(&cs);
}

static void test_appendLen(void)
{
    int const   flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    char        buff[8];
    cstring_t   cs;
    CSTRING_RC  rc;


    /* must succeed in stack buffer. */

    rc = cstring_createEx(&cs, "small", flags, buff, sizeof(buff));

    XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
    XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
    XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_appendLen(&cs, "ish, but big enough", 19);

    if(CSTRING_RC_SUCCESS != rc)
    {
        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_OUTOFMEMORY, rc);
        XTESTS_TEST_INTEGER_EQUAL(flags, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
        XTESTS_TEST_INTEGER_EQUAL(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("smallish, but big enough", cs.ptr);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);


        /* shrink again */
        rc = cstring_assign(&cs, "small");

        XTESTS_TEST_ENUM_EQUAL(CSTRING_RC_SUCCESS, rc);
        XTESTS_TEST_INTEGER_EQUAL(0, cs.flags);
        XTESTS_TEST_INTEGER_EQUAL(5u, cs.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(buff, cs.ptr);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("small", cs.ptr);
    }

    cstring_destroy(&cs);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
