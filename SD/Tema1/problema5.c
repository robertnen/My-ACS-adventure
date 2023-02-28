#include <stdio.h>

long int power(int base, int exp);

int main() {
    printf("%d", power(5, 2));
    return 0;
}

long int power(int base, int exp) {
    if(!base && exp) return 0;
    if(exp == 1) return base;
    if(base == 1 || !exp) return 1;
    long int aux = power(base, exp / 2);
    return (exp % 2 ? aux * aux * base: aux * aux);
}