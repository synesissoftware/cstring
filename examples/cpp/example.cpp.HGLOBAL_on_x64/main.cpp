
#include <cstring/cstring.h>

#include <stdlib.h>
#include <string.h>

#ifndef STLSOFT_NUM_ELEMENTS
# define STLSOFT_NUM_ELEMENTS(ar)                           (sizeof(ar) / sizeof(ar[0]))
#endif /*!STLSOFT_NUM_ELEMENTS*/


int main()
{
    static char const* strings[] =
    {
        "abc"
    ,   "defghijklmno"
    ,   "pqrstuvwxyz"
    };

    size_t cchTotal = 0;

    { for(size_t i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
    {
        cchTotal += ::strlen(strings[i]);
    }}

    cstring_t       payload =   cstring_t_DEFAULT;
    cstring_flags_t flags   =   CSTRING_F_USE_WIN32_GLOBAL_MEMORY;
    CSTRING_RC      rc      =   CSTRING_RC_SUCCESS;

    rc = ::cstring_createLenFn(&payload, NULL, 0, flags, NULL, cchTotal, NULL, NULL);
    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "cstring_createLenFn() failed: %s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }
    rc = ::cstring_createLenEx(&payload, NULL, 0, flags, NULL, cchTotal);
    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "cstring_createLenEx() failed: %s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }
    rc = ::cstring_createEx(&payload, NULL, flags, NULL, cchTotal);
    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "cstring_createEx() failed: %s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }

    { for(size_t i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
    {
        rc = cstring_append(&payload, strings[i]);
        if (CSTRING_RC_SUCCESS == rc)
        {
            printf("appended '%s' => '%.*s'\n"
            ,   strings[i]
            ,   (int)payload.len, payload.ptr
            );
        }
        else
        {
            fprintf(stderr, "cstring_append() failed: %s\n", cstring_getStatusCodeString(rc));
            cstring_destroy(&payload);

            return EXIT_FAILURE;
        }
    }}

    cstring_destroy(&payload);

    return 0;
}

/* ///////////////////////////// end of file //////////////////////////// */

