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


## Performance improvements

* [ ] Performance testing and optimisation:
  * [ ] Quantify performance;
  * [ ] Compare with other popular implementations;


## Packaging improvements

* [x] ~~~README: badges; Components descriptions; examples table~~~ - ✅;
* [x] ~~~Boilerplate: **INSTALL.md**, **FAQ.md**, **KNOWN_ISSUES.md**, **AUTHORS.md** layout~~~ - ✅;
* [ ] CMake:
  * [x] ~~~custom definitions: `_BUILD_AS_UNIX` / `_BUILD_AS_WIN32`~~~ - ✅;
  * [x] ~~~`CMAKE_INSTALL_LIBDIR` (replaces legacy `LIB_INSTALL_DIR`)~~~ - ✅;
  * [x] ~~~**CTest**~~~ - ✅;
  * [ ] build DLL on Windows;
  * [x] ~~~`/MT` build option for Visual C++ (`--msvc-mt` / `MSVC_USE_MT`)~~~ - ✅;
  * [x] ~~~**shwild** dependency (testing only; `--no-shwild` / `NO_SHWILD`)~~~ - ✅;
* [x] ~~~Doxygen (**Doxyfile**, **doc/mainpage.md**, **generate_doxygen.sh**)~~~ - ✅;
* [x] ~~~Build scripts: remove project/copyright information and pick up from a project-specific file~~~ - ✅;
* [ ] GitHub Actions:
  * [x] ~~~macOS~~~ - ✅;
  * [x] ~~~Unix (ubuntu)~~~ - ✅;
  * [x] ~~~Windows~~~ - ✅;
  * [x] ~~~Linux TinyCC (**tcc**) cell + install-smoke~~~ - ✅;
  * [ ] Debug configuration;
  * [ ] Release configuration;
  * [ ] exercise `--no-cpp` / `--no-shwild` permutations beyond the current jobs;
* [-] ~~~Makefiles (legacy build trees removed; CMake-only)~~~ - ❌;
* [ ] Packages:
  * [ ] vcpkg;
  * [ ] HomeBrew;
  * [ ] . . .
* [ ] Website;
* [ ] . . .


<!-- ########################### end of file ########################### -->
