/* /////////////////////////////////////////////////////////////////////////
 * File:    internal.h
 *
 * Purpose: Private declarations for the cstring implementation units.
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


/** \file internal.h Private declarations for the cstring implementation units
 */

#ifndef CSTRING_INCL_SRC_H_INTERNAL
#define CSTRING_INCL_SRC_H_INTERNAL


/* /////////////////////////////////////////////////////////////////////////
 * checks
 */

#ifndef CSTRING_INCL_CSTRING_H_CSTRING
# error cstring/cstring.h must be included before this file
#endif /* !CSTRING_INCL_CSTRING_H_CSTRING */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */



/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */


/* /////////////////////////////////////////////////////////////////////////
 * Internal functions
 */



/* /////////////////////////////////////////////////////////
 * Windows arena allocators
 */

#ifdef _WIN32

CSTRING_EXTERN_C
void*
win32_global_realloc(
    void*   pv
,   size_t  cb
);

CSTRING_EXTERN_C
void*
win32_processheap_realloc(
    void*   pv
,   size_t  cb
);

CSTRING_EXTERN_C
void*
win32_comtask_realloc(
    void*   pv
,   size_t  cb
);
#endif /* _WIN32 */


/* ////////////////////////////////////////////////////////////////////// */

#endif /* CSTRING_INCL_SRC_H_INTERNAL */

/* ///////////////////////////// end of file //////////////////////////// */

