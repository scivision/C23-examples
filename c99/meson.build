if cc.compiles('int main(void){ int* restrict a; return 0; }', name : 'c99 restrict')
  executable('restrict', 'restrict.c')
endif

if cc.compiles('int main(void){ int* restrict a; return 0; }', name : 'c99 designated')
  executable('designated', 'designated.c')
endif
