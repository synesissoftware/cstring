# cstring - Installation and Use <!-- omit in toc -->

**cstring** is a classic-form C library, insofar as it has implementation
files in its **src** directory and header files in its **include/cstring**
directory. Thus, once "installed", one must simply include
**cstring/cstring.h** (and, where needed, **cstring/cstring.vector.h**), and
compile-in or link-in the implementation.

The **C** API has no non-standard dependencies. Building the project's tests
additionally requires **STLSoft** and **xTests** (and optionally recognises
**shwild**). C++ examples and remaining C++ tests may be omitted with
`--no-cpp` / `NO_CSTRING_CPP_API`; the **C** unit-tests still require
**STLSoft** and **xTests** unless testing is disabled.


## Table of Contents <!-- omit in toc -->

- [CMake](#cmake)
- [Bundled](#bundled)


## CMake

The primary choice for installation is by use of **CMake**.

1. Obtain the latest distribution of **cstring**, from
   https://github.com/synesissoftware/cstring/, e.g.

   ```bash
   $ mkdir -p ~/open-source
   $ cd ~/open-source
   $ git clone https://github.com/synesissoftware/cstring/
   ```

2. Prepare the CMake configuration, via the **prepare_cmake.sh** script.

   For a minimal library install (no **STLSoft** / **xTests** required):

   ```bash
   $ cd ~/open-source/cstring
   $ ./prepare_cmake.sh --no-cpp --disable-testing -v
   ```

   For a full build including examples and tests, install **STLSoft** 1.11
   (and **xTests** for tests) via their own **CMake** scripts first, then:

   ```bash
   $ cd ~/open-source/cstring
   $ ./prepare_cmake.sh -v
   ```

   Useful optional flags:

   * `--no-cpp` / `-C` — omit C++ examples and remaining C++ tests
     (`NO_CSTRING_CPP_API`);
   * `--no-shwild` — do not recognise **shwild** (`NO_SHWILD`);
   * `--disable-examples` / `-E` — omit examples (`BUILD_EXAMPLES=OFF`);
   * `--disable-testing` / `-T` — omit tests (`BUILD_TESTING=OFF`);
   * `--stlsoft-root-dir` / `-s` — pass an **STLSoft** source-tree root when
     it is not available as an installed **CMake** package;

   (**Hint**: execute `$ ./prepare_cmake.sh --help` for more information.)

3. Run a build of the generated **CMake**-derived build files via the
   **build_cmake.sh** script, as in:

   ```bash
   $ ./build_cmake.sh
   ```

   (**NOTE**: if you provide the flag `--run-make` (=== `-m`) in step 2 then
   you do not need this step.)

4. As a check (when testing was not disabled), execute the built unit-test
   programs via **run_all_unit_tests.sh**, as in:

   ```bash
   $ ./run_all_unit_tests.sh
   ```

   Examples (when enabled) may be exercised via **run_all_examples.sh**.

5. Install the library on the host, via `cmake`, as in:

   ```bash
   $ sudo cmake --install ${SIS_CMAKE_BUILD_DIR:-./_build} --config Release
   ```

6. Then to use the library, it is a simple matter as follows:

   1. Assuming a simplest possible program to verify the installation:

      ```c
      /* main.c */
      #include <cstring/cstring.h>

      #include <stdio.h>
      #include <stdlib.h>

      int main(void)
      {
          cstring_t cs;
          CSTRING_RC rc = cstring_create(&cs, "Hello");

          if (CSTRING_RC_SUCCESS != rc)
          {
              fprintf(stderr, "cstring_create: %s\n", cstring_getStatusCodeString(rc));

              return EXIT_FAILURE;
          }

          printf("len=%zu contents='%s'\n", cs.len, cs.ptr);

          cstring_destroy(&cs);

          return EXIT_SUCCESS;
      }
      ```

   2. Compile your project against **cstring**:

      Due to the installation step (step 5 above) there is no requirement
      for an explicit include directory for **cstring**:

      ```bash
      $ cc -c main.c
      ```

   3. Link your project against **cstring**:

      Due to the installation step (step 5 above) there is no requirement
      for an explicit library directory for **cstring**:

      ```bash
      $ cc main.o -lcstring
      ```

   4. Test your project:

      ```bash
      $ ./a.out
      len=5 contents='Hello'
      $
      ```

   Consumers that use **CMake** may instead depend on the installed package:

   ```cmake
   find_package(cstring REQUIRED)
   target_link_libraries(your_target PRIVATE cstring::core)
   ```


## Bundled

**cstring** is small enough that it is commonly bundled into other projects.
In that case:

* add **cstring**'s **include** directory to your project's include path;
* compile **src/cstring.core.c** and **src/cstring.vector.c** into your build
  (or link a previously built **libcstring**); and
* `#include <cstring/cstring.h>` (and **cstring/cstring.vector.h** where
  needed).


<!-- ########################### end of file ########################### -->
