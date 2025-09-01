
#include <cstring/cstring.h>

#ifdef HAS_STLSOFT
# include <stlsoft/stlsoft.h>
#endif

#include <iomanip>
#include <iostream>

#include <stdlib.h>


#define PROGRAM_NAME                                        "libver"

template<
    typename T_stream
,   typename T_integer
>
void
version(
    T_stream&   stm
,   char const* libname
,   T_integer   libver
)
{
    stm
        << libname
        << " v"
        << ((libver >> 24) & 0xff)
        << '.'
        << ((libver >> 16) & 0xff)
        << '.'
        << ((libver >> 8) & 0xff)
        << '.'
        << ((libver >> 0) & 0xff)
        << std::endl
        ;
}


int main(int /* argc */, char* /* argv */[])
{
    {
        auto const libver = CSTRING_VER;

        version(std::cout, "\tcstring", libver);
    }

#ifdef HAS_STLSOFT

    {
        auto const libver = _STLSOFT_VER;

        version(std::cout, "\tSTLSoft", libver);
    }
#endif

    return EXIT_SUCCESS;
}

