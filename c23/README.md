# C23 examples

## strndup

Observed: [strndup](https://en.cppreference.com/w/c/experimental/dynamic/strndup) is present in:
* Linux: GCC, Clang, oneAPI, NVIDIA HPC (nvc), AMD AOCC (clang)

strndup is NOT present in:
* Windows MinGW GCC 12.2, oneAPI 2023.0

## nullptr

The ambiguous NULL macro is often better replaced by nullptr when C23 is available.
