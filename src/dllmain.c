/* /////////////////////////////////////////////////////////////////////////
 * File:    dllmain.c
 *
 * Purpose: Definition of DllMain for the Win32 platform
 *
 * Created: 19th August 2005
 * Updated: 28th November 2023
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2019-2023, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2005-2019, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the names of Matthew Wilson and Synesis Information Systems nor
 *   the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file dllmain.c Definition of DllMain for the Win32 platform
 */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>
#if !defined(__MWERKS__)
# include <windows.h>
#else /* ? compiler */
# include <winerror.h>
#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if 1 &&\
    !defined(WIN32) && \
    !defined(_WIN32) && \
    !defined(WIN64) && \
    !defined(_WIN64) && \
    1
# error This file is only used for Win32 or Win64 builds
#endif /* Win32 */

#if !defined(_DLL) && \
    !defined(__DLL)
/* # error This file is only used for DLL builds */
#endif /* dll */

/* /////////////////////////////////////////////////////////////////////////
 * Windows types and declarations
 */

#if defined(__MWERKS__)

typedef int             BOOL;
typedef unsigned long   DWORD;
typedef void            *HANDLE;
typedef long            HRESULT;
typedef void            *LPVOID;
#define WINAPI          /* __stdcall */

#define DLL_PROCESS_DETACH                                  (0)
#define DLL_PROCESS_ATTACH                                  (1)
#define DLL_THREAD_ATTACH                                   (2)
#define DLL_THREAD_DETACH                                   (3)

#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////
 * declarations
 */

CSTRING_EXTERN_C CSTRING_RC cstring_apiInit(void);
CSTRING_EXTERN_C void cstring_apiUninit(void);

BOOL WINAPI DllMain(
    HANDLE  hInst
,   DWORD   dwReason
,   LPVOID  lpReserved
);

struct cstringdll_DllVersionInfo;

HRESULT WINAPI cstringdll_DllGetVersion(struct cstringdll_DllVersionInfo* pdvi);
CSTRING_EXTERN_C CSTRING_RC cstringdll_yield(
    struct cstring_t*   pcs
,   char**              ppBuff
);

/* /////////////////////////////////////////////////////////////////////////
 * DllMain
 */

BOOL WINAPI DllMain(
    HANDLE  hInst
,   DWORD   dwReason
,   LPVOID  lpReserved
)
{
    ((void)hInst);
    ((void)lpReserved);

    switch (dwReason)
    {
        case    DLL_PROCESS_ATTACH:
            return CSTRING_RC_SUCCESS == cstring_apiInit();
        case    DLL_PROCESS_DETACH:
            cstring_apiUninit();
            break;
    }

    return 1;
}

/* /////////////////////////////////////////////////////////////////////////
 * DllGetVersion
 */

struct cstringdll_DllVersionInfo
{
    DWORD   cbSize;
    DWORD   dwMajorVersion;
    DWORD   dwMinorVersion;
    DWORD   dwBuildNumber;
    DWORD   dwPlatformID;
};

#define cstringdll_DLLVER_PLATFORM_WINDOWS                  (0x00000001)    /* Windows 9x */
#define cstringdll_DLLVER_PLATFORM_NT                       (0x00000002)    /* Windows NT */

HRESULT WINAPI cstringdll_DllGetVersion(struct cstringdll_DllVersionInfo* pdvi)
{
    if (NULL == pdvi)
    {
        return E_INVALIDARG;
    }
    else if (pdvi->cbSize != sizeof(struct cstringdll_DllVersionInfo))
    {
        return E_INVALIDARG;
    }
    else
    {
        pdvi->dwMajorVersion    =   CSTRING_VER_MAJOR;
        pdvi->dwMinorVersion    =   CSTRING_VER_MINOR;
        pdvi->dwBuildNumber     =   CSTRING_VER;
        pdvi->dwPlatformID      =   cstringdll_DLLVER_PLATFORM_WINDOWS;

        return S_OK;
    }
}

/* /////////////////////////////////////////////////////////////////////////
 * cstringdll_yield
 */

CSTRING_EXTERN_C CSTRING_RC cstringdll_yield(
    struct cstring_t*   pcs
,   char**              pPayload
)
{
    if (NULL != pcs &&
        (pcs->flags & CSTRING_F_ARENA_MASK) == CSTRING_F_USE_REALLOC)
    {
        return CSTRING_RC_CANNOTYIELDFROMSO;
    }
    else
    {
        void* raw;

        return cstring_yield2(pcs, pPayload, &raw);
    }
}

CSTRING_EXTERN_C CSTRING_RC cstringdll_yield2(
    struct cstring_t*   pcs
,   char**              pPayload
,   void**              pRaw
)
{
    if (NULL != pcs &&
        (pcs->flags & CSTRING_F_ARENA_MASK) == CSTRING_F_USE_REALLOC)
    {
        return CSTRING_RC_CANNOTYIELDFROMSO;
    }
    else
    {
        return cstring_yield2(pcs, pPayload, pRaw);
    }
}

/* ///////////////////////////// end of file //////////////////////////// */

