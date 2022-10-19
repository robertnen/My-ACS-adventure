#include <stdio.h>

int main() {

    int a, b, c, d, minim, maxim;

    scanf("%d%d%d%d", &a, &b, &c, &d);

    minim = maxim = a;

    if(minim > b) minim = b;
    if(minim > c) minim = c;
    if(minim > d) minim = d;

    if(maxim < b) maxim = b;
    if(maxim < c) maxim = c;
    if(maxim < d) maxim = d;

    printf("Minim: %d.\nMaxim: %d.\n", minim, maxim);

    return 0;
}