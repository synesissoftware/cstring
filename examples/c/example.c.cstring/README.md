# example.c.cstring <!-- omit in toc -->


## Purpose

Exercises common `cstring_t` operations: create (including length-bounded and Windows allocator flags where available), assign, append, truncate, copy, and swap.


## Build

Built when `BUILD_EXAMPLES` is enabled (the default).


## Run

```sh
${SIS_CMAKE_BUILD_DIR:-./_build}/examples/c/example.c.cstring/example.c.cstring
```


## Expected output

On non-Windows hosts, two scenarios are printed (default heap, then fixed/borrowed). Pointer values in copy/swap lines vary per run. Illustrative sample:

```
========================================
cstring_createLen():
  Initial contents: string-#1

  Assigning another C-style string to the instance:
  Contents: another string

  Assigning part of another C-style string to the instance:
  Contents: some more content

  Appending another C-style string to the instance:
  Contents: some more content - 

  Appending part of another C-style string to the instance:
  Contents: some more content - and another

  Appending part of another C-style string to the instance:
  Contents: some more content - and another; and a whole lot more stringy stuff to try and precipitate a reallocation, in order to check that the 3.3 change will be tested

  Appending part of another C-style string to the instance:
  Contents: some more content - and another; and a whole lot more stringy stuff to try and precipitate a reallocation, in order to check that the 3.3 change will be tested; and a last bit to try and get the remaining reallocation

  Truncating the instance to 10 characters:
  Contents: some more 

  Copying the instance:
  Contents:         0x… some more 
  Contents of copy: 0x… some more 

  Copying the instance (by C-style string):
  Contents:         0x… some more 
  Contents of copy: 0x… some more 

  Swapping with the copy:
  Contents:         0x… some more 
  Contents of copy: 0x… some more 

  Destroying the copy:

========================================
cstring_createLenEx(CSTRING_F_MEMORY_IS_FIXED | CSTRING_F_MEMORY_IS_BORROWED):
  Initial contents: string-#4
  …
    error: operation cannot procede because the current capacity would be exceeded and the cstring has fixed capacity
  …
    error: operation cannot procede because the current capacity would be exceeded and the cstring is borrowed
  …
    error: operation cannot procede because the cstring is borrowed
  …
```

On Windows, additional scenarios for process-heap and COM-task allocators are also printed.


<!-- ########################### end of file ########################### -->
