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

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * lose-lose
 *
 * NUL-terminated forms measure the length once, then add. djb2, FNV-1a, and
 * SDBM do that too, so the ratio compares the mix: addition against
 * hash*33+octet, the FNV-1a xor-multiply, and hash*65599+octet. The
 * published LoseLose loop that calls strlen on every step is not used here.
 * Wide forms add every octet of each wchar_t, low byte first. Case forms
 * map ASCII A-Z to a-z before those octets are taken.
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

static uint8_t
lose_lose_ascii_fold_octet_(uint8_t octet)
{
    if (octet >= (uint8_t)'A' && octet <= (uint8_t)'Z')
    {
        octet = (uint8_t)(octet + 0x20u);
    }

    return octet;
}

static wchar_t
lose_lose_ascii_fold_wchar_(wchar_t unit)
{
    if (unit >= L'A' && unit <= L'Z')
    {
        unit = (wchar_t)(unit + 0x20);
    }

    return unit;
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
            hash += lose_lose_ascii_fold_octet_(p[i]);
        }
    }

    return hash;
}

static cstring_hash_t
lose_lose_wchar_octets_(
    cstring_hash_t  hash
,   wchar_t         unit
)
{
    cstring_hash_t  bits = (cstring_hash_t)unit;
    size_t          b;

    for (b = 0; b != sizeof(wchar_t); ++b)
    {
        hash += (uint8_t)(bits & 0xffu);
        bits >>= 8;
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
            hash = lose_lose_wchar_octets_(hash, s[i]);
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
            hash = lose_lose_wchar_octets_(hash, lose_lose_ascii_fold_wchar_(s[i]));
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

