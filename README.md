# cstring
C-style strings


# cstring
**C**-style **string**s is a small, standalone library, that provides extensible C-style string instances and extensible arrays of such.


## Table of Contents

- [cstring](#cstring)
- [cstring](#cstring-1)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Components](#components)
    - [API / core library](#api--core-library)
  - [Examples](#examples)
  - [Project Information](#project-information)
    - [Where to get help](#where-to-get-help)
    - [Contribution guidelines](#contribution-guidelines)
    - [Dependencies](#dependencies)
      - [Tests-only Dependencies](#tests-only-dependencies)
    - [Related projects](#related-projects)
    - [License](#license)


## Introduction

T.B.C.


## Installation

T.B.C.


## Components

### API / core library

The C API is based around the `cstring_t` structure, defined as follows:

```C
struct cstring_t
{
    size_t          len;        /*!< Number of characters.                              */
    cstring_char_t* ptr;        /*!< Pointer to the string. If capacity is 0, the value
                                     value of this member is undetermined.              */
    size_t          capacity;   /*!< Number of bytes available.                         */
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

Examples are provided in the ```examples``` directory, along with a markdown description for each.


## Project Information


### Where to get help

[GitHub Page](https://github.com/synesissoftware/cstring "GitHub Page")


### Contribution guidelines

Defecesynesissoftware/cstring.


### Dependencies


#### Tests-only Dependencies

For unit-testing, **cstring** depends on:

* [**STLSoft 1.10**](http://github.com/synesissoftware/STLSoft-1.10/);
* [**xTests**](http://github.com/synesissoftware/xTests/);


### Related projects

Projects in which **cstring** is used include:

* [**shwild.fnmatch**](https://github.com/synesissoftware/shwild.fnmatch)


### License

**cstring** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->

