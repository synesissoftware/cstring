# example.c.auto_buffer <!-- omit in toc -->


## Purpose

Demonstrates creating a `cstring_t` on a fixed borrowed buffer, then appending past that capacity so the string grows onto the heap (`CSTRING_F_MEMORY_IS_BORROWED` | `CSTRING_F_MEMORY_CAN_GROW_TO_HEAP`).


## Build

Built when `BUILD_EXAMPLES` is enabled (the default).


## Run

```sh
${SIS_CMAKE_BUILD_DIR:-./_build}/examples/c/example.c.auto_buffer/example.c.auto_buffer
```


## Expected output

```
cs=<len=9, capacity=9>: 'String-#1'
cs=<len=31, capacity=32>: 'String-#1 : something very long'
```

The first line is the string still in the borrowed 10-byte buffer; the second is after `cstring_append()` forces a heap reallocation (capacity grows beyond the original buffer).


<!-- ########################### end of file ########################### -->
