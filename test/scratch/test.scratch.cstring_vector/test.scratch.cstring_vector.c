

/* cstring header files */
#include <cstring/cstring.vector.h>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *************************************************************************
 * main()
 */

int main()
{
    cstring_vector_t    csv = cstring_vector_t_DEFAULT;
    size_t              numLinesRead;
    CSTRING_RC          rc;

    rc = cstring_vector_readLines(stdin, &csv, &numLinesRead);

    if (CSTRING_RC_SUCCESS != rc &&
        CSTRING_RC_EOF != rc)
    {
        fprintf(stderr, "failed to read: %s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }
    else
    {
        printf("#lines:\t%u\n", (unsigned)numLinesRead);

        if (sizeof(int) == sizeof(size_t))
        {
            { size_t i; for (i = 0; i != csv.len; ++i)
            {
                printf("line-%u: %.*s\n", (unsigned)i, csv.ptr[i]);
            }}
        }

        cstring_vector_destroy(&csv);

        return EXIT_SUCCESS;
    }
}

/* **************************** end of file ***************************** */
