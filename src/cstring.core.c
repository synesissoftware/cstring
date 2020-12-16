/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring.core.c
 *
 * Purpose: The implementation of the cstring core API
 *
 * Created: 16th June 1994
 * Updated: 10th August 2020
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2019-2020, Matthew Wilson and Synesis Information Systems
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


/** \file cstring.core.c The implementation of the cstring core API
 */

/* /////////////////////////////////////////////////////////////////////////
 * Includes
 */

/* cstring Header Files */

#include <cstring/cstring.h>

#ifndef CSTRING_INCL_CSTRING_INTERNAL_H_SAFESTR
# include <cstring/internal/safestr.h>
#endif /* CSTRING_INCL_CSTRING_INTERNAL_H_SAFESTR */

/* Standard C Header Files */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CSTRING_USE_WIDE_STRINGS
# include <wchar.h>
#endif /* CSTRING_USE_WIDE_STRINGS */

/* /////////////////////////////////////////////////////////////////////////
 * Constants & definitions
 */

#define CSTRING_ALLOC_GRANULARITY   (8)

#define CSTRING_OFFSET_SIZE         (16)

#if defined(WIN32) || \
    defined(WIN64)
# define CSTRING_USE_WINAPI_
#endif

/* /////////////////////////////////////////////////////////////////////////
 * Debugging
 */

#define cstring_assert(expr)        assert(expr)

/* /////////////////////////////////////////////////////////////////////////
 * Compiler warnings
 */

#if defined(_MSC_VER)
# if _MSC_VER >= 1200
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# if _MSC_VER >= 1310
#  if !defined(__COMO__)
#   pragma warning(disable : 4055)
#  endif /* !__COMO__ */
# endif /* _MSC_VER >= 1310 */
#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////
 * Character encoding
 */

#ifdef CSTRING_USE_WIDE_STRINGS
# define cstring_strlen_        wcslen
# define cstring_strncpy_       wcsncpy
# define cstring_strstr_        wcsstr
#else /* ? CSTRING_USE_WIDE_STRINGS */
# define cstring_strlen_        strlen
# define cstring_strncpy_       strncpy
# define cstring_strstr_        strstr
#endif /* CSTRING_USE_WIDE_STRINGS */

/* /////////////////////////////////////////////////////////////////////////
 * Compiler compatibility
 */

#if defined(__BORLANDC__)
cstring_char_t*
strncpy_safe(
    cstring_char_t*         dest
,   cstring_char_t const*   src
,   size_t                  len
)
{
    if(0 != len)
    {
        cstring_strncpy_(dest, src, len);
    }

    return dest;
}
# define strncpy    strncpy_safe
#endif /* compiler */

#if defined(UNIX) || \
    defined(unix)
  /* This required, otherwise get name shadowing warning from Linux /usr/include/string.h */
# define index index_disambiguated_1
#endif

/* /////////////////////////////////////////////////////////////////////////
 * Utility functions
 */

static
size_t
cstring_strlen_safe_(
    cstring_char_t const* s
)
{
    return (NULL == s) ? 0 : cstring_strlen_(s);
}

static
CSTRING_RC
convert_negative_index(
    cstring_t const*    pcs
,   int                 index
,   size_t*             realIndex
)
{
    cstring_assert(NULL != pcs);
    cstring_assert(index < 0);

    ++index;

    if(-index > (int)pcs->len)
    {
        return CSTRING_RC_INVALIDSECTION;
    }

    *realIndex = pcs->len - (size_t)(-index);

    return CSTRING_RC_SUCCESS;
}

/* /////////////////////////////////////////////////////////////////////////
 * Allocation functions
 */

#if defined(CSTRING_USE_WINAPI_)
static void* win32_global_realloc(void* pv, size_t cb);
static void* win32_processheap_realloc(void* pv, size_t cb);
static void* win32_comtask_realloc(void* pv, size_t cb);
#endif /* CSTRING_USE_WINAPI_ */

static
void*
cstring_realloc_2(
    void*                       pv
,   size_t                      cch
,   cstring_flags_t             flags
,   CSTRING_RC*                 prc
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
)
{
    void*   pvNew;
    size_t  cb;

    if(CSTRING_F_MEMORY_IS_OFFSET & flags)
    {
        if(NULL != pv)
        {
            pv = (cstring_char_t*)pv - CSTRING_OFFSET_SIZE;

            if(NULL == pfnAllocFailHandler)
            {
                memcpy(&pfnAllocFailHandler, pv, sizeof(pfnAllocFailHandler));
            }
        }

        if(0 != cch)
        {
            cch += CSTRING_OFFSET_SIZE;
        }
    }

    cb = sizeof(cstring_char_t) * cch;

    cb = (cb + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);

alloc_retry:

    switch(CSTRING_F_ARENA_MASK & flags)
    {
        case    CSTRING_F_USE_REALLOC:
#if defined(_MSC_VER) && \
    defined(_DEBUG)
            if(0 == cb)
            {
                free(pv);
                return NULL;
            }
#endif /* _DEBUG */
            pvNew = realloc(pv, cb);
            break;
#if defined(CSTRING_USE_WINAPI_)
        case    CSTRING_F_USE_WIN32_GLOBAL_MEMORY:
            pvNew = win32_global_realloc(pv, cb);
            break;
        case    CSTRING_F_USE_WIN32_PROCESSHEAP_MEMORY:
            pvNew = win32_processheap_realloc(pv, cb);
            break;
        case    CSTRING_F_USE_WIN32_COM_TASK_MEMORY:
            pvNew = win32_comtask_realloc(pv, cb);
            break;
#endif /* CSTRING_USE_WINAPI_ */
#if defined(CSTRING_USE_SYNESIS_APIS)
        case    CSTRING_F_USE_SYNESIS_HATOR:
#endif /* CSTRING_USE_SYNESIS_APIS */
        case    CSTRING_F_USE_CUSTOMARENAFUNCTIONS:
        default:
            *prc = CSTRING_RC_INVALIDARENA;
            return NULL;
    }

    if(NULL == pvNew)
    {
        if( 0 != cb &&
            NULL != pfnAllocFailHandler &&
            1 == (*pfnAllocFailHandler)(pv, cb, flags, param))
        {
            goto alloc_retry;
        }

        *prc = CSTRING_RC_OUTOFMEMORY;
    }

    pv = pvNew;

    if(CSTRING_F_MEMORY_IS_OFFSET & flags)
    {
        if(NULL != pv)
        {
            if(NULL != pfnAllocFailHandler)
            {
                memcpy(pv, &pfnAllocFailHandler, sizeof(pfnAllocFailHandler));
            }

            pv = (cstring_char_t*)pv + CSTRING_OFFSET_SIZE;
        }
    }

    return pv;
}

static
void*
cstring_realloc_(
    void*           pv
,   size_t          cch
,   cstring_flags_t flags
,   CSTRING_RC*     prc
)
{
    return cstring_realloc_2(pv, cch, flags, prc, NULL, NULL);
}

/* /////////////////////////////////////////////////////////////////////////
 * API
 */

#if defined(_DLL) || \
    defined(__DLL) || \
    1
CSTRING_EXTERN_C CSTRING_RC cstring_apiInit(void);
CSTRING_EXTERN_C void cstring_apiUninit(void);

CSTRING_EXTERN_C CSTRING_RC cstring_apiInit(void)
{
    return CSTRING_RC_SUCCESS;
}

CSTRING_EXTERN_C void cstring_apiUninit(void)
{
}
#endif /* _DLL */

CSTRING_EXTERN_C char const* cstring_getStatusCodeString(
    CSTRING_RC rc
)
{
    switch(rc)
    {
        default:    return "<<unknown error>>";
        case    CSTRING_RC_SUCCESS                  :   return "operation completed successfully";
        case    CSTRING_RC_OUTOFMEMORY              :   return "out of memory";
        case    CSTRING_RC_FIXED                    :   return "operation cannot procede because the cstring has fixed capacity";
        case    CSTRING_RC_BORROWED                 :   return "operation cannot procede because the cstring is borrowed";
        case    CSTRING_RC_READONLY                 :   return "operation cannot procede because the cstring is readonly";
        case    CSTRING_RC_INVALIDARENA             :   return "invalid arena";
        case    CSTRING_RC_CUSTOMARENANOTSUPPORTED  :   return "custom arena functionality not currently supported";
        case    CSTRING_RC_EXCEEDFIXEDCAPACITY      :   return "operation cannot procede because the current capacity would be exceeded and the cstring has fixed capacity";
        case    CSTRING_RC_EXCEEDBORROWEDCAPACITY   :   return "operation cannot procede because the current capacity would be exceeded and the cstring is borrowed";
        case    CSTRING_RC_CANNOTYIELDFROMSO        :   return "yield operation from a dynamic-library version of cstring was not allowed";
        case    CSTRING_RC_ARENAOVERLOADED          :   return "cannot use arena parameter for both borrowed memory and custom arena";

        case    CSTRING_RC_INVALIDSTREAM            :   return "the stream handle is invalid";
        case    CSTRING_RC_EOF                      :   return "reached the end of stream";
        case    CSTRING_RC_INVALIDSECTION           :   return "the given section is invalid";
        case    CSTRING_RC_IOERROR                  :   return "an I/O error occured";

        case    CSTRING_RC_SYSTEMSPECIFICFAILURE    :   return "system-specific failure occurred";

        case    CSTRING_RC_REQUESTTOOLARGE          :   return "request exceeded inherent or runtime limit";
    }
}

CSTRING_EXTERN_C size_t cstring_getStatusCodeStringLength(
    CSTRING_RC rc
)
{
    return strlen(cstring_getStatusCodeString(rc));
}

CSTRING_EXTERN_C char const* cstring_error(
    CSTRING_RC rc
)
{
    return cstring_getStatusCodeString(rc);
}

CSTRING_EXTERN_C CSTRING_RC cstring_init(
    struct cstring_t* pcs
)
{
    cstring_assert(NULL != pcs);

    pcs->len        =   0;
    pcs->ptr        =   NULL;
    pcs->capacity   =   0;
    pcs->flags      =   0;

    return CSTRING_RC_SUCCESS;
}

CSTRING_EXTERN_C CSTRING_RC cstring_create(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
)
{
    size_t const    len = cstring_strlen_safe_(s);
    size_t          cch;
    CSTRING_RC      rc;

    cstring_assert(NULL != pcs);

    cch =   (0 == len) ? 1u : len;
    cch =   (cch + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);

    pcs->ptr = (cstring_char_t*)cstring_realloc_(NULL, cch + 1, 0, &rc);

    if(NULL == pcs->ptr)
    {
        return rc;
    }
    else
    {
        pcs->len        =   len;
        memcpy(pcs->ptr, s, len * sizeof(cstring_char_t));
        pcs->ptr[len]   =   '\0';
        pcs->capacity   =   cch;
        pcs->flags      =   CSTRING_F_MEMORY_IS_INTERNAL_HEAP | CSTRING_F_USE_REALLOC;

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_createLen(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   size_t                  len
)
{
    size_t      cch;
    CSTRING_RC  rc;

    cstring_assert(NULL != pcs);

    cch =   sizeof(cstring_char_t) * ((0 == len) ? 1u : len);
    cch =   (cch + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);

    pcs->ptr = (cstring_char_t*)cstring_realloc_(NULL, cch + 1, 0, &rc);

    if(NULL == pcs->ptr)
    {
        return rc;
    }
    else
    {
        pcs->len        =   len;
        memcpy(pcs->ptr, s, len * sizeof(cstring_char_t));
        pcs->ptr[len]   =   '\0';
        pcs->capacity   =   cch;
        pcs->flags      =   CSTRING_F_MEMORY_IS_INTERNAL_HEAP | CSTRING_F_USE_REALLOC;

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_createN(
    struct cstring_t*       pcs
,   cstring_char_t          ch
,   size_t                  n
)
{
    static cstring_char_t const s_empty[] = { 0 };

    CSTRING_RC rc = cstring_createLen(pcs, s_empty, n);

    if(CSTRING_RC_SUCCESS == rc)
    {
        size_t i;

        cstring_assert(n == pcs->len);

        for(i = 0; i != n; ++i)
        {
            pcs->ptr[i] = ch;
        }
    }

    return rc;
}

CSTRING_EXTERN_C CSTRING_RC cstring_createEx(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   cstring_flags_t         flags
,   void*                   arena
,   size_t                  capacity
)
{
    size_t const len = cstring_strlen_safe_(s);

    return cstring_createLenEx(pcs, s, len, flags, arena, capacity);
}

CSTRING_EXTERN_C CSTRING_RC cstring_createLenEx(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   size_t                  len
,   cstring_flags_t         flags
,   void*                   arena
,   size_t                  capacity
)
{
    return cstring_createLenFn(pcs, s, len, flags, arena, capacity, NULL, NULL);
}

/** This is an experimental feature */
CSTRING_EXTERN_C CSTRING_RC cstring_createLenFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   size_t                      len
,   cstring_flags_t             flags
,   void*                       arena
,   size_t                      capacity
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
)
{
    cstring_assert(NULL != pcs);

    if(NULL != pfnAllocFailHandler)
    {
        flags |= CSTRING_F_MEMORY_IS_OFFSET;
    }

    /* Borrowed => fixed */
    if(CSTRING_F_MEMORY_IS_BORROWED & flags)
    {
        if(0 == (CSTRING_F_MEMORY_CAN_GROW_TO_HEAP & flags))
        {
            flags |= CSTRING_F_MEMORY_IS_FIXED;
        }
    }

    if( NULL != arena &&
        !(CSTRING_F_MEMORY_IS_BORROWED & flags))
    {
        return CSTRING_RC_CUSTOMARENANOTSUPPORTED;
    }
    else
    {
        if(CSTRING_F_MEMORY_IS_BORROWED & flags)
        {
            if(len + 1 > capacity)
            {
                if(CSTRING_F_MEMORY_CAN_GROW_TO_HEAP & flags)
                {
                    cstring_t   cs2;
                    CSTRING_RC  rc2 = cstring_createLenFn(&cs2, s, len, 0, NULL, capacity, pfnAllocFailHandler, param);

                    if(CSTRING_RC_SUCCESS != rc2)
                    {
                        return rc2;
                    }
                    else
                    {
                        memcpy(pcs, &cs2, sizeof(cstring_t));

                        return rc2;
                    }
                }
                else
                {
                    return CSTRING_RC_EXCEEDBORROWEDCAPACITY;
                }
            }

            pcs->ptr        =   (cstring_char_t*)arena;
            pcs->capacity   =   capacity - 1;
        }
        else
        {
            size_t      cch;
            CSTRING_RC  rc;

            cch = (0 == len) ? 1u : len;
            if(cch < capacity)
            {
                cch = capacity;
            }
            cch = (cch + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);

            pcs->ptr = (cstring_char_t*)cstring_realloc_2(NULL, cch + 1, flags, &rc, pfnAllocFailHandler, param);

            if(NULL == pcs->ptr)
            {
                return rc;
            }

            pcs->capacity = cch;
        }

        pcs->len        =   len;
        memcpy(pcs->ptr, s, len * sizeof(cstring_char_t));
        pcs->ptr[len]   =   '\0';
        pcs->flags      =   flags;

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_destroy(
    struct cstring_t* pcs
)
{
    CSTRING_RC  rc  =   CSTRING_RC_SUCCESS;

    cstring_assert(NULL != pcs);

    if(!(CSTRING_F_MEMORY_IS_BORROWED & pcs->flags))
    {
        (void)cstring_realloc_(pcs->ptr, 0, pcs->flags, &rc);
    }

    pcs->len        =   0;
    pcs->ptr        =   NULL;
    pcs->capacity   =   0;
    pcs->flags      =   0;

    return rc;
}

#ifndef CSTRING_OBSOLETE
CSTRING_EXTERN_C CSTRING_RC cstring_yield(
    struct cstring_t*   pcs
,   cstring_char_t**    ppBuff
);
#endif /* !CSTRING_OBSOLETE */

/**
 * \deprecated
 */
CSTRING_EXTERN_C CSTRING_RC cstring_yield(
    struct cstring_t*   pcs
,   cstring_char_t**    ppBuff
)
{
    cstring_assert(NULL != pcs);
    cstring_assert(NULL != ppBuff);

    *ppBuff = NULL;

    if(CSTRING_F_MEMORY_IS_READONLY & pcs->flags)
    {
        return CSTRING_RC_READONLY;
    }
    else if(CSTRING_F_MEMORY_IS_BORROWED & pcs->flags)
    {
        return CSTRING_RC_BORROWED;
    }
    else
    {
        *ppBuff = pcs->ptr;

        pcs->ptr        =   NULL;
        pcs->len        =   0;
        pcs->capacity   =   0;

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_yield2(
    struct cstring_t*   pcs
,   cstring_char_t**    pPayload
,   void**              pRaw
)
{
    cstring_assert(NULL != pcs);
    cstring_assert(NULL != pPayload);
    cstring_assert(NULL != pRaw);
    cstring_assert((void**)pPayload != pRaw);

    *pPayload   =   NULL;
    *pRaw       =   NULL;

    if(CSTRING_F_MEMORY_IS_READONLY & pcs->flags)
    {
        return CSTRING_RC_READONLY;
    }
    else if(CSTRING_F_MEMORY_IS_BORROWED & pcs->flags)
    {
        return CSTRING_RC_BORROWED;
    }
    else
    {
        *pPayload   =   pcs->ptr;
        *pRaw       =   pcs->ptr;

        pcs->ptr        =   NULL;
        pcs->len        =   0;
        pcs->capacity   =   0;

        return CSTRING_RC_SUCCESS;
    }
}


CSTRING_EXTERN_C CSTRING_RC cstring_setCapacity(
    struct cstring_t*   pcs
,   size_t              capacity
)
{
    return cstring_setCapacityFn(pcs, capacity, NULL, NULL);
}

/** This is an experimental feature */
CSTRING_EXTERN_C CSTRING_RC cstring_setCapacityFn(
    struct cstring_t*           pcs
,   size_t                      newCapacity
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
)
{
    cstring_assert(NULL != pcs);

    if(CSTRING_F_MEMORY_IS_READONLY & pcs->flags)
    {
        return CSTRING_RC_READONLY;
    }
    else
    {
        if(CSTRING_F_MEMORY_IS_FIXED & pcs->flags)
        {
            return CSTRING_RC_EXCEEDFIXEDCAPACITY;
        }
        else if(CSTRING_F_MEMORY_IS_BORROWED & pcs->flags)
        {
            if( newCapacity != pcs->capacity &&
                newCapacity > pcs->len)
            {
                if(CSTRING_F_MEMORY_CAN_GROW_TO_HEAP & pcs->flags)
                {
                    cstring_t   cs2;
                    CSTRING_RC  rc2 = cstring_createLenEx(&cs2, pcs->ptr, pcs->len, 0, NULL, newCapacity);

                    if(CSTRING_RC_SUCCESS != rc2)
                    {
                        return rc2;
                    }
                    else
                    {
                        memcpy(pcs, &cs2, sizeof(cstring_t));

                        return rc2;
                    }
                }
                else
                {
                    return CSTRING_RC_EXCEEDBORROWEDCAPACITY;
                }
            }
        }
        else if(newCapacity != pcs->capacity &&
                newCapacity > pcs->len)
        {
            CSTRING_RC      rc;
            cstring_char_t* newPtr;

            newCapacity =   (newCapacity + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);
            newPtr      =   (cstring_char_t*)cstring_realloc_2(pcs->ptr, newCapacity + 1, pcs->flags, &rc, pfnAllocFailHandler, param);

            if(NULL == newPtr)
            {
                return rc;
            }
            else
            {
                pcs->ptr            =   newPtr;
                pcs->ptr[pcs->len]  =   '\0';
            }

            pcs->capacity = newCapacity;
        }

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_assign(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
)
{
    return cstring_assignFn(pcs, s, NULL, NULL);
}

/** This is an experimental feature */
CSTRING_EXTERN_C CSTRING_RC cstring_assignFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
)
{
    cstring_assert(NULL != pcs);

    if(CSTRING_F_MEMORY_IS_READONLY & pcs->flags)
    {
        return CSTRING_RC_READONLY;
    }
    else
    {
        const size_t len = cstring_strlen_safe_(s);

        if( 0 == pcs->capacity ||
            pcs->capacity < len)
        {
            size_t cch;

            cch =   (0 == len) ? 1u : len;
            cch =   (cch + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);

            if(cch < pcs->capacity * 2)
            {
                cch = pcs->capacity * 2;
            }

            if(CSTRING_F_MEMORY_IS_FIXED & pcs->flags)
            {
                return CSTRING_RC_EXCEEDFIXEDCAPACITY;
            }
            else if(CSTRING_F_MEMORY_IS_BORROWED & pcs->flags)
            {
                if(CSTRING_F_MEMORY_CAN_GROW_TO_HEAP & pcs->flags)
                {
                    cstring_t   cs2;
                    CSTRING_RC  rc2 = cstring_createLenFn(&cs2, s, len, 0, NULL, 0, pfnAllocFailHandler, param);

                    if(CSTRING_RC_SUCCESS != rc2)
                    {
                        return rc2;
                    }
                    else
                    {
                        cstring_destroy(pcs);

                        memcpy(pcs, &cs2, sizeof(cstring_t));

                        return rc2;
                    }
                }
                else
                {
                    return CSTRING_RC_EXCEEDBORROWEDCAPACITY;
                }
            }
            else
            {
                CSTRING_RC      rc;
                cstring_char_t* newPtr = (cstring_char_t*)cstring_realloc_2(pcs->ptr, cch + 1, pcs->flags, &rc, pfnAllocFailHandler, param);

                if(NULL == newPtr)
                {
                    return rc;
                }
                else
                {
                    pcs->ptr = newPtr;
                }

                pcs->capacity = cch;
            }
        }

        /* WARNING: This code is not self-assignment safe */

        pcs->len = len;
        memcpy(pcs->ptr, s, len * sizeof(cstring_char_t));
        pcs->ptr[len] = '\0';

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_assignLen(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   size_t                  len
)
{
    return cstring_assignLenFn(pcs, s, len, NULL, NULL);
}

/** This is an experimental feature */
CSTRING_EXTERN_C CSTRING_RC cstring_assignLenFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   size_t                      len
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
)
{
    cstring_assert(NULL != pcs);

    if(CSTRING_F_MEMORY_IS_READONLY & pcs->flags)
    {
        return CSTRING_RC_READONLY;
    }
    else
    {
        if( 0 == pcs->capacity ||
            pcs->capacity < len)
        {
            size_t cch;

            cch =   (0 == len) ? 1u : len;
            cch =   (cch + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);

            if(cch < pcs->capacity * 2)
            {
                cch = pcs->capacity * 2;
            }

            if(CSTRING_F_MEMORY_IS_FIXED & pcs->flags)
            {
                return CSTRING_RC_EXCEEDFIXEDCAPACITY;
            }
            else if(CSTRING_F_MEMORY_IS_BORROWED & pcs->flags)
            {
                if(CSTRING_F_MEMORY_CAN_GROW_TO_HEAP & pcs->flags)
                {
                    cstring_t   cs2;
                    CSTRING_RC  rc2 = cstring_createLenFn(&cs2, s, len, 0, NULL, 0, pfnAllocFailHandler, param);

                    if(CSTRING_RC_SUCCESS != rc2)
                    {
                        return rc2;
                    }
                    else
                    {
                        cstring_destroy(pcs);

                        memcpy(pcs, &cs2, sizeof(cstring_t));

                        return rc2;
                    }
                }
                else
                {
                    return CSTRING_RC_EXCEEDBORROWEDCAPACITY;
                }
            }
            else
            {
                CSTRING_RC      rc;
                cstring_char_t* newPtr = (cstring_char_t*)cstring_realloc_2(pcs->ptr, cch + 1, pcs->flags, &rc, pfnAllocFailHandler, param);

                if(NULL == newPtr)
                {
                    return rc;
                }
                else
                {
                    pcs->ptr = newPtr;
                }

                pcs->capacity = cch;
            }
        }

        pcs->len = len;
        memcpy(pcs->ptr, s, len * sizeof(cstring_char_t));
        pcs->ptr[len] = '\0';

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_copy(
    struct cstring_t*         pcs
,   struct cstring_t const*   pcsSrc
)
{
    cstring_assert(NULL != pcs);
    cstring_assert(NULL != pcsSrc);

    return cstring_assignLen(pcs, pcsSrc->ptr, pcsSrc->len);
}

CSTRING_EXTERN_C CSTRING_RC cstring_append(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
)
{
    return cstring_appendFn(pcs, s,NULL, NULL);
}

/** This is an experimental feature */
CSTRING_EXTERN_C CSTRING_RC cstring_appendFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
)
{
    cstring_assert(NULL != pcs);

    if(CSTRING_F_MEMORY_IS_READONLY & pcs->flags)
    {
        return CSTRING_RC_READONLY;
    }
    else
    {
        size_t const    len     =   cstring_strlen_safe_(s);
        size_t const    newLen  =   pcs->len + len;

        if(pcs->capacity < newLen)
        {
            size_t cch;

            cch =   newLen;
            cch =   (cch + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);

            if(cch < pcs->capacity * 2)
            {
                cch = pcs->capacity * 2;
            }

            if(CSTRING_F_MEMORY_IS_FIXED & pcs->flags)
            {
                return CSTRING_RC_EXCEEDFIXEDCAPACITY;
            }
            else if(CSTRING_F_MEMORY_IS_BORROWED & pcs->flags)
            {
                if(CSTRING_F_MEMORY_CAN_GROW_TO_HEAP & pcs->flags)
                {
                    cstring_t       cs2;
                    size_t const    len2    =   len + pcs->len;
                    CSTRING_RC      rc2     =   cstring_createLenEx(&cs2, pcs->ptr, pcs->len, 0, NULL, len2);

                    if(CSTRING_RC_SUCCESS != rc2)
                    {
                        return rc2;
                    }
                    else
                    {
                        rc2 = cstring_appendFn(&cs2, s, pfnAllocFailHandler, param);

                        if(CSTRING_RC_SUCCESS != rc2)
                        {
                            return rc2;
                        }
                        else
                        {
                            memcpy(pcs, &cs2, sizeof(cstring_t));

                            return rc2;
                        }
                    }
                }
                else
                {
                    return CSTRING_RC_EXCEEDBORROWEDCAPACITY;
                }
            }
            else
            {
                CSTRING_RC      rc;
                cstring_char_t* newPtr = (cstring_char_t*)cstring_realloc_2(pcs->ptr, cch + 1, pcs->flags, &rc, pfnAllocFailHandler, param);

                if(NULL == newPtr)
                {
                    return rc;
                }
                else
                {
                    pcs->ptr = newPtr;
                }

                pcs->capacity = cch;
            }
        }

        memcpy(pcs->ptr + pcs->len, s, len * sizeof(cstring_char_t));
        pcs->len            +=  len;
        pcs->ptr[pcs->len]  =   '\0';

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_appendLen(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   size_t                  len
)
{
    return cstring_appendLenFn(pcs, s, len, NULL, NULL);
}

/** This is an experimental feature */
CSTRING_EXTERN_C CSTRING_RC cstring_appendLenFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   size_t                      len
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
)
{
    cstring_assert(NULL != pcs);
    cstring_assert(NULL != s || 0 == len);

    if(CSTRING_F_MEMORY_IS_READONLY & pcs->flags)
    {
        return CSTRING_RC_READONLY;
    }
    else
    {
        size_t newLen = pcs->len + len;

        if(pcs->capacity < newLen)
        {
            size_t cch;

            cch  =   pcs->len + len;
            cch  =   (cch + (CSTRING_ALLOC_GRANULARITY - 1)) & ~(CSTRING_ALLOC_GRANULARITY - 1);

            if(cch < pcs->capacity * 2)
            {
                cch = pcs->capacity * 2;
            }

            if(CSTRING_F_MEMORY_IS_FIXED & pcs->flags)
            {
                return CSTRING_RC_EXCEEDFIXEDCAPACITY;
            }
            else if(CSTRING_F_MEMORY_IS_BORROWED & pcs->flags)
            {
                if(CSTRING_F_MEMORY_CAN_GROW_TO_HEAP & pcs->flags)
                {
                    cstring_t       cs2;
                    size_t const    len2    =   len + pcs->len;
                    CSTRING_RC      rc2     =   cstring_createLenEx(&cs2, pcs->ptr, pcs->len, 0, NULL, len2);

                    if(CSTRING_RC_SUCCESS != rc2)
                    {
                        return rc2;
                    }
                    else
                    {
                        rc2 = cstring_appendLenFn(&cs2, s, len, pfnAllocFailHandler, param);

                        if(CSTRING_RC_SUCCESS != rc2)
                        {
                            return rc2;
                        }
                        else
                        {
                            cstring_destroy(pcs);

                            memcpy(pcs, &cs2, sizeof(cstring_t));

                            return rc2;
                        }
                    }
                }
                else
                {
                    return CSTRING_RC_EXCEEDBORROWEDCAPACITY;
                }
            }
            else
            {
                CSTRING_RC      rc;
                cstring_char_t* newPtr = (cstring_char_t*)cstring_realloc_2(pcs->ptr, cch + 1, pcs->flags, &rc, pfnAllocFailHandler, param);

                if(NULL == newPtr)
                {
                    return rc;
                }
                else
                {
                    pcs->ptr = newPtr;
                }

                pcs->capacity = cch;
            }
        }

        memcpy(pcs->ptr + pcs->len, s, len * sizeof(cstring_char_t));
        pcs->len            +=  len;
        pcs->ptr[pcs->len]  =   '\0';

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_truncate(
    struct cstring_t*   pcs
,   size_t              len
)
{
    cstring_assert(NULL != pcs);

    if(CSTRING_F_MEMORY_IS_READONLY & pcs->flags)
    {
        return CSTRING_RC_READONLY;
    }
    else
    {
        if(len < pcs->len)
        {
            pcs->ptr[pcs->len = len] = '\0';
        }

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_swap(
    struct cstring_t* pcs1
,   struct cstring_t* pcs2
)
{
    cstring_assert(NULL != pcs1);
    cstring_assert(NULL != pcs2);

    if( (CSTRING_F_MEMORY_IS_READONLY & pcs1->flags) ||
        (CSTRING_F_MEMORY_IS_READONLY & pcs2->flags))
    {
        return CSTRING_RC_READONLY;
    }
    else if((CSTRING_F_MEMORY_IS_BORROWED & pcs1->flags) ||
            (CSTRING_F_MEMORY_IS_BORROWED & pcs2->flags))
    {
        return CSTRING_RC_BORROWED;
    }
    else
    {
        struct cstring_t cs;

        cs      =   *pcs1;
        *pcs1   =   *pcs2;
        *pcs2   =   cs;

        return CSTRING_RC_SUCCESS;
    }
}

/* /////////////////////////////////////////////////////////////////////////
 * File functions
 */

CSTRING_EXTERN_C CSTRING_RC cstring_readline(
    FILE*               stm
,   struct cstring_t*   pcs
,   size_t*             numRead /* = NULL */
)
{
    int     previous = '\0';
    size_t  numRead_;

    cstring_assert(NULL != pcs);

    if(NULL == numRead)
    {
        numRead = &numRead_;
    }

    if( NULL == stm ||
        0 != ferror(stm))
    {
        return CSTRING_RC_INVALIDSTREAM;
    }

    *numRead = 0u;

    cstring_truncate(pcs, 0);

    for(;;)
    {
        int ch = fgetc(stm);

        if(EOF == ch)
        {
            return CSTRING_RC_EOF;
        }
        else
        {
            if('\n' == ch)
            {
                if('\r' == previous)
                {
                    cstring_truncate(pcs, pcs->len - 1u);
                }

                return CSTRING_RC_SUCCESS;
            }
            else
            {
                cstring_char_t  c1 = (char)ch;
                CSTRING_RC      rc = cstring_appendLen(pcs, &c1, 1u);

                if(CSTRING_RC_SUCCESS != rc)
                {
                    return rc;
                }

                ++*numRead;

                previous = ch;
            }

        }
    }
}

static
CSTRING_RC
cstring_write_(
    FILE*                   stm
,   struct cstring_t const* pcs
,   size_t*                 numWritten /* = NULL */
,   char const*             fmt
)
{
    int     r;
    size_t  numWritten_;

    cstring_assert(NULL != pcs);

    if(NULL == numWritten)
    {
        numWritten = &numWritten_;
    }

    if( NULL == stm ||
        0 != ferror(stm))
    {
        return CSTRING_RC_INVALIDSTREAM;
    }

    *numWritten = 0u;

    r = fprintf(stm, fmt, (int)pcs->len, pcs->ptr);

    if(r < 0)
    {
        return CSTRING_RC_IOERROR;
    }
    else
    {
        *numWritten = (size_t)r;

        return CSTRING_RC_SUCCESS;
    }
}

CSTRING_EXTERN_C CSTRING_RC cstring_writeline(
    FILE*                   stm
,   struct cstring_t const* pcs
,   size_t*                 numWritten /* = NULL */
)
{
    return cstring_write_(stm, pcs, numWritten, "%.*s\n");
}

CSTRING_EXTERN_C CSTRING_RC cstring_write(
    FILE*                   stm
,   struct cstring_t const* pcs
,   size_t*                 numWritten /* = NULL */
)
{
    return cstring_write_(stm, pcs, numWritten, "%.*s");
}

/* /////////////////////////////////////////////////////////////////////////
 * Search/replace functions
 */

CSTRING_EXTERN_C CSTRING_RC cstring_insert(
    struct cstring_t*       pcs
,   int                     index
,   cstring_char_t const*   s
)
{
    const size_t cch = cstring_strlen_safe_(s);

    return cstring_insertLen(pcs, index, s, cch);
}

CSTRING_EXTERN_C CSTRING_RC cstring_insertLen(
    struct cstring_t*       pcs
,   int                     index
,   cstring_char_t const*   s
,   size_t                  len
)
{
    size_t  realIndex;

    cstring_assert(NULL != pcs);

    if(index < 0)
    {
        CSTRING_RC rc = convert_negative_index(pcs, index, &realIndex);

        if(rc != CSTRING_RC_SUCCESS)
        {
            return rc;
        }
    }
    else
    {
        realIndex = (size_t)index;
    }

    if(realIndex > pcs->len)
    {
        return CSTRING_RC_INVALIDSECTION;
    }

    if(len > pcs->capacity - pcs->len)
    {
        CSTRING_RC rc = cstring_setCapacity(pcs, pcs->len + len);

        if(rc != CSTRING_RC_SUCCESS)
        {
            return rc;
        }
    }

    if(0 != len)
    {
        /* copy over the rhs of the string */
        const size_t n = pcs->len - realIndex;

        memmove(pcs->ptr + realIndex + len, pcs->ptr + realIndex, n * sizeof(cstring_char_t));

        pcs->len += len;
        memcpy(pcs->ptr + realIndex, s, sizeof(cstring_char_t) * len);
        pcs->ptr[pcs->len] = '\0';
    }

    return CSTRING_RC_SUCCESS;
}

CSTRING_EXTERN_C CSTRING_RC cstring_replace(
    struct cstring_t*       pcs
,   int                     index
,   size_t                  len
,   cstring_char_t const*   s
)
{
    const size_t cch = cstring_strlen_safe_(s);

    return cstring_replaceLen(pcs, index, len, s, cch);
}

CSTRING_EXTERN_C CSTRING_RC cstring_replaceLen(
    struct cstring_t*       pcs
,   int                     index
,   size_t                  len
,   cstring_char_t const*   s
,   size_t                  cch
)
{
    size_t  realIndex;

    cstring_assert(NULL != pcs);

    if(index < 0)
    {
        CSTRING_RC rc = convert_negative_index(pcs, index, &realIndex);

        if(rc != CSTRING_RC_SUCCESS)
        {
            return rc;
        }
    }
    else
    {
        realIndex = (size_t)index;
    }

    if(realIndex + len > pcs->len)
    {
        return CSTRING_RC_INVALIDSECTION;
    }

    if(cch > len)
    {
        CSTRING_RC rc = cstring_setCapacity(pcs, pcs->len + (cch - len));

        if(rc != CSTRING_RC_SUCCESS)
        {
            return rc;
        }
    }

    if(len != cch)
    {
        /* copy over the rhs of the string */
        const size_t n = pcs->len - (realIndex + len);

        memmove(pcs->ptr + realIndex + cch, pcs->ptr + realIndex + len, n * sizeof(cstring_char_t));

        if(cch > len)
        {
            pcs->len += (cch - len);
        }
        else
        {
            pcs->len -= (len - cch);
        }

        pcs->ptr[pcs->len] = '\0';
    }

    /* we can simply replace directly */
    memcpy(pcs->ptr + realIndex, s, sizeof(cstring_char_t) * cch);

    return CSTRING_RC_SUCCESS;
}

CSTRING_EXTERN_C CSTRING_RC cstring_replaceAll(
    struct cstring_t*       pcs
,   cstring_char_t const*   f
,   cstring_char_t const*   t
,   size_t*                 numReplaced /* = NULL */
)
{
    size_t  numReplaced_;

    cstring_assert(NULL != pcs);

    if(NULL == numReplaced)
    {
        numReplaced = &numReplaced_;
    }

    *numReplaced = 0u;

    if( NULL == f ||
        '\0' == 0[f])
    {
       return CSTRING_RC_SUCCESS;
    }
    else if(0 == pcs->len)
    {
       return CSTRING_RC_SUCCESS;
    }
    else
    {
        /* Search for first, then replace, then repeat from search pos */
        const size_t    flen    =   cstring_strlen_(f);
        const size_t    tlen    =   cstring_strlen_safe_(t);
        size_t          pos     =   0;
        cstring_char_t* p;

        for(; NULL != (p = cstring_strstr_(pcs->ptr + pos, f)); pos += tlen)
        {
            CSTRING_RC rc;

            pos = (size_t)(p - pcs->ptr);

            rc = cstring_replaceLen(pcs, (int)pos, flen, t, tlen);

            if(CSTRING_RC_SUCCESS != rc)
            {
                return rc;
            }
        }

        return CSTRING_RC_SUCCESS;
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * Win32 functions
 */

#if defined(CSTRING_USE_WINAPI_)

# ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
#  if defined(__MWERKS__)
#   define  GMEM_FIXED      0
#   define  GMEM_MOVEABLE   2
#   define  WINAPI          __stdcall
typedef int             BOOL;
typedef void*           HANDLE;
typedef void*           HGLOBAL;
typedef void*           HMODULE;
typedef void*           HINSTANCE;
typedef long            LONG;
__declspec(dllimport) long      __stdcall   InterlockedExchange(LONG volatile *, LONG);
__declspec(dllimport) HANDLE    __stdcall   GetProcessHeap(void);
__declspec(dllimport) HGLOBAL   __stdcall   GlobalAlloc(unsigned int, unsigned long);
__declspec(dllimport) HGLOBAL   __stdcall   GlobalFree(HGLOBAL);
__declspec(dllimport) HGLOBAL   __stdcall   GlobalReAlloc(HGLOBAL, unsigned long, unsigned int);
__declspec(dllimport) void*     __stdcall  HeapAlloc(HANDLE, unsigned long, unsigned int);
__declspec(dllimport) BOOL      __stdcall   HeapFree(HANDLE, unsigned long, void* );
__declspec(dllimport) void*     __stdcall  HeapReAlloc(HANDLE, unsigned long, void*, unsigned int);
__declspec(dllimport) void      __stdcall   Sleep(unsigned long);
__declspec(dllimport) HINSTANCE __stdcall   LoadLibraryA(char const* );
__declspec(dllimport) BOOL      __stdcall   FreeLibrary(HMODULE );
__declspec(dllimport) void*     __stdcall  GetProcAddress(HMODULE, char const*);
#  else /* ? compiler */
#   include <windows.h>
#  endif /* compiler */
# endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */

/* ////////////////////////////////////////////////////////////////////// */

static
void*
win32_global_realloc(
    void*   pv
,   size_t  cb
)
{
    /* Logic borrowed from implementation of SynesisWin::GlobalAtor class (in
     * file MWAtors.h) from the Synesis Software Public Domain Source Code
     * Library (http://synesis.com.au/software).
     */
    if(NULL != pv)
    {
        if(0 == cb)
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

static
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
    if(NULL != pv)
    {
        if(0 == cb)
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

static
void*
win32_comtask_realloc(
    void*   pv
,   size_t  cb
)
{
    typedef void* (WINAPI *PfnCoTaskMemRealloc)(void* , size_t );

    static LONG                 s_cstring_PfnCoTaskMemRealloc_init  =   0;
    static LONG                 s_cstring_PfnCoTaskMemRealloc_spin  =   0;
    static HINSTANCE            s_cstring_ole32_HINSTANCE           =   NULL;
    static PfnCoTaskMemRealloc  s_cstring_pfnCoTaskMemRealloc       =   NULL;

    if(NULL == pv)
    {
        for(; 0 != InterlockedExchange(&s_cstring_PfnCoTaskMemRealloc_spin, 1); Sleep(0))
        {}

        if(1 == ++s_cstring_PfnCoTaskMemRealloc_init)
        {
            s_cstring_ole32_HINSTANCE       =   LoadLibraryA("OLE32");
            s_cstring_pfnCoTaskMemRealloc   =   (PfnCoTaskMemRealloc)GetProcAddress(s_cstring_ole32_HINSTANCE, "CoTaskMemRealloc");

            if( NULL == s_cstring_ole32_HINSTANCE ||
                NULL == s_cstring_pfnCoTaskMemRealloc)
            {
                --s_cstring_PfnCoTaskMemRealloc_init;
            }
        }

        InterlockedExchange(&s_cstring_PfnCoTaskMemRealloc_spin, 0);
    }

    pv = (NULL != s_cstring_pfnCoTaskMemRealloc) ? s_cstring_pfnCoTaskMemRealloc(pv, cb) : NULL;

    if(0 == cb)
    {
        for(; 0 != InterlockedExchange(&s_cstring_PfnCoTaskMemRealloc_spin, 1); Sleep(0))
        {}

        if(0 == --s_cstring_PfnCoTaskMemRealloc_init)
        {
            FreeLibrary(s_cstring_ole32_HINSTANCE);
        }

        InterlockedExchange(&s_cstring_PfnCoTaskMemRealloc_spin, 0);
    }

    return pv;
}

/* ////////////////////////////////////////////////////////////////////// */

#endif /* CSTRING_USE_WINAPI_ */

/* /////////////////////////////////////////////////////////////////////////
 * Compiler warnings
 */

#if defined(_MSC_VER) && \
    _MSC_VER >= 1200
# pragma warning(pop)
#endif /* compiler */

/* ///////////////////////////// end of file //////////////////////////// */

