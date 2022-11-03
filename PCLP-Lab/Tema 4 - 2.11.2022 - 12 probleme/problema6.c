#include <stdlib.h>
#include <stdio.h>
#include "myheader.h"

//scoate elementele de sub diagonala secundara prin criteriul cerut
// matrix[n - j][i], unde i = 1 -> (n - 1) si j = i -> 1
void underDiagonalElements(int** matrix, int size);

int main() {

    int size, **matrix;

    scanf("%d", size);

    readMatrix(&matrix, size, size);

    underDiagonalElements(matrix, size);
    
    freeMatrix(&matrix, size);

    return 0;
}

void underDiagonalElements(int** matrix, int size) {

    for(int i = 1; i < size; i++) 
        for(int j = i; j > 0; j--)
            printf("%d ", matrix[size - j][i]);
}