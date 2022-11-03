#include <stdlib.h>
#include <stdio.h>
#include "myheader.h"

int main() {

    int sizeA, sizeB, *A, *B;

    scanf("%d", &sizeA);

    readVector(&A, sizeA);

    scanf("%d", &sizeB);

    readVector(&B, sizeB);
    
    int* C = malloc((sizeA + sizeB) * sizeof(int));
    int sizeC, i, j; //le voi folosi ca un index

    sizeC = i = j = 0;

    //interclasez vectorii
    while(i < sizeA && j < sizeB) {

        if(A[i] < B[j]) C[sizeC++] = A[i++];
        else C[sizeC++] = B[j++];
        
    }

    while(i < sizeA) C[sizeC++] = A[i++];
    while(j < sizeB) C[sizeC++] = B[j++];

    free(A);
    free(B);

    showVector(C, 0, sizeC - 1);

    free(C);

    return 0;
}