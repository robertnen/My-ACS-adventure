#include <stdio.h>

int cifra(int n, int c);

int main() {

    int n, c;

    scanf("%d%d", &n, &c);

    if(cifra(n, c)) printf("DA");
    else printf("NU");

    return 0;

}

int cifra(int n, int c) {

    if(n == 0 && c == 0) return 1;

    while(n) {

        if(n % 10 == c) return 1;
        
        n /= 10;

    }

    return 0;

}