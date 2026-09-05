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
  - [Types](#types)
  - [String API](#string-api)
    - [Status and capacity](#status-and-capacity)
    - [Creation/destruction functions](#creationdestruction-functions)
    - [Modification functions\*\*](#modification-functions)
    - [File functions\*\*](#file-functions)
    - [Hashing functions](#hashing-functions)
  - [Vector API](#vector-api)
  - [C++ Integration](#c-integration)
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


### Types

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

Supporting scalar typedefs:
* `cstring_char_t` — character type (`char`, or `wchar_t` when `CSTRING_USE_WIDE_STRINGS` is defined);
* `cstring_flags_t` — bit flags controlling allocation and capacity semantics;
* `cstring_hash_t` — 64-bit unsigned integer type (`uint64_t`) representing hash values;


### String API

Defined in **cstring/cstring.h**:


#### Status and capacity

* `cstring_getStatusCodeString()` — returns a nul-terminated description of a `CSTRING_RC` code;
* `cstring_setCapacity()` — adjusts capacity (subject to fixed / borrowed / readonly rules);
* `cstring_yield2()` — yields ownership of the payload (and raw buffer) to the caller;

#### Creation/destruction functions

* `cstring_init()` — initialises an instance to default values (and does not require a following call to `cstring_destroy()`);
* `cstring_create()` — creates an instance from a C-style string;
* `cstring_createLen()` — creates an instance from a (portion of a) C-style string;
* `cstring_createN()` — creates an instance from a number of repetitions of a character value;
* `cstring_createEx()` — creates an instance with special characteristics (borrowed buffer, allocator flags, …);
* `cstring_createLenEx()` — as `cstring_createEx()`, from a fixed number of characters;
* `cstring_destroy()` — releases resources and resets the instance;

#### Modification functions**

* `cstring_assign()` — assigns a C-style string (may reallocate);
* `cstring_assignLen()` — assigns a fixed character count (embedded NULs allowed);
* `cstring_copy()` — copies one `cstring_t` into another;
* `cstring_append()` — appends a C-style string;
* `cstring_appendLen()` — appends a fixed character count;
* `cstring_insert()` — inserts a C-style string at an index (`CSTRING_FROM_END` supported);
* `cstring_insertLen()` — inserts a fixed character count at an index;
* `cstring_replace()` — replaces a section at an index with a C-style string;
* `cstring_replaceLen()` — replaces a section at an index with a fixed character count;
* `cstring_replaceAll()` — replaces all occurrences of one substring with another;
* `cstring_truncate()` — shortens the logical length (capacity unchanged);
* `cstring_swap()` — swaps the contents of two instances;

#### File functions**

* `cstring_readline()` — reads a line of text from the given text stream into the instance;
* `cstring_write()` — writes the string to the given text stream;
* `cstring_writeline()` — writes the string followed by a newline to the given text stream;


#### Hashing functions

Both 64-bit **djb2** (initial seed `5381`) and **FNV-1a** (offset basis `0xcbf29ce484222325ULL`, prime `0x100000001b3ULL`) hash functions are provided, returning `cstring_hash_t` (`uint64_t`). Buffer/slice variants (`_len`) allow hashing character sequences without constructing a `cstring_t` instance. Case-insensitive variants (`_ci`) fold characters to lower case, facilitating case-folded lookups and comparisons. All functions safely tolerate `NULL` pointers and zero lengths, returning the respective algorithm's initial basis / seed value:

* `cstring_hash_djb2()` — calculates a 64-bit djb2 hash of a `cstring_t` instance;
* `cstring_hash_djb2_ci()` — calculates a case-insensitive 64-bit djb2 hash of a `cstring_t` instance;
* `cstring_hash_djb2_len()` — calculates a 64-bit djb2 hash of a character buffer or slice;
* `cstring_hash_djb2_len_ci()` — calculates a case-insensitive 64-bit djb2 hash of a character buffer or slice;
* `cstring_hash_fnv1a()` — calculates a 64-bit FNV-1a hash of a `cstring_t` instance;
* `cstring_hash_fnv1a_ci()` — calculates a case-insensitive 64-bit FNV-1a hash of a `cstring_t` instance;
* `cstring_hash_fnv1a_len()` — calculates a 64-bit FNV-1a hash of a character buffer or slice;
* `cstring_hash_fnv1a_len_ci()` — calculates a case-insensitive 64-bit FNV-1a hash of a character buffer or slice;


### Vector API

Defined in **cstring/cstring.vector.h**:

* `cstring_vector_init()` — initialises a vector, optionally with a minimum capacity;
* `cstring_vector_create()` — creates a vector of a given initial size (elements default-initialised);
* `cstring_vector_destroy()` — destroys each element and frees the vector buffer;
* `cstring_vector_truncate()` — shortens the vector, destroying trailing elements;
* `cstring_vector_insertAt()` — inserts one or more `cstring_t` instances at a position;
* `cstring_vector_append()` / `cstring_vector_prepend()` — macros over `cstring_vector_insertAt()`;
* `cstring_vector_readLines()` — reads lines from a stream into the vector;


### C++ Integration

When included in C++ compilation units, **cstring/cstring.h** provides inline access shims:
* **String access shims** — `c_str_data()`, `c_str_len()`, and `c_str_ptr()`, allowing `cstring_t` instances to be used directly with **STLSoft** and generic C++ templates;
* **Hash access shims** — `hash_djb2()`, `hash_djb2_ci()`, `hash_fnv1a()`, and `hash_fnv1a_ci()`, overloaded for `struct cstring_t const&`, `struct cstring_t const*`, and slice / buffer forms `(cstring_char_t const* s, size_t cch)`;


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

