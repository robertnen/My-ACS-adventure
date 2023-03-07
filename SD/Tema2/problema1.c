#include <stdio.h>

int f(int);

int main() {
    printf("f(4) = %d\n", f(4));
    return 0;
}

int f(int k) {
    return (k < 3 ? 1 : f(k - 1) + f(k - 2) + f(k - 3));
}