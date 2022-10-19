//afisarea a 3 numere reale cu %f %e si %g

#include <stdio.h>

int main() {

    float f, e, g;

    scanf("%f%e%g", &f, &e, &g);

    printf("%f %e %g", f, e, g);

    return 0;
}