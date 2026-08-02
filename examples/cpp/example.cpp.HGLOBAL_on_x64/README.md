# example.cpp.HGLOBAL_on_x64 <!-- omit in toc -->


## Purpose

Windows-only C++ example that allocates a `cstring_t` with `CSTRING_F_USE_WIN32_GLOBAL_MEMORY` (process `HGLOBAL` heap) and appends several fragments.


## Build

Built when `BUILD_EXAMPLES` is enabled, `NO_CSTRING_CPP_API` is off, and the target is Windows.


## Run

```sh
${SIS_CMAKE_BUILD_DIR:-./_build}/examples/cpp/example.cpp.HGLOBAL_on_x64/example.cpp.HGLOBAL_on_x64
```


## Expected output

None (exit status 0 on success). The example exercises allocation/append/destroy without printing.


<!-- ########################### end of file ########################### -->
