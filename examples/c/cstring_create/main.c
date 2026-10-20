/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/c/cstring_create/main.c
 *
 * Purpose: Minimal example of `cstring_create()` / `cstring_destroy()`.
 *
 * Created: 12th January 2024
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* cstring header files */
#include <cstring/cstring.h>
#include "cstring.helpers.h"

/* Standard C header files */
#include <stdio.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    cstring_t   cs;
    CSTRING_RC  rc  =   cstring_create(&cs, CSTRING_T_("String-#1"));

    ((void)&argc);
    ((void)&argv);

    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "failed to create string: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        printf(
            "successfully created string with length %lu capacity %lu and contents '"
        ,   (unsigned long)cs.len
        ,   (unsigned long)cs.capacity
        );
        cstring_write(stdout, &cs, NULL);
        printf("'\n");

        cstring_destroy(&cs);
    }

    return 0;
}


/* ///////////////////////////// end of file //////////////////////////// */

