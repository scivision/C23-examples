#ifdef _WIN32
  #define _LINT 4
#else
  #define _LINT 8
#endif

int main(void) {

  static_assert(sizeof(long) == _LINT, "long not expected bytes on this platform");

  return 0;
}
