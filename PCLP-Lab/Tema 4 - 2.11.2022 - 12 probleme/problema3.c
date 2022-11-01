#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main() {

    int row, col;

    scanf("%d%d", &row, &col);

    //imi e frica cand scriu * la pointeri, dar la doua deja am cosmaruri...
    int** array = malloc(row * sizeof(int*));

    for(int i = 0; i < row; i++) {

        array[i] = malloc(col * sizeof(int));

        for(int j = 0; j < col; j++)
            scanf("%d", &array[i][j]);

    } 


    //de ce se numeste "șa" ce se cere??
    int maximum, saddle;
    bool isFirstTime = true;

    //caut cel mai mare numar de pe fiecare linie si in acelasi timp minimul dintre cele mai mari numere 
    for(int i = 0; i < row; i++) {

        maximum = array[i][0];

        for(int j = 1; j < col; j++)
            if(maximum < array[i][j]) maximum = array[i][j];

        if(isFirstTime) {

            saddle = maximum; 
            isFirstTime = false;

        } else if(saddle > maximum) saddle = maximum;

    }

     free(array);

     printf("%d", saddle);

     return 0;
}