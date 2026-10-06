/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/hash/lose_lose.h
 *
 * Purpose: Degenerate lose-lose hash used as the timing baseline.
 *
 * Created: 6th October 2026
 * Updated: 6th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#ifndef CSTRING_TEST_PERFORMANCE_HASH_LOSE_LOSE_H_INCLUDED
#define CSTRING_TEST_PERFORMANCE_HASH_LOSE_LOSE_H_INCLUDED


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>


/* /////////////////////////////////////////////////////////////////////////
 * API
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Each function walks the same octets as the matching cstring hash entry
 * point. The mix is addition only. Case forms fold, then add the low 8
 * bits. Wide forms add the low 8 bits of each code unit. NULL yields 0.
 */

cstring_hash_t
lose_lose_cstring(
    struct cstring_t const* pcs
);

cstring_hash_t
lose_lose_cstring_case(
    struct cstring_t const* pcs
);

cstring_hash_t
lose_lose_mbs(
    char const* s
);

cstring_hash_t
lose_lose_mbs_case(
    char const* s
);

cstring_hash_t
lose_lose_mbuf(
    char const* s
,   size_t      cch
);

cstring_hash_t
lose_lose_mbuf_case(
    char const* s
,   size_t      cch
);

cstring_hash_t
lose_lose_wcs(
    wchar_t const* s
);

cstring_hash_t
lose_lose_wcs_case(
    wchar_t const* s
);

cstring_hash_t
lose_lose_wbuf(
    wchar_t const*  s
,   size_t          cch
);

cstring_hash_t
lose_lose_wbuf_case(
    wchar_t const*  s
,   size_t          cch
);


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#endif /* !CSTRING_TEST_PERFORMANCE_HASH_LOSE_LOSE_H_INCLUDED */


/* ///////////////////////////// end of file //////////////////////////// */

