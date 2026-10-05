# cstring - TODO <!-- omit in toc -->


## Table of Contents <!-- omit in toc -->

- [Functional improvements](#functional-improvements)
- [Performance improvements](#performance-improvements)
- [Packaging improvements](#packaging-improvements)


## Functional improvements

* [x] ~~~Examples: moved scratch programs into **examples/** with per-example **README.md**~~~ - ✅;
* [x] ~~~Scratch **libver** retained under **test/scratch**~~~ - ✅;
* [x] ~~~Delete Visual Studio 98 files~~~ - ✅;
* [x] ~~~Delete Visual Studio 2003+ files~~~ - ✅;
* [x] ~~~discriminate on `_WIN32` in implementation (and maybe also in API)~~~ - ✅;
* [x] ~~~check `CSTRING_USE_WINAPI_`~~~;
* [ ] custom arena(s);
* [ ] `cstring_vector_readlineEx()` that takes a flag to prevent truncate, thereby allowing client code to add to an existing string;
* [ ] when go to 5.x, change the name of `cstring_vector_readLines()` to `cstring_vector_readlines()`;
* [ ] when go to 5.x, consider use of SSO;
* [ ] when go to 5.x, consider expanding `cstring_vector_t` to allow it to own the memory of the strings it manages, such that can do a single file read and then break up into strings without allocating payload memory;


## Performance improvements

* [x] ~~~Performance testing and optimisation:~~~ - ✅:
  * [x] ~~~Quantify performance~~~ - ✅;
  * [x] ~~~Compare with other popular implementations~~~ - ✅;
* [ ] Analyse performance results and optimise hot paths;
* [ ] `cstring_readline()` to use block logic on regular files;
* [ ] `cstring_readlines()` to use block logic on regular files;


## Packaging improvements

* [x] ~~~README: badges; Components descriptions; examples table~~~ - ✅;
* [x] ~~~Boilerplate: **INSTALL.md**, **FAQ.md**, **KNOWN_ISSUES.md**, **AUTHORS.md** layout~~~ - ✅;
* [ ] CMake:
  * [x] ~~~custom definitions: `_BUILD_AS_UNIX` / `_BUILD_AS_WIN32`~~~ - ✅;
  * [x] ~~~`CMAKE_INSTALL_LIBDIR` (replaces legacy `LIB_INSTALL_DIR`)~~~ - ✅;
  * [x] ~~~**CTest**~~~ - ✅;
  * [ ] build DLL on Windows;
  * [ ] build dylib on macOS;
  * [x] ~~~`/MT` build option for Visual C++ (`--msvc-mt` / `MSVC_USE_MT`)~~~ - ✅;
  * [x] ~~~**shwild** dependency (testing only; `--no-shwild` / `NO_SHWILD`)~~~ - ✅;
* [x] ~~~Doxygen (**Doxyfile**, **doc/mainpage.md**, **generate_doxygen.sh**)~~~ - ✅;
* [x] ~~~Build scripts: remove project/copyright information and pick up from a project-specific file~~~ - ✅;
* [ ] GitHub Actions:
  * [x] ~~~macOS~~~ - ✅;
  * [x] ~~~Unix (ubuntu)~~~ - ✅;
  * [x] ~~~Windows~~~ - ✅;
  * [ ] Debug configuration;
  * [ ] Release configuration;
  * [ ] exercise CI permutations:
    * [ ] `--no-cpp`;
    * [ ] `--no-p99`;
    * [ ] `--no-shwild`;
    * [x] ~~~`--wide-strings`~~~ - ✅;
* [-] ~~~Makefiles (legacy build trees removed; CMake-only)~~~ - ❌;
* [ ] Packages:
  * [ ] vcpkg;
  * [ ] HomeBrew;
  * [ ] . . .
* [ ] Website;
* [ ] . . .


<!-- ########################### end of file ########################### -->
