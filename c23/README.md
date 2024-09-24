# C23 examples

## strdup

 [strdup](https://en.cppreference.com/w/c/string/byte/strdup)
 is present in all the current C compilers we trid.

## strndup

Observed: [strndup](https://en.cppreference.com/w/c/string/byte/strndup) is present in:
* Linux: GCC, Clang, oneAPI, NVIDIA HPC (nvc), AMD AOCC (clang)

strndup is NOT present in:
* Windows MinGW GCC 12.2, oneAPI 2023.0, MSVC

## nullptr

The ambiguous NULL macro is often better replaced by nullptr when C23 is available.
