#include <stdlib.h>
#include <stdio.h>

int main() {

    int n, numOfPos, numOfNeg;

    numOfNeg = numOfPos = 0;

    scanf("%d", &n);

    int* array = (int *) malloc(n * sizeof(int));

    for(int i = 0; i < n; i++) {

        scanf("%d", array + i);
        array[i] < 0 ? numOfNeg++ : numOfPos++;

    }

    free(array);

    printf("%d %d", numOfNeg, numOfPos);

    return 0;
}