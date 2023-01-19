#include "Produs.h"

int main(int argc, char *argv[]) {

    creare_fisier("a.bin");
    afisare_fisier("a.bin");
    return 0;
}

void creare_fisier(char* nume_fisier) {
    FILE* fout = fopen(nume_fisier, "wb");
    int i, aux; char str[100]; produs p;
    for(i = 0; i < 99; i++) {
        aux = rand();
        sprintf(p.nume_produs, "Produs%d", aux);
        p.cantitate = aux % 100;
        p.pret_produs = (aux <= 100 ? aux : aux % 100);
        sprintf(str, "%s %d %lf", p.nume_produs, p.cantitate, p.pret_produs);
        fwrite(str, sizeof str[0], sizeof(str), fout);
    }
    fclose(fout);
}

void afisare_fisier(char* nume_fisier) {
    FILE* fin = fopen(nume_fisier, "rb");
    char str[100];
    while(fread(str, sizeof str[0], 100, fin) != 0) {
        puts(str);
    }
    fclose(fin);
}

void swap_strings(char s1[], char s2[]) {

    char aux[100];
    strcpy(aux, s2);
    strcpy(s2, s1);
    strcpy(s1, aux);
}

void sort_fisier(char* nume_fisier) {

    char products[100][40];
    FILE* f = fopen(nume_fisier, "r+b");
    char str[100]; int count = -1, i; bool isSorted = false;
    while(fread(str, 1, 100, f) != 0) strcpy(products[++count], str);
    while(!isSorted) {
        isSorted = true;
        for(i = 0; i < count; i++)
            if(strcmp(products[i], products[i + 1]) > 0);
    }
    fclose(f);
}