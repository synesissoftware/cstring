# example.c.cstring_vector <!-- omit in toc -->


## Purpose

Reads lines from a text stream into a `cstring_vector_t`, prints them, then sorts forward and reverse.


## Build

Built when `BUILD_EXAMPLES` is enabled (the default).


## Run

Requires an input source:

```sh
${SIS_CMAKE_BUILD_DIR:-./_build}/examples/c/example.c.cstring_vector/example.c.cstring_vector path/to/file.txt
${SIS_CMAKE_BUILD_DIR:-./_build}/examples/c/example.c.cstring_vector/example.c.cstring_vector --   # stdin
printf 'beta\nalpha\ngamma\n' | ${SIS_CMAKE_BUILD_DIR:-./_build}/examples/c/example.c.cstring_vector/example.c.cstring_vector --
```


## Expected output

For the `printf 'beta\nalpha\ngamma\n' | … --` invocation above:

```
#lines:	3
line-0: beta
line-1: alpha
line-2: gamma

#sorted-lines (forward):	3
line-0: alpha
line-1: beta
line-2: gamma

#sorted-lines (reverse):	3
line-0: gamma
line-1: beta
line-2: alpha
```


<!-- ########################### end of file ########################### -->
