#ifndef PRODUS_H
#define PRODUS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

    typedef struct Produs {
        char nume_produs[20];
        int cantitate;
        double pret_produs;
    } produs;

    void creare_fisier(char* nume_fisier);
    void afisare_fisier(char* nume_fisier);
    void swap_strings(char s1[], char s2[]);
    void sort_fisier(char* nume_fisier);

#elif
    printf("-");
#endif