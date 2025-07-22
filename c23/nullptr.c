// https://en.cppreference.com/w/c/language/nullptr

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void g([[maybe_unused]] int* arg)
{
    puts("Function g called");
}

#define DETECT_NULL_POINTER_CONSTANT(e) \
    _Generic(e,                         \
        void* : puts("void*"),          \
        nullptr_t : puts("nullptr_t"),  \
        default : puts("integer")       \
    )

int main(void)
{
    g(nullptr);        // Fine
    g(NULL);           // Fine
    g(0);              // Fine

    puts("----------------");

    nullptr_t cloned_nullptr = nullptr;
    nullptr_t cloned_NULL   = NULL;
    nullptr_t cloned_zero   = 0;
    g(cloned_nullptr); // Fine
//  g(cloned_NULL);    // ERROR
//  g(cloned_zero);    // ERROR

    puts("----------------");

    DETECT_NULL_POINTER_CONSTANT(((void*)0));
    DETECT_NULL_POINTER_CONSTANT(0);
    DETECT_NULL_POINTER_CONSTANT(nullptr);
    DETECT_NULL_POINTER_CONSTANT(NULL); // implementation-defined

    return EXIT_SUCCESS;
}
