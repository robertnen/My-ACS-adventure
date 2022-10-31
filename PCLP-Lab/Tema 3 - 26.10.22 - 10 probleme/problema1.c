#include <stdio.h>

int main() {

    //afisez la fiecare n / 10 pasi o linie de 10 caractere 
    for(int i = 32; i < 128; i++) 
        ((i - 32) % 10) ? printf("\t%c = %d", (char)i, i) : printf("\n%c = %d", (char)i, i);

    return 0;
}