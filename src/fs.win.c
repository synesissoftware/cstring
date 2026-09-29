
#include <cstring/cstring.h>
#include "internal.h"

#include <windows.h>


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
        WIN32_FILE_ATTRIBUTE_DATAA fi;

        if (GetFileAttributesExA(name, GetFileExInfoStandard, &fi))
        {
            if (0 == (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                ULARGE_INTEGER size;

                size.HighPart   =   fileInfo.nFileSizeHigh;
                size.LowPart    =   fileInfo.nFileSizeLow;

                *pFileSize      =   size.QuadPart;

                return 1;
            }
        }

        *pFileSize = 0;

        return 0;
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

