/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring/hash.h
 *
 * Purpose: Definition of the cstring hash API.
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


/** \file cstring/hash.h Definition of the cstring hash API
 */

#ifndef CSTRING_INCL_CSTRING_H_HASH
#define CSTRING_INCL_CSTRING_H_HASH


/* /////////////////////////////////////////////////////////////////////////
 * version
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# define CSTRING_VER_CSTRING_H_HASH_MAJOR       1
# define CSTRING_VER_CSTRING_H_HASH_MINOR       0
# define CSTRING_VER_CSTRING_H_HASH_REVISION    1
# define CSTRING_VER_CSTRING_H_HASH_EDIT        1
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/common.h>

/* cstring/cstring.h includes this header once cstring_t is defined.
 * Including this header directly includes cstring/cstring.h when that
 * include is not already in progress.
 */

#ifndef CSTRING_INCL_CSTRING_H_CSTRING
# include <cstring/cstring.h>
#endif /* !CSTRING_INCL_CSTRING_H_CSTRING */


/* /////////////////////////////////////////////////////////////////////////
 * hash types and constants
 */

/** \defgroup group__cstring_api__hashing Hashing Functions
 * \ingroup group__cstring_api
 * \brief Hash functions for cstring instances, C strings, and buffers.
 *
 * djb2 (\c CSTRING_HASH_DJB2_SEED) and FNV-1a
 * (\c CSTRING_HASH_FNV1A_OFFSET, \c CSTRING_HASH_FNV1A_PRIME) are 64-bit.
 * \c _mbs and \c _mbuf take multibyte \c char strings. \c _wcs and \c _wbuf
 * take \c wchar_t strings. Both pairs exist in every build. \c _buf takes
 * the ambient \c cstring_char_t and calls \c _mbuf or \c _wbuf.
 *
 * Nul-terminated forms stop at the first nul. Buffer forms hash exactly
 * \c cch code units, including embedded nuls. Each code unit contributes
 * its low 8 bits, so ASCII text has one hash in both encodings. NULL, or a
 * zero length, yields that algorithm's empty-input value. Case-insensitive
 * forms fold with \c tolower or \c towlower, which follow the process
 * locale, and then take the low 8 bits.
 *
 * In C++, \c hash_djb2(), \c hash_djb2_case(), \c hash_fnv1a(), and
 * \c hash_fnv1a_case() overload on \c cstring_t (pointer and reference),
 * \c char const*, \c wchar_t const*, and both buffer forms. NULL is
 * ambiguous between \c char const* and \c wchar_t const* and must be cast.
 * @{
 */

/** \brief Hash value type
 * \ingroup group__cstring_api__hashing
 */
#if 0
#elif defined(CSTRING_HAS_h_stdint_) ||\
      defined(CSTRING_DOCUMENTATION_SKIP_SECTION)

typedef uint64_t                                            cstring_hash_t;
#elif defined(_MSC_VER)

typedef unsigned __int64_t                                  cstring_hash_t;
#else

# error 64-bit unsigned integer type not discriminated
#endif

/** \def CSTRING_HASH_DJB2_SEED
 * \ingroup group__cstring_api__hashing
 * \brief djb2 initial seed (also the hash of an empty input)
 *
 * Daniel J. Bernstein's djb2, as published by Ozan Yigit.
 * \sa http://www.cse.yorku.ca/~oz/hash.html#djb2
 */
#define CSTRING_HASH_DJB2_SEED                              5381ULL

/** \def CSTRING_HASH_FNV1A_OFFSET
 * \ingroup group__cstring_api__hashing
 * \brief FNV-1a 64-bit offset basis (also the hash of an empty input)
 *
 * FNV-1a offset basis published by Fowler, Noll, and Vo, and in RFC 9923.
 * \sa https://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a
 * \sa https://www.isthe.com/chongo/tech/comp/fnv/#FNV-param
 * \sa https://www.rfc-editor.org/rfc/rfc9923.html#section-2.2
 * \sa https://www.rfc-editor.org/rfc/rfc9923.html#section-5
 */
#define CSTRING_HASH_FNV1A_OFFSET                           0xcbf29ce484222325ULL

/** \def CSTRING_HASH_FNV1A_PRIME
 * \ingroup group__cstring_api__hashing
 * \brief FNV-1a 64-bit prime
 *
 * FNV-1a prime published by Fowler, Noll, and Vo, and in RFC 9923.
 * \sa https://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a
 * \sa https://www.isthe.com/chongo/tech/comp/fnv/#FNV-param
 * \sa https://www.isthe.com/chongo/tech/comp/fnv/#fnv-prime
 * \sa https://www.rfc-editor.org/rfc/rfc9923.html#section-2.1
 * \sa https://www.rfc-editor.org/rfc/rfc9923.html#section-5
 */
#define CSTRING_HASH_FNV1A_PRIME                            0x100000001b3ULL


/* /////////////////////////////////////////////////////////////////////////
 * djb2
 */

/** \brief Computes a 64-bit djb2 hash of a cstring instance.
 *
 * \param pcs The cstring instance. May be NULL;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2(
    struct cstring_t const* pcs
);

/** \brief Computes a 64-bit djb2 hash of a nul-terminated multibyte string.
 *
 * \param s The multibyte string. May be NULL;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_mbs(
    char const* s
);

/** \brief Computes a 64-bit djb2 hash of a nul-terminated wide string.
 *
 * \param s The wide string. May be NULL;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_wcs(
    wchar_t const* s
);

/** \brief Computes a 64-bit djb2 hash of an ambient character buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_buf(
    cstring_char_t const*   s
,   size_t                  cch
);

/** \brief Computes a 64-bit djb2 hash of a multibyte character buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_mbuf(
    char const* s
,   size_t      cch
);

/** \brief Computes a 64-bit djb2 hash of a wide-character buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_wbuf(
    wchar_t const*  s
,   size_t          cch
);

/** \brief Computes a case-insensitive 64-bit djb2 hash of a cstring.
 *
 * \param pcs The cstring instance. May be NULL;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_case(
    struct cstring_t const* pcs
);

/** \brief Computes a case-insensitive 64-bit djb2 hash of a multibyte
 *   string.
 *
 * \param s The multibyte string. May be NULL;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_mbs_case(
    char const* s
);

/** \brief Computes a case-insensitive 64-bit djb2 hash of a wide string.
 *
 * \param s The wide string. May be NULL;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_wcs_case(
    wchar_t const* s
);

/** \brief Computes a case-insensitive 64-bit djb2 hash of an ambient
 *   character buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_buf_case(
    cstring_char_t const*   s
,   size_t                  cch
);

/** \brief Computes a case-insensitive 64-bit djb2 hash of a multibyte
 *   buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_mbuf_case(
    char const* s
,   size_t      cch
);

/** \brief Computes a case-insensitive 64-bit djb2 hash of a wide buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit djb2 hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_djb2_wbuf_case(
    wchar_t const*  s
,   size_t          cch
);


/* /////////////////////////////////////////////////////////////////////////
 * FNV-1a
 */

/** \brief Computes a 64-bit FNV-1a hash of a cstring instance.
 *
 * \param pcs The cstring instance. May be NULL;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a(
    struct cstring_t const* pcs
);

/** \brief Computes a 64-bit FNV-1a hash of a nul-terminated multibyte
 *   string.
 *
 * \param s The multibyte string. May be NULL;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_mbs(
    char const* s
);

/** \brief Computes a 64-bit FNV-1a hash of a nul-terminated wide string.
 *
 * \param s The wide string. May be NULL;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_wcs(
    wchar_t const* s
);

/** \brief Computes a 64-bit FNV-1a hash of an ambient character buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_buf(
    cstring_char_t const*   s
,   size_t                  cch
);

/** \brief Computes a 64-bit FNV-1a hash of a multibyte character buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_mbuf(
    char const* s
,   size_t      cch
);

/** \brief Computes a 64-bit FNV-1a hash of a wide-character buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_wbuf(
    wchar_t const*  s
,   size_t          cch
);

/** \brief Computes a case-insensitive 64-bit FNV-1a hash of a cstring.
 *
 * \param pcs The cstring instance. May be NULL;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_case(
    struct cstring_t const* pcs
);

/** \brief Computes a case-insensitive 64-bit FNV-1a hash of a multibyte
 *   string.
 *
 * \param s The multibyte string. May be NULL;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_mbs_case(
    char const* s
);

/** \brief Computes a case-insensitive 64-bit FNV-1a hash of a wide string.
 *
 * \param s The wide string. May be NULL;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_wcs_case(
    wchar_t const* s
);

/** \brief Computes a case-insensitive 64-bit FNV-1a hash of an ambient
 *   character buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_buf_case(
    cstring_char_t const*   s
,   size_t                  cch
);

/** \brief Computes a case-insensitive 64-bit FNV-1a hash of a multibyte
 *   buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_mbuf_case(
    char const* s
,   size_t      cch
);

/** \brief Computes a case-insensitive 64-bit FNV-1a hash of a wide buffer.
 *
 * \param s The buffer. May be NULL;
 * \param cch The number of code units, including embedded nuls;
 *
 * \return The 64-bit FNV-1a hash;
 */
CSTRING_EXTERN_C
cstring_hash_t
cstring_hash_fnv1a_wbuf_case(
    wchar_t const*  s
,   size_t          cch
);

/** @} */


/* /////////////////////////////////////////////////////////////////////////
 * compiler warnings
 */

#if defined(_MSC_VER) &&\
    _MSC_VER >= 1200
# pragma warning(push)
# pragma warning(disable : 4514) /* unreferenced inline function has been removed */
#endif /* compiler */


/* /////////////////////////////////////////////////////////////////////////
 * C++ hash access shims
 */

#ifdef __cplusplus

/* NULL is ambiguous between char const* and wchar_t const*. Cast it, for
 * example static_cast<char const*>(NULL).
 */

inline
cstring_hash_t
hash_djb2(
    struct cstring_t const* pcs
)
{
    return cstring_hash_djb2(pcs);
}

inline
cstring_hash_t
hash_djb2(
    struct cstring_t const& cs
)
{
    return cstring_hash_djb2(&cs);
}

inline
cstring_hash_t
hash_djb2(
    char const* s
)
{
    return cstring_hash_djb2_mbs(s);
}

inline
cstring_hash_t
hash_djb2(
    wchar_t const* s
)
{
    return cstring_hash_djb2_wcs(s);
}

inline
cstring_hash_t
hash_djb2(
    char const* s
,   size_t      cch
)
{
    return cstring_hash_djb2_mbuf(s, cch);
}

inline
cstring_hash_t
hash_djb2(
    wchar_t const*  s
,   size_t          cch
)
{
    return cstring_hash_djb2_wbuf(s, cch);
}

inline
cstring_hash_t
hash_djb2_case(
    struct cstring_t const* pcs
)
{
    return cstring_hash_djb2_case(pcs);
}

inline
cstring_hash_t
hash_djb2_case(
    struct cstring_t const& cs
)
{
    return cstring_hash_djb2_case(&cs);
}

inline
cstring_hash_t
hash_djb2_case(
    char const* s
)
{
    return cstring_hash_djb2_mbs_case(s);
}

inline
cstring_hash_t
hash_djb2_case(
    wchar_t const* s
)
{
    return cstring_hash_djb2_wcs_case(s);
}

inline
cstring_hash_t
hash_djb2_case(
    char const* s
,   size_t      cch
)
{
    return cstring_hash_djb2_mbuf_case(s, cch);
}

inline
cstring_hash_t
hash_djb2_case(
    wchar_t const*  s
,   size_t          cch
)
{
    return cstring_hash_djb2_wbuf_case(s, cch);
}

inline
cstring_hash_t
hash_fnv1a(
    struct cstring_t const* pcs
)
{
    return cstring_hash_fnv1a(pcs);
}

inline
cstring_hash_t
hash_fnv1a(
    struct cstring_t const& cs
)
{
    return cstring_hash_fnv1a(&cs);
}

inline
cstring_hash_t
hash_fnv1a(
    char const* s
)
{
    return cstring_hash_fnv1a_mbs(s);
}

inline
cstring_hash_t
hash_fnv1a(
    wchar_t const* s
)
{
    return cstring_hash_fnv1a_wcs(s);
}

inline
cstring_hash_t
hash_fnv1a(
    char const* s
,   size_t      cch
)
{
    return cstring_hash_fnv1a_mbuf(s, cch);
}

inline
cstring_hash_t
hash_fnv1a(
    wchar_t const*  s
,   size_t          cch
)
{
    return cstring_hash_fnv1a_wbuf(s, cch);
}

inline
cstring_hash_t
hash_fnv1a_case(
    struct cstring_t const* pcs
)
{
    return cstring_hash_fnv1a_case(pcs);
}

inline
cstring_hash_t
hash_fnv1a_case(
    struct cstring_t const& cs
)
{
    return cstring_hash_fnv1a_case(&cs);
}

inline
cstring_hash_t
hash_fnv1a_case(
    char const* s
)
{
    return cstring_hash_fnv1a_mbs_case(s);
}

inline
cstring_hash_t
hash_fnv1a_case(
    wchar_t const* s
)
{
    return cstring_hash_fnv1a_wcs_case(s);
}

inline
cstring_hash_t
hash_fnv1a_case(
    char const* s
,   size_t      cch
)
{
    return cstring_hash_fnv1a_mbuf_case(s, cch);
}

inline
cstring_hash_t
hash_fnv1a_case(
    wchar_t const*  s
,   size_t          cch
)
{
    return cstring_hash_fnv1a_wbuf_case(s, cch);
}

#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * compiler warnings
 */

#if defined(_MSC_VER) &&\
    _MSC_VER >= 1200
# pragma warning(pop)
#endif /* compiler */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* CSTRING_INCL_CSTRING_H_HASH */

/* ///////////////////////////// end of file //////////////////////////// */

