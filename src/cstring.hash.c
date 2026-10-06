/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring.hash.c
 *
 * Purpose: The implementation of the cstring hash API
 *
 * Created: 5th September 2026
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
#include <string.h>
#include <wchar.h>
#include <wctype.h>


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

/* Each code unit contributes its low 8 bits. Multibyte input is read as
 * unsigned char. Wide input is truncated to uint8_t. Case-insensitive forms
 * fold with tolower or towlower before that truncation.
 */

static cstring_hash_t
cstring_hash_djb2_step_(
    cstring_hash_t  hash
,   uint8_t         octet
)
{
    return ((hash << 5) + hash) + octet;
}

static cstring_hash_t
cstring_hash_fnv1a_step_(
    cstring_hash_t  hash
,   uint8_t         octet
)
{
    hash ^= octet;
    hash *= CSTRING_HASH_FNV1A_PRIME;

    return hash;
}

static cstring_hash_t
cstring_hash_sdbm_step_(
    cstring_hash_t  hash
,   uint8_t         octet
)
{
    return (hash * CSTRING_HASH_SDBM_MULTIPLIER) + octet;
}


/* /////////////////////////////////////////////////////////////////////////
 * djb2
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

    return cstring_hash_djb2_buf(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_djb2_mbs(
    char const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_DJB2_SEED;
    }

    return cstring_hash_djb2_mbuf(s, strlen(s));
}

cstring_hash_t
cstring_hash_djb2_wcs(
    wchar_t const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_DJB2_SEED;
    }

    return cstring_hash_djb2_wbuf(s, wcslen(s));
}

cstring_hash_t
cstring_hash_djb2_buf(
    cstring_char_t const*   s
,   size_t                  cch
)
{
#ifdef CSTRING_USE_WIDE_STRINGS

    return cstring_hash_djb2_wbuf(s, cch);
#else /* ? CSTRING_USE_WIDE_STRINGS */

    return cstring_hash_djb2_mbuf(s, cch);
#endif /* CSTRING_USE_WIDE_STRINGS */
}

cstring_hash_t
cstring_hash_djb2_mbuf(
    char const* s
,   size_t      cch
)
{
    cstring_hash_t hash = CSTRING_HASH_DJB2_SEED;

    if (NULL != s)
    {
        unsigned char const* p = (unsigned char const*)s;
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_djb2_step_(hash, p[i]);
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_djb2_wbuf(
    wchar_t const*  s
,   size_t          cch
)
{
    cstring_hash_t hash = CSTRING_HASH_DJB2_SEED;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_djb2_step_(hash, (uint8_t)s[i]);
        }
    }

    return hash;
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

    return cstring_hash_djb2_buf_case(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_djb2_mbs_case(
    char const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_DJB2_SEED;
    }

    return cstring_hash_djb2_mbuf_case(s, strlen(s));
}

cstring_hash_t
cstring_hash_djb2_wcs_case(
    wchar_t const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_DJB2_SEED;
    }

    return cstring_hash_djb2_wbuf_case(s, wcslen(s));
}

cstring_hash_t
cstring_hash_djb2_buf_case(
    cstring_char_t const*   s
,   size_t                  cch
)
{
#ifdef CSTRING_USE_WIDE_STRINGS

    return cstring_hash_djb2_wbuf_case(s, cch);
#else /* ? CSTRING_USE_WIDE_STRINGS */

    return cstring_hash_djb2_mbuf_case(s, cch);
#endif /* CSTRING_USE_WIDE_STRINGS */
}

cstring_hash_t
cstring_hash_djb2_mbuf_case(
    char const* s
,   size_t      cch
)
{
    cstring_hash_t hash = CSTRING_HASH_DJB2_SEED;

    if (NULL != s)
    {
        unsigned char const* p = (unsigned char const*)s;
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_djb2_step_(hash, (uint8_t)tolower(p[i]));
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_djb2_wbuf_case(
    wchar_t const*  s
,   size_t          cch
)
{
    cstring_hash_t hash = CSTRING_HASH_DJB2_SEED;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            uint8_t const octet = (uint8_t)(unsigned)towlower(s[i]);

            hash = cstring_hash_djb2_step_(hash, octet);
        }
    }

    return hash;
}


/* /////////////////////////////////////////////////////////////////////////
 * FNV-1a
 */

cstring_hash_t
cstring_hash_fnv1a(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return CSTRING_HASH_FNV1A_OFFSET;
    }

    return cstring_hash_fnv1a_buf(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_fnv1a_mbs(
    char const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_FNV1A_OFFSET;
    }

    return cstring_hash_fnv1a_mbuf(s, strlen(s));
}

cstring_hash_t
cstring_hash_fnv1a_wcs(
    wchar_t const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_FNV1A_OFFSET;
    }

    return cstring_hash_fnv1a_wbuf(s, wcslen(s));
}

cstring_hash_t
cstring_hash_fnv1a_buf(
    cstring_char_t const*   s
,   size_t                  cch
)
{
#ifdef CSTRING_USE_WIDE_STRINGS

    return cstring_hash_fnv1a_wbuf(s, cch);
#else /* ? CSTRING_USE_WIDE_STRINGS */

    return cstring_hash_fnv1a_mbuf(s, cch);
#endif /* CSTRING_USE_WIDE_STRINGS */
}

cstring_hash_t
cstring_hash_fnv1a_mbuf(
    char const* s
,   size_t      cch
)
{
    cstring_hash_t hash = CSTRING_HASH_FNV1A_OFFSET;

    if (NULL != s)
    {
        unsigned char const* p = (unsigned char const*)s;
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_fnv1a_step_(hash, p[i]);
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_fnv1a_wbuf(
    wchar_t const*  s
,   size_t          cch
)
{
    cstring_hash_t hash = CSTRING_HASH_FNV1A_OFFSET;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_fnv1a_step_(hash, (uint8_t)s[i]);
        }
    }

    return hash;
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

    return cstring_hash_fnv1a_buf_case(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_fnv1a_mbs_case(
    char const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_FNV1A_OFFSET;
    }

    return cstring_hash_fnv1a_mbuf_case(s, strlen(s));
}

cstring_hash_t
cstring_hash_fnv1a_wcs_case(
    wchar_t const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_FNV1A_OFFSET;
    }

    return cstring_hash_fnv1a_wbuf_case(s, wcslen(s));
}

cstring_hash_t
cstring_hash_fnv1a_buf_case(
    cstring_char_t const*   s
,   size_t                  cch
)
{
#ifdef CSTRING_USE_WIDE_STRINGS

    return cstring_hash_fnv1a_wbuf_case(s, cch);
#else /* ? CSTRING_USE_WIDE_STRINGS */

    return cstring_hash_fnv1a_mbuf_case(s, cch);
#endif /* CSTRING_USE_WIDE_STRINGS */
}

cstring_hash_t
cstring_hash_fnv1a_mbuf_case(
    char const* s
,   size_t      cch
)
{
    cstring_hash_t hash = CSTRING_HASH_FNV1A_OFFSET;

    if (NULL != s)
    {
        unsigned char const* p = (unsigned char const*)s;
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_fnv1a_step_(hash, (uint8_t)tolower(p[i]));
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_fnv1a_wbuf_case(
    wchar_t const*  s
,   size_t          cch
)
{
    cstring_hash_t hash = CSTRING_HASH_FNV1A_OFFSET;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            uint8_t const octet = (uint8_t)(unsigned)towlower(s[i]);

            hash = cstring_hash_fnv1a_step_(hash, octet);
        }
    }

    return hash;
}


/* /////////////////////////////////////////////////////////////////////////
 * SDBM
 */

cstring_hash_t
cstring_hash_sdbm(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return CSTRING_HASH_SDBM_SEED;
    }

    return cstring_hash_sdbm_buf(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_sdbm_mbs(
    char const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_SDBM_SEED;
    }

    return cstring_hash_sdbm_mbuf(s, strlen(s));
}

cstring_hash_t
cstring_hash_sdbm_wcs(
    wchar_t const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_SDBM_SEED;
    }

    return cstring_hash_sdbm_wbuf(s, wcslen(s));
}

cstring_hash_t
cstring_hash_sdbm_buf(
    cstring_char_t const*   s
,   size_t                  cch
)
{
#ifdef CSTRING_USE_WIDE_STRINGS

    return cstring_hash_sdbm_wbuf(s, cch);
#else /* ? CSTRING_USE_WIDE_STRINGS */

    return cstring_hash_sdbm_mbuf(s, cch);
#endif /* CSTRING_USE_WIDE_STRINGS */
}

cstring_hash_t
cstring_hash_sdbm_mbuf(
    char const* s
,   size_t      cch
)
{
    cstring_hash_t hash = CSTRING_HASH_SDBM_SEED;

    if (NULL != s)
    {
        unsigned char const* p = (unsigned char const*)s;
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_sdbm_step_(hash, p[i]);
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_sdbm_wbuf(
    wchar_t const*  s
,   size_t          cch
)
{
    cstring_hash_t hash = CSTRING_HASH_SDBM_SEED;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_sdbm_step_(hash, (uint8_t)s[i]);
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_sdbm_case(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return CSTRING_HASH_SDBM_SEED;
    }

    return cstring_hash_sdbm_buf_case(pcs->ptr, pcs->len);
}

cstring_hash_t
cstring_hash_sdbm_mbs_case(
    char const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_SDBM_SEED;
    }

    return cstring_hash_sdbm_mbuf_case(s, strlen(s));
}

cstring_hash_t
cstring_hash_sdbm_wcs_case(
    wchar_t const* s
)
{
    if (NULL == s)
    {
        return CSTRING_HASH_SDBM_SEED;
    }

    return cstring_hash_sdbm_wbuf_case(s, wcslen(s));
}

cstring_hash_t
cstring_hash_sdbm_buf_case(
    cstring_char_t const*   s
,   size_t                  cch
)
{
#ifdef CSTRING_USE_WIDE_STRINGS

    return cstring_hash_sdbm_wbuf_case(s, cch);
#else /* ? CSTRING_USE_WIDE_STRINGS */

    return cstring_hash_sdbm_mbuf_case(s, cch);
#endif /* CSTRING_USE_WIDE_STRINGS */
}

cstring_hash_t
cstring_hash_sdbm_mbuf_case(
    char const* s
,   size_t      cch
)
{
    cstring_hash_t hash = CSTRING_HASH_SDBM_SEED;

    if (NULL != s)
    {
        unsigned char const* p = (unsigned char const*)s;
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash = cstring_hash_sdbm_step_(hash, (uint8_t)tolower(p[i]));
        }
    }

    return hash;
}

cstring_hash_t
cstring_hash_sdbm_wbuf_case(
    wchar_t const*  s
,   size_t          cch
)
{
    cstring_hash_t hash = CSTRING_HASH_SDBM_SEED;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            uint8_t const octet = (uint8_t)(unsigned)towlower(s[i]);

            hash = cstring_hash_sdbm_step_(hash, octet);
        }
    }

    return hash;
}


/* ///////////////////////////// end of file //////////////////////////// */

