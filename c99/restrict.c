// https://en.cppreference.com/w/c/language/restrict

float x[100];
float *c;
void f(int n, float * restrict a, float * const b) {
    int i;
    for ( i=0; i<n; i++ )
       a[i] = b[i] + c[i];
}
void g3(void) {
    float d[100], e[100];
    c = x; f(100,   d,    e); // OK
           f( 50,   d, d+50); // OK
           f( 99, d+1,    d); // undefined behavior
    c = d; f( 99, d+1,    e); // undefined behavior
           f( 99,   e,  d+1); // OK
}

int main(void){ return 0; }
