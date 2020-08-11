# --- static assert
if cc.compiles('''
#include <assert.h>
int main(void) { static_assert(0==0, ""); return 0; }
''', name : 'c11 static assert')

  sa_src = is_windows ? 'static_assert_windows.c' : 'static_assert.c'

  executable('static_assert', sa_src)
endif
# --- Generic
if cc.compiles('''
#define cbrt(X) _Generic((X), \
default: cbrt,  \
  float: cbrtf  \
)(X)

int main(void) { return 0; }
''', name: 'c11 generic')

  executable('generic', 'generic.c')

endif
# --- variable length array
if cc.compiles('int main(void){for (int i = 1; i < 5; i++){int a[i];} return 0;}', name: 'c11 vla')
  vla = executable('vla', 'vla.c')
  test('c11vla', vla, args: ['3'])
endif
