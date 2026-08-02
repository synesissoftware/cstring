# cstring <!-- omit in toc -->

**C**-style **string**s is a small, standalone library, that provides extensible C-style string instances and extensible arrays of such, for Unix and Windows.


![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![GitHub release](https://img.shields.io/github/v/release/synesissoftware/cstring.svg)](https://github.com/synesissoftware/cstring/releases/latest)
[![Last Commit](https://img.shields.io/github/last-commit/synesissoftware/cstring)](https://github.com/synesissoftware/cstring/commits/master)
[![CMake on multiple platforms](https://github.com/synesissoftware/cstring/actions/workflows/ci.yml/badge.svg)](https://github.com/synesissoftware/cstring/actions/workflows/ci.yml)



## Table of Contents <!-- omit in toc -->

- [Installation](#installation)
- [Components](#components)
  - [API / core library](#api--core-library)
- [Examples](#examples)
- [Project Information](#project-information)
  - [Where to get help](#where-to-get-help)
  - [Contribution guidelines](#contribution-guidelines)
  - [Dependencies](#dependencies)
  - [Related projects](#related-projects)
  - [License](#license)


## Installation

Detailed instructions - via **CMake**, via bundling - are provided in the accompanying [INSTALL.md](./INSTALL.md) file.


## Components


### API / core library

The C API is based around two structures:
* `cstring_t`, which represents a resizeable string instance; and
  ```C
  struct cstring_t
  {
    size_t          len;        /*!< Number of characters.                              */
    cstring_char_t* ptr;        /*!< Pointer to the string. If capacity is 0, the value
                                     of this member is undetermined.                    */
    size_t          capacity;   /*!< Number of bytes available.                         */
    cstring_flags_t flags;      /*!< Flags. This field belongs to the implementation,
                                     and must not be modified by any application code.  */
  };
  ```
* `cstring_vector_t`, which represents a sequence of `cstring_t` instances;
  ```C
  struct cstring_vector_t
  {
    size_t          len;        /*!< Number of strings.                                 */
    cstring_t*      ptr;        /*!< Pointer to the first string. If capacity is 0, the
                                     value of this member is undetermined.              */
    size_t          capacity;   /*!< Number of instances available.                     */
    cstring_flags_t flags;      /*!< Flags. This field belongs to the implementation,
                                     and must not be modified by any application code.  */
  };
  ```


**Creation/destruction functions**:

* `cstring_init()` - initialises an instance to default values (and does not required a following call to `cstring_destroy()`);
* `cstring_create()` - creates an instance from a C-style string;
* `cstring_createLen()` - creates an instance from a (portion of a) C-style string;
* `cstring_createN()` - creates an instance from a a number of repetitions of a `char` value;
* `cstring_createEx()` - creates an instance with special characteristics (such as using stack memory, ...);
* `cstring_createExLen()` - creates an instance with special characteristics (such as using stack memory, ...);
* `cstring_destroy()`

**Modification functions**:

* `cstring_assign()` - T.B.C.;
* `cstring_assignLen()` - T.B.C.;
* `cstring_copy()` - T.B.C.;
* `cstring_append()` - T.B.C.;
* `cstring_appendLen()` - T.B.C.;
* `cstring_insert()` - T.B.C.;
* `cstring_insertLen()` - T.B.C.;
* `cstring_replace()` - T.B.C.;
* `cstring_replaceLen()` - T.B.C.;
* `cstring_replaceAll()` - T.B.C.;
* `cstring_truncate()` - T.B.C.;
* `cstring_swap()` - T.B.C.;

**File functions**:

* `cstring_readline()` - reads in a line of text from the given text stream;
* `cstring_write()` - writes a string to the given text stream;
* `cstring_writeline()` - writes a line of text to the given text stream;


## Examples

Examples live under **examples/** (`c/` and `cpp/`), each with a short **README.md**. Build them with `BUILD_EXAMPLES` (on by default); run via **run_all_examples.sh**.

| Example | Language | Notes |
| ------- | -------- | ----- |
| [**example.c.auto_buffer**](./examples/c/example.c.auto_buffer/) | C | Borrowed buffer that may grow to the heap |
| [**example.c.cstring**](./examples/c/example.c.cstring/) | C | Core `cstring_t` create / assign / append / truncate / copy / swap |
| [**example.c.cstring_create**](./examples/c/example.c.cstring_create/) | C | Minimal `cstring_create()` |
| [**example.c.cstring_vector**](./examples/c/example.c.cstring_vector/) | C | Read lines into `cstring_vector_t` and sort (requires input path or `--`) |
| [**example.cpp.cstring.dynload**](./examples/cpp/example.cpp.cstring.dynload/) | C++ | Windows-only dynamic load of the cstring DLL |
| [**example.cpp.HGLOBAL_on_x64**](./examples/cpp/example.cpp.HGLOBAL_on_x64/) | C++ | Windows-only `CSTRING_F_USE_WIN32_GLOBAL_MEMORY` |


## Project Information


### Where to get help

[GitHub Page](https://github.com/synesissoftware/cstring "GitHub Page")


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/cstring.


### Dependencies

The **C** API has no non-standard dependencies.

| Dependency | Role | Required? |
| ---------- | ---- | --------- |
| [**STLSoft**](https://github.com/synesissoftware/STLSoft) 1.11 | Test headers / remaining C++ tests and examples | ⚪ Tests only (`BUILD_TESTING`) |
| [**xTests**](https://github.com/synesissoftware/xTests) (≥ 0.26) | Unit / component / scratch tests | ⚪ Tests only (`BUILD_TESTING`) |
| [**shwild**](https://github.com/synesissoftware/shwild) | Enhanced pattern-match assertions in **xTests** | ⚪ Optional; tests only (unless `NO_SHWILD` / `--no-shwild`) |

When supplying `'--no-cpp'` to **prepare_cmake.sh** — sets the CMake option `NO_CSTRING_CPP_API=ON` — C++ examples and remaining C++ tests are omitted; the **C** unit-tests still require **STLSoft** and **xTests**.

When supplying `'--no-shwild'` — sets `NO_SHWILD=ON` — **shwild** is not recognised and pattern-match assertions are compiled out; other unit-tests still run.


### Related projects

Projects in which **cstring** is used include:

* [**shwild.fnmatch**](https://github.com/synesissoftware/shwild.fnmatch)


### License

**cstring** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->

