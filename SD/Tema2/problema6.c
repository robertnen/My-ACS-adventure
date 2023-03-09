#include <stdio.h>

int numOfDigits(int n);
int powOfTen(int n);
int max(int a, int b);

long int product(long int a, long int b) {
    // if(!a || !b) return 0;
    // if(a == 1) return b;
    // if(b == 1) return a;
    if(a < 10 || b < 10) return a * b;
    int na = numOfDigits(a), nb = numOfDigits(b), n = max(na, nb);
    int a1 = a / powOfTen(na / 2), a2 = a % powOfTen(na / 2);
    int b1 = b / powOfTen(nb / 2), b2 = b % powOfTen(nb / 2);
    int p, q, r;
    p = product(a1, b1);
    q = product(a2, b2);
    r = product(a1 + a2, b1 + b2);
    return product(powOfTen(n), p) + product(powOfTen(n / 2), r - p - q) + q;
}

int main() {
    printf("%d\n", product(20, 30));
    return 0;
}
int max(int a, int b) {
    return (a > b ? a : b);
}

int numOfDigits(int n) {
    if(n < 10) return 1;
    if(n < 100) return 2;
    if(n < 1000) return 3;
    if(n < 10000) return 4;
    if(n < 100000) return 5;
    if(n < 1000000) return 6;
    if(n < 10000000) return 7;
    if(n < 100000000) return 8;
    if(n < 1000000000) return 9;
}

int powOfTen(int n) {
    switch (n) {
    case 0:
        return 1;
    case 1:
        return 10;
    case 2:
        return 100;
    case 3:
        return 1000;
    case 4:
        return 10000;
    case 5:
        return 100000;
    case 6:
        return 1000000;
    case 7:
        return 10000000;
    case 8:
        return 100000000;
    case 9:
        return 1000000000;
    default:
        return -1;
    }
}