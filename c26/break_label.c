// adapted from https://thephd.dev/c2y-hitting-the-ground-running

int main (void) {
foo:
    switch (1) {
    case 1:
        for (;;)
            break foo;
        return 1;
    }
	return 0;
}
