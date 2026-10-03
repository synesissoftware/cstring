/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/cstring.borrowed/entry.c
 *
 * Purpose: Tests borrowed string functionality.
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

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_cstring_createEx_FLAG_COMBINATIONS(void);
static void TEST_cstring_createEx_GROW_TO_HEAP(void);
static void TEST_cstring_createLenEx_GROW_TO_HEAP(void);
static void TEST_cstring_setCapacity_GROW_TO_HEAP(void);
static void TEST_cstring_assign_GROW_TO_HEAP(void);
static void TEST_cstring_assignLen_GROW_TO_HEAP(void);
static void TEST_cstring_append_GROW_TO_HEAP(void);
static void TEST_cstring_appendLen_GROW_TO_HEAP(void);


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */


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

    if (XTESTS_START_RUNNER("cstring.borrowed", verbosity))
    {
        XTESTS_RUN_CASE(TEST_cstring_createEx_FLAG_COMBINATIONS);
        XTESTS_RUN_CASE(TEST_cstring_createEx_GROW_TO_HEAP);
        XTESTS_RUN_CASE(TEST_cstring_createLenEx_GROW_TO_HEAP);
        XTESTS_RUN_CASE(TEST_cstring_setCapacity_GROW_TO_HEAP);
        XTESTS_RUN_CASE(TEST_cstring_assign_GROW_TO_HEAP);
        XTESTS_RUN_CASE(TEST_cstring_assignLen_GROW_TO_HEAP);
        XTESTS_RUN_CASE(TEST_cstring_append_GROW_TO_HEAP);
        XTESTS_RUN_CASE(TEST_cstring_appendLen_GROW_TO_HEAP);

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

static void TEST_cstring_createEx_FLAG_COMBINATIONS(void)
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

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(goods); ++i)
    {
        int const   flags   =   0
                            |   goods[i]
                            ;
        char        buff[10];
        cstring_t   cs;
        CSTRING_RC  rc;

        rc = cstring_createEx(&cs, "string: ", flags, buff, sizeof(buff));

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    }}

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(bads); ++i)
    {
        int const   flags   =   0
                            |   bads[i]
                            ;
        char        buff[10];
        cstring_t   cs;
        CSTRING_RC  rc;

        rc = cstring_createEx(&cs, "string: ", flags, buff, sizeof(buff));

        TEST_ENUM_NE(CSTRING_RC_SUCCESS, rc);
    }}
}

static void TEST_cstring_createEx_GROW_TO_HEAP(void)
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

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(5u, cs.len);
    TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);

    cstring_destroy(&cs);


    /* try to resize. */

    rc = cstring_createEx(&cs, "oversized", flags, buff, sizeof(buff));

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_ENUM_EQ(CSTRING_RC_OUTOFMEMORY, rc);
        TEST_INT_EQ(flags, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_EQ(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
        TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        TEST_INT_EQ(0, cs.flags);
        TEST_MS_EQ("oversized", cs.ptr);
        TEST_PTR_NE(buff, cs.ptr);

        cstring_destroy(&cs);
    }
}

static void TEST_cstring_createLenEx_GROW_TO_HEAP(void)
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

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(5u, cs.len);
    TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);

    cstring_destroy(&cs);


    /* try to resize. */

    rc = cstring_createLenEx(&cs, "oversized string", 9, flags, buff, sizeof(buff));

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_ENUM_EQ(CSTRING_RC_OUTOFMEMORY, rc);
        TEST_INT_EQ(flags, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_EQ(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
        TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        TEST_INT_EQ(0, cs.flags);
        TEST_MS_EQ("oversized", cs.ptr);
        TEST_PTR_NE(buff, cs.ptr);

        cstring_destroy(&cs);
    }
}

static void TEST_cstring_setCapacity_GROW_TO_HEAP(void)
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

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(5u, cs.len);
    TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_setCapacity(&cs, 9);

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_ENUM_EQ(CSTRING_RC_OUTOFMEMORY, rc);
        TEST_INT_EQ(flags, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_EQ(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
        TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        TEST_INT_EQ(0, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_NE(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
        TEST_INT_GE(9u - 1u, cs.capacity);
    }

    cstring_destroy(&cs);
}

static void TEST_cstring_assign_GROW_TO_HEAP(void)
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

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(5u, cs.len);
    TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_assign(&cs, "oversized");

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_ENUM_EQ(CSTRING_RC_OUTOFMEMORY, rc);
        TEST_INT_EQ(flags, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_EQ(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
        TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        TEST_INT_EQ(0, cs.flags);
        TEST_MS_EQ("oversized", cs.ptr);
        TEST_PTR_NE(buff, cs.ptr);


        /* shrink again */
        rc = cstring_assign(&cs, "small");

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
        TEST_INT_EQ(0, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_NE(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
    }

    cstring_destroy(&cs);
}

static void TEST_cstring_assignLen_GROW_TO_HEAP(void)
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

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(5u, cs.len);
    TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_assignLen(&cs, "oversized", 9);

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_ENUM_EQ(CSTRING_RC_OUTOFMEMORY, rc);
        TEST_INT_EQ(flags, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_EQ(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
        TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        TEST_INT_EQ(0, cs.flags);
        TEST_MS_EQ("oversized", cs.ptr);
        TEST_PTR_NE(buff, cs.ptr);


        /* shrink again */
        rc = cstring_assign(&cs, "small");

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
        TEST_INT_EQ(0, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_NE(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
    }

    cstring_destroy(&cs);
}

static void TEST_cstring_append_GROW_TO_HEAP(void)
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

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(5u, cs.len);
    TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_append(&cs, "ish, but big enough");

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_ENUM_EQ(CSTRING_RC_OUTOFMEMORY, rc);
        TEST_INT_EQ(flags, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_EQ(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
        TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        TEST_INT_EQ(0, cs.flags);
        TEST_MS_EQ("smallish, but big enough", cs.ptr);
        TEST_PTR_NE(buff, cs.ptr);


        /* shrink again */
        rc = cstring_assign(&cs, "small");

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
        TEST_INT_EQ(0, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_NE(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
    }

    cstring_destroy(&cs);
}

static void TEST_cstring_appendLen_GROW_TO_HEAP(void)
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

    TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
    TEST_INT_EQ(5u, cs.len);
    TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);


    /* try to resize. */

    rc = cstring_appendLen(&cs, "ish, but big enough", 19);

    if (CSTRING_RC_SUCCESS != rc)
    {
        TEST_ENUM_EQ(CSTRING_RC_OUTOFMEMORY, rc);
        TEST_INT_EQ(flags, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_EQ(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
        TEST_INT_EQ(sizeof(buff) - 1u, cs.capacity);
    }
    else
    {
        TEST_INT_EQ(0, cs.flags);
        TEST_MS_EQ("smallish, but big enough", cs.ptr);
        TEST_PTR_NE(buff, cs.ptr);


        /* shrink again */
        rc = cstring_assign(&cs, "small");

        TEST_ENUM_EQ(CSTRING_RC_SUCCESS, rc);
        TEST_INT_EQ(0, cs.flags);
        TEST_INT_EQ(5u, cs.len);
        TEST_PTR_NE(buff, cs.ptr);
        TEST_MS_EQ("small", cs.ptr);
    }

    cstring_destroy(&cs);
}


/* ///////////////////////////// end of file //////////////////////////// */
