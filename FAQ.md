# cstring - FAQ <!-- omit in toc -->

The FAQ list is under (constant) development. If you post a question on the
Issues forum (https://github.com/synesissoftware/cstring/issues)
it will be used to create one.


## Table of Contents <!-- omit in toc -->

- [Q1: "How do I build cstring?"](#q1-how-do-i-build-cstring)
- [Q2: "How do I install cstring?"](#q2-how-do-i-install-cstring)
- [Q3: "How do I use cstring?"](#q3-how-do-i-use-cstring)
- [Q4: "Does cstring have its own unit-tests?"](#q4-does-cstring-have-its-own-unit-tests)
- [Q5: "How do I build without the C++ examples and tests?"](#q5-how-do-i-build-without-the-c-examples-and-tests)
- [Q6: "Where are the examples?"](#q6-where-are-the-examples)


# FAQs: <!-- omit in toc -->


## Q1: "How do I build cstring?"

See [INSTALL.md](./INSTALL.md) for the recommended **CMake** flow
(**prepare_cmake.sh**, then **build_cmake.sh**).

For a minimal library install with no external dependencies:

```bash
$ ./prepare_cmake.sh --no-cpp --disable-testing -m
```

For a full build including examples and tests, install **STLSoft** 1.11 and
**xTests** first, then:

```bash
$ ./prepare_cmake.sh -m
```

Execute `$ ./prepare_cmake.sh --help` for the full set of options.


## Q2: "How do I install cstring?"

See [INSTALL.md](./INSTALL.md) for details of how to install **cstring**.


## Q3: "How do I use cstring?"

Include **cstring/cstring.h** (and **cstring/cstring.vector.h** where needed)
and link against **libcstring** (the **CMake** target is `cstring::core`).
Create and destroy instances with `cstring_create()` / `cstring_destroy()`,
and mutate with `cstring_assign()`, `cstring_append()`, and related APIs.

A minimal sketch:

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
        return EXIT_FAILURE;
    }

    printf("%s\n", cs.ptr);

    cstring_destroy(&cs);

    return EXIT_SUCCESS;
}
```

See [INSTALL.md](./INSTALL.md) and the examples under **examples/**.


## Q4: "Does cstring have its own unit-tests?"

Yes. Automated tests live under:

* **./test/unit** — unit tests;
* **./test/component** — component tests;
* **./test/scratch** — scratch / exploratory programs (for example **libver**);

When testing is enabled, build them via **prepare_cmake.sh** / **build_cmake.sh**
and run with **run_all_unit_tests.sh** (and **CTest** where configured). Tests
require **STLSoft** and **xTests** (and may optionally recognise **shwild**).


## Q5: "How do I build without the C++ examples and tests?"

Pass `--no-cpp` (or `-C`) to **prepare_cmake.sh**, which sets CMake
`NO_CSTRING_CPP_API=ON`. That omits C++ examples and remaining C++ tests.

The **C** unit-tests still require **STLSoft** and **xTests** unless you also
pass `--disable-testing` / `-T`.


## Q6: "Where are the examples?"

Examples live under **examples/** (`c/` and `cpp/`), each with a short
**README.md**. They are built when `BUILD_EXAMPLES` is on (the default); omit
them with `--disable-examples` / `-E`. Run built examples via
**run_all_examples.sh**. See the examples table in [README.md](./README.md).


<!-- ########################### end of file ########################### -->
