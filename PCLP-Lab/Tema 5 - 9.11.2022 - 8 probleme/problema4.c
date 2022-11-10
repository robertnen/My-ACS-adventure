#include <stdio.h>

//gasesc cel mai mic multiplu comun a doua numere
int cmmmc(int a, int b);

int main() {

    int x1, x2, y1, y2;

    //citirea a patru numere
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

    //tin minte cmmmc-ul
    int y = cmmmc(y1, y2);

    //inmultesc numaratorii cu ce voi amplifica fractia
    x1 = x1 * y / y1;
    x2 = x2 * y / y2;


    //afisarea
    printf("%d %d\n%d %d\n", x1, y, x2, y);

    return 0;

}

int cmmmc(int a, int b) {

    //folosesc formula a * b = [a, b] * (a, b)
    int product = a * b;

    //in memoriam Euclidis
    while(a != b) {

        if(a > b) a -= b;
        else b -= a;

    }

    return product / a;

}
