
#include <cstring/cstring.h>
#include "internal.h"

#include <errno.h>
#include <sys/stat.h>


CSTRING_EXTERN_C
int
cstring_try_get_regular_file_size_m_(
    char const*         name
,   cstring_uint64_t*   pFileSize
)
{
    CSTRING_ASSERT(NULL != name);
    CSTRING_ASSERT(NULL != pFileSize);

    {
        struct stat st;
        int const   r1  =   stat(name, &st);

        if (0 == r1)
        {
            if (S_ISREG(st.st_mode))
            {
                *pFileSize = st.st_size;

                return 1;
            }
        }

        *pFileSize = 0;

        return 0;
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

