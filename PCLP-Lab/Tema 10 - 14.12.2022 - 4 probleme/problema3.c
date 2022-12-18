#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct MATERIA {

    char nume[15];
    int ore_curs;
    enum {C = 'C', S = 'S', A = 'A'} tip_examen;

} materie;

void citire_MAT(materie* mat);
void citire_PROGRAMA(materie programa[]);
void afisare(materie programa[]);

int main() {

    materie PROGRAMA[MAX];

    citire_PROGRAMA(PROGRAMA);
    afisare(PROGRAMA);

    return 0;
}

void citire_MAT(materie* mat) {

    printf("Nume materie: ");
    fgets(mat->nume, 16, stdin);

    mat->nume[strlen(mat->nume) - 1] = '\0'; // nume

    char aux[15];

    mat->ore_curs = -1;

    printf("Numar de ore: ");
    while(mat->ore_curs < 0) {

        fgets(aux, 16, stdin);

        aux[strlen(aux) - 1] = '\0';

        mat->ore_curs = atoi(aux);
    
    } // ore  

    printf("Tip de examen: ");
    fgets(aux, 2, stdin);

    if(aux[0] == 'A') mat->tip_examen = A;
    else if(aux[0] == 'S') mat->tip_examen = S;
        else mat->tip_examen = C; //examen

}

void citire_PROGRAMA(materie programa[]) {

    for(int i = 0; i < 4; i++) { //am pus 4, dar poate fi modificat

        printf("Programa %d:\n", i + 1);

        if(i) fgets(programa[i].nume, 15, stdin); //e gol

        citire_MAT(&programa[i]);

    }
}

void afisare(materie programa[]) {

    for(int i = 0; i < 4; i++)
        printf("Programa: %d\nMaterie: %s\nNumar de ore: %d\nTip de examen: %c\n", i + 1, programa[i].nume, programa[i].ore_curs, programa[i].tip_examen);
}