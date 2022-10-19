/*
Se dau a, b, c numere reale care reprezinta lungimile laturilor unui triunghi.
Sa se verifice natura triunghiului... (2 nr reale sunt considerate egale daca
diferenta lor in modul e < 1e-4).
*/

#include <stdio.h>

//numele spune tot...
void swap(double*, double*);

int main() {

    //semafoare
    short isDreptunghic, isIsoscel;

    double a, b, c;

    scanf("%lf%lf%lf", &a, &b, &c);

    //afisare v.1
    if(a == b && b == c) printf("echilateral");
    else {

        //le ordonez crescator
        if(a > b) swap(&a, &b);
        if(a > c) swap(&a, &c);
        if(b > c) swap(&c, &b);

        double diff = a * a + b * b - c * c;

        if(diff < 0) diff *= -1;

        isDreptunghic = (diff < 0.001) ? 1 : 0;

        if(a == b || b == c || c == a) isIsoscel = 1;
        else isIsoscel = 0;


        //afisarea v.2
        if(isDreptunghic && isIsoscel) printf("dreptunghic isoscel\n");
        else if(isDreptunghic) printf("dreptunghic\n");
             else if(isIsoscel) printf("isoscel\n");
                  else printf("oarecare\n");

    }

    return 0;
}

void swap(double* x, double* y) {

    double aux;

    aux = (*x);
    (*x) = (*y);
    (*y) = aux;

}