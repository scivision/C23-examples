// https://stackoverflow.com/a/76847906

int sum(int a, int b)
[[reproducible]]
{
    return a + b;
}

int main(){
    int a = 1;
    int b = 2;

    int c = sum(a, b);
    c = sum(a+1, b);
    c = sum(a, b);

    return (c == 3) ? 0 : 1;
}
