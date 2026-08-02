# **cstring** Changes <!-- omit in toc -->


## 4.0.13 - 2nd August 2026

* Modular GitHub Actions CI (**ci.yml** + **ci-cell.yml**), with install-smoke and MinGW cells;
* Retained `--no-cpp` CI job; retired **cmake-multi-platform.yml**;
* README CI badge now targets **ci.yml**;
* Replaced leftover `cstring_error()` calls with `cstring_getStatusCodeString()` in **test.unit.cstring.1** and **test.unit.cstring.2**;
* Suppressed MinGW `-Wcast-function-type` on `GetProcAddress` cast in **cstring.core.c**;
* Fixed MinGW `size_t` printf format in **test.scratch.cstring_create**;
* Added **prepare_cmake.sh** `--no-cpp` / CMake `NO_CSTRING_CPP_API`;
* CI job for `--no-cpp` builds and unit-tests;
* Converted unit-tests **test.unit.cstring.2**, **test.unit.cstring.auto_buffer**, and **test.unit.cstring.cstring_getStatusCodeString** from C++ to C (so they build under `NO_CSTRING_CPP_API`);
* Clarified dependencies documentation in **README.md**;


## 4.0.12 - 2nd September 2025

* GitHub Actions;
* CTest;
* CMake helper scripts now define default make command as `"mingw32-make.exe"` if recognise MinGW;
* Documentation;
* `*.sh`: moved info-lines into **./.sis/script_info_lines.txt**;
* Added **libver** scratch test;
* **.gitattributes**;


## 4.0.11 - 23rd February 2025

* Boilerplate;
* Simplification of dependencies;


## 4.0.10 - 25th October 2024

* Substantial CMake improvements;
* MinGW compatibility;


## 4.0.9 - 28th January 2024

* Improved CMake support;
* CMake language standards now C-11 and C++14;
* Fixed typo defect in definition of `CSTRING_F_USE_WINDOWS_PROCESSHEAP_MEMORY`;
* Added project boilerplate files: **AUTHORS.md**, **CHANGES.txt**, **FAQ.md**, **HISTORY.md**, **NEWS.md**;


## 4.0.8 - 12th January 2024

* Added **cstring.vector** API;
* Added API function `cstring_write()`;
* Wide string support (indicated via `CSTRING_USE_WIDE_STRINGS`);
* Partial CMake support;
* Added result code `CSTRING_RC_REQUESTTOOLARGE`;
* Added component test **test.component.cstring_writeline**;
* Added scratch test **test.scratch.cstring_vector**;
* Added unit test **test.unit.cstring.cstring_vector**;


## 3.6.2 - 20th February 2012

* Added `CSTRING_RC_SYSTEMSPECIFICFAILURE`;
* All makefiles now build `cstring.3.core*.(lib|a)` rather than `cstring.3*.(lib|a)`: this was erroneously omitted from the 3.6.1 release;


## 3.6.1 - 24th January 2012

* Added `CSTRING_F_MEMORY_CAN_GROW_TO_HEAP` flag, which allows a borrowed buffer to grow (into the heap);
* Renamed output library to `cstring.core.*` (in preparation for coming 4.x expansions);
* Added string access shims for `CSTRING_RC`;
* Added `cstring_getStatusCodeStringLength()`;
* Renamed `cstring_error()` ⇒ `cstring_getStatusCodeString()`;
* Added VC10 solution and project files;
* Added VC9 solution and project files;
* Added **test.unit.cstring.auto_buffer**;
* Added **test.unit.cstring.cstring_getStatusCodeString**;
* Added **test.scratch.auto_buffer**;
* Full Win64 compatibility;
* Fixed up minor documentation mistakes;


## 3.5.4 - 22nd January 2012

* Win64-compatibility;
* Added **test.scratch.HGLOBAL_on_x64** project;
* VC++ 10 compatibility;


## 3.5.3 - 11th January 2010

* Trivial formatting changes;


## 3.5.2 - 11th July 2009

* Fixed implicit link defects;
* Completed Win64 compatibility;
* Minor adjustments to compiler warnings;


## 3.5.1 - 10th July 2009

* Added new API functions for cstring I/O, replacing and inserting substrings, and initialisation;
* Added compatibility with Borland C/C++ 5.8.2, 5.9 and 6.1, Intel C/C++ 9–11, and GCC 4.1–4.4;
* Added three unit/component test programs;


## 3.4.4 - 4th May 2008

* Additional error codes in API;
* Compatible with Win64;
* Compatible with Safe String library;


## 3.4.3 - 26th January 2007

* Distribution now roots under `cstring-X.Y`, e.g. `cstring-3.4.3`;


## 3.4.2 - 30th April 2006

* Only minor edits, and little fixes;


## 3.4.1 - 7th October 2005

* Makefiles now build libraries whose names include the major version number, e.g. **cstring.3.vc6.lib**, in addition to the unversioned form, e.g. **cstring.vc6.lib**;
* Type `cstring_flags_t` is defined to disambiguate flags params from size params (which use `size_t`);
* Added `CSTRING_RC_CANNOTYIELDFROMSO` return code, used when trying to yield a string from a dynamic library implementation that has been allocated using `realloc()`;
* `cstring_yield()` has been deprecated in favour of `cstring_yield2()`; define `CSTRING_OBSOLETE` for the old behaviour;


## 3.3.1 - 8th August 2005

* Changed the memory allocation algorithm such that each reallocation is at least twice the size of the extant block;
* Now dynamically loads the `CoTaskMemRealloc()` function from **OLE32.DLL**, easing the linking burden when working with a variety of compilers;


## 3.2.1 - 29th July 2005

* Initial public release of this formerly proprietary library from Synesis Software;
* Plain-C library, platform/compiler independent;
* When compiled under Win32, provides facility to use Win32 **Global**, **Process Heap** and **COM Task Allocator** memory, rather than the default C library `realloc()`;


<!-- ########################### end of file ########################### -->
