#include <stdlib.h>
#include <stdio.h>

//citeste o matrice si da inapoi numarul de linii si coloane
void readMatrix(int***, int* row, int* col);
//calculeaza produsul dintre A si B
void matrixProductCalculator(int***, int**, int**, int, int, int);
//afiseaza o matrice
void showMatrix(int**, int, int);

int main() {

    int rowA, rowB, colA, colB;
    int **arrA, **arrB, **arrC;

    readMatrix(&arrA, &rowA, &colA);
    readMatrix(&arrB, &rowB, &colB);

    if(colA != rowB) printf("imposibil\n");
    else {

        matrixProductCalculator(&arrC, arrA, arrB, rowA, colA, colB);
        
        showMatrix(arrC, rowA, colB);

    }

    free(arrA);
    free(arrB);
    free(arrC);

    return 0;
}

void readMatrix(int*** matrix, int* row, int* col) {

    scanf("%d%d", &(*row), &(*col));

    (*matrix) = malloc((*row) * sizeof(int*));
    
    for(int i = 0; i < (*row); i++) {

        (*matrix)[i] = malloc((*col) * sizeof(int));

        for(int j = 0; j < (*col); j++) 
            scanf("%d", &(*matrix)[i][j]);
        
    }
}

void matrixProductCalculator(int*** c, int** a, int** b, int rowA, int colA, int colB){

    // C = A * B are rowA linii si colB coloane
    *c = malloc(rowA * sizeof(int*));

    for(int i = 0; i < rowA; i++) {

        (*c)[i] = malloc(colB * sizeof(int));

        //calculez elementele din C
        for(int j = 0; j < colB; j++) 
             for(int k = 0; k < colA; k++)
                (*c)[i][j] = a[i][k] * b[k][j];

    }
}

void showMatrix(int** matrix, int row, int col) {

    for(int i = 0; i < row; i++) {

        for(int j = 0; j < col; j++)
            printf("%d ", matrix[i][j]);
        
        printf("\n");
    }
}