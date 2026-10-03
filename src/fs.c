
#include <cstring/cstring.h>
#include "internal.h"


/* /////////////////////////////////////////////////////////////////////////
 * portability
 */

/* Seek/tell discrimination (widest practical portability):
 *
 * 1. MSVC 2005+ (and toolchains advertising that CRT) — 64-bit;
 * 2. MinGW — fseeko64 / ftello64;
 * 3. Older MSVC (incl. VC6) — long fseek / ftell;
 * 4. UNIX / POSIX — fseeko / ftello (64-bit when LFS is enabled);
 * 5. Otherwise — ISO long fseek / ftell.
 */

#if 0
#elif 1 &&\
      defined(_MSC_VER) &&\
      _MSC_VER >= 1400 &&\
      1

# define CSTRING_STREAM_SEEK_(stm, off, whence)             _fseeki64((stm), (off), (whence))
# define CSTRING_STREAM_TELL_(stm)                          _ftelli64(stm)
#elif 0 ||\
      defined(__MINGW32__) ||\
      defined(__MINGW64__) ||\
      0

# define CSTRING_STREAM_SEEK_(stm, off, whence)             fseeko64((stm), (off64_t)(off), (whence))
# define CSTRING_STREAM_TELL_(stm)                          ftello64(stm)
#elif defined(_MSC_VER)

# define CSTRING_STREAM_SEEK_(stm, off, whence)             fseek((stm), (long)(off), (whence))
# define CSTRING_STREAM_TELL_(stm)                          ftell(stm)
#elif 0 ||\
      defined(__APPLE__) ||\
      defined(__linux__) ||\
      defined(__unix__) ||\
      defined(unix) ||\
      defined(UNIX) ||\
      0

# define CSTRING_STREAM_SEEK_(stm, off, whence)             fseeko((stm), (off_t)(off), (whence))
# define CSTRING_STREAM_TELL_(stm)                          ftello(stm)
#else

# define CSTRING_STREAM_SEEK_(stm, off, whence)             fseek((stm), (long)(off), (whence))
# define CSTRING_STREAM_TELL_(stm)                          ftell(stm)
#endif


/* /////////////////////////////////////////////////////////////////////////
 * internal API functions
 */

CSTRING_EXTERN_C
int
cstring_stream_try_get_size_(
    FILE*               stm
,   cstring_uint64_t*   pFileSize
)
{
    CSTRING_ASSERT(NULL != stm);
    CSTRING_ASSERT(NULL != pFileSize);

    {
        cstring_int64_t const   pos =   (cstring_int64_t)CSTRING_STREAM_TELL_(stm);

        if (pos < 0)
        {
            *pFileSize = 0;

            return 0;
        }
        else
        {
            if (0 != CSTRING_STREAM_SEEK_(stm, 0, SEEK_END))
            {
                (void)CSTRING_STREAM_SEEK_(stm, pos, SEEK_SET);

                *pFileSize = 0;

                return 0;
            }
            else
            {
                cstring_int64_t const   end =   (cstring_int64_t)CSTRING_STREAM_TELL_(stm);
                int const               r   =   CSTRING_STREAM_SEEK_(stm, pos, SEEK_SET);

                if (0 != r ||
                    end < 0 ||
                    end < pos)
                {
                    *pFileSize = 0;

                    return 0;
                }
                else
                {
                    *pFileSize = (cstring_uint64_t)(end - pos);

                    return 1;
                }
            }
        }
    }
}


/* ///////////////////////////// end of file //////////////////////////// */
