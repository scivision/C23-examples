set_property(DIRECTORY PROPERTY LABELS C23)

check_source_compiles(C
"int main(void){ int i = nullptr; return 0; }"
c23nullptr)

if(c23nullptr)
  add_executable(nullptr nullptr.c)
endif()
