#if __has_c_attribute(nodiscard)
#  define NODISCARD [[nodiscard]]
#else
#  define NODISCARD
#endif

NODISCARD int addone(int x) {
    return x + 1;
}

int main(void) {
    return addone(-1);
}
