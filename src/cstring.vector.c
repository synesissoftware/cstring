/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring.vector.c
 *
 * Purpose: The implementation of the cstring.vector API
 *
 * Created: 16th June 1994
 * Updated: 16th December 2020
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


/** \file cstring.vector.c The implementation of the cstring.vector API
 */

/* /////////////////////////////////////////////////////////////////////////
 * Includes
 */

/* cstring Header Files */

#include <cstring/cstring.vector.h>

#ifndef CSTRING_INCL_CSTRING_INTERNAL_H_SAFESTR
# include <cstring/internal/safestr.h>
#endif /* CSTRING_INCL_CSTRING_INTERNAL_H_SAFESTR */

/* Standard C Header Files */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* /////////////////////////////////////////////////////////////////////////
 * Constants & definitions
 */

#define CSTRING_VECTOR_DEF_CAPACITY_    (8)

/* /////////////////////////////////////////////////////////////////////////
 * Debugging
 */

#define cstring_vector_assert(expr)     assert(expr)

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
 * Compiler compatibility
 */

#if defined(__BORLANDC__)
char* strncpy_safe(char* dest, char const* src, size_t len)
{
    if(0 != len)
    {
        strncpy(dest, src, len);
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
 * cstring.vector API functions
 */

CSTRING_RC
cstring_vector_init(
    cstring_vector_t*   pcsv
,   size_t              minCapacity
)
{
    cstring_vector_assert(NULL != pcsv);

    if(cstring_vector_DEFAULT_CAPACITY == minCapacity)
    {
        minCapacity = CSTRING_VECTOR_DEF_CAPACITY_;
    }

    if(0 == minCapacity)
    {
        cstring_vector_t const csv = cstring_vector_t_DEFAULT;

        *pcsv = csv;

        return CSTRING_RC_SUCCESS;
    }
    else
    {
        CSTRING_RC  rc  =   CSTRING_RC_SUCCESS;
        cstring_t*  ptr =   malloc(sizeof(cstring_t) * minCapacity);

        if(NULL == ptr)
        {
            rc = CSTRING_RC_OUTOFMEMORY;
        }
        else
        {
            pcsv->len       =   0;
            pcsv->ptr       =   ptr;
            pcsv->capacity  =   minCapacity;
            pcsv->flags     =   0;
        }

        return rc;
    }
}

CSTRING_RC
cstring_vector_destroy(
    cstring_vector_t*   pcsv
)
{
    CSTRING_RC  rc = CSTRING_RC_SUCCESS;
    size_t      i;

    cstring_vector_assert(NULL != pcsv);

    for(i = 0; i != pcsv->len; ++i)
    {
        CSTRING_RC rc2 = cstring_destroy(pcsv->ptr + i);

        if( CSTRING_RC_SUCCESS != rc2 &&
            CSTRING_RC_SUCCESS == rc)
        {
            rc = rc2;
        }
    }

    free(pcsv->ptr);

    pcsv->len       =   0;
    pcsv->ptr       =   NULL;
    pcsv->capacity  =   0;
    pcsv->flags     =   0;

    return rc;
}

CSTRING_RC
cstring_vector_truncate(
    cstring_vector_t*   pcsv
,   size_t              len
)
{
    CSTRING_RC  rc = CSTRING_RC_SUCCESS;
    size_t      i;

    cstring_vector_assert(NULL != pcsv);
    cstring_vector_assert(len <= pcsv->len);

    for(i = len; i != pcsv->len; ++i)
    {
        CSTRING_RC rc2 = cstring_destroy(pcsv->ptr + i);

        if( CSTRING_RC_SUCCESS != rc2 &&
            CSTRING_RC_SUCCESS == rc)
        {
            rc = rc2;
        }
    }

    pcsv->len = len;

    return rc;
}


CSTRING_RC
cstring_vector_create(
    cstring_vector_t*   pcsv
,   size_t              initialSize
)
{
    cstring_vector_assert(NULL != pcsv);

    if(cstring_vector_DEFAULT_CAPACITY == initialSize)
    {
        return (CSTRING_RC)CSTRING_RC_REQUESTTOOLARGE;
    }
    else
    {
        CSTRING_RC rc = cstring_vector_init(pcsv, initialSize);

        if(CSTRING_RC_SUCCESS == rc)
        {
            size_t i;

            cstring_vector_assert(pcsv->capacity >= initialSize);

            for(i = 0; i != initialSize; ++i)
            {
                CSTRING_RC rc2 = cstring_init(pcsv->ptr + i);

                if(CSTRING_RC_SUCCESS != rc2)
                {
                    while(0 != i)
                    {
                        cstring_destroy(pcsv->ptr + (i - 1));

                        --i;
                    }

                    rc = rc2;

                    pcsv->len = 0;

                    cstring_vector_destroy(pcsv);

                    break;
                }
            }
        }

        if(CSTRING_RC_SUCCESS == rc)
        {
            pcsv->len = initialSize;
        }

        return rc;
    }
}

CSTRING_RC
cstring_vector_insertAt(
    cstring_vector_t*   pcsv
,   size_t              position
,   cstring_t const*    strings
,   size_t              numStrings
)
{
    cstring_vector_assert(NULL != pcsv);
    cstring_vector_assert(NULL != strings || 0 == numStrings);

    if(0 == numStrings)
    {
        return CSTRING_RC_SUCCESS;
    }
    else
    {
        CSTRING_RC  rc  =   CSTRING_RC_SUCCESS;
        size_t      i;
        size_t      newSize = pcsv->len + numStrings;

        if(newSize > pcsv->capacity)
        {
            cstring_t* newPtr = realloc(pcsv->ptr, sizeof(cstring_t) * newSize);

            if(NULL == newPtr)
            {
                return CSTRING_RC_OUTOFMEMORY;
            }
            else
            {
                pcsv->ptr       =   newPtr;
                pcsv->capacity  =   newSize;
            }
        }

        /* Make space for new items */
        if(position < pcsv->len)
        {
            memmove(pcsv->ptr + pcsv->len + numStrings, pcsv->ptr + pcsv->len, sizeof(cstring_t) * numStrings);
        }

        for(i = 0; i != numStrings; ++i)
        {
            cstring_t* dest = pcsv->ptr + pcsv->len + i;

            if(NULL == strings)
            {
                cstring_t const cs = cstring_t_DEFAULT;

                *dest = cs;
            }
            else
            {
                cstring_t const*    src =   strings + i;
                CSTRING_RC          rc2 =   cstring_createLen(dest, src->ptr, src->len);

                if(CSTRING_RC_SUCCESS != rc2)
                {
                    while(0 != i)
                    {
                        cstring_destroy(pcsv->ptr + pcsv->len + (i - 1));

                        --i;
                    }

                    rc = rc2;
                    break;
                }
            }
        }

        if(CSTRING_RC_SUCCESS == rc)
        {
            pcsv->len += numStrings;
        }
        else
        {
            /* If it's failed, and we made space for new items, remove the gap (leaving it with increased capacity) */
            if(position < pcsv->len)
            {
                memmove(pcsv->ptr + pcsv->len, pcsv->ptr + pcsv->len + numStrings, sizeof(cstring_t) * numStrings);
            }
        }

        return rc;
    }
}

CSTRING_RC
cstring_vector_readLines(
    FILE*               stm
,   cstring_vector_t*   pcsv
,   size_t*             numLinesRead /* = NULL */
)
{
    CSTRING_RC  rc;
    cstring_t   cs = cstring_t_DEFAULT;
    size_t      numLinesRead_;
    size_t      initialLen;

    cstring_vector_assert(NULL != pcsv);

    initialLen = pcsv->len;

    if(NULL == numLinesRead)
    {
        numLinesRead = &numLinesRead_;
    }

    *numLinesRead = 0u;

    do
    {
        rc = cstring_readline(stm, &cs, NULL);

        if( CSTRING_RC_SUCCESS == rc ||
            CSTRING_RC_EOF == rc)
        {
            if( 0 != cs.len ||
                CSTRING_RC_EOF != rc)
            {
                CSTRING_RC rc2 = cstring_vector_append(pcsv, &cs, 1);

                if(CSTRING_RC_SUCCESS != rc2)
                {
                    /* TODO : make this "failure"-safe (i.e. carry out the operation into an empty csv then blat in all at once */

                    cstring_vector_truncate(pcsv, initialLen);

                    rc = rc2;

                    break;
                }
                else
                {
                    ++*numLinesRead;
                }
            }
        }

    } while(CSTRING_RC_SUCCESS == rc);

    cstring_destroy(&cs);

    return rc;
}

/* /////////////////////////////////////////////////////////////////////////
 * Compiler warnings
 */

#if defined(_MSC_VER) && \
    _MSC_VER >= 1200
# pragma warning(pop)
#endif /* compiler */

/* ///////////////////////////// end of file //////////////////////////// */

