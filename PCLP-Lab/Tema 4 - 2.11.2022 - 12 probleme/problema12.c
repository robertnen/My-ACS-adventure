#include <stdlib.h>
#include <stdio.h>
#include "myheader.h"

//operatia de adunare a elementelor intre B si E cu V
void addVector(int** vector, int valueToAdd, int iPos, int fPos);

int main() {

    int n, m, iPos, fPos, toAdd;

    scanf("%d%d", &n, &m);

    int* vector = (int*) malloc(n * sizeof(int));

    //toate elementele din vector au valoarea 0
    nullVector(&vector, n);

    for(int i = 0; i < m; i++) {

        scanf("%d%d%d", &iPos, &fPos, &toAdd);

        addVector(&vector, toAdd, iPos, fPos);

    }

    //afisez rezultatul
    showVector(vector, 0, n - 1);

    return 0;

}

void addVector(int** vector, int valueToAdd, int iPos, int fPos) {

    for(int i = iPos; i <= fPos; i++)
        (*vector)[i] += valueToAdd;

}