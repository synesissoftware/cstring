# example.cpp.cstring.dynload <!-- omit in toc -->


## Purpose

Windows-only C++ example that loads the **cstring** shared library at runtime (`LoadLibrary` / `GetProcAddress`) and calls selected API entry points.


## Build

Built when `BUILD_EXAMPLES` is enabled, `NO_CSTRING_CPP_API` is off, and the target is Windows.


## Run

```sh
${SIS_CMAKE_BUILD_DIR:-./_build}/examples/cpp/example.cpp.cstring.dynload/example.cpp.cstring.dynload
```

Expects a suitable **cstring** DLL (for example `cstring.3.debug.dll`) to be loadable on the process search path.


## Expected output

Depends on whether the DLL loads and which entry points resolve. On a successful path you may see lines such as:

```
caught expected exception: …
string=Hello
```

If the DLL is missing, the program typically exits quietly with status 0 after a failed `LoadLibrary` / null proc check. Treat this example as a Windows integration sketch rather than a fixed golden-output demo.


<!-- ########################### end of file ########################### -->
