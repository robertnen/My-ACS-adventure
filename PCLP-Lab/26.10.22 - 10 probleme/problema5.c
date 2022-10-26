#include <stdio.h>

int main() {

    int n, a, b;

    scanf("%d", &n);

    //daca n e par, primul triunghi va fi mereu de forma (0, n / 2, n / 2)
    //daca n e impar, - ,, - de forma (0, n / 2, n / 2 - 1)
    a = n / 2;
    
    b = (n % 2) ? n / 2 + 1 : n / 2;

    for(int i = 0; i <= n / 3; i++) {

        printf("%d %d %d\n", i, a, b);

        //din cauza ca e triunghi si ca se afiseaza ordonat, nu se pot afisa 3 triplete cu acelasi i
        if(b > a + 1) { 

            b--; a++;
            printf("%d %d %d\n", i, a, b);

        } else a--;
    }

    return 0;
}

