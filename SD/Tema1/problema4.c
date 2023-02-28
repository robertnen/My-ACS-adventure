#include <stdio.h>

long int factorial(int num);

int main() {
    printf("%d", factorial(5));
    return 0;
}

long int factorial(int num) {
    return (!num ? 1 : num * factorial(num - 1));
}