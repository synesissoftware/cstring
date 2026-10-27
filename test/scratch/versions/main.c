/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/versions/main.c
 *
 * Purpose: Prints cstring composite version (and STLSoft when present).
 *
 * Created: 17th September 2026
 * Updated: 27th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <cstring/cstring.h>

#ifdef HAS_p99
# include <p99/p99.h>
#endif

#ifdef HAS_shwild
# include <shwild/shwild.h>
#endif

#ifdef HAS_STLSoft
# include <stlsoft/stlsoft.h>
#endif

#ifdef HAS_xTests
# include <xtests/xtests.h>
#endif

#include <stdio.h>
#include <stdlib.h>


#define PROGRAM_NAME                                        "versions"


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
    size_t efferent_counts = 0;

    ((void)&argc);
    ((void)&argv);

    {
        unsigned const libver = (unsigned)CSTRING_VER;

        version(stdout, "", "cstring", "CSTRING_VER", libver);
    }

#ifdef HAS_p99

    if (0 == efferent_counts++)
    {
        fputs("\nefferent dependencies:\n", stdout);
    }

    {
        unsigned const libver = (unsigned)P99_VER;

        version(stdout, "\t", "p99", "P99_VER", libver);
    }
#endif

#ifdef HAS_shwild

    if (0 == efferent_counts++)
    {
        fputs("\nefferent dependencies:\n", stdout);
    }

    {
        unsigned const libver = (unsigned)SHWILD_VER;

        version(stdout, "\t", "shwild", "SHWILD_VER", libver);
    }
#endif

#ifdef HAS_STLSoft

    if (0 == efferent_counts++)
    {
        fputs("\nefferent dependencies:\n", stdout);
    }

    {
        unsigned const libver = (unsigned)_STLSOFT_VER;

        version(stdout, "\t", "STLSoft", "_STLSOFT_VER", libver);
    }
#endif

#ifdef HAS_xTests

    if (0 == efferent_counts++)
    {
        fputs("\nefferent dependencies:\n", stdout);
    }

    {
        unsigned const libver = (unsigned)_XTESTS_VER;

        version(stdout, "\t", "xTests", "_XTESTS_VER", libver);
    }
#endif

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

