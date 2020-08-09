if cc.compiles('''
#define cbrt(X) _Generic((X), \
default: cbrt,  \
  float: cbrtf  \
)(X)

int main(void) { return 0; }
''', name: 'c11 generic')

  executable('generic', 'generic.c')

endif
