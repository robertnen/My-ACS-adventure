#include <stdio.h>

//verifica daca un numar n e prim
int prim(int n);

int main() {

    int n;

    scanf("%d", &n);

    //deoarece se afiseaza sume de termeni ordonati
    //voi merge pana la n / 2 (inclusiv)
    for(int i = 1; i <= n / 2; i++)
        if(prim(i) && prim(n - i)) printf("%d + %d\n", i, n - i);

    return 0;

}

int prim(int n) {

    //cum 1 e aparent numar prim
    //verific daca n e nr par si nu mai verific daca e 1
    if(n % 2 == 0) return 0;

    //daca n e 2 am terminat
    if(n == 2) return 1;

    //verific daca e prim
    for(int i = 3; i * i <= n; i += 2)
        if(n % i == 0) return 0;

    //numarul e prim
    return 1;
}