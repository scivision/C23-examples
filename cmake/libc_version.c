// print compile-time and runtime standard C library version

// macOS: Homebrew does not use glibc but uses Apple's own libc.
//   thus __GLIBC__ is not defined for macOS Homebrew GCC.
// AppleClang defines __apple_build_version__, but Homebrew GCC does not.

#include <stdio.h>

#if defined(__GLIBC__)
#include <features.h>
#include <gnu/libc-version.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <AvailabilityMacros.h>
#endif


int main(void){

#if defined(__GLIBC__)
printf("GNU %s %d.%d\n", gnu_get_libc_version(), __GLIBC__, __GLIBC_MINOR__);
#elif defined(__APPLE__) && defined(__MACH__)
#  if defined(__apple_build_version__)
printf("Apple XCode %d", __apple_build_version__);
#  endif
#  if defined(__MAC_OS_X_VERSION_MAX_ALLOWED)
printf(" macOS maximum allowed: %d\n",__MAC_OS_X_VERSION_MAX_ALLOWED);
#  endif
#elif defined(_MSC_VER)
printf("Microsoft %d\n", _MSC_VER);
#endif

return 0;
}
