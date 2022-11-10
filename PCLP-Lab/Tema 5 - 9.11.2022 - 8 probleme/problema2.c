#include <stdio.h>

//returneaza 1 daca am gasit cifra c in n sau 0 daca nu
int cifra(int n, int c);

int main() {

    int n, c;

    //citire
    scanf("%d%d", &n, &c);

    //afisare
    if(cifra(n, c)) printf("DA");
    else printf("NU");

    return 0;

}

int cifra(int n, int c) {

    //verific cazul n = 0
    if(n == 0 && c == 0) return 1;

    //caut daca apare cifra
    while(n) {

        if(n % 10 == c) return 1;
        
        n /= 10;

    }

    //nu am gasit cifra
    return 0;

}