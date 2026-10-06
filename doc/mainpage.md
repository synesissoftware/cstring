# cstring {#mainpage}

**cstring** is a small, standalone library that provides extensible C-style
string instances and extensible arrays of such, for Unix and Windows.


## Components

| Module | Header | Summary |
| ------ | ------ | ------- |
| @ref group__cstring_api | `<cstring/cstring.h>` | Core `cstring_t` API (create, mutate, stream I/O, status codes) |
| @ref group__cstring_api__hashing | `<cstring/hash.h>` | djb2, FNV-1a, and SDBM hashes of `cstring_t`, C strings, and buffers |
| @ref group__cstring_api__hashing__djb2 | `<cstring/hash.h>` | djb2 (seed `5381`); instance, C string, and buffer forms |
| @ref group__cstring_api__hashing__fnv1a | `<cstring/hash.h>` | FNV-1a 64-bit; the same forms as djb2 |
| @ref group__cstring_api__hashing__sdbm | `<cstring/hash.h>` | SDBM (seed `0`, multiplier `65599`); the same forms as djb2 |
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

Projects that call the **cstring** API, or that require the **CMake** package `cstring`:

| Project | Use |
| ------- | --- |
| [errni](https://github.com/sistools/errni) | Builds each result line and writes it with `cstring_writeline()` |
| [lnunique](https://github.com/sistools/lnunique) | Requires `cstring` 4.0 and links `cstring::core` for line strings |
| [rstrip](https://github.com/sistools/rstrip) | Accumulates each output line and writes it with `cstring_write()` |
| [shwild.fnmatch](https://github.com/synesissoftware/shwild.fnmatch) | Holds patterns and subject strings as `cstring_t` |
| [STLSoft](https://github.com/synesissoftware/STLSoft) | Optional; the C unit test `output_debug_line.C` uses `cstring_t` when the package is found |


<!-- ########################### end of file ########################### -->
