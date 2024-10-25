/* /////////////////////////////////////////////////////////////////////////
 * File:    test.scratch.cstring.dynload.cpp
 *
 * Purpose: Implementation file for the test.scratch.cstring.dynload project.
 *
 * Created: 19th August 2005
 * Updated: 26th October 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* cstring header files */
#include <cstring/cstring.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/conversion/integer_to_string.hpp>
#include <winstl/winstl.h>

/* Standard C++ header files */
#include <exception>
#include <new>
#include <stdexcept>

#ifdef __WATCOMC__
namespace std
{
    using ::exception;
}
#endif /* __WATCOMC__ */


/* Standard C header files */
#include <stdio.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace cstring
{
    static void setCapacity(struct cstring_t* pcs, size_t capacity)
    {
        struct _
        {
            static int onAllocFail(void* /* pv */, size_t /* cb */, cstring_flags_t /* flags */, void* param)
            {
                *static_cast<bool*>(param) = true;

                return 0;
            }

        };

        bool    bThrow  =   false;

        if (CSTRING_RC_SUCCESS != cstring_setCapacityFn(pcs, capacity, _::onAllocFail, &bThrow))
        {
            if (bThrow)
            {
                throw std::bad_alloc();
            }
        }
    }


}  // namespace cstring

/* ////////////////////////////////////////////////////////////////////// */

static char const* cstring_error_(CSTRING_RC rc)
{
    static char s_sz[21];

    return stlsoft::integer_to_string(&s_sz[0], STLSOFT_NUM_ELEMENTS(s_sz), rc);
}

#define cstring_error   cstring_error_

static int main_(int /* argc */, char ** /*argv*/)
{
    /* . */
    HINSTANCE   hinst   =   ::LoadLibrary("cstring.3.debug.dll");

    GetLastError();

    CSTRING_RC (*_create)(cstring_t* , char const* );
    CSTRING_RC (*_yield)(cstring_t* pcs, char** );
    CSTRING_RC (*_createEx)(cstring_t* , char const* , size_t , void* , size_t );

    (FARPROC&)(_create)     =   ::GetProcAddress(hinst, "cstring_create");
    (FARPROC&)(_createEx)   =   ::GetProcAddress(hinst, "cstring_createEx");
    (FARPROC&)(_yield)      =   ::GetProcAddress(hinst, "cstring_yield");

    if (NULL != _create &&
        NULL != _yield)
    {
        cstring_t   cs;
#if 0
        CSTRING_RC  rc  =   _create(&cs, "Hello");
#else /* ? 0 */
        CSTRING_RC  rc  =   _createEx(&cs, "Hello", CSTRING_F_USE_WIN32_GLOBAL_MEMORY, NULL, 100);
#endif /* 0 */
        char*       p;

        try
        {
            cstring::setCapacity(&cs, 0x7feeffff);
        }
        catch(std::exception &x)
        {
            fprintf(stdout, "caught expected exception: %s\n", x.what());
        }

        if (CSTRING_RC_SUCCESS != rc)
        {
            fprintf(stderr, "create failed: %s\n", cstring_error(rc));
        }
        else
        {
            fprintf(stdout, "string=%s\n", cs.ptr);

            rc = _yield(&cs, &p);

            if (CSTRING_RC_SUCCESS != rc)
            {
                fprintf(stderr, "yield failed: %s\n", cstring_error(rc));
            }
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    try
    {
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
        puts("test.scratch.cstring.dynload: " STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

        return main_(argc, argv);
    }
    catch(std::exception &x)
    {
        fprintf(stderr, "Unhandled error: %s\n", x.what());
    }
    catch(...)
    {
        fprintf(stderr, "Unhandled unknown error\n");
    }

    return EXIT_FAILURE;
}


/* ///////////////////////////// end of file //////////////////////////// */

