/* /////////////////////////////////////////////////////////////////////////
 * File:    test/cstring_testing.h
 *
 * Purpose: Character-width helpers for tests that must compile when
 *          cstring_char_t is char or wchar_t.
 *
 * Created: 4th October 2026
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#ifndef CSTRING_INCL_TEST_H_CSTRING_TESTING
#define CSTRING_INCL_TEST_H_CSTRING_TESTING

#include <cstring/cstring.h>
#include "cstring.helpers.h"


/* /////////////////////////////////////////////////////////////////////////
 * C / C++ assertion and search aliases
 */

#ifdef CSTRING_USE_WIDE_STRINGS

# define TEST_STR_EQ_                                       TEST_WS_EQ
# define TEST_STR_EQ_N_                                     TEST_WS_EQ_N
# define cstring_testing_strlen_                            wcslen
# define cstring_testing_strpbrk_                           wcspbrk
#else /* ? CSTRING_USE_WIDE_STRINGS */

# define TEST_STR_EQ_                                       TEST_MS_EQ
# define TEST_STR_EQ_N_                                     TEST_MS_EQ_N
# define cstring_testing_strlen_                            strlen
# define cstring_testing_strpbrk_                           strpbrk
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * C++ : compare a multibyte expectation with a cstring result
 */

#ifdef __cplusplus

# include <string>

# ifdef CSTRING_USE_WIDE_STRINGS

inline
std::wstring
cstring_testing_widen_(
    char const* mb
)
{
    std::wstring w;

    if (NULL != mb)
    {
        for (; '\0' != *mb; ++mb)
        {
            w.push_back(static_cast<cstring_char_t>(static_cast<unsigned char>(*mb)));
        }
    }

    return w;
}

#  define TEST_MB_EQ_(mb, actual)                           TEST_WS_EQ(cstring_testing_widen_(mb).c_str(), (actual))

inline
CSTRING_RC
cstring_testing_createEx_mb_(
    cstring_t*      pcs
,   char const*     mb
,   int             flags
,   void*           arena
,   size_t          capacity
)
{
    std::wstring const w = cstring_testing_widen_(mb);

    return cstring_createEx(pcs, w.c_str(), flags, arena, capacity);
}

# else /* ? CSTRING_USE_WIDE_STRINGS */

#  define TEST_MB_EQ_(mb, actual)                           TEST_MS_EQ((mb), (actual))

inline
CSTRING_RC
cstring_testing_createEx_mb_(
    cstring_t*      pcs
,   char const*     mb
,   int             flags
,   void*           arena
,   size_t          capacity
)
{
    return cstring_createEx(pcs, mb, flags, arena, capacity);
}

# endif /* CSTRING_USE_WIDE_STRINGS */
#endif /* __cplusplus */


#endif /* CSTRING_INCL_TEST_H_CSTRING_TESTING */


/* ///////////////////////////// end of file //////////////////////////// */

