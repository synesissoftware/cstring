/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/cstring_vector/entry.c
 *
 * Purpose: Tests `cstring_vector_t` functionality.
 *
 * Created: 12th January 2024
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <cstring/cstring.vector.h>

/* /////////////////////////////////////
 * general includes
 */

#ifdef USE_PANTHEIOS_EXTRAS_DIAGUTIL_MAIN

# include <pantheios/extras/diagutil/main_leak_trace.h>
#endif

#include "../../cstring_testing.h"

/* xTests header files */
#include <xtests/terse-api.h>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_cstring_vector_t_DEFAULT(void);
static void TEST_cstring_vector_init_ZERO(void);
static void TEST_cstring_vector_init_WITH_CAPACITY(void);
static void TEST_cstring_vector_create_ZERO(void);
static void TEST_cstring_vector_create_N(void);
static void TEST_cstring_vector_insertAt_ONE(void);
static void TEST_cstring_vector_insertAt_LIST(void);


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

static
int main0(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.cstring_vector", verbosity))
    {
        XTESTS_RUN_CASE(TEST_cstring_vector_t_DEFAULT);
        XTESTS_RUN_CASE(TEST_cstring_vector_init_ZERO);
        XTESTS_RUN_CASE(TEST_cstring_vector_init_WITH_CAPACITY);
        XTESTS_RUN_CASE(TEST_cstring_vector_create_ZERO);
        XTESTS_RUN_CASE(TEST_cstring_vector_create_N);
        XTESTS_RUN_CASE(TEST_cstring_vector_insertAt_ONE);
        XTESTS_RUN_CASE(TEST_cstring_vector_insertAt_LIST);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

int main(int argc, char **argv)
{
#ifdef USE_PANTHEIOS_EXTRAS_DIAGUTIL_MAIN

    return pantheios_extras_diagutil_main_leak_trace_invoke(argc, argv, main0);
#else

    return main0(argc, argv);
#endif
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_cstring_vector_t_DEFAULT(void)
{
    cstring_vector_t    csv = cstring_vector_t_DEFAULT;

    TEST_INT_EQ(0, csv.len);
    TEST_PTR_EQ(NULL, csv.ptr);
    TEST_INT_EQ(0, csv.capacity);

    cstring_vector_destroy(&csv);
}

static void TEST_cstring_vector_init_ZERO(void)
{
    cstring_vector_t    csv;
    CSTRING_RC          rc = cstring_vector_init(&csv, 0);

    if (CSTRING_RC_OUTOFMEMORY == rc)
    {
        /*XTESTS_TEST_WARN(*/
    }
    else
    if (CSTRING_RC_SUCCESS == rc)
    {
        TEST_INT_EQ(0, csv.len);
        TEST_PTR_EQ(NULL, csv.ptr);
        TEST_INT_EQ(0, csv.capacity);

        cstring_vector_destroy(&csv);
    }
    else
    {
        TEST_FAIL("should only fail cstring_vector_init() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void TEST_cstring_vector_init_WITH_CAPACITY(void)
{
    cstring_vector_t    csv;
    CSTRING_RC          rc = cstring_vector_init(&csv, 10);

    if (CSTRING_RC_OUTOFMEMORY == rc)
    {
        /*XTESTS_TEST_WARN(*/
    }
    else
    if (CSTRING_RC_SUCCESS == rc)
    {
        TEST_INT_EQ(0, csv.len);
        TEST_PTR_NE(NULL, csv.ptr);
        TEST_INT_GE(10, csv.capacity);

        cstring_vector_destroy(&csv);
    }
    else
    {
        TEST_FAIL("should only fail cstring_vector_init() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void TEST_cstring_vector_create_ZERO(void)
{
    cstring_vector_t    csv;
    CSTRING_RC          rc = cstring_vector_create(&csv, 0);

    if (CSTRING_RC_OUTOFMEMORY == rc)
    {
        /*XTESTS_TEST_WARN(*/
    }
    else
    if (CSTRING_RC_SUCCESS == rc)
    {
        TEST_INT_EQ(0, csv.len);
        TEST_PTR_EQ(NULL, csv.ptr);
        TEST_INT_EQ(0, csv.capacity);

        cstring_vector_destroy(&csv);
    }
    else
    {
        TEST_FAIL("should only fail cstring_vector_create() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void TEST_cstring_vector_create_N(void)
{
    cstring_vector_t    csv;
    CSTRING_RC          rc = cstring_vector_create(&csv, 10);

    if (CSTRING_RC_OUTOFMEMORY == rc)
    {
        /*XTESTS_TEST_WARN(*/
    }
    else
    if (CSTRING_RC_SUCCESS == rc)
    {
        TEST_INT_EQ(10, csv.len);
        TEST_PTR_NE(NULL, csv.ptr);
        TEST_INT_GE(10, csv.capacity);

        cstring_vector_destroy(&csv);
    }
    else
    {
        TEST_FAIL("should only fail cstring_vector_create() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void TEST_cstring_vector_insertAt_ONE(void)
{
    cstring_vector_t    csv;
    CSTRING_RC          rc = cstring_vector_create(&csv, 0);

    if (CSTRING_RC_OUTOFMEMORY == rc)
    {
        /*XTESTS_TEST_WARN(*/
    }
    else
    if (CSTRING_RC_SUCCESS == rc)
    {
        cstring_t cs = cstring_t_DEFAULT;

        TEST_INT_EQ(0, csv.len);
        TEST_PTR_EQ(NULL, csv.ptr);
        TEST_INT_EQ(0, csv.capacity);

        rc = cstring_vector_insertAt(&csv, 0, &cs, 1);

        if (CSTRING_RC_OUTOFMEMORY == rc)
        {
            /*XTESTS_TEST_WARN(*/
        }
        else
        if (CSTRING_RC_SUCCESS == rc)
        {
            TEST_INT_EQ(1, csv.len);
            TEST_PTR_NE(NULL, csv.ptr);
            TEST_INT_GE(1, csv.capacity);
        }
        else
        {
            TEST_FAIL("should only fail cstring_vector_insertAt() with CSTRING_RC_OUTOFMEMORY");
        }

        cstring_vector_destroy(&csv);
    }
    else
    {
        TEST_FAIL("should only fail cstring_vector_create() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void TEST_cstring_vector_insertAt_LIST(void)
{
    cstring_char_t const* const strings[] =
    {
        CSTRING_T_("blah"),
        CSTRING_T_(""),
        CSTRING_T_("abcdefghijklmnopqrstuvwxyz"),
        CSTRING_T_("My Ever Changing Moods"),
        CSTRING_T_("I Can Give You Everything"),
        CSTRING_T_("Newborn Friend"),
        CSTRING_T_("Escape Velocity"),
        CSTRING_T_("Weapon Of Choice"),
        CSTRING_T_("Ain't No Doubt"),
        CSTRING_T_("Eye Know"),
        CSTRING_T_("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"),
    };

    cstring_vector_t    csv;
    CSTRING_RC          rc = cstring_vector_create(&csv, 0);

    if (CSTRING_RC_OUTOFMEMORY == rc)
    {
        /*XTESTS_TEST_WARN(*/
    }
    else
    if (CSTRING_RC_SUCCESS == rc)
    {
        cstring_t   cs = cstring_t_DEFAULT;
        size_t      i;

        TEST_INT_EQ(0, csv.len);
        TEST_PTR_EQ(NULL, csv.ptr);
        TEST_INT_EQ(0, csv.capacity);

        for (i = 0; i != STLSOFT_NUM_ELEMENTS(strings) && CSTRING_RC_SUCCESS == rc; ++i)
        {
            rc = cstring_assign(&cs, strings[i]);

            if (CSTRING_RC_SUCCESS == rc)
            {
                rc = cstring_vector_insertAt(&csv, i, &cs, 1);
            }
        }

        cstring_destroy(&cs);

        if (CSTRING_RC_OUTOFMEMORY == rc)
        {
            /*XTESTS_TEST_WARN(*/
        }
        else
        if (CSTRING_RC_SUCCESS == rc)
        {
            XTESTS_REQUIRE(TEST_INT_EQ(STLSOFT_NUM_ELEMENTS(strings), csv.len));
            TEST_PTR_NE(NULL, csv.ptr);
            TEST_INT_GE(STLSOFT_NUM_ELEMENTS(strings), csv.capacity);

            for (i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
            {
                TEST_INT_EQ(cstring_testing_strlen_(strings[i]), csv.ptr[i].len);
                TEST_STR_EQ_(strings[i], csv.ptr[i].ptr);
            }
        }
        else
        {
            TEST_FAIL("should only fail cstring_vector_insertAt() with CSTRING_RC_OUTOFMEMORY");
        }

        cstring_vector_destroy(&csv);
    }
    else
    {
        TEST_FAIL("should only fail cstring_vector_create() with CSTRING_RC_OUTOFMEMORY");
    }
}

/* ///////////////////////////// end of file //////////////////////////// */

