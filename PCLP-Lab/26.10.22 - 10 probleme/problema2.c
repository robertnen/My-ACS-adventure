#include <stdio.h>

int main() {

    int n, m, numberCounter, lineCounter;

    scanf("%d%d", &n, &m);

    numberCounter = 1; // numar de la 1
    lineCounter   = 0; // numar fiecare linie

    while(numberCounter <= n) {

        //daca am 24 de randuri, opresc while-ul si nu intru in for
        (lineCounter == 24) ? numberCounter = n + 1 : lineCounter++;

        for(int line = 0; line < m && numberCounter <= n; line++) 
            printf("%d ", numberCounter++);

        printf("\n");
    }

    return 0;
}