// C11 static assert

#include <assert.h>

int main(void) {

  static_assert(sizeof(long) == 4, "long is not 4 bytes on this platform");

  return 0;
}
