/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/c/auto-buffer/main.c
 *
 * Purpose: Example illustrating borrowed buffer growth to the heap
 *          (`CSTRING_F_MEMORY_IS_BORROWED` +
 *          `CSTRING_F_MEMORY_CAN_GROW_TO_HEAP`).
 *
 * Created: 28th July 2011
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* cstring header files */
#include <cstring/cstring.h>
#include "cstring.helpers.h"

/* STLSoft header files */
#if 0
#include <stlsoft/stlsoft.h>
#if _STLSOFT_VER >= 0x0a000000
# if defined(_WIN32)
#  include <winstl/diagnostics/output_debug_line.h>
# endif
#endif
#endif /* 0 */

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    /* Create on a fixed buffer. */
    cstring_t   cs;
    cstring_char_t  buff[10];
    int         flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    CSTRING_RC  rc      =   cstring_createEx(&cs, CSTRING_T_("String-#1"), flags, buff, sizeof(buff) / sizeof(buff[0]));

    ((void)&argc);
    ((void)&argv);

    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "Error: %s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }

    printf("cs=<len=%lu, capacity=%lu>: '"
    ,   (unsigned long)cs.len
    ,   (unsigned long)cs.capacity
    );
    cstring_write(stdout, &cs, NULL);
    printf("'\n");

    /* add some more to exceed capacity */
    rc = cstring_append(&cs, CSTRING_T_(" : something very long"));

    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "Error: %s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }

    printf("cs=<len=%lu, capacity=%lu>: '"
    ,   (unsigned long)cs.len
    ,   (unsigned long)cs.capacity
    );
    cstring_write(stdout, &cs, NULL);
    printf("'\n");

    cstring_destroy(&cs);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

