# cstring {#mainpage}

**cstring** is a small, standalone library that provides extensible C-style
string instances and extensible arrays of such, for Unix and Windows.


## Components

| Module | Header | Summary |
| ------ | ------ | ------- |
| @ref group__cstring_api | `<cstring/cstring.h>` | Core `cstring_t` API (create, mutate, stream I/O, status codes) |
| @ref group__cstring_api__flags | `<cstring/cstring.h>` | Memory-arena and capacity control flags |
| Vector API | `<cstring/cstring.vector.h>` | `cstring_vector_t` sequences of `cstring_t` |


## Quick start

```c
#include <cstring/cstring.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    cstring_t cs;
    CSTRING_RC rc = cstring_create(&cs, "Hello");

    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "%s\n", cstring_getStatusCodeString(rc));

        return EXIT_FAILURE;
    }

    printf("len=%zu contents='%s'\n", cs.len, cs.ptr);

    cstring_destroy(&cs);

    return EXIT_SUCCESS;
}
```

Consumer **CMake** projects may use `find_package(cstring)` and link
`cstring::core`. See
[INSTALL.md](https://github.com/synesissoftware/cstring/blob/master/INSTALL.md)
for build and install instructions.


## Related projects

* [shwild.fnmatch](https://github.com/synesissoftware/shwild.fnmatch)


<!-- ########################### end of file ########################### -->
