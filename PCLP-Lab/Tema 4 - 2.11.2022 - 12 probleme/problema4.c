#include <stdlib.h>
#include <stdio.h>
#include "myheader.h"

//Calculeaza produsul dintre A si B
void matrixProductCalculator(int*** c, int** a, int** b, int rowA, int colA, int colB);

int main() {

    int rowA, rowB, colA, colB;
    int **A, **B, **C;

    readMatrix(&A, rowA, colA);
    readMatrix(&B, rowB, colB);

    if(colA != rowB) printf("imposibil\n");
    else {

        matrixProductCalculator(&C, A, B, rowA, colA, colB);
        
        showMatrix(C, rowA, colB);

    }

    freeMatrix(&A, rowA);
    freeMatrix(&B, rowB);
    freeMatrix(&C, colA);

    return 0;
}

void matrixProductCalculator(int*** c, int** a, int** b, int rowA, int colA, int colB){

    // C = A * B are rowA linii si colB coloane
    (*c) = (int**) malloc(rowA * sizeof(int*));

    for(int i = 0; i < rowA; i++) {

        (*c)[i] = (int*) malloc(colB * sizeof(int));

        //calculez elementele din C
        for(int j = 0; j < colB; j++) 
             for(int k = 0; k < colA; k++)
                (*c)[i][j] = a[i][k] * b[k][j];

    }
}
