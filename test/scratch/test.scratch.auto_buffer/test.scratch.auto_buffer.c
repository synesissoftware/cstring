/* /////////////////////////////////////////////////////////////////////////
 * File:    test.scratch.auto_buffer.c
 *
 * Purpose: Implementation file for the test.scratch.auto_buffer project.
 *
 * Created: 28th July 2011
 * Updated: 23rd February 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* cstring header files */
#include <cstring/cstring.h>

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
    char        buff[10];
    int         flags   =   0
                        |   CSTRING_F_MEMORY_IS_BORROWED
                        |   CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
                        ;
    CSTRING_RC  rc      =   cstring_createEx(&cs, "String-#1", flags, buff, sizeof(buff));

    ((void)&argc);
    ((void)&argv);

    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "Error: %s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }

    /* add some more to exceed capacity */
    rc = cstring_append(&cs, " : something very long");

    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "Error: %s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }


    cstring_destroy(&cs);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

