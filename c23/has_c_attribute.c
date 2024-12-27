#if !__has_c_attribute(nodiscard)
#error "missing __has_c_attribute"
#endif

[[nodiscard]]
int addone(int x) {
    return x + 1;
}

int main(void) {
    return addone(-1);
}
