/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/hash/lose_lose.c
 *
 * Purpose: Degenerate lose-lose hash (Kernighan; Partow's LoseLose). This
 *          translation unit is separate so the timed calls stay opaque to
 *          the C++ driver, as the cstring hash functions are.
 *
 * Created: 6th October 2026
 * Updated: 6th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include "lose_lose.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>


/* /////////////////////////////////////////////////////////////////////////
 * lose-lose
 *
 * NUL-terminated forms measure the length once, then add. djb2 and FNV-1a
 * do that too, so the ratio compares the mix: addition against
 * hash*33+octet and against the FNV-1a xor-multiply. The published LoseLose
 * loop that calls strlen on every step is not used here.
 */

cstring_hash_t
lose_lose_mbuf(
    char const* s
,   size_t      cch
)
{
    cstring_hash_t hash = 0;

    if (NULL != s)
    {
        unsigned char const* p = (unsigned char const*)s;
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash += p[i];
        }
    }

    return hash;
}

cstring_hash_t
lose_lose_mbuf_case(
    char const* s
,   size_t      cch
)
{
    cstring_hash_t hash = 0;

    if (NULL != s)
    {
        unsigned char const* p = (unsigned char const*)s;
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash += (uint8_t)tolower(p[i]);
        }
    }

    return hash;
}

cstring_hash_t
lose_lose_wbuf(
    wchar_t const*  s
,   size_t          cch
)
{
    cstring_hash_t hash = 0;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            hash += (uint8_t)s[i];
        }
    }

    return hash;
}

cstring_hash_t
lose_lose_wbuf_case(
    wchar_t const*  s
,   size_t          cch
)
{
    cstring_hash_t hash = 0;

    if (NULL != s)
    {
        size_t i;

        for (i = 0; i != cch; ++i)
        {
            uint8_t const octet = (uint8_t)(unsigned)towlower(s[i]);

            hash += octet;
        }
    }

    return hash;
}

cstring_hash_t
lose_lose_mbs(
    char const* s
)
{
    if (NULL == s)
    {
        return 0;
    }

    return lose_lose_mbuf(s, strlen(s));
}

cstring_hash_t
lose_lose_mbs_case(
    char const* s
)
{
    if (NULL == s)
    {
        return 0;
    }

    return lose_lose_mbuf_case(s, strlen(s));
}

cstring_hash_t
lose_lose_wcs(
    wchar_t const* s
)
{
    if (NULL == s)
    {
        return 0;
    }

    return lose_lose_wbuf(s, wcslen(s));
}

cstring_hash_t
lose_lose_wcs_case(
    wchar_t const* s
)
{
    if (NULL == s)
    {
        return 0;
    }

    return lose_lose_wbuf_case(s, wcslen(s));
}

cstring_hash_t
lose_lose_cstring(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return 0;
    }

#ifdef CSTRING_USE_WIDE_STRINGS

    return lose_lose_wbuf(pcs->ptr, pcs->len);
#else /* ? CSTRING_USE_WIDE_STRINGS */

    return lose_lose_mbuf(pcs->ptr, pcs->len);
#endif /* CSTRING_USE_WIDE_STRINGS */
}

cstring_hash_t
lose_lose_cstring_case(
    struct cstring_t const* pcs
)
{
    if (NULL == pcs)
    {
        return 0;
    }

#ifdef CSTRING_USE_WIDE_STRINGS

    return lose_lose_wbuf_case(pcs->ptr, pcs->len);
#else /* ? CSTRING_USE_WIDE_STRINGS */

    return lose_lose_mbuf_case(pcs->ptr, pcs->len);
#endif /* CSTRING_USE_WIDE_STRINGS */
}


/* ///////////////////////////// end of file //////////////////////////// */

