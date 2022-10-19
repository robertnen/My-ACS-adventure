#include <stdio.h>
#include <math.h>

int main() {

    short isDreptunghic, isIsoscel;

    double a, b, c;

    scanf("%lf%lf%lf", &a, &b, &c);

    if(a == b && b == c) printf("echilateral");
    else {

        double aux;

        if(a > b) {aux = a; a = b; b = aux;}
        if(a > c) {aux = a; a = c; a = aux;}
        if(b > c) {aux = b; b = c; c = aux;}

        double diff = a * a + b * b - c * c;

        if(diff < 0) diff *= -1;

        isDreptunghic = (diff < 0.001) ? 1 : 0;

        if(a == b || b == c || c == a) isIsoscel = 1;
        else isIsoscel = 0;

        if(isDreptunghic && isIsoscel) printf("dreptunghic isoscel\n");
        else if(isDreptunghic) printf("dreptunghic\n");
             else if(isIsoscel) printf("isoscel\n");
                  else printf("oarecare\n");

    }

    return 0;
}