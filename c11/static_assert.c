// C11 static assert

#include <assert.h>

int main(void) {

  static_assert(sizeof(long) == 8, "long is not 8 bytes on this platfrom");

  return 0;
}
