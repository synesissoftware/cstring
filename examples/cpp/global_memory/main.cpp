/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/cpp/cstring.global_memory/main.cpp
 *
 * Purpose: Windows-only example loading the cstring DLL dynamically via
 *          `LoadLibrary` / `GetProcAddress`.
 *
 * Created: 19th August 2005
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* cstring header files */
#include <cstring/cstring.h>
#include "cstring.helpers.h"

#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

#ifndef STLSOFT_NUM_ELEMENTS
# define STLSOFT_NUM_ELEMENTS(ar)                           (sizeof(ar) / sizeof(ar[0]))
#endif /*!STLSOFT_NUM_ELEMENTS*/


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    static cstring_char_t const* strings[] =
    {
        CSTRING_T_("abc")
    ,   CSTRING_T_("defghijklmno")
    ,   CSTRING_T_("pqrstuvwxyz")
    };

    size_t cchTotal = 0;

    { for(size_t i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
    {
#ifdef CSTRING_USE_WIDE_STRINGS
        cchTotal += ::wcslen(strings[i]);
#else /* ? CSTRING_USE_WIDE_STRINGS */
        cchTotal += ::strlen(strings[i]);
#endif /* CSTRING_USE_WIDE_STRINGS */
    }}

    cstring_t       payload =   cstring_t_DEFAULT;
    cstring_flags_t flags   =   CSTRING_F_USE_WINDOWS_GLOBAL_MEMORY;
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
            cstring_t shown = cstring_t_DEFAULT;

#ifdef CSTRING_USE_WIDE_STRINGS
            shown.len = ::wcslen(strings[i]);
#else /* ? CSTRING_USE_WIDE_STRINGS */
            shown.len = ::strlen(strings[i]);
#endif /* CSTRING_USE_WIDE_STRINGS */
            shown.ptr = const_cast<cstring_char_t*>(strings[i]);

            printf("appended '");
            cstring_write(stdout, &shown, NULL);
            printf("' => '");
            cstring_write(stdout, &payload, NULL);
            printf("'\n");
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

