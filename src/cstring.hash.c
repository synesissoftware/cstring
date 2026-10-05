/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring.hash.c
 *
 * Purpose: The implementation of the cstring hash API
 *
 * Created: 5th September 2026
 * Updated: 5th October 2026
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


/** \file cstring.hash.c The implementation of the cstring hash API
 */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* cstring header files */

#include <cstring/cstring.h>
#include "internal.h"

/* Standard C header files */

#include <ctype.h>
#ifdef CSTRING_USE_WIDE_STRINGS
# include <wctype.h>
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * character encoding
 */

#ifdef CSTRING_USE_WIDE_STRINGS

# define cstring_tolower_                                   towlower
#else /* ? CSTRING_USE_WIDE_STRINGS */

# define cstring_tolower_                                   tolower
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * hashing functions
 */

cstring_hash_t
cstring_hash_djb2(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return CSTRING_HASH_DJB2_SEED;
    }

    return cstring_hash_djb2_len(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_djb2_case(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return CSTRING_HASH_DJB2_SEED;
    }

    return cstring_hash_djb2_len_case(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_djb2_len(
    cstring_char_t const*   s
,   size_t                  cch
)
{
    cstring_hash_t hash = CSTRING_HASH_DJB2_SEED;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            uint8_t const c = (uint8_t)s[i];

            hash = ((hash << 5) + hash) + c;
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_djb2_len_case(
    cstring_char_t const*   s
,   size_t                  cch
)
{
    cstring_hash_t hash = CSTRING_HASH_DJB2_SEED;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
#ifdef CSTRING_USE_WIDE_STRINGS
            uint8_t const c = (uint8_t)(unsigned int)cstring_tolower_(s[i]);
#else
            uint8_t const c = (uint8_t)cstring_tolower_((unsigned char)s[i]);
#endif

            hash = ((hash << 5) + hash) + c;
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_fnv1a(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return CSTRING_HASH_FNV1A_OFFSET;
    }

    return cstring_hash_fnv1a_len(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_fnv1a_case(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return CSTRING_HASH_FNV1A_OFFSET;
    }

    return cstring_hash_fnv1a_len_case(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_fnv1a_len(
    cstring_char_t const*   s
,   size_t                  cch
)
{
    cstring_hash_t hash = CSTRING_HASH_FNV1A_OFFSET;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            uint8_t const c = (uint8_t)s[i];

            hash ^= c;
            hash *= CSTRING_HASH_FNV1A_PRIME;
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_fnv1a_len_case(
    cstring_char_t const*   s
,   size_t                  cch
)
{
    cstring_hash_t hash = CSTRING_HASH_FNV1A_OFFSET;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
#ifdef CSTRING_USE_WIDE_STRINGS
            uint8_t const c = (uint8_t)(unsigned int)cstring_tolower_(s[i]);
#else
            uint8_t const c = (uint8_t)cstring_tolower_((unsigned char)s[i]);
#endif

            hash ^= c;
            hash *= CSTRING_HASH_FNV1A_PRIME;
        }
    }

    return hash;
}


/* ///////////////////////////// end of file //////////////////////////// */

