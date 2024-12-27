#if !__has_c_attribute(nodiscard)
#error "missing [[nodiscard]]"
#endif

[[nodiscard]]
int addone(int x) {
    return x + 1;
}

int main(void) {
    return addone(-1);
}
