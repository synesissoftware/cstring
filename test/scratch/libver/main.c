/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/libver/main.c
 *
 * Purpose: Prints cstring composite version (and STLSoft when present).
 *
 * Created: 17th September 2026
 * Updated: 17th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <cstring/cstring.h>

#ifdef HAS_STLSOFT
# include <stlsoft/stlsoft.h>
#endif

#include <stdio.h>
#include <stdlib.h>


#define PROGRAM_NAME                                        "libver"


static void
version(
    FILE*       stm
,   char const* prefix
,   char const* libname
,   char const* macroname
,   unsigned    libver
)
{
    fprintf(
        stm
    ,   "%s%s: v%u.%u.%u.%u (%s = 0x%08x)\n"
    ,   prefix
    ,   libname
    ,   (libver >> 24) & 0xff
    ,   (libver >> 16) & 0xff
    ,   (libver >> 8) & 0xff
    ,   (libver >> 0) & 0xff
    ,   macroname
    ,   libver
    );
}


int main(int argc, char* argv[])
{
    ((void)&argc);
    ((void)&argv);

    {
        unsigned const libver = (unsigned)CSTRING_VER;

        version(stdout, "", "cstring", "CSTRING_VER", libver);
    }

#ifdef HAS_STLSOFT

    fputs("\nefferent dependencies:\n", stdout);

    {
        unsigned const libver = (unsigned)_STLSOFT_VER;

        version(stdout, "\t", "STLSoft", "_STLSOFT_VER", libver);
    }
#endif

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

