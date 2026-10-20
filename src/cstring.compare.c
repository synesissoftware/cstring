/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring.compare.c
 *
 * Purpose: Equality and ordering of cstring instances
 *
 * Created: 6th October 2026
 * Updated: 6th October 2026
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2026, Matthew Wilson and Synesis Information Systems
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


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>
#include "internal.h"

#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * comparison
 *
 * A NULL cstring_t, or a zero length, is empty. That payload is not read.
 * cstring_equal() returns before any read when the lengths differ.
 * Multibyte ordering is memcmp, which matches unsigned char order. Wide
 * ordering walks wchar_t values. A shared prefix with a shorter length
 * compares less.
 */

cstring_truthy_t
cstring_equal(
    struct cstring_t const* lhs
,   struct cstring_t const* rhs
)
{
    size_t const    lhs_len =   (NULL == lhs) ? 0u : lhs->len;
    size_t const    rhs_len =   (NULL == rhs) ? 0u : rhs->len;

    CSTRING_ASSERT(0u == lhs_len || NULL != lhs->ptr);
    CSTRING_ASSERT(0u == rhs_len || NULL != rhs->ptr);

    if (lhs_len != rhs_len)
    {
        return 0;
    }

    if (0u == lhs_len)
    {
        return 1;
    }

    return 0 == memcmp(
        lhs->ptr
    ,   rhs->ptr
    ,   lhs_len * sizeof(cstring_char_t)
    );
}

cstring_sint_t
cstring_compare(
    struct cstring_t const* lhs
,   struct cstring_t const* rhs
)
{
    size_t const    lhs_len =   (NULL == lhs) ? 0u : lhs->len;
    size_t const    rhs_len =   (NULL == rhs) ? 0u : rhs->len;
    size_t const    n       =   (lhs_len < rhs_len) ? lhs_len : rhs_len;

    CSTRING_ASSERT(0u == lhs_len || NULL != lhs->ptr);
    CSTRING_ASSERT(0u == rhs_len || NULL != rhs->ptr);

    if (0u != n)
    {
#ifndef CSTRING_USE_WIDE_STRINGS

        int const cmp = memcmp(lhs->ptr, rhs->ptr, n);

        if (cmp < 0)
        {
            return -1;
        }
        if (0 < cmp)
        {
            return +1;
        }
#else /* ? CSTRING_USE_WIDE_STRINGS */

        cstring_char_t const*   lhs_ptr =   (0u == n) ? NULL : lhs->ptr;
        cstring_char_t const*   rhs_ptr =   (0u == n) ? NULL : rhs->ptr;
        size_t                  i;

        for (i = 0; i != n; ++i)
        {
            cstring_char_t const lu = lhs_ptr[i];
            cstring_char_t const ru = rhs_ptr[i];

            if (lu < ru)
            {
                return -1;
            }
            if (ru < lu)
            {
                return +1;
            }
        }
#endif /* CSTRING_USE_WIDE_STRINGS */
    }

    if (lhs_len < rhs_len)
    {
        return -1;
    }
    if (rhs_len < lhs_len)
    {
        return +1;
    }

    return 0;
}


/* ///////////////////////////// end of file //////////////////////////// */

