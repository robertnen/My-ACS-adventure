#include <stdio.h>

int prim(int n);

int main() {

    int n;

    scanf("%d", &n);

    for(int i = 1; i <= n / 2; i++)
        if(prim(i) && prim(n - i)) printf("%d + %d\n", i, n - i);

    return 0;

}

int prim(int n) {

    if(n == 0 || n % 2 == 0) return 0;

    if(n == 2) return 1;

    for(int i = 3; i * i <= n; i += 2)
        if(n % i == 0) return 0;

    return 1;
}