

#include <cstring/cstring.vector.h>

#ifdef USE_PANTHEIOS_EXTRAS_DIAGUTIL_MAIN

# include <pantheios/extras/diagutil/main_leak_trace.h>
#endif

#include <xtests/xtests.h>

#include <stdlib.h>
#include <string.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_1_00(void);
static void test_1_01(void);
static void test_1_02(void);
static void test_1_03(void);
static void test_1_04(void);
static void test_1_05(void);
static void test_1_06(void);
static void test_1_07(void);
static void test_1_08(void);
static void test_1_09(void);
static void test_1_10(void);
static void test_1_11(void);
static void test_1_12(void);
static void test_1_13(void);
static void test_1_14(void);
static void test_1_15(void);
static void test_1_16(void);
static void test_1_17(void);
static void test_1_18(void);
static void test_1_19(void);

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

    if (XTESTS_START_RUNNER("test.unit.cstring.cstring_vector", verbosity))
    {
        XTESTS_RUN_CASE(test_1_00);
        XTESTS_RUN_CASE(test_1_01);
        XTESTS_RUN_CASE(test_1_02);
        XTESTS_RUN_CASE(test_1_03);
        XTESTS_RUN_CASE(test_1_04);
        XTESTS_RUN_CASE(test_1_05);
        XTESTS_RUN_CASE(test_1_06);
        XTESTS_RUN_CASE(test_1_07);
        XTESTS_RUN_CASE(test_1_08);
        XTESTS_RUN_CASE(test_1_09);
        XTESTS_RUN_CASE(test_1_10);
        XTESTS_RUN_CASE(test_1_11);
        XTESTS_RUN_CASE(test_1_12);
        XTESTS_RUN_CASE(test_1_13);
        XTESTS_RUN_CASE(test_1_14);
        XTESTS_RUN_CASE(test_1_15);
        XTESTS_RUN_CASE(test_1_16);
        XTESTS_RUN_CASE(test_1_17);
        XTESTS_RUN_CASE(test_1_18);
        XTESTS_RUN_CASE(test_1_19);

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

static void test_1_00(void)
{
    cstring_vector_t    csv = cstring_vector_t_DEFAULT;

    XTESTS_TEST_INTEGER_EQUAL(0, csv.len);
    XTESTS_TEST_POINTER_EQUAL(NULL, csv.ptr);
    XTESTS_TEST_INTEGER_EQUAL(0, csv.capacity);

    cstring_vector_destroy(&csv);
}

static void test_1_01(void)
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
        XTESTS_TEST_INTEGER_EQUAL(0, csv.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, csv.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0, csv.capacity);

        cstring_vector_destroy(&csv);
    }
    else
    {
        XTESTS_TEST_FAIL("should only fail cstring_vector_init() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void test_1_02(void)
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
        XTESTS_TEST_INTEGER_EQUAL(0, csv.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, csv.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(10, csv.capacity);

        cstring_vector_destroy(&csv);
    }
    else
    {
        XTESTS_TEST_FAIL("should only fail cstring_vector_init() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void test_1_03(void)
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
        XTESTS_TEST_INTEGER_EQUAL(0, csv.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, csv.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0, csv.capacity);

        cstring_vector_destroy(&csv);
    }
    else
    {
        XTESTS_TEST_FAIL("should only fail cstring_vector_create() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void test_1_04(void)
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
        XTESTS_TEST_INTEGER_EQUAL(10, csv.len);
        XTESTS_TEST_POINTER_NOT_EQUAL(NULL, csv.ptr);
        XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(10, csv.capacity);

        cstring_vector_destroy(&csv);
    }
    else
    {
        XTESTS_TEST_FAIL("should only fail cstring_vector_create() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void test_1_05(void)
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

        XTESTS_TEST_INTEGER_EQUAL(0, csv.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, csv.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0, csv.capacity);

        rc = cstring_vector_insertAt(&csv, 0, &cs, 1);

        if (CSTRING_RC_OUTOFMEMORY == rc)
        {
            /*XTESTS_TEST_WARN(*/
        }
        else
        if (CSTRING_RC_SUCCESS == rc)
        {
            XTESTS_TEST_INTEGER_EQUAL(1, csv.len);
            XTESTS_TEST_POINTER_NOT_EQUAL(NULL, csv.ptr);
            XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(1, csv.capacity);
        }
        else
        {
            XTESTS_TEST_FAIL("should only fail cstring_vector_insertAt() with CSTRING_RC_OUTOFMEMORY");
        }

        cstring_vector_destroy(&csv);
    }
    else
    {
        XTESTS_TEST_FAIL("should only fail cstring_vector_create() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void test_1_06(void)
{
    char const* const   strings[] =
    {
        "blah",
        "",
        "abcdefghijklmnopqrstuvwxyz",
        "My Ever Changing Moods",
        "I Can Give You Everything",
        "Newborn Friend",
        "Escape Velocity",
        "Weapon Of Choice",
        "Ain't No Doubt",
        "Eye Know",
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
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

        XTESTS_TEST_INTEGER_EQUAL(0, csv.len);
        XTESTS_TEST_POINTER_EQUAL(NULL, csv.ptr);
        XTESTS_TEST_INTEGER_EQUAL(0, csv.capacity);

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
            XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(STLSOFT_NUM_ELEMENTS(strings), csv.len));
            XTESTS_TEST_POINTER_NOT_EQUAL(NULL, csv.ptr);
            XTESTS_TEST_INTEGER_GREATER_OR_EQUAL(STLSOFT_NUM_ELEMENTS(strings), csv.capacity);

            for (i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
            {
                XTESTS_TEST_INTEGER_EQUAL(strlen(strings[i]), csv.ptr[i].len);
                XTESTS_TEST_MULTIBYTE_STRING_EQUAL(strings[i], csv.ptr[i].ptr);
            }
        }
        else
        {
            XTESTS_TEST_FAIL("should only fail cstring_vector_insertAt() with CSTRING_RC_OUTOFMEMORY");
        }

        cstring_vector_destroy(&csv);
    }
    else
    {
        XTESTS_TEST_FAIL("should only fail cstring_vector_create() with CSTRING_RC_OUTOFMEMORY");
    }
}

static void test_1_07(void)
{
}

static void test_1_08(void)
{
}

static void test_1_09(void)
{
}

static void test_1_10(void)
{
}

static void test_1_11(void)
{
}

static void test_1_12(void)
{
}

static void test_1_13(void)
{
}

static void test_1_14(void)
{
}

static void test_1_15(void)
{
}

static void test_1_16(void)
{
}

static void test_1_17(void)
{
}

static void test_1_18(void)
{
}

static void test_1_19(void)
{
}

/* ///////////////////////////// end of file //////////////////////////// */

