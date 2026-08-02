/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/c/example.c.cstring_create/main.c
 *
 * Purpose: Minimal example of `cstring_create()` / `cstring_destroy()`.
 *
 * Created: ...
 * Updated: 2nd August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* cstring header files */
#include <cstring/cstring.h>

/* Standard C header files */
#include <stdio.h>

/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    cstring_t   cs;
    CSTRING_RC  rc  =   cstring_create(&cs, "String-#1");

    ((void)&argc);
    ((void)&argv);

    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "failed to create string: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        printf(
            "successfully created string with length %lu capacity %lu and contents '%.*s'\n"
        ,   (unsigned long)cs.len
        ,   (unsigned long)cs.capacity
        ,   (int)cs.len, cs.ptr
        );

        cstring_destroy(&cs);
    }

    return 0;
}


/* ///////////////////////////// end of file //////////////////////////// */

