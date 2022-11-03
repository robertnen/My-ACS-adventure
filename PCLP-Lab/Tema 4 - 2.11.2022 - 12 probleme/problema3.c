#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "myheader.h"

int main() {

    int row, col;

    scanf("%d%d", &row, &col);

    int** matrix = (int**) malloc(row * sizeof(int*));

    readMatrix(&matrix, row, col);

    int maximum, saddle;
    bool isFirstTime = true;

    //caut cel mai mare numar de pe fiecare linie si in acelasi timp minimul dintre cele mai mari numere 
    for(int i = 0; i < row; i++) {

        maximum = matrix[i][0];

        for(int j = 1; j < col; j++)
            if(maximum < matrix[i][j]) maximum = matrix[i][j];

        if(isFirstTime) {

            saddle = maximum; 
            isFirstTime = false;

        } else if(saddle > maximum) saddle = maximum;

    }

     //functie care elibereaza spatiul alocat pentru o matrice
     freeMatrix(&matrix, row);

     printf("%d", saddle);

     return 0;
}