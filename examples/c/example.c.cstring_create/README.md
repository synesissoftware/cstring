# example.c.cstring_create <!-- omit in toc -->


## Purpose

Minimal illustration of `cstring_create()` and `cstring_destroy()`, printing the resulting length, capacity, and contents.


## Build

Built when `BUILD_EXAMPLES` is enabled (the default).


## Run

```sh
${SIS_CMAKE_BUILD_DIR:-./_build}/examples/c/example.c.cstring_create/example.c.cstring_create
```


## Expected output

```
successfully created string with length 9 capacity 16 and contents 'String-#1'
```

Capacity may vary by allocator / growth policy; length and contents should match.


<!-- ########################### end of file ########################### -->
