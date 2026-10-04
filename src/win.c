/* /////////////////////////////////////////////////////////////////////////
 * File:    win.c
 *
 * Purpose: Windows memory arenas for the cstring core API.
 *
 * Created: 28th September 2026
 * Updated: 29th September 2026
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 1994-2019, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the names of Matthew Wilson and Synesis Information Systems nor
 *   the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file win.c Windows memory arenas for the cstring core API
 */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>
#include "internal.h"


/* /////////////////////////////////////////////////////////////////////////
 * Win32 functions
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# if defined(__MWERKS__)
#  define  GMEM_FIXED                           0
#  define  GMEM_MOVEABLE                        2
typedef int                                     BOOL;
typedef void*                                   HANDLE;
typedef void*                                   HGLOBAL;
__declspec(dllimport) HANDLE    __stdcall       GetProcessHeap(void);
__declspec(dllimport) HGLOBAL   __stdcall       GlobalAlloc(unsigned int, unsigned long);
__declspec(dllimport) HGLOBAL   __stdcall       GlobalFree(HGLOBAL);
__declspec(dllimport) HGLOBAL   __stdcall       GlobalReAlloc(HGLOBAL, unsigned long, unsigned int);
__declspec(dllimport) void*     __stdcall       HeapAlloc(HANDLE, unsigned long, unsigned int);
__declspec(dllimport) BOOL      __stdcall       HeapFree(HANDLE, unsigned long, void* );
__declspec(dllimport) void*     __stdcall       HeapReAlloc(HANDLE, unsigned long, void*, unsigned int);
__declspec(dllimport) void*     __stdcall       CoTaskMemAlloc(unsigned long);
__declspec(dllimport) void      __stdcall       CoTaskMemFree(void* );
__declspec(dllimport) void*     __stdcall       CoTaskMemRealloc(void* , unsigned long);
# else /* ? compiler */

#  include <windows.h>
#  include <objbase.h>
# endif /* compiler */
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */

/* ////////////////////////////////////////////////////////////////////// */

void*
win32_global_realloc(
    void*   pv
,   size_t  cb
)
{
    /* Logic borrowed from implementation of SynesisWin::GlobalAtor class
     * (in file MWAtors.h) from the Synesis Software Public Domain Source
     * Code Library (http://synesis.com.au/software).
     */
    if (NULL != pv)
    {
        if (0 == cb)
        {
            return (GlobalFree((HGLOBAL)pv), (void*)NULL);
        }
        else
        {
            return (void*)GlobalReAlloc((HGLOBAL)pv, cb, GMEM_MOVEABLE);
        }
    }
    else
    {
        return (void*)GlobalAlloc(GMEM_FIXED, cb);
    }
}

void*
win32_processheap_realloc(
    void*   pv
,   size_t  cb
)
{
    /* Logic borrowed from implementation of SynesisWin::HeapAtor class (in
     * file MWAtors.h) from the Synesis Software Public Domain Source Code
     * Library (http://synesis.com.au/software).
     */
    if (NULL != pv)
    {
        if (0 == cb)
        {
            return (HeapFree(GetProcessHeap(), 0, (HGLOBAL)pv), (void*)NULL);
        }
        else
        {
            return (void*)HeapReAlloc(GetProcessHeap(), 0, (HGLOBAL)pv, cb);
        }
    }
    else
    {
        return (void*)HeapAlloc(GetProcessHeap(), 0, cb);
    }
}

void*
win32_comtask_realloc(
    void*   pv
,   size_t  cb
)
{
    /* Direct (statically linked) COM Task Allocator API — CoTaskMemAlloc /
     * CoTaskMemFree / CoTaskMemRealloc from ole32.
     */
    if (NULL != pv)
    {
        if (0 == cb)
        {
            return (CoTaskMemFree(pv), (void*)NULL);
        }
        else
        {
            return CoTaskMemRealloc(pv, cb);
        }
    }
    else
    {
        return CoTaskMemAlloc(cb);
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

