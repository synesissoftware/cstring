/*
 * TODO: move to examples
 */

/* cstring header files */
#include <cstring/cstring.vector.h>

/* Standard C header files */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *************************************************************************
 * main()
 */

static
int run_(
    FILE*       stream
,   char const* input_path    /* May be null */
);

int main(int argc, char* argv[])
{
    char const* const   arg0        =   argv[0];
    FILE*               stream;
    char const*         input_path;

    switch (argc)
    {
    case 1:

        fprintf(stderr, "%s: input source not specified; use --help for usage\n", arg0);

        return EXIT_FAILURE;
    case 2:

        if (0 == strcmp("--help", argv[1]))
        {
            fprintf(
                stdout
            ,   "USAGE: %s { <input-path> | -- | --help }\n"
            ,   arg0
            );

            return EXIT_SUCCESS;
        }
        else
        {
            if (0 == strcmp("--", argv[1]))
            {
                input_path  =   NULL;

                stream      =   stdin;
            }
            else
            {
                input_path = argv[1];

                if (NULL == (stream = fopen(input_path, "r")))
                {
                    int const e = errno;

                    fprintf(stderr, "%s: could not open file '%s': %s\n", arg0, input_path, strerror(e));

                    return EXIT_FAILURE;
                }
            }
        }

        break;
    default:

        fprintf(stderr, "%s: too many arguments; use --help for usage\n", arg0);

        return EXIT_FAILURE;
    }

    return run_(stream, input_path);
}

static
int
cstring_compare(
    cstring_t const*    cs1
,   cstring_t const*    cs2
)
{
    size_t const    min_len =   (cs1->len < cs2->len) ? cs1->len : cs2->len;
    int             r       =   strncmp(cs1->ptr, cs2->ptr, min_len);

    if (0 == r)
    {
        if (cs1->len > cs2->len)
        {
            return -1;
        }
        if (cs1->len < cs2->len)
        {
            return +1;
        }
    }

    return r;
}

static
int
cstring_compare_pv(
    void const* p1
,   void const* p2
)
{
    cstring_t const*    cs1 =   p1;
    cstring_t const*    cs2 =   p2;

    return cstring_compare(cs1, cs2);
}

static
int
cstring_compare_reverse_pv(
    void const* p1
,   void const* p2
)
{
    cstring_t const*    cs1 =   p1;
    cstring_t const*    cs2 =   p2;

    return cstring_compare(cs2, cs1);
}

static
int run_(
    FILE*       stream
,   char const* input_path    /* May be null */
)
{
    cstring_vector_t    csv = cstring_vector_t_DEFAULT;
    size_t              numLinesRead;
    CSTRING_RC          rc;

    rc = cstring_vector_readLines(stream, &csv, &numLinesRead);

    if (CSTRING_RC_SUCCESS != rc &&
        CSTRING_RC_EOF != rc)
    {
        fprintf(
            stderr
        ,   "failed to read from %s: %s\n"
        ,   (NULL == input_path) ? "standard input" : input_path
        ,   cstring_getStatusCodeString(rc)
        );

        return EXIT_FAILURE;
    }
    else
    {
        printf("#lines:\t%u\n", (unsigned)numLinesRead);

        { size_t i; for (i = 0; i != csv.len; ++i)
        {
            if (sizeof(int) == sizeof(size_t))
            {
                printf("line-%u: %.*s\n", (unsigned)i, csv.ptr[i]);
            }
            else
            {
                printf("line-%u: %.*s\n", (unsigned)i, (int)csv.ptr[i].len, csv.ptr[i].ptr);
            }
        }}
        printf("\n");


        printf("#sorted-lines (forward):\t%u\n", (unsigned)numLinesRead);

        qsort(
            &csv.ptr[0]
        ,   numLinesRead
        ,   sizeof(csv.ptr[0])
        ,   cstring_compare_pv
        );

        { size_t i; for (i = 0; i != csv.len; ++i)
        {
            if (sizeof(int) == sizeof(size_t))
            {
                printf("line-%u: %.*s\n", (unsigned)i, csv.ptr[i]);
            }
            else
            {
                printf("line-%u: %.*s\n", (unsigned)i, (int)csv.ptr[i].len, csv.ptr[i].ptr);
            }
        }}
        printf("\n");


        printf("#sorted-lines (reverse):\t%u\n", (unsigned)numLinesRead);

        qsort(
            &csv.ptr[0]
        ,   numLinesRead
        ,   sizeof(csv.ptr[0])
        ,   cstring_compare_reverse_pv
        );

        { size_t i; for (i = 0; i != csv.len; ++i)
        {
            if (sizeof(int) == sizeof(size_t))
            {
                printf("line-%u: %.*s\n", (unsigned)i, csv.ptr[i]);
            }
            else
            {
                printf("line-%u: %.*s\n", (unsigned)i, (int)csv.ptr[i].len, csv.ptr[i].ptr);
            }
        }}
        printf("\n");


        cstring_vector_destroy(&csv);

        return EXIT_SUCCESS;
    }
}

/* ///////////////////////////// end of file //////////////////////////// */

